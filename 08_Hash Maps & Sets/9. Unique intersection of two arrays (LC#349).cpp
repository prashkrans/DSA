/*	Hashmap Problem #8 - LC#349. Intersection of Two Arrays
Given two integer arrays nums1 and nums2, return an array of their intersection. Each element 
in the result must be unique and you may return the result in any order.

Example 1:
Input: nums1 = [1,2,2,1], nums2 = [2,2]
Output: [2]
*/
// 	Running time = O(m+n)
//	Auxiliary space = O(m) if m>n or O(n) if n>m

class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> umap;
        vector<int> ans;
        for(auto i : nums1) {
            umap[i]++;			// 	Map all the elements of the array 1 in umap with their occurrences 
        }
        for(auto i : nums2) {	//	Check whether an element of the array 2 is present in the umap
            if(umap.count(i)==1 && umap[i]>0) {	//	If it does add it to the answer array and make the value of that key = 0
                ans.push_back(i);
                umap[i] = 0;
            }
        }
        return ans;
    }
};