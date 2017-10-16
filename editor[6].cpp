#include <iostream>
#include <string>
#include <fstream>
#include "double_linked_list.cpp"
using namespace std;
//use double_linked_list to implement editor
class Editor: public DLlist<string>{
public:
	Editor(){}
	//Editor(ifstream * in, ofstream * out);
	bool get_command();
	void do_command();
//private:
	//ifstream * in_file;
	//ofstream * out_file;
	char user_command;
	//auxiliary function
	bool next_line();
	bool pre_line();
	bool goto_line();
	bool insert_line();
	bool change_line();
	bool substitude_line();
	void read_file();
	void write_file();
	bool find_string();
	void print_all_line();
};
//implementation
/*Editor::Editor(ifstream * in, ofstream * out){
	in_file = in;
	out_file = out;
}*/
bool Editor::get_command(){
	//print current line
	if (current_Node) cout << current_position << " : " << current_Node->entry << "\n??" << flush;
	else cout << "File is empty.\n??" << flush;
		cout << "B C D E F G H I N P R S V W" << endl;
	//get command
	cin >> user_command;
	cin.clear();
	cin.sync();
	if (user_command == 'q') return 0;
	return 1;
}
void Editor::do_command(){
	string temp = "";
	switch(user_command){
		case 'B':
			if (empty()) cout << "Warning: empty buffer " << endl;
			else 
				while(pre_line());
		break;
		case 'C':
			if (empty()) cout << "Warning: empty buffer " << endl;
			else if (!change_line()) cout << "Warning: change failed " << endl;
		break;
		case 'D':
			if (!remove(current_position, temp)) cout << "Warning: deletion failed" << endl;
		break;
		case 'E':
			if (empty()) cout << "Warning: empty buffer " << endl;
			else 
				while(next_line());
		break;
		case 'F':
			if (empty()) cout << "Warning: empty buffer " << endl;
			else if (!find_string()) cout << "Warning: No such string in buffer" << endl;
		break;
		case 'G':
			if (!goto_line()) cout << "Warning: No such line " << endl;
		break;
		case 'H':
			cout << "no help" << endl;
		break;
		case 'I':
			if (!insert_line()) cout << "Warning: insertion failed " << endl;
		break;
		case 'N':
			if (!next_line()) cout << "Warning: at end of buffer" << endl;
		break;
		case 'P':
			if (!pre_line()) cout << "Warning: at start of buffer" << endl;
		break;
		//read from file
		case 'R':
			read_file();
		break;
		case 'S':
			if (!substitude_line()) cout << "Warning: substition failed " << endl;
		break;
		case 'V':
			print_all_line();
		break;
		case 'W':
			if (empty()) cout << "Warning: empty buffer " << endl;
			else write_file();
		break;
		default:
			cout << "invalid command! please input H for help or input a valid command : " << flush;
	}
}
bool Editor::next_line(){
	if (current_position + 1 >= count) return 0;
	current_position++;
	current_Node = current_Node->next;
	return 1;
}
bool Editor::pre_line(){
	if (current_position - 1 < 0) return 0;
	current_position--;
	current_Node = current_Node->back;
	return 1;
}
bool Editor::goto_line(){
	int line;
	cout << "please input the line number you want to go : " << flush;
	cin >> line;
	if (line < 0 && line >= count) return 0;
	set_position(line);
	return 1;
}
bool Editor::insert_line(){
	string s = "";
	cout << "please input the line to be inserted: " << endl;
	getline(cin, s);
	int line;
	cout << "please input the line number you want to insert : " << flush;
	cin >> line;
	return insert(line, s);
}
bool Editor::change_line(){
	string sub = "", s = "";
	unsigned int i = 0;
	cout << "please input the string to change: " << endl;
	getline(cin, sub);
	cout << "please input the string to substitute: " << endl;
	getline(cin, s);
	if ((i = current_Node->entry.find(sub)) == string::npos) { cout << i << endl; return 0; }
	current_Node->entry.replace(i, sub.size(), s);
	return 1;
}
bool Editor::substitude_line(){
	int line;
	cout << "please input the line number to be substitute: " << endl;
	cin >> line;
	if (line < 0 || line >= count) return 0;
	set_position(line);
	cout << current_position << " : " << current_Node->entry << endl;
	cout << "input Y to keep substitute : ";
	char c;
	cin >> c;
	cin.clear();
	cin.sync();
	if (c != 'Y') return 0;
	string s = "";
	cout << "please input the string to substitute this line: " << endl;
	getline(cin, s);
	current_Node->entry = s;
	return 1;
}
void Editor::read_file(){
	cout << "input the file name: ";
	string s;
	cin >> s;
	ifstream in(s);
	if (!in) { cout << "error file" << endl; return; }
	clear();
	while(getline(in, s)) insert(count, s);
	in.close();
}
void Editor::write_file(){
	cout << "input the file name: ";
	string s;
	cin >> s;
	ofstream out(s);
	if (!out) { cout << "error file" << endl; return; }
	Node <string> * p = current_Node;
	int pos = current_position;
	set_position(0);
	while (current_Node){
		out << current_Node->entry << endl;
		current_Node = current_Node->next;
	}
	current_Node = p;
	current_position = pos;
}
bool Editor::find_string(){
	string sub = "";
	cout << "please input the string to search for : " << endl;
	getline(cin, sub);
	set_position(0);
	unsigned int i = 0;
	Node<string> *p = current_Node;
	while(p){
		if ((i = p->entry.find(sub)) != string::npos){
			cout << current_position << " : " << p->entry << "\n    ";
			for (unsigned int j = 0; j < i; j++)	cout << ' ';
			for (unsigned int j = 0; j < sub.size(); j++) cout << '^';
			cout << endl;
			return 1;
		}
		p = p->next;
	}
	return 0;
}
void Editor::print_all_line(){
	if (empty()) return;
	set_position(0);
	Node<string> *p = current_Node;
	while(p){
		cout << p->entry << endl;
		p = p->next;
	}
}
int main(int argc, char const *argv[])
{
	Editor buffer;
	while(buffer.get_command()) buffer.do_command();
	/*buffer.insert_line();
	buffer.print_all_line();*/
}