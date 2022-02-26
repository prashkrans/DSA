/* Bit manipulation problem 16. (XOR problem 10.) LC#1863. Sum of All Subset XOR Totals
Given an array nums, return the sum of all XOR totals for every subset of nums. 
The XOR total of an array is defined as the bitwise XOR of all its elements, or 0 if the array is empty.
For example, the XOR total of the array [2,5,6] is 2 XOR 5 XOR 6 = 1.
Note: Subsets with the same elements should be counted multiple times.
An array a is a subset of an array b if a can be obtained from b by deleting some (possibly zero) elements of b.

Example 1:
Input: nums = [5,1,6]
Output: 28
Explanation: The 8 subsets of [5,1,6] are:
- The empty subset has an XOR total of 0.
- [5] has an XOR total of 5.
- [1] has an XOR total of 1.
- [6] has an XOR total of 6.
- [5,1] has an XOR total of 5 XOR 1 = 4.
- [5,6] has an XOR total of 5 XOR 6 = 3.
- [1,6] has an XOR total of 1 XOR 6 = 7.
- [5,1,6] has an XOR total of 5 XOR 1 XOR 6 = 2.
0 + 5 + 1 + 6 + 4 + 3 + 7 + 2 = 28

Note:
No. of contiguous subarrays = n(n+1)/2
No. of subsets = 2^n

This problem can be solved by two methods:
1. 	Bit manipulation (Bit masking type 2)
2. 	Recursion
*/

//	Method 1. Bit manipulation (Bit masking type 2)
//	Running time = O(n*2^n) since i iterates from 0 to 2^n-1 (i.e. 2^n times) and for each i, j iterates n times 
//	since, the size of the mask vector is the same as that of the nums array. 
//	Auxiliary space = O(2^n) i.e. the size of the power set subsets i.e. the output array or O(n) due to the 
//	subSet vector if the size of the output array is ignored

class Solution {
public:
    int subsetXORSum(vector<int>& nums) {
        int n = nums.size();
        int xorVal = 0;
        int sum = 0;
        for(int mask=0; mask<(1<<n); mask++) {
            xorVal=0;
            for(int i=0; i<n; i++) {
                if(mask&(1<<i)) xorVal^=nums[i];
            }
            sum+=xorVal;
        }
        return sum;
    }
};

//	Method 2. Recursion (a. Top down approach or b. Bottop up approach)
//	Running time = O(2^n) as (i, R.T) is (1, 2), (2, 4), (3, 8), ... (n, 2^n) => Sum = 2*(2^n-1) 
//	=> R.T. = O(2^(n+1)-2) ~ O(2^n) i.e. exponential hence it is better than method 1.
//	Auxiliary space = O(n) or O(2^n)
//	Incomplete