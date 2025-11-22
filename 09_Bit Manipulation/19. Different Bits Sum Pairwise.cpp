/* Bit manipulation problem 19. Different Bits Sum Pairwise
You are given an array of N positive integers, A1, A2 ,…, AN. Find sum of f(Ai, Aj) for all pairs (i, j) 
such that 1 ≤ i, j ≤ N. (Optional - Return the answer modulo 10^9+7)
We define f(X, Y) as number of different corresponding bits in binary representation of X and Y. For example, 
f(2, 7) = 2, since binary representation of 2 and 7 are 010 and 111, respectively. The first and the third bit 
differ, so f(2, 7) = 2.

Example 1:
A=[1, 3, 5]

f(1, 1) + f(1, 3) + f(1, 5) + 
f(3, 1) + f(3, 3) + f(3, 5) +
f(5, 1) + f(5, 3) + f(5, 5) =

0 + 1 + 1 +
1 + 0 + 2 +
1 + 2 + 0 = 8
As we can see the matrix is symmetric hence, we can get the sum of the upper triangular matrix excluding the 
the diagonal values (as diag values are 0s) and double it to get the total sum.

This problem could be solved by two methods:
1.	Naive solution: R.T. = O(n^2), A.S. = O(1)
2.	Efficient solution: R.T. = O(32n or 64n) ~ O(n) i.e. linear time, A.S. = O(1)
	Steps:
	i.	Iterate through all the bits from i = 0 to max_size, here 32.
	ii.	For each i, iterate through all the elements in the given array of size n and count the number of set bits.
		a. 	If say count stores the no. of set bits => (n-count) is equal to the no. of bits that are not set
		b.	Then cout*(n-count) would give the pairs (u, v) with different ith bits i.e. f(u, v) >= 1
	iii.Finally, double the sum to since the pairs are ordered but have the same value i.e. f(u, v) = f(v, u)
Note:	
a.	This method is similar to the method discussed for problem 12. Sum of XOR of all pairs of an array
b.	Use %1000000007 only when it is required to return the ans%(10^9+7) 
	
*/
//	Method 1. Naive solution:
//	Running time = O(n^2) i.e. quadratic
//	Auxiliary space = O(1)

int Solution::cntBits(vector<int> &A) {
    int n = A.size();
    int sum = 0;
    for(int i=0; i<n; i++) {
        for(int j=i+1; j<n; j++) {
            //cout<<"("<<A[i]<<", "<<A[j]<<") ";
            int val = A[i]^A[j];
            for(int k=0; k<32; k++) {					// or while(val) {count++; val = val&(val-1)} sum += val;
                if(val&(1<<k)) sum += 1%1000000007;
            }
        }
    }
    sum = (2*sum)%1000000007;
    return sum;
}

//	Method 2a. Efficient solution:
//	Running time = O(32n or 64n) ~ O(n) i.e. linear
//	Auxiliary space = O(1)

int Solution::cntBits(vector<int> &A) {
    int n = A.size();
    int sum = 0;
    for(int i=0; i<32; i++) {
        int count = 0;
        for(int j=0; j<n; j++) {
            if(A[j]&(1<<i)) count++;
        }
        sum += (count*(n-count)*2);
    }
    return sum;
}

//	Method 2b. Efficient solution:
//	Exactly same as the method 2a. but with different way to calculate the set bits and the non-set bits
//	Running time = O(32n or 64n) ~ O(n) i.e. linear
//	Auxiliary space = O(1)

int Solution::cntBits(vector<int> &A) {
    int n = A.size();
    int sum = 0;
    for(int i=0; i<32; i++) {
        long int setCount = 0;
        long int notSetCount = 0;
        for(int j=0; j<n; j++) {
            if(A[j]&(1<<i)) setCount++;
            else notSetCount++;
        }
        sum = sum + (setCount*notSetCount*2);
    }
    return sum%1000000007;
}