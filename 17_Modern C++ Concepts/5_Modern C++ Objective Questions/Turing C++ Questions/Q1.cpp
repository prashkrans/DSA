#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

void myfunction(int i) {
    cout<<" "<<i;
}

void multiply(int a) {
    a*2;
}

int main() {
    int t[] = {10, 5, 9, 6, 2, 4, 7, 8, 3, 1};
    vector<int> v1(t, t+10);
    for_each(v1.begin(), v1.end(), multiply);
    iter_swap(v1.begin(), t+9);
    for_each(v1.begin(), v1.end(), myfunction);
    return 0;
}
