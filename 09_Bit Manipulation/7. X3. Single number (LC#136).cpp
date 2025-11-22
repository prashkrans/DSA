/* Bit Manipulation problem: 7. (XOR problem 3.) LC#136. Single number
Given an array where every element repeats twice except one element, find that non repeating element.

Example 1:
Input: arr[] = {1, 2, 3, 2, 4, 1, 4}
Output: 3

Constraints:
1 <= nums.length <= 3 * 104
-3 * 104 <= nums[i] <= 3 * 104
Each element in the array appears twice except for one element which appears only once.

This problem could be solved by three methods
1.	Novice approach.
	R.T. = O(n^2)
2.	Hashmap or unordered_set
	R.T. = O(n)
3.	Bitwise XOR operator
	R.T. = O(n)
*/

//	Method 3. Bitwise XOR operator
//	Running time = O(n) as we traverse the nums array once
//	Auxiliary space = O(1) due to the xorVal variable

#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int n = nums.size();
        int xorVal = 0;
        for(int i=0; i<n; i++) xorVal = xorVal ^ nums[i];
        return xorVal;
    }
};

int main() {
	int n;
	cin>>n;
	vector<int> nums(n);
	for(int i=0; i<n; i++) cin>>nums[i];
	Solution obj;
	cout<<"Single number = "<<obj.singleNumber(nums);
	return 0;
}

/*
//	Method 2a. Hashmap
//	Running time = O(n)
//	Auxiliary space = O(n)

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        unordered_map<int, int> mp;
        int sN;
        for(auto num : nums) mp[num]++;
        for(auto i : mp) if(i.second==1) sN = i.first;
        return sN;
    }
};

//	Method 2a. Unordered set
//	Running time = O(n)
//	Auxiliary space = O(n/2) ~ O(n)

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        unordered_set<int> st;
        for(auto num : nums) {
			if(st.count(num)>0) st.erase(num);
			else st.insert(num);
		}
        return *st.begin();
    }
};
*/
