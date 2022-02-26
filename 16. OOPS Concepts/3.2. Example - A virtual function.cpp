#include<iostream>
using namespace std;

class base {
public:
	virtual void foo() {    //  Using the virtual keyword before void foo() in the base class makes sure the appropriate foo() function is called.
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
	base  *b1, *b2, *b3;    //  Make sure to use asterisk before the pointer name i.e. base *b1, b2; => b1 is a pointer while b2 is an object
	b1 = new base;          //  b1 points to a base object and thus calls the base class's foo()
	b1->foo();
    b2 = new derived;       //  Both b2 and b3 point to a derived object and since the base class uses a virtual function,
	b2->foo();              //  both b2->foo() and b3->foo() calls the derived class's foo()
	derived d;
	b3 = &d;
	b3->foo();
	return 0;
}

