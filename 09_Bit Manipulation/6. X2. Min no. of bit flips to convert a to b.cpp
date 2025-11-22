/* Bit Manipulation problem: 6. (XOR problem 2.) Minimum no. of bit flips required to convert a to b.
Given two numbers a and b, return the minimum no. of bit flips required to convert a to b.
*/

//  Running time = O(no. of 1s in c i.e. a^b) which could be O(log_base2(a^b)) in the worst case
//  Auxiliary space = O(1) due to the variables c and count

#include<iostream>
using namespace std;

int minBitFlips(int a, int b) {
	int c = a^b;
	int count = 0;
	while(c) {
        count++;
        c = c&(c-1);
	}
	return count;
}

int main() {
	char input = 'y';
	int a, b;
	while(input=='y') {
		cout<<"Enter the values of the numbers a and b:\n";
		cin>>a>>b;
		cout<<"The min no. of bit flips required to convert a to b are = ";
		cout<<minBitFlips(a, b)<<"\n";
		cout<<"Wanna continue? (y/n)\n";
		cin>>input;
	}
	return 0;
}
