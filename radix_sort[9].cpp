//radix sort could be applied to those whose keys are alphanumeric strings
#include <iostream>
#include <list>
#include <queue>
using namespace std;
typedef string Key;
const int keysize = 5;
const int chars = 28;
//define Record, with alphanumeric Key name 
class Record{
public:
	Record(const Key & s):name(""){
		for (unsigned int i = 0; i < keysize - s.size(); i++) name += ' ';
		name += s; 
	}
	int get_blocknum(int position){
		if (name[position] == ' ') return 0;
		if (name[position] <= 'z' && name[position] >= 'a') return name[position] - 'a' + 1;
		return 27;
	}
	Key get_name(){ return name; }
	operator Key() const{ return name; }
private:
	Key name;
};
//define a sortable list
class Sortable_list{
public:
	Sortable_list(){}
	void read();
	void radix_sort();//sort
	void print();
private:
	list<Record> namelist;
	void rethread(queue<Record> Q[]);//rethread the blocks divided by char into namelist
};
void Sortable_list::read(){
	int n;
	cin >> n;
	Key k = "";
	while(n--){
		cin >> k;
		Record r(k);
		namelist.push_back(r);
	}
}
void Sortable_list::radix_sort(){
	queue<Record> Q[chars]; //create blocks to divide records
	for(int i = keysize - 1; i >= 0; i--){
		while(!namelist.empty()){
			int j = namelist.begin()->get_blocknum(i);
			/*Key k = *namelist.begin();
			Record n(k);
			Q[j].push(n);*/
			//since Record contains no pointer, we could not to create a new Record
			Q[j].push(*namelist.begin());
			namelist.erase(namelist.begin());
		}
		rethread(Q);
	}
}
void Sortable_list::print(){
	for (auto it = namelist.begin(); it != namelist.end(); it++)
		cout << it->get_name() << endl;
}
void Sortable_list::rethread(queue<Record> Q[]){
	for (int i = 0; i < chars; i++)
		while(!Q[i].empty()){
			/*Key k = Q[i].front();
			Record n(k);
			namelist.push_back(n);*/
			namelist.push_back(Q[i].front());
			Q[i].pop();
		}
}
int main(){
	Sortable_list L;
	L.read();
	L.print();
	L.radix_sort();
	L.print();
}