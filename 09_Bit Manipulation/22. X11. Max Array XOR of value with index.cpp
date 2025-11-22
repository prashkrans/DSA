/*Bit manipulation problem 22. (XOR problem 11.) Max Array XOR of value with index (Codechef contest problem)
Value of an array A of length L is defined as the sum of (Ai^i) for all 0<=i<L, where ^ denotes bitwise
xor operation. Note that array indices start from zero.
You are given an integer N and an array A consisting of 2N integers where Ai=i for all 0<=i<2^N.

Example :
For N=1, you have an array A of length 21=2 and A=[0,1].
For N=2, you have an array A of length 22=4 and A=[0,1,2,3].
You can do at most K operations on this array. In one operation, you can choose two indices i and j (0<=i,j<2^N)
and swap Ai and Aj (i.e. Ai becomes Aj and vice versa).

What is the maximum value of array A you can obtain after at most K operations?

Constraints:
1<=T<=10^5
1<=N<=30
0<=K<=10^9
*/

//  Method 1. R.T. = O(k) so it gets TLE and A.S. = O(1)

#include<iostream>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
	int t;
	int n, k, sum, maxVal;
	cin>>t;
	while(t--) {
		cin>>n>>k;
		sum = 0;
		maxVal = (1<<n)-1;
		if(k>(1<<(n-1))) k = 1<<(n-1);
		for(int i=0; i<k; i++) sum += i^(maxVal-i);
		cout<<2*sum<<"\n";
	}
	return 0;
}

//  Method 2. R.T. = O(1) i.e. constant time so it passes and A.S. = O(1)
//  Note: We'll have to use long or long long int for ans as if n = 30 => ans = 2*k*(2^n-1)
//  which cannot be stored in just int data type

#include<iostream>
using namespace std;
typedef long l;

int main() {
	ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
	int t;
	int n, k;
	cin>>t;
	while(t--) {
		cin>>n>>k;
		l maxVal = (1<<n)-1;            //  Note: maxVal may be int or long but the ans i.e. 2*k*maxVal should be long so, better take maxVal as long
		if(k>(1<<(n-1))) k = 1<<(n-1);  //  Since, we have to use atmost k operations and any more operation than (2^n/2) is not needed
		cout<<2*k*maxVal<<"\n";         //  Each swap will create two values with maxVal so the ans = 2*k*maxVal
	}
	return 0;
}
