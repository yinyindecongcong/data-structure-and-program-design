//二叉树的基本操作的实现，二叉查找树，建造树
//ADT for basic binary tree
//二叉树基类，包含其基本操作
#include <iostream>
#include <vector>
using namespace std;
//带*为AVL树所需语句
enum balance_factor{left_higher, equal_height, right_higher};
template <class entry>
struct binary_node{
  //constructor
  binary_node():lchild(0), rchild(0){}
  binary_node(const entry & key):data(key), lchild(0), rchild(0){}
  
  //data members
  entry data;
  binary_node<entry> * lchild;
  binary_node<entry> * rchild;
  //*virtual balance_factor get_balance()const{ return equal_height; }
  //*virtual void set_balance(balance_factor b){}
  //*virtual ~binary_node(){}
  //AVL树中AVL节点为二叉树节点的子类，操作中传参类型为二叉节点（实际为AVL节点，使用虚函数实现多态，使编译通过）
  //具体见http://blog.csdn.net/wanlijunjun/article/details/53606352
};

template <class entry>
class binary_tree{
public:
  //constructor
  binary_tree():root(0), num_node(0){}
  binary_tree(const binary_tree<entry> & original){
  	num_node = original.num_node;
  	au_copy(root, original.root);
  }
  //orerator =
  binary_tree & operator = (const binary_tree<entry> & original){
  	clear();
  	num_node = original.num_node;
  	au_copy(root, original.root);
  	return *this;
  }
  //destructor
  ~binary_tree(){
  	clear();
  }
  
  //function
  int size()const{ return num_node; }
  bool empty()const{ return num_node == 0; }
  int height()const{ return au_height(root); }
  bool insert(const entry& key){ num_node++; au_insert(root, key); return 1; }
  void clear(){	num_node = 0;	au_clear(root); }
  //traverse
  void preorder(void (*visit)(entry&)){
  	preorder_recursive(root, visit);
  }
  void inorder(void (*visit)(entry&)){
  	inorder_recursive(root, visit);
  }
  void postorder(void (*visit)(entry&)){
  	postorder_recursive(root, visit);
  }
protected:
  //auxiliary function
  void au_copy(binary_node<entry> *& obj, const binary_node<entry> * ori){
  	if (!ori) return;
  	obj = new binary_node<entry>(ori->data);
  	au_copy(obj->lchild, ori->lchild);
  	au_copy(obj->rchild, ori->rchild);
  }
  int au_height(const binary_node<entry> * tree)const{
  	if (!tree) return 0;
  	return 1 + max(au_height(tree->lchild), au_height(tree->rchild));
  }
  void au_insert(binary_node<entry> *& root, const entry& key){
  	if (!root){root = new binary_node<entry>(key); return; }
	if (key == root->data) return;
  	if (key < root->data) au_insert(root->lchild, key);
  	else if (key > root->data) au_insert(root->rchild, key);
  }
  void au_clear(binary_node<entry> *& root){
  	if (!root) return;
  	au_clear(root->lchild);
  	au_clear(root->rchild);
  	delete root;
  }
  void preorder_recursive(binary_node<entry> *root, void (*visit)(entry&)){
  	if (!root) return;
  	visit(root->data);
  	preorder_recursive(root->lchild, visit);
  	preorder_recursive(root->rchild, visit);
  }
  void inorder_recursive(binary_node<entry> *root, void (*visit)(entry&)){
  	if (!root) return;
  	inorder_recursive(root->lchild, visit);
  	visit(root->data);
  	inorder_recursive(root->rchild, visit);
  }
  void postorder_recursive(binary_node<entry> *root, void (*visit)(entry&)){
  	if (!root) return;
  	postorder_recursive(root->lchild, visit);
  	postorder_recursive(root->rchild, visit);
  	visit(root->data);
  }	
protected:
  binary_node<entry> * root;
  int num_node;
};
template <class entry>
void visit(entry& key){
  	cout << key << endl;
}

