#include<iostream>
using namespace std;

class base {
protected:
	int x;                      //  x is not private hence, inherited
public:
	base(int x_): x(x_) {cout<<"Constructor of the base class called\n";}
	virtual void foo() = 0;
};

class derived: public base {
	int y;
public:
	derived(int x_, int y_): base(x_), y(y_) {}
	void foo() {
		cout<<"x = "<<x<<", y = "<<y<<"\n";
	}
};

int main() {
	derived d(2, 5);
	d.foo();
	base *b = new derived(1, 3);
	b->foo();
	return 0;
}
