// 5.1.1. Friend as a global function (Prefer this over friend as method of a class)

#include<iostream>
using namespace std;

class classA {
	int a;
public:
	classA(int a_) : a(a_) {}               //  friend function
	friend void friendOfA(classA &obj);     //  If we used friend void friendOfA(class obj) here + line 14
	void print() {
        cout<<"Value of a = "<<a<<"\n";
    }
};

void friendOfA(classA &obj) {               //  and void friendOfA(class obj) we can only access but not modify 'a'
    cout<<"Accessing and modifying private member 'a' of classA\n";
    obj.a *= 2;
}

int main() {
	classA obj(5);
	obj.print();
    friendOfA(obj);
    obj.print();
	return 0;
}
