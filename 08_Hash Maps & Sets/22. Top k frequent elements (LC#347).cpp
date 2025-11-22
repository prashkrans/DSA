/*	Hashmap Problem #20 - LC#347. Top K Frequent Elements
Given an integer array nums and an integer k, return the k most frequent elements. 
You may return the answer in any order. 

Constraints:
1 <= nums.length <= 105
k is in the range [1, the number of unique elements in the array].
It is guaranteed that the answer is unique. 

Example 1:
Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]

Example 2: [IMP]
Input: [4,1,-1,2,-1,2,3], k = 2
Output: [-1,2]
*/
//	Method 1 - Hoare's selection algorithm 
//	Running time = O(n) in average cases and O(n^2) in worst case (but the probability is neglegible)
//	Auxiliary space = O(n)
//	Refer - https://leetcode.com/problems/top-k-frequent-elements/solution/

// 	Method 2 - Using a hashmap and a heap 
//	Running time = O(nlogk)
//	Auxiliary space = O(n)

//	My Method 3 - Using a hashmap only 
//	Running time = O(nk) i.e. quadratic
//	Auxiliary space = O(n)

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        if(k==nums.size()) return nums;					// 	[IMP] as it makes the case faster i.e. O(1)
        unordered_map<int, int> mp;
        vector<int> ans;
        for(int i=0; i<nums.size(); i++) mp[nums[i]]++;
        vector<int> a;
        for(auto i : mp) a.push_back(i.second);
        sort(a.begin(), a.end(), greater<int>());		//	Sorted the array in descending order
        //for(int i=0; i<a.size(); i++) cout<<a[i]<<" ";
        //cout<<"\n";
        for(int i=0; i<k; i++) {						// 	O(k*n)
            for(auto j : mp) {
                if(j.second == a[i]) {
                    ans.push_back(j.first);				
                    mp.erase(j.first);					// 	Note to erase the key from the map else it keeps returning the same key for different keys with the same values
                    break;								//	Break the for loop once the value has been found else results in redundant values being fed to the ans array
                }
            }
        }
        return ans;
    }
};