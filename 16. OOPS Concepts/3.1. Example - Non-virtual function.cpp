#include<iostream>
using namespace std;

class base {
public:
	void foo() {
		cout<<"Base class's function is called\n";
	}
};

class derived : public base {
public:
	void foo() {
		cout<<"Derived class's function is called\n";
	}
};

int main() {
	base  *b1, *b2, *b3;
	b1 = new base;      //  b1 points to a base object and thus calls the base class's foo()
	b1->foo();
    b2 = new derived;   //  Both b2 and b3 point to a derived object but still calls the base class's foo()
	b2->foo();
	derived d;
	b3 = &d;
	b3->foo();
	return 0;
}
