/* Bit Manipulation problem: 3. LC#78. Subsets
Given an integer array nums of unique elements, return all possible subsets (the power set).
The solution set must not contain duplicate subsets. Return the solution in any order.

Example 1:
Input: nums = [1,2,3]
Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]

Example 2:
Input: nums = [0]
Output: [[],[0]]

Constraints:
1 <= nums.length <= 10
-10 <= nums[i] <= 10
All the numbers of nums are unique.

This problem can be solved by two methods:
1. 	Bit manipulation (Bit masking type 2)
2. 	Recursion
*/

//	Method 1. Bit manipulation (Bit masking type 2)
//	Running time = O(n*2^n) since i iterates from 0 to 2^n-1 (i.e. 2^n times) and for each i, j iterates n times 
//	since the size of the mask vector is the same as that of the nums array. Also note that there is actually 
//	no need to create a mask vector as the binary representation of each i itself acts as a mask vector.
//	Auxiliary space = O(2^n) i.e. the size of the power set subsets i.e. the output array or O(n) due to the 
//	subSet vector if the size of the output array is ignored

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        int n = nums.size();
        int limit = (1 << n);
        vector<vector<int>> ans;
        for(int mask=0; mask<limit; mask++) {
            vector<int> subSet;            
            for(int j=0; j<n; j++) {    //  Note: j traverses backwards from n-1 to 0 i.e. 0 <=> n-1 and n-1 <=> 0
                if(mask&(1<<j)) subSet.push_back(nums[j]);
            }
            ans.push_back(subSet);
        }
        return ans;
    }
};

//	Method 2a. Recursion with backtracking (Bottom up approach) [Verified R.T. = O(2^n) so it is faster than method 1]
//	Running time = O(2^n) as (i, R.T) is (n-1, 2), (n-2, 4), (n-3, 8), ... (0, 2^n) => Sum = 2*(2^n-1) 
//	=> R.T. = O(2^(n+1)-2) ~ O(2^n) i.e. exponential hence it is better than method 1.
//	Auxiliary space = O(2^n) due to the temp 2D vector

class Solution {
public:
	vector<vector<int>> recur(int n, vector<int> nums, int i) {   
		if(i==n-1) {                    //  Bottom up recursion
			vector<vector<int>> res;
			vector<int> currSet;
			res.push_back(currSet);     //  Push the empty subset
            currSet.push_back(nums[i]);
			res.push_back(currSet);     //  Push the subset containing only the last element 
			return res;
		}
		vector<vector<int>> temp = recur(n, nums, i+1);
		int size = temp.size()*2;       //  Double the size of the result after recursion finishes
		vector<vector<int>> res(size);
		for(int k=0; k<size/2; k++) {
			res[k] = temp[k];
		}
        int j = 0;
		for(int k=size/2; k<size; k++) {//  Adding the current element to the lower half of the result while keeping the result obtained from the recursion in the upper half 
			res[k] = temp[j];               
			res[k].push_back(nums[i]);
            j++;
		}
		return res;
	}
	vector<vector<int>> subsets(vector<int> &nums) {
		int n = nums.size();
		vector<vector<int>> output;
		output = recur(n, nums, 0);
		return output;
	}
};

//	Method 2b. Recursion (Top down approach)
//	Running time = O(2^n) as (i, R.T) is (1, 2), (2, 4), (3, 8), ... (n, 2^n) => Sum = 2*(2^n-1) 
//	=> R.T. = O(2^(n+1)-2) ~ O(2^n) i.e. exponential hence it is better than method 1.
//	Auxiliary space = O(n) due to the currSet which has max n elements or O(2^n) if the size of the
//	output 2D vector is considered

class Solution {
public:
    void recur(int n, vector<int>::iterator it, vector<vector<int>> &res, vector<int> currSet) {
        if(n==0) {
            //for(int i=0; i<currSet.size(); i++) cout<<currSet[i]<<" "; cout<<"\n";
            res.push_back(currSet);
            return;
        }
        currSet.push_back(*it);
        recur(n-1, ++it, res, currSet);
        currSet.pop_back();     //  Pop the latest element pushed
        --it;                   //  Since, we have used ++it instead of it + 1, so need to revert it back to its current position
        recur(n-1, ++it, res, currSet);
    }
    
    vector<vector<int>> subsets(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> res;
        vector<int> currSet;
        recur(n, nums.begin(), res, currSet);
        return res;
    }
};