//ADT for BST
//二叉查找树作为二叉树的子类，新增或重写查找/插入/删除操作 override：签名与返回类型相同
template <class entry>
class Search_tree :public binary_tree<entry>{
public:
	bool insert(const entry& key){
		this->num_node++;
		return insert_bst(this->root, key);
	}
	bool search(entry& key){
		binary_node<entry> * found = search_bst(this->root, key);
		if (!found) return 0;
		key = found->data;
		return 1;
	}
	bool remove(const entry& key){
		if (remove_bst(this->root, key)) {
			this->num_node--;
			return 1;
		}
		return 0;
	}
private:
	bool insert_bst(binary_node<entry> *& root, const entry& key){
		if (!root){root = new binary_node<entry>(key); return 1; }
		if (key == root->data) return 0;
  		if (key < root->data) return insert_bst(root->lchild, key);
  		else if (key > root->data) return insert_bst(root->rchild, key);
  		return 1;
	}
	binary_node<entry> * search_bst(binary_node<entry> * root, const entry& key){
		if (!root || root->data == key) return root;
		if (key < root->data) return search_bst(root->lchild, key);
		if (key > root->data) return search_bst(root->rchild, key);
	}
	bool remove_bst(binary_node<entry> *& root, const entry& key){
		if (!root || root->data == key) return au_remove_bst(root);
		if (key < root->data) return remove_bst(root->lchild, key);
		return remove_bst(root->rchild, key);
	}
	bool au_remove_bst(binary_node<entry> *& root){
		if (!root) return 0;
		binary_node<entry> * to_delete = root; 
		if (!root->lchild) root = root->rchild;
		else if (!root->rchild)	root = root->lchild;
		else{
			binary_node<entry> * s = root;
			to_delete = to_delete->lchild;
			while(to_delete->rchild){
				s = to_delete;
				to_delete = to_delete->rchild;
			}
			root->data = to_delete->data;
			if (s == root) s->lchild = to_delete->lchild;
			else s->rchild = to_delete->lchild;
		}
		delete to_delete;
		return 1;
	}
};

//建造树--作为查找树的子类，对于已排序的key序列，若采用上述insert将得到高度不平衡树。
//此时可采用建造树，得到相对平衡二叉树（若序列长度为2的幂减一，则为完全平衡二叉树）
//uses:循环调用build_insert，最后调用connect_tree链接右边的悬挂点
template <class entry>
class buildable_tree: public Search_tree<entry>{
public:
	bool build_tree(vector<entry> sequence){
		//pos:若sequence非递增，且得到树为从头起最长递增序列所建造的平衡树，返回值为0 
		bool result = 1;
		vector<binary_node<entry> *> last_node; //记录每一层最右的节点
		last_node.push_back(0);
		while(this->num_node < sequence.size()){
			if (this->num_node > 0 && sequence[this->num_node] < sequence[this->num_node - 1]) {
				result = 0;
				break;
			}
			else {
				build_insert(this->num_node + 1, sequence[this->num_node], last_node);
				this->num_node++;
			}
		} 
		this->root = last_node[last_node.size() - 1];
		connect_tree(last_node);
		return result;
	}
protected:
	void build_insert(int count, const entry& key, vector<binary_node<entry> *> &last_node){ 
		//count为第几个元素，所在层数为1 + count的因数中2的最高次数
		int level = 1;
		while(count % 2 == 0){
			level ++;
			count /= 2;
		}
		binary_node<entry> * new_node = new binary_node<entry>(key);
		//1.左孩子为往下一层最右节点 2.若往上一层的最右节点右孩子为空，新节点为其右孩子 3.更新last_node
		new_node->lchild = last_node[level - 1];
		if (level == last_node.size()) last_node.push_back(new_node);
		else last_node[level] = new_node;
		if (last_node.size() > level + 1 && last_node[level + 1]->rchild == NULL)  last_node[level + 1]->rchild = new_node;
	}
	void connect_tree(vector<binary_node<entry> *> &last_node){
		int high_level = last_node.size() - 1;
		binary_node<entry> * high_node = NULL, * low_node = NULL; 
		while(high_level > 2){ //0-2层无需调整 
			if (last_node[high_level]->rchild) high_level--;
			else{
				int low_level = high_level; //自顶而下找到右边第一个悬挂点
				high_node = last_node[high_level]; 
				do{
					low_node = last_node[--low_level];
				}while(low_node && low_node->data < high_node->data);
				high_node->rchild = low_node;
				high_level = low_level;
			} 
		}
	}
}; 
/*
int main(){
	buildable_tree<int> T;
	vector<int> a;
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(4);
	a.push_back(5);
	a.push_back(6);
	a.push_back(7);
	a.push_back(8);
	a.push_back(9);
	T.build_tree(a);
	T.inorder(visit);
}
*/

