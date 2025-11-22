/* Bit Manipulation problem: 1b. LC#338. Counting Bits
Given an integer n, return an array ans of length n + 1 such that for each i (0 <= i <= n), ans[i] is 
the number of 1's in the binary representation of i.

Example 2:
Input: n = 5
Output: [0,1,1,2,1,2]
Explanation:
0 --> 0
1 --> 1
2 --> 10
3 --> 11
4 --> 100
5 --> 101

This problem can be solved using two methods
1.	n&(n-1) (Faster solution)
2.	Right shifting 
*/

//	Method 1. Using the fact that n&(n-1) reduces the no. of '1's by one.

//	Running time = O(n*(no. of 1s in the bin reprn of n)) which would become O(n*log_base2(n)) in worst cases where n is 
//	the given number. Thus, it performs better than method 2.
//	Auxiliary space = O(n+1) ~ O(n) i.e. the size of the vector that stores the no. of 1s for all integers 0 to n

class Solution {
public:
    int hammingWeight(int x) {
        int count=0;
        while(x) {
            count++;
            x = x&(x-1);
        }
        return count;
    }
    
    vector<int> countBits(int n) {
        vector<int> ans(n+1);
        ans[0] = 0;
        for(int i=1; i<=n; i++) ans[i] = hammingWeight(i);
        return ans;
    }
};

//	Method 2. Using the right shift operator
//	Here, we keep right shifting the given number and increment count by 1 if the current number has 1 
//	as its right most bit.

// 	Running time = O(n*log_base2(n)) in all the cases i.e. as (log_base2(n) + 1) is the no. of bits in n
//	Auxiliary space = O(n+1) ~ O(n) i.e. the size of the vector that stores the no. of 1s for all integers 0 to n

class Solution {
public:
	int hammingWeight(int n) {
		int count = 0;
		while(n>0) {
			if(n&1==1) count++;
			n = n >> 1;
		}
		return count;
	}    
    vector<int> countBits(int n) {
        vector<int> ans(n+1);
        ans[0] = 0;
        for(int i=1; i<=n; i++) ans[i] = hammingWeight(i);
        return ans;
    }
};
