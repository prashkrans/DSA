/*	Hashmap Problem #16 - LC#49. Group Anagrams
Given an array of strings strs, group the anagrams together. You can return the answer in any order.
An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase, typically 
using all the original letters exactly once.
strs[i] consists of lower-case English letters.

Example 1:
Input: strs = ["eat","tea","tan","ate","nat","bat"]
Output: [["bat"],["nat","tan"],["ate","eat","tea"]]

Example 2:
Input: strs = [""]
Output: [[""]]
*/

// 	Method 1 - 
//	Intuition: Two strings are anagrams if and only if their sorted strings are equal.
//	Algorithm: Maintain a map ans : {String -> List} where each key K is a sorted string, and each 
//	value is the list of strings from the initial input that when sorted, are equal to K
//	Running time = O(NKlogK), where N is the length of strs, and K is the maximum length of a 
//	string in strs. The outer loop has complexity O(N) as we iterate through each string. Then, 
//	we sort each string in O(Klog K) time.
//	Auxiliary space = O(NK), the total information content stored in ans.

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> mp;   //  This is the most important thing that we declare an unordered map
        vector<vector<string>> ans;                 //  that takes key as a string and value as a vector<string>
        for(int i=0; i<strs.size(); i++) {          //  i.e. "aet" => {"eat", "tea", "ate"}
            string s = strs[i];
            sort(s.begin(), s.end());               //  Here the key is a sorted string 
            mp[s].push_back(strs[i]);               //  Note - don't write mp[s] = strs[i] as it will store only the last strs[i] encountered 
        }                                           //  thus, mp[s].push_back is used
        /*for(auto i : mp) {
            for(int j=0; j<i.second.size(); j++) cout<<i.second[j]<<" ";
            cout<<"\n";
        }*/
        for(auto i : mp) {
            vector<string> ss;
            for(int j=0; j<i.second.size(); j++) {
                ss.push_back(i.second[j]);
            }
            ans.push_back(ss);
        }
        return ans;
    }
};