//AVL树
//定义AVL_node

template <class entry>
struct AVL_node: public binary_node<entry>{
	//construction,调用父类对应构造函数 
	AVL_node():binary_node<entry>(), balance(equal_height){} 
	AVL_node(const entry& key):binary_node<entry>(key), balance(equal_height){}
	//add balance_factor and its operation
	balance_factor balance;
	balance_factor get_balance()const{ return balance; }
	void set_balance(balance_factor b){ balance = b; }
}; 

//AVL树--高度平衡的二叉查找树，作为查找树的子类并重写insert和remove操作
//参考《DATA STRUCTURES AND PROGRAM DESIGN IN C++》，chapter 10
template <class entry>
class AVL_tree: public Search_tree<entry>{
public:
	bool insert(const entry& key){
		bool taller;
		this->num_node++;
		return avl_insert(this->root, key, taller);
	}
	bool remove(entry key){
		bool shorter;
		this->num_node--;
		return avl_remove(this->root, key, shorter);
	}
protected:
	bool avl_remove(binary_node<entry> *& root, entry& key, bool & shorter){
		if (!root) return 0;
		else if (root->data == key){
			binary_node<entry> * to_delete = root;
			if (root->lchild && root->rchild){	//若有左右孩子，转化问题为只有左孩子的情况 
				to_delete = root->lchild;
				while(to_delete->rchild) to_delete = to_delete->rchild;
				key = root->data = to_delete->data;
				goto jmp; 
			}
			else if (!root->lchild) root = root->rchild;
			else if (!root->rchild) root = root->lchild;
			shorter = 1;
			delete to_delete; 
		}
		else if (key < root->data){
		jmp:
			avl_remove(root->lchild, key, shorter);
			if (shorter){
				switch(root->get_balance()){
					case equal_height:
						root->set_balance(right_higher);
						shorter = 0;
					break;
					case left_higher:
						root->set_balance(equal_height);
					break;
					case right_higher:
						//除了左孩子的平衡因子为equal_height的情况插入不可能出现，
						//其余情况可看成（但不完全相同）往左子树插入了一个节点达到不平衡状态，但平衡因子的调整与左右旋是完全相同的 
						//故只需在此处增加equal_height情况的处理即可（由于shorter变化不同，不可直接加在平衡函数中） 
						if (root->rchild->get_balance() == equal_height){
							root->rchild->set_balance(left_higher);
							left_rotate(root);
							shorter = 0;
						}
						else right_balance(root);
					break;
				}
			}
		}
		else if (key > root->data){
			avl_remove(root->rchild, key, shorter);
			if (shorter){
				switch(root->get_balance()){
					case equal_height:
						root->set_balance(left_higher);
						shorter = 0;
					break;
					case right_higher:
						root->set_balance(equal_height);
					break;
					case left_higher:
						//除了左孩子的平衡因子为equal_height的情况插入不可能出现，
						//其余情况可看成（但不完全相同）往左子树插入了一个节点达到不平衡状态，但平衡因子的调整与左右旋是完全相同的 
						//故只需在此处增加equal_height情况的处理即可（由于shorter变化不同，不可直接加在平衡函数中） 
						if (root->lchild->get_balance() == equal_height){
							root->lchild->set_balance(right_higher);
							right_rotate(root);
							shorter = 0;
						}
						else left_balance(root);
					break;
				}
			}
		}
	}
	bool avl_insert(binary_node<entry> *& root, const entry& key, bool &taller){
		bool result = 1;
		if (!root){
			root = new AVL_node<entry>(key);
			taller = 1; 
		}
		else if (root->data == key) taller = result = 0;  
		if (key < root->data){
			result = avl_insert(root->lchild, key, taller); //插入左子树 
			if (taller){									//若长高,需调整的位置只调整一次，不可用while 
				switch(root->get_balance()){
					case left_higher:						//左高左平衡，不长高 
						left_balance(root);
						taller = 0;
					break;								
					case equal_height:						//一样高变为左高，长高 
						root->set_balance(left_higher); 
					break;
					case right_higher:
						root->set_balance(equal_height);	//右高变为一样高，不长高
						taller = 0; 
					break;
				}
			}
		}
		else if (key > root->data){
			result = avl_insert(root->rchild, key, taller); //插入左子树 
			if (taller){									//若长高,需调整的位置只调整一次，不可用while 
				switch(root->get_balance()){
					case right_higher:						//左高左调整，不长高 
						right_balance(root);
						taller = 0;
					break;								
					case equal_height:						//一样高变为左高，长高 
						root->set_balance(right_higher); 
					break;
					case left_higher:
						root->set_balance(equal_height);	//右高变为一样高，不长高
						taller = 0; 
					break;
				}
			}
		}
		return result;
	}
	//调整函数的辅助函数--左旋右旋
	void right_rotate(binary_node<entry> *& root){
		if (!root || !root->lchild) {
			cout << "error" << endl;
			return;
		} 
		binary_node<entry> * newroot = root->lchild;
		root->lchild = newroot->rchild;
		newroot->rchild = root;
		root = newroot;
	} 
	void left_rotate(binary_node<entry> *& root){
		if (!root || !root->rchild) {
			cout << "error" << endl;
			return;
		} 
		binary_node<entry> * newroot = root->rchild;
		root->rchild = newroot->lchild;
		newroot->lchild = root;
		root = newroot;
	}
	//调整函数
	/*
	右调整为例，则root右边高，判断root右孩子平衡情况 
	1.右边高，左旋
	2.等高，不可能
	3.左边高，先右旋再左旋，平衡因子调整分情况 
	*/
	void right_balance(binary_node<entry> *& root){
		binary_node<entry> * right = root->rchild;
		switch(right->get_balance()){
			case right_higher:
				right->set_balance(equal_height);
				root->set_balance(equal_height);
				left_rotate(root);
			break;
			case equal_height:
				//只有删除节点时可能出现
				cout << "only delete" << endl;	
			break;
			case left_higher:
				binary_node<entry> * sub = right->lchild;
				//调整平衡因子,画图即可 
				switch(sub->get_balance()){
					case equal_height:
						right->set_balance(equal_height);
						root->set_balance(equal_height);
					break;
					case left_higher:
						right->set_balance(right_higher);
						root->set_balance(equal_height);
					break;
					case right_higher:
						right->set_balance(equal_height);
						root->set_balance(left_higher);
					break;
				}
				sub->set_balance(equal_height);
				right_rotate(right);
				left_rotate(root); 
			break;
		} 
	}
	void left_balance(binary_node<entry> *& root){
		binary_node<entry> * left = root->lchild;
		switch(left->get_balance()){
			case left_higher:
				left->set_balance(equal_height);
				root->set_balance(equal_height);
				right_rotate(root);
			break;
			case equal_height:
				//只有删除节点时可能出现
				cout << "only delete" << endl; 
			break;
			case right_higher:
				binary_node<entry> * sub = left->rchild;
				//调整平衡因子,画图即可 
				switch(sub->get_balance()){
					case equal_height:
						left->set_balance(equal_height);
						root->set_balance(equal_height);
					break;
					case left_higher:
						left->set_balance(equal_height);
						root->set_balance(right_higher);
					break;
					case right_higher:
						left->set_balance(left_higher);
						root->set_balance(equal_height);
					break;
				}
				sub->set_balance(equal_height);
				left_rotate(left);
				right_rotate(root); 
			break;
		} 
	}
}; 
/*
int main(){
	AVL_tree<int> T;
	T.insert(1);
	T.insert(2);
	T.insert(3);
	T.insert(4);
	T.insert(5);
	T.insert(6);
	T.insert(7);
	T.insert(8);
	T.insert(9);
	T.inorder(visit);
	cout << endl;
	T.remove(4);
	T.remove(1); 
	T.preorder(visit);
	cout << T.height() << endl;
}*/

