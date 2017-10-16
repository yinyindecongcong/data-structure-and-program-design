#include <iostream>
using namespace std;
const int maxsize = 20;
template <class Node_entry>
struct Node
{
	Node_entry entry;
	int next;
};
template <class Node_entry>
class ARlist{
public:
	ARlist(){ head = availible = last_use = -1; count = 0; }
	int size()const{ return count; }
	bool full()const{ return count == maxsize; }
	bool empty()const{ return count == 0; }
	void clear();
	bool insert(int i, Node_entry value){
		if (i < 0 || i > count || full()) return 0;
		int pre, follow;
		if (i == 0) follow = head;
		else {
			pre = get_index(i - 1);
			follow = array[pre].next;
		}
		int new_index = new_node();
		array[new_index].entry = value;
		array[new_index].next = follow;
		if (i == 0) head = new_index;
		else array[pre].next = new_index;
		count ++;
		return 1; 
	}
	bool remove(int i){
		if (empty() || i < 0 || i >= count) return 0;
		int old_index = get_index(i);
		cout << old_index << endl;
		delete_node(old_index);
		count--;
		return 1;
	}
	void print(){
		int p = head;
		while(p != -1){
			cout << array[p].entry << ' ';
			p = array[p].next;
		}
		cout << endl;
	}
protected:
	int head, availible, last_use;
	//represent first ele, previously used but now availible ele, and the last index, respectively
	int count;
	Node<Node_entry> array[maxsize];
	int new_node(){//new a Node
		int new_index;
		if (availible != -1){
			new_index = availible;
			availible = array[availible].next;
		}
		else if (last_use < maxsize - 1)
			new_index = ++last_use;
		else return -1;
		array[new_index].next = -1;
		return new_index;
	}
	void delete_node(int old_index){
		int pre;
		if (old_index == head) head = array[old_index].next;
		else {
			pre = get_index(get_position(old_index) - 1);
			array[pre].next = array[old_index].next;
		}
		array[old_index].next = availible;
		availible = old_index;
	} 
	int get_position(int index)const{
		if (head == index) return 0;
		int p = array[head].next, pos = 1;
		while (p != -1){
			if (p == index) return pos; 
			p = array[p].next;
			pos++;
		}
		return -1;
	}
	int get_index(int position)const{
		int index = head;
		for(int i = 0; i < position; i++)
			index = array[index].next;
		return index;
	}
};
int main(){
	ARlist<int> AL;
	AL.insert(0,3);
	AL.insert(0,1);
	AL.insert(1,2);
	AL.insert(3,4);
	AL.print();
	AL.remove(0);
	AL.print();
	AL.insert(3,5);
	AL.print();
}