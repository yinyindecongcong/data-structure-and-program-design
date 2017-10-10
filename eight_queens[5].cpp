#include <iostream>
using namespace std;
//define a class queen
const int maxsize = 30;
class queen{
public:
	queen(int size);
	bool is_solve() const;
	bool unguarded(int col)const;
	void insert(int col);
	void remove(int col);
	void print()const;
	int board_size;
private:
	int count;//indicate which row we reach
	bool queen_square[maxsize][maxsize];
}; 
queen::queen(int size){
	count = 0;
	board_size = size;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			queen_square[i][j] = 0;
}
bool queen::is_solve() const{
	return count == board_size;
}
bool queen::unguarded(int col)const{
	for (int i = 0; i < count; i++) 
		if (queen_square[i][col] == 1) return 0;
	for (int i = 1; count - i >= 0 && col - i >= 0; i++)
		if (queen_square[count - i][col - i] == 1) return 0;
	for (int i = 1; count - i >= 0 && col + i < board_size; i++)
		if (queen_square[count - i][col + i] == 1) return 0;
	return 1;
}
void queen::insert(int col){
	queen_square[count++][col] = 1;
}
void queen::remove(int col){
	queen_square[--count][col] = 0;
}
void queen::print()const{
	for (int i = 0; i < board_size; i++){
		for (int j = 0; j < board_size; j++)
			cout << queen_square[i][j] << ' ';
		cout << endl;
	}
	cout << endl;
}
class queen2{
public:
	queen2(int size);
	bool is_solve() const;
	bool unguarded(int col)const;
	void insert(int col);
	void remove(int col);
	void print()const;
	int board_size;
private:
	int count;//indicate which row we reach
	bool col_free[maxsize];
	bool upward_free[2 * maxsize - 1];
	bool downward_free[2 * maxsize - 1];
	int queen_in_row[maxsize];
};
queen2::queen2(int size){
	count = 0;
	board_size = size;
	for (int i = 0; i < size; i++) col_free[i] = 1;
	for (int i = 0; i < 2 * size - 1; i++) upward_free[i] = downward_free[i] = 1;
}
bool queen2::is_solve() const{
	return count == board_size;
}
bool queen2::unguarded(int col)const{
	return col_free[col] && upward_free[count - col + board_size - 1] && downward_free[count + col];
}
void queen2::insert(int col){
	col_free[col] = 0;
	upward_free[count - col + board_size - 1] = 0;
	downward_free[count + col] = 0;
	queen_in_row[count++] = col;
}
void queen2::remove(int col){
	count --;
	col_free[col] = 1;
	upward_free[count - col + board_size - 1] = 1;
	downward_free[count + col] = 1;
}
void queen2::print()const{
	for (int i = 0; i < board_size; i++){
		for (int j = 0; j < board_size; j++)
			cout << (queen_in_row[i] == j) << ' ';
		cout << endl;
	}
	cout << endl; 
}


void solve_from(queen & configuration){
	/*
	pre:a partially completed arrangement
	pos:print all possible arrangement
	uses:class queen, function solve_from, recursively
	*/
	if (configuration.is_solve()) configuration.print();
	else 
		for (int col = 0; col < configuration.board_size; col++)
			if (configuration.unguarded(col)){
				configuration.insert(col);
				solve_from(configuration);
				configuration.remove(col);
			}
}
void solve_from(queen2 & configuration){
	/*
	pre:a partially completed arrangement
	pos:print all possible arrangement
	uses:class queen, function solve_from, recursively
	*/
	if (configuration.is_solve()) configuration.print();
	else 
		for (int col = 0; col < configuration.board_size; col++)
			if (configuration.unguarded(col)){
				configuration.insert(col);
				solve_from(configuration);
				configuration.remove(col);
			}
}
int main(){
	queen2 a(8);
	solve_from(a);
}