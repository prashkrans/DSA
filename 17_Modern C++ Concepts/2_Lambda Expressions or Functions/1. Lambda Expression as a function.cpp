//  Lambda expression as a function

#include<iostream>
using namespace std;

int main() {
	int a, b;
	cin>>a>>b;
	auto sum1 = [=]() {cout<<a+b<<"\n";};
	auto sum2 = [&]() {cout<<++a+(++b)<<"\n";};
	auto sum3 = [a, b]() {cout<<a+b<<"\n";};
	auto sum4 = [&a, &b]() {cout<<++a+(++b)<<"\n";};
	auto sum5 = [](int a, int b) {cout<<a+b<<"\n";};
	auto sum6 = [](int &a, int &b) {cout<<++a+(++b)<<"\n";};
	sum1();
	sum2();
	sum3();
	sum4();
	sum5(a, b);
	cout<<a<<" "<<b<<"\n";
	sum6(a, b);
	cout<<a<<" "<<b<<"\n";
	return 0;
}
