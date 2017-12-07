#include <iostream>
using namespace std;
//n阶B树
/*
1. 除了根以外的内点最多有n个孩子，最少有（n + 1）/2个孩子，元素数 = 孩子数 - 1
2. 所有叶子都在同一层->通过只增加根节点来维护
3. 根最多有n个孩子，若非叶节点至少有2个孩子 
*/ 
/*
递归或迭代实现查找，插入，删除
查找：类似二叉树，每个节点内部需遍历查找（可选择顺序查找或折半查找）
插入：插入叶节点并根据是否已满（overflow）回溯调整 
删除：若非叶节点则用直接前驱代替，转化为删除叶节点的情况，根据是否孩子过少回溯调整 
*/
//定义节点结构体
template <class entry, int order>
struct B_node{
	int count; //数据个数，为孩子个数 - 1
	entry data[order - 1];
	B_node<entry, order> *branch[order];
	B_node():count(0){
		for (int i = 0; i < order; i++) branch[i] = NULL;
	} 
}; 
//定义B树类
enum error_code{duplicate, not_present, success, overflow};
template <class entry, int order>
class B_tree{
public:
	B_tree():root(NULL){}
	~B_tree(){
		clear();
	}
	void clear(){
		re_clear(root);
	}
	void re_clear(B_node<entry, order> *& root){
		if (root == NULL) return;
		for (int i = 0; i < root->count + 1; i++)
			re_clear(root->branch[i]);
		delete root;
		cout << 1 << endl;
		root = NULL;
	}
	//add other constructors
	error_code search_tree(const entry& target){
		return iteration_search(root, target);
	}
	error_code insert_tree(const entry& target){
		return au_insert(root, target); 
	} 
	error_code remove_tree(entry& target){
		return au_remove(root, target);
	}
	bool empty(){ return root == 0; }
	int height(){
		int h = 0;
		B_node<entry, order> * p = root;
		while (p != NULL){
			h++;
			p = p->branch[0];
		}
		return h;
	}
	void print(){
		re_print(root);
		cout << endl;
	}
	void print2(){
		for (int i = 0; i < root->count; i++) cout << root->data[i] << ' ';
		if (root) cout << endl << root->count << endl;
		for (int i = 0; i < root->branch[0]->count; i++) cout << root->branch[0]->data[i] << ' ';
		cout << endl << root->branch[0]->count << endl;
		for (int i = 0; i < root->branch[1]->count; i++) cout << root->branch[1]->data[i] << ' ';
		cout << endl << root->branch[1]->count << endl;
	}
private:
	//auxiliary function
	error_code iteration_search(B_node<entry, order> * root, const entry& target){
		int position;  
		while(root){
			if (search_node(root, target, position) == success) return success;
			root = root->branch[position];
		}
		return not_present;
	}
	error_code search_node(B_node<entry, order> * Node, const entry& target, int & position){
		//若找到，position为对应下标，否则position为target（若存在的话）所在分支对应下标 
		position = 0;
		while(position < Node->count && target > Node->data[position])
			position++;
		if (position < Node->count && target == Node->data[position]) return success;
		return not_present;
	} 
	error_code au_insert(B_node<entry, order> *& root, const entry& target){
		//若已存在，返回duplicate；否则插入叶节点并返回success
		entry median;
		B_node<entry, order> * right_branch = NULL; //若已满分解，median为中间节点，root指向其左子树，right_branch指向其右子树 
		error_code result = recursive_insert(root, target, median, right_branch); 
		if(result == overflow){
			B_node<entry, order> * newroot = new B_node<entry, order>;
			newroot->data[0] = median;
			newroot->count++;
			newroot->branch[0] = root;
			newroot->branch[1] = right_branch;
			root = newroot;
			result = success;
		}
		return result;
	}
	error_code recursive_insert(B_node<entry, order> *& root, const entry& target, entry& median, B_node<entry, order> *& right_branch){
		//若已存在，返回duplicate；否则插入叶节点适当位置，若插入后节点数过大，返回overflow，否则返回success 
		if (root == NULL){ //若为空，不在空节点插入，故返回overflow 
			right_branch = NULL;
			median = target;
			return overflow; 
		}
		entry extra_entry;
		B_node<entry, order> * extra_branch = NULL; //作为递归调用的中间变量 
		int position;
		error_code result = search_node(root, target, position); 
		if (result == success) return duplicate;  //若找到，返回duplicate 
		else result = recursive_insert(root->branch[position], target, extra_entry, extra_branch); 
		if (result == overflow){
			if (root->count < order - 1) {
				push_in(root, position, extra_entry, extra_branch);  //往非满节点插入 
				result = success;
			}
			else split_node(root, position, extra_entry, median, extra_branch, right_branch);  //分割节点 
		} 
		return result;
	}
	void push_in(B_node<entry, order> *& Node, int position, entry & extra_entry, B_node<entry, order> *& extra_branch){
		//往非满节点Node的position位置插入extra_entry节点，且Node->branch[position]为其左子树， extra_branch为其右子树
		for (int i = Node->count; i > position; i--){
			Node->data[i] = Node->data[i - 1];
			Node->branch[i + 1] = Node->branch[i];
		} 
		Node->data[position] = extra_entry;
		Node->branch[position + 1] = extra_branch;
		//左子树不用调整
		Node->count++; 
	}
	void split_node(B_node<entry, order> *& Node, int position, entry& extra_entry, entry& median, B_node<entry, order> *&extra_branch, B_node<entry, order> *& right_branch){
		//将节点分为左右两部分，使median为左边最大元素，再从左边分出中间节点
		//pre：若有位置，extra_entry应在Node的position位置，extra_branch为其右子树 
		//pos：median为中间节点，Node为其左子树，right_branch为其右子树 
		right_branch = new B_node<entry, order>;
		int mid = order / 2;
		//根据position分两种情况
		if (position <= mid){
			for(int i = mid; i < order; i++){
				right_branch->data[i - mid] = Node->data[i];
				right_branch->branch[i - mid + 1] = Node->branch[i + 1];
			}
			Node->count = mid;
			right_branch->count = order - 1 - mid;
			push_in(Node, position, extra_entry, extra_branch); 
		} 
		else {
			mid++;
			for (int i = mid; i < order; i++){
				right_branch->data[i - mid] = Node->data[i];
				right_branch->branch[i - mid + 1] = Node->branch[i + 1];
			}
			Node->count = mid;
			right_branch->count = order - 1 - mid;
			push_in(right_branch, position - mid, extra_entry, extra_branch);
		}
		median = Node->data[Node->count - 1];
		right_branch->branch[0] = Node->branch[Node->count];
		Node->count--;
	}
	error_code au_remove(B_node<entry, order> *& root, entry& target){
		//若不存在，返回not_present, 否则删除节点，返回success
		error_code result = recursive_remove(root, target);
		if (root && root->count == 0){ //则根与子节点合并成为branch[0] 
			B_node<entry, order> * oldroot = root;
			root = root->branch[0];
			delete oldroot;
		} 
		return result;
	}
	error_code recursive_remove(B_node<entry, order> *& Node, entry& target){
		//若存在，删除，返回success，否则返回not_present
		error_code result;
		int position;
		if (!Node) return not_present;
		if (search_node(Node, target, position) == success){
			result = success;
			if (Node->branch[position] != NULL){ //不是叶节点，用直接前驱代替 
				 B_node<entry, order> * copy = Node->branch[position];
				 while(copy->branch[copy->count] != NULL) copy = copy->branch[copy->count];
				 Node->data[position] = copy->data[copy->count - 1];
				 recursive_remove(Node->branch[position], Node->data[position]);
			}
			else { //为叶节点，直接删除，没有孩子，不用调整分支 
				for(int i = position; i < Node->count - 1; i++)
					Node->data[i] = Node->data[i + 1];
				Node->count--;
			}
		}
		else result = recursive_remove(Node->branch[position], target);
		//此时position为删除节点所在分支下标或root为叶节点的时候显然成立 
		if (Node->branch[position] != NULL && Node->branch[position]->count < (order - 1) / 2) 
			restore(Node, position); //若孩子数过少，修复 
		return result;
	}
	void restore(B_node<entry, order> *& Node, int position){
		//pre: Node->branch[position]孩子数过少 
		//若兄弟节点孩子数大于最少，则调整，否则合并，两种均优先使用左兄弟 
		if (position == Node->count) //最右 
			if (Node->branch[position - 1]->count >= order / 2) move_right(Node, position - 1); 
			else combine(Node, position);
		else if (position == 0)
			if (Node->branch[1]->count > (order - 1) / 2) move_left(Node, 1);
			else combine(Node, 1); 
		else if (Node->branch[position - 1]->count > (order - 1) / 2) move_right(Node, position - 1);
		else if (Node->branch[position + 1]->count  > (order - 1) / 2) move_left(Node, position + 1);
		else combine(Node, position);
	} 
	void move_right(B_node<entry, order> *& Node, int position){//Node->branch[position + 1]元素过少 
		B_node<entry, order> * left = Node->branch[position], *right = Node->branch[position + 1];
		//右分支右移，腾出位置给转移过来的节点
		right->branch[right->count + 1] = right->branch[right->count];
		for (int i = right->count; i > 0; i--){
			right->data[i] = right->data[i - 1];
			right->branch[i] = right->branch[i - 1];
		}  
		right->count++;
		right->data[0] = Node->data[position];
		right->branch[0] = left->branch[left->count--];
		Node->data[position] = left->data[left->count];
	}
	void move_left(B_node<entry, order> *& Node, int position){//Node->branch[position - 1]元素过少 
		//调整左分支 
		B_node<entry, order> * left = Node->branch[position - 1], *right = Node->branch[position];
		left->data[left->count++] = Node->data[position - 1];
		left->branch[left->count] = right->branch[0];
		Node->data[position - 1] = right->data[0]; 
		//右分支左移
		right->count--;
		for(int i = 0; i < right->count; i++){
			right->data[i] = right->data[i + 1];
			right->branch[i] = right->branch[i + 1];
		} 
		right->branch[right->count] = right->branch[right->count + 1];
	}
	void combine(B_node<entry, order> *& Node, int position){////Node->branch[position]元素过少，与左兄弟合并 
		B_node<entry, order> * left = Node->branch[position - 1], *right = Node->branch[position];
		left->data[left->count++] = Node->data[position - 1]; //画图
		left->branch[left->count] = right->branch[0];
		//合并右树
		for(int i = 0; i < right->count; i++){
			left->data[left->count++] = right->data[i];
			left->branch[left->count] = right->branch[i + 1];
		} 
		//调整Node 
		Node->count--;
		for (int i = position - 1; i < Node->count; i++){
			Node->data[i] = Node->data[i + 1];
			Node->branch[i + 1] = Node->branch[i + 2];
		} 
		delete right;
	}
	void re_print(B_node<entry, order> * Node){
		if (Node == NULL) return; 
		for (int i = 0; i < Node->count; i++){
			re_print(Node->branch[i]);
			cout << Node->data[i] << ' ';
		}
		re_print(Node->branch[Node->count]);
	}
	
private:
	B_node<entry, order> * root;
}; 
template <class entry, int order>
void insert_series(B_tree<entry, order> & T){
	cout << "input the times to insert" << endl; 
	int m;
	cin >> m;
	while(m--){
		cout << "input the number of the entry to insert" << endl; 
		int n;
		entry c;
		cin >> n;
		cout << "input " << n << " entries" << endl;
		while(n--){
			cin >> c;
			T.insert_tree(c);
		}
		T.print();
		cout << T.height() << endl;
	}
}
template <class entry, int order>
void search_series(B_tree<entry, order> & T){
	cout << "input the times to search" << endl; 
	int n;
	entry c;
	cin >> n;
	while(n--){
		cout << "input the entry to search" << endl; 
		cin >> c;
		cout << (T.search_tree(c) == success) << endl;
	}
}
template <class entry, int order>
void remove_series(B_tree<entry, order> & T){
	cout << "input the times to remove" << endl; 
	int m;
	cin >> m;
	while(m--){
		cout << "input the number of the entry to remove" << endl; 
		int n;
		entry c;
		cin >> n;
		cout << "input " << n << " entries" << endl;
		while(n--){
			cin >> c;
			T.remove_tree(c);
		}
		T.print();
		cout << T.height() << endl;
	}
}
int main(){
	B_tree<char, 5> T;
	insert_series(T);
//	search_series(T);
//	remove_series(T);
	T.clear();
	T.print();
}
