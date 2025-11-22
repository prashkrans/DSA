#include<iostream>
using namespace std;

//template <class T, class U>
template <typename T, typename U>   //  Both works
class twoDatatypes {
	T a;
	U b;
public:
	twoDatatypes(T a1, U b1) : a(a1), b(b1) {}
	void print() {
		cout<<"a = "<<a<<"\n";
		cout<<"b = "<<b<<"\n";
	}
};

int main () {
	twoDatatypes<int, char> obj1(1, 'a');
	twoDatatypes<string, double> obj2("abc", 2.92);
	obj1.print();
	obj2.print();
	return 0;
}
