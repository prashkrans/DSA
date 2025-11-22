/*	Hashmap Problem #9 - LC#350. Intersection of Two Arrays II
Given two integer arrays nums1 and nums2, return an array of their intersection. Each element in the 
result must appear as many times as it shows in both arrays and you may return the result in any order.

Example 1:
Input: nums1 = [1,2,2,1], nums2 = [2,2]
Output: [2, 2]
*/
//	My Method 1 - Using a hashmap and not using auto
// 	Running time = O(m+n)
//	Auxiliary space = O(m) i.e. the size of map only depends upon the size of the first array nums1

class Solution {
    public:
        vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
            unordered_map<int, int> uMap;
            vector<int> ans;
            for(int i=0; i<nums1.size(); i++) uMap[nums1[i]]++;
            for(int i=0; i<nums2.size(); i++) {
                if(uMap[nums2[i]] > 0) {
                    ans.push_back(nums2[i]);
                    uMap[nums2[i]]--;
                }
            }
            return ans;
        }
};

//	My Method 2 - Using a hashmap and using auto (just to illustrate the use of auto)
// 	Running time = O(m+n)
//	Auxiliary space = O(m) i.e. the size of map only depends upon the size of the first array nums1

class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> mp;
        vector<int> ans;
        for(auto i : nums1) mp[i]++;
        for(auto i : nums2) {
            if(mp.find(i) != mp.end() && mp[i]>0) {
                ans.push_back(i);
                mp[i]--;
            }
        }
        return ans;
    }
};