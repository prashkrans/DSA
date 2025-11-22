/* Bit Manipulation problem: 12. (XOR problem 8.) Sum of XOR of all pairs in an array
Given an array of n integers, find the sum of xor of all pairs of numbers in the array.
Note: Here, the pairs are unordered as a^b == b^a
Input : arr[] = {5, 9, 7, 6}
Output : 47
5 ^ 9 = 12
9 ^ 7 = 14
7 ^ 6 = 1
5 ^ 7 = 2
5 ^ 6 = 3
9 ^ 6 = 15
Sum = 12 + 14 + 1 + 2 + 3 + 15 = 47

This problem could be solved by two methods:
1.  Naive solution: O(n^2), O(1)
2.  Bit manipulation without using XOR operator: O(n), O(1)
*/

//  Method 2.
//  Running time = O(n*32) or O(n*64) ~ O(n)
//  Note: One can say that R.T. = O(nlog2(n)) but since log2(n) is constant i.e. 32 or 64 R.T. = O(const*n) ~ O(n)
//  Auxiliary space = O(n) due to the set and notSet vectors

#include<iostream>
#include<vector>
using namespace std;

int sumOfXor(vector<int> arr) {
    int n = arr.size();
    int sumOfXOR = 0;
    for(int i=0; i<32; i++) {
		int numOfSetBits = 0;
		int numOfNonSetBits = 0;
		for(int j=0; j<n; j++) {
			if(arr[j]&(1<<i)) numOfSetBits++;
			else numOfNonSetBits++;
		}
		sumOfXOR += ((numOfSetBits*numOfNonSetBits)*(1<<i));
	}
	cout<<"The sum of XOR of all the unordered pairs of the given array = ";
	return sumOfXOR;
}

int main() {
	int n;
	cin>>n;
	vector<int> arr(n);
	for(int i=0; i<n; i++) cin>>arr[i];
	cout<<sumOfXor(arr);
	return 0;
}
