#include <iostream>
using namespace std;
//Node
template <class Node_entry>
struct Node
{
	Node_entry entry;
	Node<Node_entry> * next;
	Node(){}
	Node(Node_entry e, Node<Node_entry> * n = NULL):entry(e), next(n){}
};
//linked_list, without head
template <class Node_entry>
class list{
public:
	list();
	list(const list & L);
	list operator = (const list & L);
	~list();
	int size()const;
	int find(Node_entry entry);
	bool insert(int i, Node_entry entry);
	bool remove(int i, Node_entry &entry);
	void print();
	void clear();
protected:
	int count;
	Node<Node_entry> * head;
	Node<Node_entry> * set_position(int i) const; //get the Node of position i
};
//implementation
template <class Node_entry>
Node<Node_entry> * list<Node_entry>::set_position(int i) const{
	Node<Node_entry> * p = head;
	for (int j = 0; j < i; j++) p = p->next;
	return p;
}

template <class Node_entry>
list<Node_entry>::list():count(0), head(NULL){}

template <class Node_entry>
list<Node_entry>::list(const list & L){
	/*Node<Node_entry> * p = L.head;
	while(p){
		insert(count, p->entry);
		p = p->next;
	}*/
	count = L.count;
	if (!L.head) return; 
	//copy head
	Node<Node_entry> * p = L.head;
	head = new Node<Node_entry>(p->entry);
	Node<Node_entry> * r = head;
	p = p->next;
	while(p){
		Node<Node_entry> * n = new Node<Node_entry>(p->entry);
		r->next = n;
		r = n;
		p = p->next;
	}
}

template <class Node_entry>
list<Node_entry> list<Node_entry>::operator = (const list & L){
	clear();
	count = L.count;
	if (!L.head) return *this; 
	//copy head
	Node<Node_entry> * p = L.head;
	head = new Node<Node_entry>(p->entry);
	Node<Node_entry> * r = head;
	p = p->next;
	while(p){
		Node<Node_entry> * n = new Node<Node_entry>(p->entry);
		r->next = n;
		r = n;
		p = p->next;
	}
	return *this;
}

template <class Node_entry>
list<Node_entry>::~list(){ 
//clear(); 
}

template <class Node_entry>
int list<Node_entry>::size()const{ return count; }

template <class Node_entry>
int list<Node_entry>::find(Node_entry new_entry){
	Node <Node_entry> * p = head;
	int pos = 0;
	while (p){
		if (p->entry == new_entry) return pos;
		p = p->next;
		pos++;
	}
	return -1;
}

template <class Node_entry>
bool list<Node_entry>::insert(int i, Node_entry new_entry){
	if (i < 0 || i > size()) return 0;
	//get pre and follow
	Node<Node_entry> * pre = NULL, * follow = NULL;
	if (i == 0) follow = head;
	else {
		pre = set_position(i - 1);
		follow = pre->next;
	}
	Node<Node_entry> * n = new Node<Node_entry>(new_entry, follow);
	if (i == 0) head = n;
	else pre->next = n;
	count++;
	return 1;
}

template <class Node_entry>
bool list<Node_entry>::remove(int i, Node_entry &del_entry){
	if (i < 0 || i >= size()) return 0;
	//get pre and follow
	Node<Node_entry> * pre = NULL, * toremove = NULL, *follow = NULL;
	if (i == 0) toremove = head;
	else {
		pre = set_position(i - 1);
		toremove = pre->next;
	}
	follow = toremove->next;
	del_entry = toremove->entry;
	if (i == 0) head = follow;
	else pre->next = follow;
	delete toremove;
	count--;
	return 1;
}

template <class Node_entry>
void list<Node_entry>::print(){
	Node<Node_entry> * p = head;
	while(p){
		cout << p->entry << " ";
		p = p->next;
	}
	cout << endl;
}

template <class Node_entry>
void list<Node_entry>::clear(){
	Node_entry del_entry = 0;
	while(count) remove(0, del_entry);
}

int main(){
	list<int> L1;
	L1.insert(0, 1);
	L1.insert(1, 2);
	L1.insert(2, 3);
	L1.insert(3, 4);
	L1.print();
	list<int> L2(L1);
	int i = 0;
	L2.remove(3,i);
	L2.print();
	cout << i << endl;
	L2.remove(0,i);
	L2.print();
	cout << i << endl;
	L1 = L2;
	L2.print();
	L1.print();
}