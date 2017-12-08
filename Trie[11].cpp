#include <iostream>
using namespace std;
//Trie树，字典序查找树，一般用于以字符串为key值的数据存储，如果key值分布随机且稠密，Trie树查找优于binary Tree，若较稀疏，则弱于binary Tree，可结合使用

//定义Trie节点
typedef string Type;
const int num_chars = 28;
struct Trie_node{
	Type key;
	Trie_node *branch[num_chars];
	Trie_node():key(""){ for(int i = 0; i < num_chars; i++) branch[i] = NULL; }
	Trie_node(const Type & k):key(k){ for(int i = 0; i < num_chars; i++) branch[i] = NULL; }
};

class Trie{
public:
	Trie():root(new Trie_node){}
	~Trie(){ re_clear(root); }
	bool search(const Type & key){
		Trie_node * p = root;
		int pos = 0; //记录查找到key的第几个位置
		char c; //记录该位置的字符
		while(p && (c = key_letter(key, pos))!= ' '){
			p = p->branch[get_position(c)];
			pos++;
		}
		//此时已检查完key的所有字符
		if (p && p->key != "") return 1;
		return 0;
	}
	bool insert(const Type & key){
		Trie_node * p = root;
		int pos = 0; //记录检查到key的第几个位置
		char c; //记录该位置的字符
		while(p && (c = key_letter(key, pos))!= ' '){
			if (p->branch[get_position(c)] == NULL) p->branch[get_position(c)] = new Trie_node;
			p = p->branch[get_position(c)];
			pos++;
		}
		//此时已检查完key的所有字符，且p不为空
		if(p->key != "") return 0; //已存在
		p->key = key;
		return 1;
	}
	bool remove(const Type & key){
		bool become_empty; //the
		int pos = 0;
		return recursive_remove(root, key, pos, become_empty);
	}
	void clear(){
        re_clear(root);
	}
	void re_clear(Trie_node *& root){
        if (root){
            for (int i = 0 ; i < num_chars; i++) re_clear(root->branch[i]);
            delete root;
            root = NULL;
        }
	}
	void pre_order(){
        au_pre_order(root);
	}
protected:
    void au_pre_order(Trie_node * root){ //按字母顺序输出
        if (root){
            if (root->key != "") cout << root->key << endl;
            for (int i = 0 ; i < num_chars; i++) au_pre_order(root->branch[i]);
        }
    }
	Trie_node * root;
	//auxiliary function
	char key_letter(const Type & key, int i){
		if (i >= key.size()) return ' ';
		return key[i];
	}
	int get_position(char c){
		if (c == ' ') return 0;
		if (c >= 'a' && c <= 'z') return c - 'a' + 1;
		return 27;
	}
	bool empty_branch(Trie_node *& T){
		for (int i = 0; i < num_chars; i++)
			if (T->branch[i]) return 0;
		return 1;
	}
	bool recursive_remove(Trie_node *& root, const Type &key, int &pos, bool &become_empty){
	    bool result = 1;
		if (!root) result = 0; //未找到
		else {
            char c = key_letter(key, pos);
            if (c == ' ') {
                if (root->key != ""){ //已找到，key清零并判断是否分支全为空
                    root->key = "";
                    if (empty_branch(root))	{
                        delete root;
                        become_empty = 1;
                    }
                }
                else result = 0;;  //未找到
            }
            else {
                result = recursive_remove(root->branch[get_position(c)], key, ++pos, become_empty);
                if (become_empty && empty_branch(root)) delete root;
                else become_empty = 0;
            }
		}
		return result;
	}
};
int main(){
    Trie T;
    T.insert("a");
    T.insert("ab");
    T.insert("ac");
    T.insert("abd");
    T.insert("b");
    T.insert("ba");
    T.insert("bc");
    T.pre_order();
    cout << T.search("abde") << endl;
    cout << T.search("abd") << endl;

    cout << T.remove("xx") << endl;
    cout << T.remove("a") << endl << endl;
    T.pre_order();

    T.clear();
    T.pre_order();
}
