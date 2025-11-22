#include<iostream>
using namespace std;

template<typename T>
T sum(T a, T b) {
	return a+b;
}

int main () {
	cout<<sum<int>(1, 5)<<"\n";
	cout<<sum<double>(3.4, 2.7)<<"\n";
	cout<<sum<string>("T20", "WC")<<"\n";
	return 0;
}
