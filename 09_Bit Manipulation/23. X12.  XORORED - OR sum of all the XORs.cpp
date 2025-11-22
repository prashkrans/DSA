/* Bit manipulation problem 23. (XOR problem 12.) Given an array A of N non-negative integers, you can choose 
any non-negative integer X from A and replace every element Ai with (Ai^X). Using the above operation exactly 
once, the goal is to minimize the bitwise OR of the new array. In other words, find X such that (A1^X)|...|(A^X) 
is minimized. Here, ^ and | denotes the bitwise XOR and OR operations.
Find the value of X and the minimum possible bitwise OR of the new array.

Constraints:
1≤T≤5000
1≤N≤100
0≤Ai≤10^9 => int will work just fine

Both methods get successfully submitted in codechef
*/
//  My Method 1: There could only be three conditions
//  a.  All the bits in the ith posn are set => this ith set bit will become 0 as 1^1 = 0
//  b.  All the bits in the ith posn are not set => this ith non-set bit will stay 0 as 0^0 = 0
//  c.  Few bits are set while few are not set in the ith posn => this ith posn would definitely become 1 as 0^1 = 1
//  So, finally ORsum = ORsum + bit*(1<<i)

//  Running time = O(32n) ~ O(n) i.e. linear time
//  Auxiliary space = O(1)

#include<iostream>
using namespace std;

int main () {
	int t, n, ORsum, bit;
	cin>>t;
	while(t--) {
		cin>>n;
		int a[n];
		ORsum = 0;	//	This initialization is important
		for(int i=0; i<n; i++) cin>>a[i];
		for(int i=0; i<32; i++) {
			int countZ = 0;
			int countOne = 0;
			for(int j=0; j<n; j++) {
                if((a[j]&(1<<i))==0) countZ++;
                else if((a[j]&(1<<i))>0) countOne++;
			}
			if(countZ==n) bit = 0;
			else if(countOne==n) bit = 0;
			else bit = 1;
			ORsum += bit*(1<<i);
		}
		cout<<a[0]<<" "<<ORsum<<"\n";
	}
	return 0;
}

//  My Method 2: Recognised the pattern after solving a couple of examples.
//  Working principle: For any X = A0 or A1 or ... An-1, the sum of OR of (Ai^X) is the same.
//  So, we may pick any Ai as X here and ORSum = (A0^X) + (A1^X) + (A2^X) + ... A(An-1^X)
//  Running time = O(n)
//  Auxiliary space = O(1)

#include<iostream>
#include<vector>
using namespace std;

int main () {
	int t, n, ORsum;
	cin>>t;
	while(t--) {
		cin>>n;
		ORsum = 0;	//	This initialization is important
		vector<int> a(n);
		for(int i=0; i<n; i++) cin>>a[i];
		int X = a[0];
		for(int i=0; i<n; i++) {
			ORsum = ORsum | (a[i]^X);
		}
		cout<<X<<" "<<ORsum<<"\n";
	}
	return 0;
}

