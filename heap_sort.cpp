#include <iostream>
using namespace std;
//heap sort
/*
regard the list as a binary tree, suitable only for contiguous lists
*/
const int mmax = 20;
class list{
public:
	list():count(0){}
	void read(){
		for (int i = 0; i < 7; i++) 
			cin >> array[i];
		count = 7;
	}
	void build_heap(); //initialize the list into max_heap（最大堆）
	void insert_heap(int data, int low, int high); //insert data to position low and rearrange array to maintain the property of heap
	void heap_sort();
	void print(){
		for (int i = 0; i < count; i++) cout << array[i] << ' ';
		cout << endl;
	}
private:
	void swap(int a, int b){
		int t = array[a];
		array[a] = array[b];
		array[b] = t;
	}
	int count;
	int array[mmax];
};

void list::build_heap(){
	//there are nearly count / 2 internal nodes in the heap(tree)
	for (int i = count / 2 - 1; i >= 0; i--)
		insert_heap(array[i], i, count - 1); 
	print();
}
void list::insert_heap(int data, int low, int high){
	/*
	pos: data firstly insert to position low and then restore the quality of heap from low to high(index)
	*/
	array[low] = data;
	int more = -1;
	while (1){
		if (2 * low + 1 <= high && array[2 * low + 1] > array[low]) more = 2 * low + 1;
		else more = low;
		if (2 * low + 2 <= high && array[2 * low + 2] > array[more]) more = 2 * low + 2;
		if (more == low) break;
		swap(more, low); low = more; 
	}

}
void list::heap_sort(){
	build_heap();
	for (int i = count - 1; i > 0; i--){
		int data = array[i];
		array[i] = array[0];
		insert_heap(data, 0, i - 1);
	}
}
int main(){
	list L;
	L.read();
	L.print();
	L.heap_sort();
	L.print();
}