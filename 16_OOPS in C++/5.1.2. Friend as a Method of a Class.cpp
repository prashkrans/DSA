// 5.1.2. Friend as a method of a class

#include<iostream>
using namespace std;

class classA;                               //  Declare classA then classB (with friend function) later

class classB {
    int b = 0;
public:
    int friendOfA(classA &obj);             //  Cannot define friendOfA() here as classA is yet to be defined
};

class classA {
	int a;
public:
	classA(int a_) : a(a_) {}               //  friend function
	friend int classB::friendOfA(classA &obj);      //  Now, declare friend function either in public: or private: of classA
	void print() {
        cout<<"Value of a = "<<a<<"\n";
    }
};

int classB::friendOfA(classA &obj) {        //  Finally after defn of classA, then classB and decln of friendOfA(), define friendOfA()
        cout<<"Accessing and modifying private member 'a' of classA\n";     //  :: is used as friendOfClass() is not a global function but inside classB
        obj.a *= 2;
        cout<<"The modified value of a = ";
        return obj.a;
}

int main() {
	classA objA(5);
	classB objB;
	objA.print();
    cout<<objB.friendOfA(objA)<<"\n";
    objA.print();
	return 0;
}
