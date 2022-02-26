/* Hashmap Problem - 5 (LC#137: Single Number II)
Given an integer array nums where every element appears three times except for one, which appears exactly 
once. Find the single element and return it.
You must implement a solution with a linear runtime complexity and use only constant extra space.
*/
//	Running time = O(n)
//	Auxiliary space = O(n)

class Solution {
public:
    int singleNumber(vector<int>& nums) {      
        unordered_map<int, int> umap;
        for(auto i : nums) {
            umap[i]++;
        }
        unordered_map<int, int>::iterator it;
        for(it = umap.begin(); it!=umap.end(); it++) if(it->second==1) break;
        return it->first;
    }
};