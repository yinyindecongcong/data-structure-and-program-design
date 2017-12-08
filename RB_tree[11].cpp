#include <iostream>
using namespace std;
//RB_tree
/*
1.all paths from root to leaves contains the same number of BlackNode, for all subtree
2.the parent of RedNode must exist and has color Black
3.we shall define that root and empty nodes as BlackNode
property: a RB_tree with n nodes has height not greater than 2lgn
*/
/*
查找：同二叉查找树
插入：插入红色叶节点，返回状态，违背上述性质（只可能为两个连续红节点的违背），但只在祖父节点（必为黑节点）进行调整，回溯即可
删除：不会
*/
//define RB_node
enum Color {black, red};
enum error_code{duplicate_error, not_present, success};
enum RB_code{okay, red_node, right_red, left_red, duplicate};
/*
各状态情况及对应处理
okay:当前根节点颜色不改变且不违背性质，结束
red_node:当前根节点黑色变为红色，可能需要调整
right_red:当前根节点和右孩子均为红节点，需要调整
left_red:当前根节点和左孩子均为红节点，需要调整
duplicate:元素已存在，错误
*/
template <class entry>
struct RB_node{
	entry data;
	Color color;
	RB_node<entry> * lchild, * rchild;
	RB_node():color(red), lchild(NULL), rchild(NULL){}
	RB_node(const entry &c):data(c), color(red), lchild(NULL), rchild(NULL){}
	Color get_color()const{ return color; }
	void set_color(Color c){ color = c; }
};
//defind RB_tree
template <class entry>
class RB_tree{
public:
	RB_tree():root(NULL){}
	~RB_tree(){}
	error_code RB_search(const entry &key){
		return au_RB_search(root, key);
	}
	error_code RB_insert(const entry &key){
		return au_RB_insert(root, key);
	}
	void RB_remove(entry &key){}
	void print(){
		in_order(root);
		cout << endl;
	}
	void print2(){
		pre_order(root);
		cout << endl;
	}
private:
	void in_order(RB_node<entry> * root){
		if (root){
			in_order(root->lchild);
			cout << root->data << '_' << (root->get_color() == black? "B ": "R ");
			in_order(root->rchild);
		}
	}
	void pre_order(RB_node<entry> * root){
		if (root){
			cout << root->data << '_' << (root->get_color() == black? "B ": "R ");
			pre_order(root->lchild);
			pre_order(root->rchild);
		}
	}
	error_code au_RB_search(RB_node<entry> * root, const entry & key){
		if (root == NULL) return not_present;
		if (root->data == key) return success;
		if (key < root->data) return au_RB_search(root->lchild, key);
		return au_RB_search(root->rchild, key);
	}
	error_code au_RB_insert(RB_node<entry> *& root, const entry & key){
 		//调用recursive_RB_insert,根据状态调整，在根节点处不再调整，设为黑即可
 		RB_code result = recursive_RB_insert(root, key);
 		if (result == duplicate) return duplicate_error;
 		else if (result == red_node) root->set_color(black);
 		return success;
	}
	RB_code recursive_RB_insert(RB_node<entry> *& root, const entry & key){
		//若已存在，返回duplicate，否则插入节点，返回节点状态
		RB_code result, child_result;
		if (root == NULL){
			root = new RB_node<entry>(key);
			result = red_node;
		}
		else if (root->data == key) result = duplicate;
		else if (key < root->data) {
			child_result = recursive_RB_insert(root->lchild, key);
			result = modify_left(root, child_result);
		}
		else {
			child_result = recursive_RB_insert(root->rchild, key);
			result = modify_right(root, child_result);
		}
		return result;
	}
	RB_code modify_left(RB_node<entry> *& root, RB_code &child_result){
		//根据返回结果调整
		RB_code result = okay;
		if (child_result == okay) return okay;
		else if (child_result == red_node){
			if (root->get_color() == red) result = left_red;
		}
		else if (child_result == left_red){
			//根据右孩子判断
			if(root->rchild == NULL || root->rchild->get_color() == black){ //右旋
				root->set_color(red);
				root->lchild->set_color(black);
				right_rotate(root);
			}
			else { //翻转颜色
				flip_color(root);
				result = red_node;
			}
		}
		else if (child_result == right_red){ //双旋
			if (root->rchild == NULL || root->rchild->get_color() == black){
				root->set_color(red);
				root->lchild->rchild->set_color(black); 
				left_rotate(root->lchild);
				right_rotate(root);
			}
			else {
				flip_color(root);
				result = red_node;
			}
		}
		return result;
	}
	RB_code modify_right(RB_node<entry> *& root, RB_code &child_result){
		//根据返回结果调整
		RB_code result = okay;
		if (child_result == red_node){ 
			if (root->get_color() == red) result = right_red;
		}
		else if (child_result == right_red){
			//根据右孩子判断
			if(root->lchild == NULL || root->lchild->get_color() == black){ //左旋
				root->set_color(red);
				root->rchild->set_color(black);
				left_rotate(root);
			}
			else { //翻转颜色
				flip_color(root);
				result = red_node;
			}
		}
		else if (child_result == left_red){  //双旋
			if (root->lchild == NULL || root->lchild->get_color() == black){
				root->set_color(red); 
				root->rchild->lchild->set_color(black);
				right_rotate(root->rchild);
				left_rotate(root);
			}
			else {
				flip_color(root);
				result = red_node;
			}
		}
		return result;
	}
	void flip_color(RB_node<entry> *& Node){
		Node->set_color(red);
		Node->lchild->set_color(black);
		Node->rchild->set_color(black);
	}
	void left_rotate(RB_node<entry> *& Node){
		RB_node<entry> * right = Node->rchild;
		Node->rchild = right->lchild;
		right->lchild = Node;
		Node = right;
	}
	void right_rotate(RB_node<entry> *& Node){
		RB_node<entry> * left = Node->lchild;
		Node->lchild = left->rchild;
		left->rchild = Node;  
		Node = left;
	}
	RB_node<entry> * root;
};
int main(int argc, char const *argv[])
{
	RB_tree<int> T;
	T.RB_insert(50);
	T.RB_insert(40);
	T.RB_insert(30);
	T.RB_insert(20);
	T.RB_insert(8);
	T.RB_insert(7);
	T.RB_insert(9);
	T.RB_insert(100);
	T.RB_insert(23);
	T.RB_insert(67);
	T.print();

	T.print2();
	return 0;
}