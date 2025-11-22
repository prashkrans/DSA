/* Bit manipulation problem 24. Given a number n, calculate its square without using *, / and pow()

This problem could be solved using two methods:
1. 	Simple Solution: Add n to n, n-1 times. R.T. = O(n) A.S. = O(1)
2.	Bitwise operators and the property that:
	a.	if n is even => n = 2*x => n^2 = 4*x^2
	b.	if n is odd => 	n = 2*x+1 => n^2 = 4*x^2 + 4*x + 1
*/
//	Method 1:
//	Running time = O(n)
//	Auxiliary space = O(1)

//	Method 2:
// 	Running time = O(log_base2(n))
//	Auxiliay space = O(1)

#include<iostream>
using namespace std;

int getSquare(int n) {
	if(n==0) return 0;
	else if(n<0) return getSquare(-n);
	int x = n >> 1;
	if(n&1) return (getSquare(x) << 2) + (x << 2) + 1;
	else return (getSquare(x) << 2);
}

int main() {
	int t;
	cin>>t;
	while(t--) {
		int n;
		cin>>n;
		int square = getSquare(n);
		cout<<"The square of the number "<<n<<" is = "<<square<<"\n";
	}
	return 0;
}
