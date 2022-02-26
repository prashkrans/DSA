/*	Hashmap Problem #15 - LC#219. Contains Duplicate II
Given an integer array nums and an integer k, return true if there are two distinct 
indices i and j in the array such that 
1. nums[i] == nums[j] and 
2. abs(i - j) <= k.

Example 1:
Input: nums = [1,2,3,1], k = 3
Output: true

Example 2:
Input: nums = [1,0,1,1], k = 1
Output: true

Example 3:
Input: nums = [1,2,3,1,2,3], k = 2
Output: false
*/
//	Method 1 - Using a hashmap that stores the indices of the keys
//	Running time = O(n) 
//	Auxiliary space = O(n)
class Solution {
public:
	bool containsNearbyDuplicate(vector<int> &nums, int k) {
		unordered_map<int, int> mp;
		for(int i=0; i<nums.size(); i++) {
			if(mp.count(nums[i])) {
				if(abs(i - mp[nums[i]])<=k) return true;
			}
			mp[nums[i]] = i;			//	don't mention else here
		}								//	else is only to be mentioned if the if condn is written as if(mp.count(nums[i])&&abs(i - mp[nums[i]])<=k)
		return false;
	}
};


//	My Method 2 - Using a hashmap that stores the no. of occurrence of the keys and nested for loops
//	Running time = O(nk) i.e. quadratic (not efficient)
//	Auxiliary space = O(n)

class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int, int> mp;
        for(int i=0; i<nums.size(); i++) mp[nums[i]]++;
        for(int i=0; i<nums.size(); i++) {
            if(mp[nums[i]]>1) {
                for(int j=i+1; j<=i+k; j++) {
                    if(j==nums.size()) break;
                    if(nums[i]==nums[j]) return true;
                }
            }
        }
        return false;
    }
};