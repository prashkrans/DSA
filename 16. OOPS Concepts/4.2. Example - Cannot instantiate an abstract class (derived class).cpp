#include<iostream>
using namespace std;

class base {
public:
	virtual void foo() = 0;
};

class derived: public base {};		//	No definition given to the pure virtual function in the derived class, thus the derived class becomes abstract too.

int main() {
	//base b;
	derived d;                      //  Error as we cannot declare an object of an abstract class.
	return 0;
}
