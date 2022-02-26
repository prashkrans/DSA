/*	Hashmap Problem #14 - LC#387. First Unique Character in a String
Given a string s, return the first non-repeating character in it and return its index. 
If it does not exist, return -1.

Example 1:
Input: s = "leetcode"
Output: 0

Example 2:
Input: s = "loveleetcode"
Output: 2

Example 3:
Input: s = "aabb"
Output: -1
*/

//	My Method 1 - Using a hashmap (Best Solution)
//	Running time = O(n) i.e. linear (O(2n) since we go through the string of length n two times)
//	Extra space = O(n) 

class Solution {
public:
    int firstUniqChar(string s) {
        unordered_map<char, int> mp;
        for(int i=0; i<s.size(); i++) mp[s[i]]++;
        for(int i=0; i<s.size(); i++) if(mp[s[i]]==1) return i;     
        return -1;
    }
};

//	Method 2 - Using an array[26] as a hashmap given the constraint that s only contains lowercase English letters
//	ASCII code for lower case english letters varies from 97 to 122 (no need to learn it)
//	Running time = O(n) i.e. linear (O(2n) since we go through the string of length n two times)
//	Extra space = O(1) as it requires an array of size 26 i.e. constant space

class Solution {
public:
    int firstUniqChar(string s) {
        int arr[26] = {0};
        for(int i=0; i<s.size(); i++) arr[s[i]-'a']++;
        for(int i=0; i<s.size(); i++) if(arr[s[i]-'a'] == 1) return i;
        return -1;
    }
};

/* This is a problem of scenario II - Aggregate by key
The template to solve these set of problems is: 

ReturnType aggregateByKey_hashmap(vector<Type>& keys) {
    // Replace Type and InfoType with actual type of your key and value
    unordered_map<Type, InfoType> hashtable;
    for (Type key : keys) {
        if (hashmap.count(key) > 0) {
            update hashmap[key];
        }
        // Value can be any information you needed (e.g. index)
        hashmap[key] = value;
    }
    return needed_information;
}
*/
