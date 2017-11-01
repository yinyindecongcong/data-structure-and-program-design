#include <iostream>
using namespace std;
//outline
/*
algorithm permute(int new_entry, int degree, list<int>& permutation)
 pre:permutation contains a linked permutation with entries in positions 1 throught new_entry - 1
 post:all permutation with degree entries, built from the given permutation, have been constructed and processed
 uses:functions permute(recursively) and process_permulation
 for current <- 0 to permutation.size() or new_entry
 	permutation.insert(current, new_entry)
 	if new_entry == degree visit(permutation)
 	else permute(new_entry + 1, degree, permutation)
 	premutation.remove(current)
*/
void process_permulation(int * permutation){
	int current = 0;
	while (permutation[current]){
		cout << permutation[current] << ' ';
		current = permutation[current];
	}
	cout << endl;
} 
//use array-based-list, which the index of every space is the data
void permute(int new_entry, int degree, int * permutation){
	int current = 0;
	do{
		//insert
		permutation[new_entry] = permutation[current];
		permutation[current]= new_entry;
		if (new_entry == degree) process_permulation(permutation);
		else permute(new_entry + 1, degree, permutation);
		//remove
		permutation[current] = permutation[new_entry];
		//next position
		current = permutation[current];
	} while(current != 0);
}
int main (){
	int * a = new int [10];
	for (int i = 0; i < 10; i++) a[i] = 0;
	permute(1, 3, a);
}