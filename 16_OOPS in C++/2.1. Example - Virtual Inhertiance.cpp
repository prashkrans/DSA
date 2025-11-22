//	The below program demonstrates virtual inheritance and not virtual function (function overriding)

#include<iostream>
using namespace std;

class ClassA {
public:
	int a;
};

class ClassB : virtual public ClassA {		//	Since, the ambiguity arose due to the base classes B and C, they are inherited virtually.
public:
    int b;
};

class ClassC : virtual public ClassA {
public:
	int c;
};

class ClassD : public ClassB, public ClassC {
public:
	int d;
};

int main() {
	ClassD obj;
	obj.a = 10;        				//	Statement 3, works fine
	obj.a = 100;     				//	Statement 4, works fine as it overwrites the statement 3.
	obj.b = 20;
	obj.c = 30;
	obj.d = 40;
	cout<< "A : "<< obj.a;
	cout<< "\nB : "<< obj.b;
	cout<< "\nC : "<< obj.c;
	cout<< "\nD : "<< obj.d;
	return 0;
}
