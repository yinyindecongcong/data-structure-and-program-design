#include <iostream>
#include <cstring>
//uses:strlen(), strcpy(), strncpy(), strcat(), strcmp(), strstr()....
using namespace std;

class String{
public:
	String();
	~String(){delete [] entries; length = 0; }
	String(const String & copy);
	String(const char * copy);
	String operator = (const String & copy);
	const char * c_str()const;
	//compare, buxiel 
	int size()const{ return length; }
protected:
	char * entries;
	int length;
};

String::String(){ entries = NULL, length = 0; }
String::String(const String & copy){
	length = copy.length;
	entries = new char[length + 1];
	strcpy(entries, copy.entries);
}
String::String(const char * copy){
	length = strlen(copy);
	entries = new char[length + 1];
	strcpy(entries, copy);
}
String String::operator = (const String & copy){
	delete [] entries;
	length = copy.length;
	entries = new char[length + 1];
	strcpy(entries, copy.entries);
	return *this;
}
const char * String::c_str()const{
	return (const char*)entries;
}
//compare, buxiel 
String read(istream & in, char & terminate){
	char c;
	char *copy = new char[100]; 
	int size = 0;
	while (in.peek() != EOF && (c = in.get()) != '\n')
		copy[size++] = c;
	String answer(copy);
	delete []copy;
	return answer;
}
void write(ostream & out, String & s){
	out << s.c_str() << endl;
}

int main(){
	String s1;	
	String s2("8008208820");
	write(cout, s2);
	String s3(s2);
	write(cout, s3);
	const char * co = s2.c_str();
	cout << co << endl;
	s1 = s2;
	write(cout, s1);
	String s4;
	char c;
	s4 = read(cin, c);
	write(cout, s4);
}