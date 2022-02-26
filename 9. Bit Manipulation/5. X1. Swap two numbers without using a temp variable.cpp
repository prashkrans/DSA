/* Bit Manipulation problem: 5. (XOR problem 1.) Swap two numbers without using a temp variable
This problem can be solved using two methods:
1.  Arithmetic operators
2.  Bitwise XOR operator
R.T. = O(1) and A.S. = O(1) for both methods
*/

#include<iostream>
using namespace std;

void swap1(int &a, int &b) {
	if(&a == &b) return;
	a = a+b;
	b = a-b;
	a = a-b;
}

void swap2(int &a, int &b) {
	if(&a == &b) return;
	a = a^b;
	b = a^b;
	a = a^b;
}

int main() {
	char input = 'y';
	int a, b;
	while(input=='y') {
		cout<<"Enter the values of the numbers to be swapped\n";
		cout<<"a = "; cin>>a;
		cout<<"b = "; cin>>b;
		cout<<"Enter method number to be used: ";
		int m;
		cin>>m;
		if(m==1) swap1(a, b);
		else if(m==2) swap2(a, b);
		else cout<<"Input a valid method number\n";
		cout<<"The swapped values are \n";
		cout<<"a = "<<a<<"\nb = "<<b<<"\n";
		cout<<"Wanna continue? (y/n)\n";
		cin>>input;
	}
	return 0;
}
