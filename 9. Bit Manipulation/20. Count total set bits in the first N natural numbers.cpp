/* Bit manipulation problem 20. Count Total Set Bits in first N natural numbers
Given a positive integer A (i.e. a natural number), count the total number of set bits in the binary 
representation of all the numbers from 1 to A. Optional: Return the count modulo 10^9 + 7.

Example 1:
Input: A = 3
Output: 4
Explanation :
DECIMAL    BINARY  SET BIT COUNT
    1          01        1
    2          10        1
    3          11        2
Ans = 1 + 1 + 2 = 4 

This method could be solved by two methods:
1. 	Naive solution: R.T. = O(total no. of set bits in the 1st natural nos.) = O(n*log(n)) in the worst case, A.S. = O(1)
2.	Efficient solution: R.T. = O(32 or 64) ~ O(1), A.S. = O(1)
	Steps:
	a.	Increment A by 1
	b.	Traverse bit by bit i.e. i = 0 to 32 or 64 and for each i do
		i.	Using dd = dr*q + r we get the total number of set bits in the current bit pos i
		    = ((dr/2)*2^i + if(dr is odd) r)
	
*/

//	Method 1. Naive solution: 
//	Running time = O(total no. of set bits in the 1st natural nos.) = O(n*log(n)) in the worst case
//	Auxiliary space = O(1) 

int numOfSetBit(int x) {
    int count = 0;
    while(x) {
        count++;
        x = x&(x-1);
    }
    return count;
}

int Solution::solve(int A) {
    int ans = 0;
    for(int i=1; i<=A; i++) {
        ans += numOfSetBit(i)%100000007;
    }
    return ans;
}

//	Method 2a. Efficient solution (My method):
//	Running time = O(32 or 64) ~ O(1) i.e. constant time
//	Auxiliary space = O(1) 

int Solution::solve(int A) {
    int ans = 0;
    A++;
    for(int i=0; i<32; i++) {
        int q = A>>i;
        int r = A%(1<<i);
        int sb = q>>1;
        ans = (ans + sb*(1<<i));
        if(q&1) ans = (ans + r);
    }
    return ans;
}


//	Method 2b. Efficient solution: 
//	Exactly same as the method 2a. except here arithmetic operators are used for division
//	Running time = O(32 or 64) ~ O(1) i.e. constant time
//	Auxiliary space = O(1) 

int Solution::solve(int A) {
    int ans = 0;
    A++;
    for(int i=0; i<32; i++) {
        int power = (1<<i);
        int q = A/power;
        int r = A%power;
        int sb = q/2;
        ans = (ans + sb*power);
        if(q%2==1) ans = (ans + r);
    }
    return ans;
}
