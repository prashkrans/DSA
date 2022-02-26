/* DP Prob. #29. (LC#53) - Maximum Sum Subarray Problem
Given an integer array nums, find the contiguous subarray (containing at least one number)
which has the largest sum and return its sum.
A subarray is a contiguous part of an array.

Example 1:
Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
Output: 6
Explanation: [4,-1,2,1] has the largest sum = 6.

Example 2:
Input: nums = [1]
Output: 1

Constraints:
1 <= nums.length <= 10^5
-10^4 <= nums[i] <= 10^4

Follow up: If you have figured out the O(n) solution, try coding another solution using the divide and conquer approach,
which is more subtle.
*/
//  Method 1: Naive Solution or Brute Force Method
//  Running time = O(n^2) i.e. quadratic thus inefficient
//  Auxiliary space = O(1) or O(n^2)

//  Method 2: Kadane's Algorithm (DP)
//  The key concept is to store the max subarray sum at each index i which is = max(arr[i], arr[i] + max subarray sum at i-1)
//  Running time = O(n) i.e. linear thus significantly faster than method 1
//  Auxiliary space = O(1) i.e. constant space due to two variables maxCurr and maxGlobal (or currMax & maxVal)

#include<iostream>
#include<vector>
using namespace std;

int kadane(vector<int> a) {
	int maxCurr = a[0], maxGlobal = a[0];
	for(int i=1; i<a.size(); i++) {
		maxCurr = max(a[i], maxCurr + a[i]);
		maxGlobal = max(maxGlobal, maxCurr);
	}
	return maxGlobal;
}

int main() {
	int n;
	cin>>n;
	vector<int> a(n);
	for(int i=0; i<n; i++) cin>>a[i];
	cout<<"Maximum sum of a subarray is = "<<kadane(a);
	return 0;
}

/* Sample input
5
-3 2 3 -2 5
*/

//  Method 3. Divide and Conquer Approach (Incomplete)
//  Running time =
//  Auxiliary space =

// ##################################################################################

//  Leetcode #53. Maximum Subarray
//  Using method 2 i.e. Kadane's Algo

class Solution {        //  Kadane's Algo to find Maximum Sum Subarray
public:
    int maxSubArray(vector<int>& nums) {
        ios_base::sync_with_stdio(0);
        cin.tie(0); cout.tie(0);
        int currMax = nums[0], maxVal = nums[0];
        for(int i=1; i<nums.size(); i++) {
            currMax = max(nums[i], currMax+nums[i]);
            maxVal = max(maxVal, currMax);
        }
        return maxVal;
    }
};



