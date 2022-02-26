/*	Hashmap Problem #20 - LC#3. Longest Substring Without Repeating Characters
Given a string s, find the length of the longest substring without repeating characters.

Constraints:
0 <= s.length <= 5 * 104
s consists of English letters, digits, symbols and spaces.

Example 1:
Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.

Example 2:
Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.

Example 3:
Input: s = ""
Output: 0
*/

//	Method 1 - Scenario I + Sliding window approach
//	Running time = O(n)
//	Auxiliary space = O(n)

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.size();
        unordered_map<char, int> mp;
        int ans = 0;
        int i=0, j=0;                       //  i points to the start of the substring while j points to the end
        while(j<n) {
            if(mp.count(s[j])) {
                i = max(i, mp[s[j]]+1);     //  Because we don't want i to move backwards/leftwards    
            }                               //  hence use max(i, mp[s[j]]+1) as mp[s[j]+1] can be less than i too
            mp[s[j]] = j;                   //  first entry or to update the index of s[j]
            ans = max(ans, j - i + 1);            
            j++;                            
        }
        return ans;
    }
};
