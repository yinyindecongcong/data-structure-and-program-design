#include <iostream>
#include <stack>
using namespace std;
//status
enum error_code {overflow, underflow, success};
//item in polynomial
struct ITEM{
	double coefficient;
	int exponent;
	ITEM(double c = 0, int e = 0):coefficient(c), exponent(e){}
};
//queue node
struct Node{
	ITEM item;
	Node * next;
	Node(ITEM i = ITEM(), Node * n = 0):item(i), next(n){}
};
typedef ITEM queue_entry;
class EXTEND_QUEUE{
public:
	EXTEND_QUEUE():front(0), rear(0), count(0){}
	EXTEND_QUEUE(const EXTEND_QUEUE & original);
	EXTEND_QUEUE & operator = (const EXTEND_QUEUE & original);
	//operation
	error_code append(const queue_entry & item);
	error_code serve();
	error_code retrive(queue_entry & item);
	bool empty()const;
	int size() const;
	error_code serve_and_retrive(queue_entry & item);
	void clear();
	/*void print(){
		Node * p = front;
		while(p) { cout << p->item; p = p->next; }
		cout << endl;
	}*/
protected:
	Node * front, * rear;
	int count;
};
class polynomial :private EXTEND_QUEUE{
public:
	void read();
	void print() const;
	friend polynomial operator + (const polynomial & a, const polynomial & b);
	friend polynomial operator * (const polynomial & a, const polynomial & b);
private:
	polynomial mult_term(const ITEM& c)const;
};
//bool do_command(char c, stack <polynomial>& s_polinomial){
/*
pos:¸orerate according to command 'c' 
*/
	/*stack_entry p, q;
	switch(c){
		case '?': cin >> p;
			      if (s_polinomial.push(p) == overflow) cout << "ÉÏÒç³ö" << endl;
			      break;
		case '=': if (s_polinomial.top(p) == underflow) cout << "ÏÂÒç³ö" << endl;
				  else cout << p << endl;
				  break;
		case '+': if (s_polinomial.top(p) == underflow) cout << "ÎÞÔªËØ" << endl;
				  else {
				  	s_polinomial.pop();
				  	if (s_polinomial.top(q) == underflow) { cout << "Ö»ÓÐÒ»¸öÔªËØ" << endl; s_polinomial.push(p); }
				  	else {
				  		s_polinomial.pop(); 
				  		s_polinomial.push(p + q);
				  	}
				  }
				  break;
		case '-': if (s_polinomial.top(p) == underflow) cout << "ÎÞÔªËØ" << endl;
				  else {
				  	s_polinomial.pop();
				  	if (s_polinomial.top(q) == underflow) { cout << "Ö»ÓÐÒ»¸öÔªËØ" << endl; s_polinomial.push(p); }
				  	else {
				  		s_polinomial.pop(); 
				  		s_polinomial.push(q - p);
				  	}
				  }
				  break;
		case '*': if (s_polinomial.top(p) == underflow) cout << "ÎÞÔªËØ" << endl;
				  else {
				  	s_polinomial.pop();
				  	if (s_polinomial.top(q) == underflow) { cout << "Ö»ÓÐÒ»¸öÔªËØ" << endl; s_polinomial.push(p); }
				  	else {
				  		s_polinomial.pop(); 
				  		s_polinomial.push(p * q);
				  	}
				  }
				  break;
		case '/': if (s_polinomial.top(p) == underflow) cout << "ÎÞÔªËØ" << endl;
				  else {
				  	s_polinomial.pop();
				  	if (s_polinomial.top(q) == underflow) { cout << "Ö»ÓÐÒ»¸öÔªËØ" << endl; s_polinomial.push(p); }
				  	else {
				  		s_polinomial.pop(); 
				  		s_polinomial.push(q / p);
				  	}
				  }
				  break;
		case 'q':
		case 'Q': cout << "end" << endl;
				  return 0;
				  break;
	}
	return 1;
}*/
int main(){
	//cout << get_command() << endl;
	/*STACK s_polinomial;
	intrcduction();
	while(do_command(get_command(), s_polinomial));*/
/*EXTEND_QUEUE():front(0), rear(0), count(0){}
	EXTEND_QUEUE(const EXTEND_QUEUE & original);
	EXTEND_QUEUE & operator = (const EXTEND_QUEUE & original);
	//»ù±¾²Ù×÷
	error_code append(const queue_entry & item);
	error_code serve();
	error_code retrive(queue_entry & item);
	bool empty()const;
	int size() const;
	error_code serve_and_retrive(queue_entry & item);
	void clear();
protected:
	Node * front, * rear;
	int count;*/

	/*EXTEND_QUEUE a1;
	a1.append(1);
	a1.append(5);
	a1.append(7);
	a1.print();
	EXTEND_QUEUE a2(a1);
	a2.print();
	a2.serve();
	EXTEND_QUEUE a3(a1);
	a3.print();
	a3 = a2;
	a3.print();*/

	polynomial a, b, sum;
	a.read();
	b.read();
	sum = a * b;
	sum.print();
} 
error_code EXTEND_QUEUE::append(const queue_entry & item){
	Node * n = new Node(item);
	if (front == 0) front = rear = n;
	else {
		rear->next = n;
		rear = n;
	}
	count++;
	return success;
}
error_code EXTEND_QUEUE::serve(){
	if (front == 0) return underflow;
	Node * q = front;
	front = front->next;
	if (front == 0) rear = 0;
	delete q;
	count --;
	return success;
}
error_code EXTEND_QUEUE::retrive(queue_entry & item){
	if (front == 0) return underflow;
	item = front->item;
	return success;
}
bool EXTEND_QUEUE::empty()const{ return count == 0; }
int EXTEND_QUEUE::size() const{ return count; }
error_code EXTEND_QUEUE::serve_and_retrive(queue_entry & item){
	if (front == 0) return underflow;
	item = front->item;
	return serve();
}
void EXTEND_QUEUE::clear(){
	while(!empty()) serve();
}
EXTEND_QUEUE::EXTEND_QUEUE(const EXTEND_QUEUE & original){
	front = rear = 0;
	count = 0;
	Node * p = original.front;
	while(p){
		append(p->item);
		p = p->next;
	}
}
EXTEND_QUEUE & EXTEND_QUEUE::operator = (const EXTEND_QUEUE & original){
	clear();
	Node * p = original.front;
	while(p){
		append(p->item);
		p = p->next;
	}
	return *this;
}
void polynomial::read(){
	clear();
	cout << "enter the coefficients and exponents for the polynomial" << endl 
		 << "one pair per line. exponents must be in descending order" << endl
		 << "enter a coefficient of 0 or an exponent of 0 to terminate." << endl;
	double coefficient = 1, exponent = 1, last_exponent;
	int first = 1;
	while (coefficient != 0 && exponent != 0){
		cout << "coefficient: " << flush;
		cin >> coefficient;
		if (coefficient != 0){
			cout << "exponent: " << flush;
			cin >> exponent;
			if ((!first && exponent >= last_exponent) || exponent < 0) cout << "data error" << endl;
			else {
				ITEM n(coefficient, exponent);
				append(n);
				first = 0;
			}
			last_exponent = exponent;
		}
	}	
}
void polynomial::print() const{
	Node * p = front;
	if (!p) {cout << '0' << endl; return; }
	bool first = 1;
	while(p){
		if (p->item.coefficient > 0){
			if (!first) cout << "+";
			if (p->item.exponent == 0) {cout << p->item.coefficient; break; }
			else {
				if (p->item.coefficient != 1) cout << p->item.coefficient;
				cout << "x^" << p->item.exponent;
			}
		}
		else if (p->item.coefficient < 0){
			if (p->item.exponent == 0) {cout << p->item.coefficient; break; }
			else {
				if (p->item.coefficient == -1) cout << '-';
				else cout << p->item.coefficient;
				cout << "x^" << p->item.exponent;
			}
		}
		first = 0;
		p = p->next;
	}
	cout << endl;
}
char get_command(){
/*
get command from user and return the command
*/
	char c;
	cout << "input your operation" << flush;
	while (1){
		cin >> c;
		if (c == '?' || c == '=' || c == '+' || c == '-' || c == '*' || c == '/' || c == 'q' || c == 'Q') break;
		else  cout << "wrong operation" << endl;

	}
	return c;
}
polynomial operator + (const polynomial & a, const polynomial & b){
	polynomial sum;
	Node * p = a.front;
	Node * q = b.front;
	while(p && q){
		if (p->item.exponent > q->item.exponent){
			ITEM n(p->item.coefficient, p->item.exponent);
			sum.append(n);
			p = p->next;
		}
		else if (p->item.exponent < q->item.exponent){
			ITEM n(q->item.coefficient, q->item.exponent);
			sum.append(n);
			q = q->next;
		}
		else {
			if (p->item.coefficient + q->item.coefficient != 0){
				ITEM n(p->item.coefficient + q->item.coefficient, p->item.exponent);
				sum.append(n);
			}
			p = p->next;
			q = q->next;
		}
	}
	while(p){
		ITEM n(p->item.coefficient, p->item.exponent);
			sum.append(n);
			p = p->next;
	}
	while(q){
		ITEM n(q->item.coefficient, q->item.exponent);
			sum.append(n);
			q = q->next;
	}
	return sum;
}
polynomial polynomial::mult_term(const ITEM& c)const{
	polynomial temp;
	Node * p = front;
	while(p){
		ITEM n(p->item.coefficient * c.coefficient, p->item.exponent + c.exponent);
		temp.append(n);
		p = p->next;
	}
	return temp;
}
polynomial operator * (const polynomial & a, const polynomial & b){
	polynomial multi;
	Node * p = b.front;
	while(p){
		polynomial temp;
		temp = a.mult_term(p->item);
		multi = multi + temp;
		p = p->next;
	}
	return multi;
}