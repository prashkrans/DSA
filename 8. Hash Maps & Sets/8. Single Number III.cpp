/* Hashmap Problem #6 - (LC#260 : Single Number III)
Given an integer array nums, in which exactly two elements appear only once and all the other elements appear 
exactly twice. Find the two elements that appear only once. You can return the answer in any order.
You must write an algorithm that runs in linear runtime complexity and uses only constant extra space.
*/
//	Running time = O(n)
//	Auxiliary Space = O(n)

class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        unordered_map<int, int> umap;
        vector<int> ans;
        for(auto i : nums) {
            umap[i]++;
        }
        unordered_map<int, int>::iterator it;
        for(it = umap.begin(); it!=umap.end(); it++) if(it->second==1) ans.push_back(it->first);
        return ans;
    }
};