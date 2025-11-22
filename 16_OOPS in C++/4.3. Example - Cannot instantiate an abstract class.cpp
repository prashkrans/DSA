#include<iostream>
using namespace std;

class test {
	int x;
public:
	test(int x_) : x(x_) {}
	virtual void foo() = 0;
	int getX() { return x; }
};

int main() {
	test t(5);          //	Gives an error, as we cannot instantiate an abstract class.
	t.getX();
	return 0;
}
