#include <iostream>
#include <stack>
using namespace std;
/*
outline:
algorithm look_ahead(configuration, depth, recommend)
 pre:a partitially completed game configuration, the depth to look ahead
 pos:recommend is the best choice through looking ahead
 if depth == 0 or configuration.done()
 	return configuration.evaluate()  //if game over, get a score
 for every legal Move
 	let configuration make the Move
 	score = look_ahead(configuration, depth - 1, reply) //recursively look ahead
	if better(score,best_score)   //if score better
		best_score = score
		recommend = Move
	detele the Move from configuration
//after the loop, best_score will be best, recommend will be the choice to get best score
 return best_score
*/
 //tic-tac-toe
typedef pair<int, int> Move;
class board{
public:
	board();
	bool done()const;
	void print()const;
	bool better(int value, int old_value)const;
	void play(Move try_it);
	void deplay(Move try_it);
	int worst_case()const;
	int evaluate()const;
	int legal_move(stack<Move> &moves)const; //get all legal Move and store them into a stack

	int square[3][3];
	int move_done;  //count
	int winner()const; //if someone win
};
board::board(){
	move_done = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			square[i][j] = 0;
}
bool board::done()const{
	return move_done == 9 || winner();
}
void board::print()const{
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++)
			cout << square[i][j] << ' ';
		cout << endl;
	}
}
bool board::better(int value, int old_value)const{
	if (move_done % 2) return value > old_value;
	return value < old_value;
}
void board::play(Move try_it){
	square[try_it.first][try_it.second] = move_done++ % 2 + 1;
}
void board::deplay(Move try_it){
	square[try_it.first][try_it.second] = 0;
	move_done--;
}
int board::worst_case()const{
	return move_done % 2? 10: -10;
}
int board::evaluate()const{
	int w = winner();
	if (w == 1) return 10 - move_done;
	else if (w == 2) return move_done - 10;
	return 0;
}
int board::legal_move(stack<Move> &moves)const{
	int count = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (square[i][j] == 0) { moves.push(pair<int, int>(i, j)); count ++; }
	return count;
}
int board::winner()const{
	for (int i = 0; i < 3; i++){
		if (square[i][0] && square[i][0] == square[i][1] && square[i][0] == square[i][2]) return square[i][0];
		if (square[0][i] && square[0][i] == square[1][i] && square[0][i] == square[2][i]) return square[0][i];
	}
	if (square[0][0] && square[0][0] == square[1][1] && square[0][0] == square[2][2]) return square[0][0];
	if (square[0][2] && square[0][2] == square[1][1] && square[0][2] == square[2][0]) return square[0][2];
	return 0;
}
int look_ahead(board & configuration, int depth, Move & recommend){
	if (depth == 0 || configuration.done()) return configuration.evaluate();
	stack<Move> st;
	configuration.legal_move(st);
	int best_score = configuration.worst_case();
	while (!st.empty()){
		Move try_it = st.top(), reply;
		configuration.play(try_it);
		int score = look_ahead(configuration, depth - 1, reply);
		if (configuration.better(score, best_score)){
			best_score = score;
			recommend = try_it;
		}
		configuration.deplay(try_it);
		st.pop();
	}
	return best_score;
}
int main(){
	board B;
	B.square[0][0] = 1; B.move_done ++;
	B.square[1][1] = 1; B.move_done ++;
	B.square[2][2] = 2; B.move_done ++;
	B.square[0][1] = 2; B.move_done ++;
	Move recommend;
	cout << look_ahead(B, 9, recommend) << endl;

}
