/* Bit Manipulation problem: 11. (XOR problem 7.) XOR of Sum of all pairs of an array.
Given an array A of size n. the task is to generate a new sequence B with size N^2 having elements
sum of every pair of array A and find the xor value of the sum of all the pairs formed.
Note: Here (A[i], A[i]), (A[i], A[j]), (A[j], A[i]) all are considered as different pairs.

Example 1:
Input: arr = {1, 5, 6}
Output: 4
sum[3][3] = {1+1, 1+5, 1+6,
		     5+1, 5+5, 5+6,
		     6+1, 6+5, 6+6}
sum[3][3] = {2, 6, 7,
		     6, 10, 11,
		     7, 11, 12}
So, 2 ^ 6 ^ 7 ^ 6 ^ 10 ^ 11 ^ 7 ^ 6 ^ 11 ^ 12 = 4

This problem could be solved using two methods:
1.	Naive solution: O(n^2), O(1)
2.	Twice the XOR of all the elements in the given array: O(n), O(1)
Note: All the elements in the sum matrix except the ones one the diagonal repeat twice. Hence,
using the property that A^A == 0, we can ignore the elements not on the diagonal.
Now, the elements on the diagonal are A[1] + A[1], A[2] + A[2], ... A[n-1] + A[n-1]. So, the
answer becomes 2*(A[1]^A[2]^A[3]...A[n-1]).
*/

//	Method 1 - Get the XOR of all the elements in the array and multiply it by 2 [Verified]
//	Running time = O(n) as we traverse the given array once
//	Auxiliary space = O(1) due to the xorVal variable

#include<iostream>
#include<vector>
using namespace std;

int main() {
	char ch = 'y';
	while(ch=='y') {
        int n;
        cin>>n;
        vector<int> arr(n);
        for(int i=0; i<n; i++) cin>>arr[i];
        int xorVal = 0;
        for(int i=0; i<n; i++) xorVal ^= arr[i];
        xorVal *= 2;
        cout<<"XOR of sum of all pairs of the given array = "<<xorVal<<"\n";
        cout<<"Wanna continue? (y/n)";
        cin>>ch;
	}
	return 0;
}


