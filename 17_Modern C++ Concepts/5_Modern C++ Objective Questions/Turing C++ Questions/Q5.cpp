#include<iostream>
using namespace std;

class base {
public:
    void foo() {
    cout<<"Base foo()\n";
    }
};

class d1: public base {
public:
    void foo() {
        cout<<"d1 foo()\n";
    }
};

class d2: public base {
};

int main() {
    base b;
    b.foo();
    d1 D1;
    D1.foo();\
    d2 D2;
    D2.foo();
    return 0;
}

