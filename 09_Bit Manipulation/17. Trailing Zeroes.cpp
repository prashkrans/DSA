/* Bit manipulation problem 17. Trailing zeroes
Given an integer A, count and return the number of trailing zeroes.

Example 1:
Input: 8
Output: 3
Explanation: 8 in binary is represented as: 1000, there are 3 trailing zeroes.

Constraints:
1 <= A <= 10^9 i.e A is int type
*/

//	Method 1. Get the right most set bit and return the pos i of the right most set bit.
//	Running time = O(32 or 64) ~ O(1) i.e. constant time
//	Auxiliary space = O(1) i.e the variable if

int Solution::solve(int A) {
    A = A&(-A);
	//  A = A&(~(A-1));
	//  A = A^(A&(A-1)); 
    for(int i=0; i<32; i++) {
        if(A&(1<<i)) return i;
    }
}