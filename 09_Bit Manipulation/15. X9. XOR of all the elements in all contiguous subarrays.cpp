/* Bit manipulation problem 15. (XOR problem 9.) XOR of the elements in all contiguous subarrays
Given an array, find the value obtained by XOR-ing the contiguous subarrays (not subsets), followed by 
XOR-ing the values thus obtained. Determine this value.

https://www.hackerrank.com/challenges/sansa-and-xor/problem

No. of contiguous subarrays = n(n+1)/2
No. of subsets = 2^n
No. of times an element at index i is found in all the contiguous subarrays = (i+1)*(n-1) (say repNum)
where n is the size of the given array.
Using the property of XOR that A^A == 0 we have:
	a.	If repNum of arr[i] is even then it cancels out its other instances and is not included in the xorVal.
	b.	If repNum of arr[i] is odd then it A^A...^A = A and is thus, included in the xorVal.
*/

//	Method 1. repNum = (i+1)*(n-1) and if (repNum is odd) xorVal ^= arr[i]
//	Running time = O(n) as we traverse the array once
//	Auxiliary space = O(1) due to the variable xorVal

int sansaXor(vector<int> arr) {
    int n = arr.size();
    int xorVal = 0;
    for(int i=0; i<n; i++) {
        int repNum = (i+1)*(n-i);			//	repNum stores the total number of times arr[i] is found in all the contiguous subarrays
        if(repNum&1) xorVal ^= arr[i];		//	Both lines 22 and 23, check if repNum is odd, however & is faster than % operation
        // or if(repNum%2==1) xorVal ^= arr[i];
    }
    return xorVal;
}