#include <iostream>
using namespace std;
//Node
template <class Node_entry>
struct Node
{
	Node_entry entry;
	Node<Node_entry> * back, *next;
	Node(){}
	Node(Node_entry e, Node<Node_entry> * b, Node<Node_entry> * n):entry(e), back(b), next(n){}
};
//double_linked_list
template <class Node_entry>
class DLlist{
public:
	DLlist();
	DLlist(const DLlist & L);
	DLlist operator = (const DLlist & L);
	void clear();
	~DLlist();
	bool insert(int i, Node_entry e);
	bool remove(int i, Node_entry & e);
	void print()const;
protected:
	int count;
	mutable int current_position;
	mutable Node<Node_entry> * current_Node;
	void set_position(int i)const;
	//pos:current_Node points to the Node at position i
};
//implementation
template <class Node_entry>
void DLlist<Node_entry>::set_position(int i)const{
	if (current_position <= i)
		for ( ; current_position != i; current_position++)
			current_Node = current_Node->next;
	else 
		for ( ; current_position != i; current_position--)
			current_Node = current_Node->back;
}
template <class Node_entry>
DLlist<Node_entry>::DLlist():count(0), current_position(0), current_Node(NULL){}
template <class Node_entry>
DLlist<Node_entry>::DLlist(const DLlist & L):count(0), current_position(0), current_Node(NULL){
	if (L.count == 0) return;
	L.set_position(0);
	Node<Node_entry> * p = L.current_Node;
	while(p){
		insert(count, p->entry);
		p = p->next;
	}
}
template <class Node_entry>
DLlist<Node_entry> DLlist<Node_entry>::operator = (const DLlist & L){
	clear();
	if (L.count == 0) return *this;
	L.set_position(0);
	Node<Node_entry> * p = L.current_Node;
	while(p){
		insert(count, p->entry);
		p = p->next;
	}
	return *this;
}
template <class Node_entry>
void DLlist<Node_entry>::clear(){
	Node_entry e = 0;
	while(count){
		remove(0, e);
	}
}
template <class Node_entry>
DLlist<Node_entry>::~DLlist(){
	clear();
}
template <class Node_entry>
bool DLlist<Node_entry>::insert(int i, Node_entry e){
	if (i < 0 || i > count) return 0;
	//find pre and follow
	Node<Node_entry> * pre = NULL, * follow = NULL;
	if (i == 0){
		set_position(0);
		follow = current_Node;
	}
	else {
		set_position(i - 1);
		pre = current_Node;
		follow = pre->next;
	}
	//create NEW Node
	Node<Node_entry> * n = new Node<Node_entry>(e, pre, follow);
	if (pre) pre->next = n;
	if (follow) follow->back = n;
	current_Node = n;
	current_position = i;
	count++;
	return 1; 
}
template <class Node_entry>
bool DLlist<Node_entry>::remove(int i, Node_entry & e){
	if (i < 0 || i >= count) return 0;
	//find pre, toremove and follow
	Node<Node_entry> * pre = NULL, * toremove = NULL, * follow = NULL;
	if (i == 0){
		set_position(0);
		toremove = current_Node;
	}
	else {
		set_position(i - 1);
		pre = current_Node;
		toremove = pre->next;
	}
	follow = toremove->next;
	e = toremove->entry;
	if (pre) pre->next = follow;
	if (follow) follow->back = pre;
	delete toremove;
	if (i == 0) current_Node = follow; //else current_Node would point nothing
	count--;
	return 1;
}
template <class Node_entry>
void DLlist<Node_entry>::print()const{
	set_position(0);
	Node<Node_entry> * p = current_Node;
	while(p){
		cout << p->entry << ' ';
		p = p->next;
	}
	cout << endl;
}

int main(){
	DLlist<int> DL;
	DL.insert(0,3);
	DL.insert(0,1);
	DL.insert(1,2);
	DL.insert(3,4);
	DL.insert(4,5);
	DL.print();
	DLlist<int> DL2(DL);
	int i = 0;
	DL2.remove(0, i);
	DL2.print();
	cout << i << endl;
	DL2.remove(1, i);
	DL2.print();
	cout << i << endl;
	DL2.remove(2, i);
	DL2.print();
	cout << i << endl;
	DLlist<int> DL3(DL2);
	DL3.print();
	DL3 = DL;
	DL3.print();
}