#include<iostream>
#include<algorithm>
#include<set>

using namespace std;

class A {
    int a;
public:
    A(int a) : a(a) {}
    int getA() const {
        return a;
    }
    void setA(int a) {
        this->a = a;
    }
    operator int() const {
        return a;
    }
};

int main() {
    int t[] = {1, 2, 3, 2, 3, 5, 1, 2, 7, 3, 2, 1, 10, 4, 4, 5};
    set<A> s(t, t+15);
    cout<<equal(s.begin(), s.end(), t)<<endl;
    return 0;
}