//伸展树 splay tree，作为二叉查找树的子类，增加一个splay操作，将指定节点调整到根的位置
/*
若指定节点为父节点的左孩子，称为zig，右孩子称为zag
自下而上：zig-zig ------right_rotate(large) + right_rotate(middle) ---升高二层
				 zig-zag ------left_rotate(small) + right_rotate(root)    ---升高二层
				 zig ----------right_rotate(large)                        ---升高一层
				 zag等同上
《DATA STRUCTURE AND PROGRAM DESIGN IN C++》里面采用下面更简单的方法
自顶而下：有三棵树作为辅助，分别为
					central_tree:包含目标节点（如果存在的话）
					smaller_key_tree:包含key值严格小于central_tree所有节点key值的节点
					larger_key_tree:包含key值严格大于central_tree所有节点key值的节点
					zig-zig ------right_rotate(large) + link_right(middle) 
				    zig-zag ------link_right(large) + link_left(small)   
				    zig ----------link_right(large)                        
				    zag等同上
*/
template <class entry>		
class splay_tree: public Search_tree<entry>{
public:
	bool splay(const entry &key){//若key不存在，插入并调整，返回0，否则调整key，返回1
		if (adj_splay(this->root, key) == 0) { this->num_node++; return 0;}
		return 1;

	}
protected:
	//若key不存在，插入并调整，返回0，否则调整key，返回1
	//smaller_key_tree和larger_key_tree初始化为辅助节点dummy,child为对应中间节点
	bool adj_splay(binary_node<entry> *& root, const entry & key){
		bool result = 0; 
		binary_node<entry> * dummy = new binary_node<entry>;
		binary_node<entry> * first_large = dummy, * first_small = dummy, * child = NULL;
		while(root && root->data != key){
			if (key < root->data){
				child = root->lchild;
				if (!child || child->data == key) //zig-move
					link_right(root, first_large);
				else if (key < child->data){      //zig-zig-move
					right_rotate(root);//root已改变
					link_right(root, first_large);
				}
				else {                            //zig-zag-move
					link_right(root, first_large);//root已改变
					link_left(root, first_small);
				}
			}
			else if (key > root->data){
				child = root->rchild;
				if (!child || child->data == key) //zag-move
					link_left(root, first_small);
				else if (key > child->data){      //zag-zag-move
					left_rotate(root);//root已改变
					link_left(root, first_small);
				}
				else {                            //zag-zig-move
					link_left(root, first_small);//root已改变
					link_right(root, first_large);
				}
			}
		}
		//此时root为空（表示未找到key）或root不为空，即为key
		if (!root){
			root = new binary_node<entry>(key);
			//first_large和first_small调整
			first_large->lchild = first_small->rchild = NULL;
		}
		else {
			//first_large和first_small调整
			first_large->lchild = root->rchild;
			first_small->rchild = root->lchild;
			result = 1;
		}
		root->lchild = dummy->rchild;
		root->rchild = dummy->lchild;
		delete dummy;
		return result;
	}
	//link_right和link_left辅助函数
	//first_large为large_key_tree最小的元素，first_small为smaller_key_tree最大的元素
	void link_right(binary_node<entry> *& root, binary_node<entry> *& first_large){
		first_large->lchild = root;
		first_large = root;
		root = root->lchild;
	}
	void link_left(binary_node<entry> *& root, binary_node<entry> *& first_small){
		first_small->rchild = root;
		first_small = root;
		root = root->rchild;
	}
	//左旋右旋
	void right_rotate(binary_node<entry> *& root){
		if (!root || !root->lchild) {
			cout << "error" << endl;
			return;
		} 
		binary_node<entry> * newroot = root->lchild;
		root->lchild = newroot->rchild;
		newroot->rchild = root;
		root = newroot;
	} 
	void left_rotate(binary_node<entry> *& root){
		if (!root || !root->rchild) {
			cout << "error" << endl;
			return;
		} 
		binary_node<entry> * newroot = root->rchild;
		root->rchild = newroot->lchild;
		newroot->lchild = root;
		root = newroot;
	}
};

int main(){
	splay_tree<int> T;
	T.splay(1);
	T.splay(2);
	T.splay(3);
	T.splay(4);
	T.splay(5);
	T.splay(6);
	T.splay(7);
	T.splay(8);
	T.splay(9);
	T.inorder(visit);
	T.splay(6);
	T.preorder(visit);
	cout << T.height() << endl;
}