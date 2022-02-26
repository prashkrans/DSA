/* Hashset problem 4 - LC#136: Single Number
Given a non-empty array of integers nums, every element appears twice except for one. Find that single one.
You must implement a solution with a linear runtime complexity and use only constant extra space.
*/
//  Running time = O(n)
//  Extra Space = O(n)
//  Method 1 - using an unordered set
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int n = nums.size();
        if (n==1) return nums[0];
        else {
            unordered_set<int> s;
            for(auto i : nums) {
                if(s.count(i)==0) s.insert(i);
                else s.erase(i);        //  i.e. if an element is already present delete it
            }
            auto it = s.begin();        //  or unordered_set<int>::iterator it = s.begin();
            return *it;
        }
    }
};

//  Method 2 - using an unordered map
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
