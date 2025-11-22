/*	Hashmap Problem #12 - LC#205. Isomorphic Strings
Given two strings s and t, determine if they are isomorphic.
Two strings s and t are isomorphic if the characters in s can be replaced to get t.
All occurrences of a character must be replaced with another character while preserving 
the order of characters. No two characters may map to the same character, but a character may map to itself.

Example 1:
Input: s = "egg", t = "add"
Output: true

Example 2:
Input: s = "foo", t = "bar"
Output: false
*/

//	1. Using two hashmaps i.e. one for mapping characters from s to t and the other for keeping a record if a character
//	from t has already been mapped/visited or not.
//	The mapping here basically requires two conditions to be fullfilled
//	a.	each character from s maps to a unique character of t
//	b. 	each character from s maps to a single character of t
//	Running time = O(n) as it reduces O(n^2) of condition b. to O(n)
//	Extra space = O(n)

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        unordered_map<char, char> mp1;
        unordered_map<char, int> mp2;					// Value = 1 or 0 i.e. visited or not visited
        for(int i=0; i<s.size(); i++) {
            auto currKey = mp1.find(s[i]);
            if(currKey!=mp1.end()) {
                if(currKey->second!=t[i]) return false;	//	Condition a. same as that of method 2 but written using .find() function
            }
            else {
                mp1[s[i]] = t[i];
                auto currKey2 = mp2.find(t[i]);			//	Condition b. i.e. checks whether a char of t has already been mapped or not
                if(currKey2 != mp2.end()) {				//	If it has already been mapped then it cannot be mapped to another char of s
                    return false;
                }	
                else mp2[t[i]] = 1;      				// Since it is being mapped for the first time making its value = 1 i.e. visited          
            }
        }
        return true;
    }
};

// 	2. My Method - Uses a single hashmap but has a quadratic running time due to value search
//	Running time = O(n^2)
//	Extra space = O(n)

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        unordered_map<char, char> mp;
        for(int i=0; i<s.size(); i++) {
            if(mp.count(s[i])>0) {
                if(mp[s[i]]!=t[i]) 						//	Condition a. same as that of method 1 but written using .count() function
                    return false;                
            }
            mp[s[i]] = t[i];
        }
        for(auto i : mp) {
            cout<<i.first<<" "<<i.second<<"\n";
        }
        if(mp.size()>1) {
            for(auto it = mp.begin(); it!=mp.end(); it++) {
                char value = it->second;
                int count = 0;
                unordered_map<char, char>:: iterator it2 = it;
                while(it2!=mp.end()) {
                    if(it2->second == value) count++;	
                    it2++;
                }
                if(count>1) return false;				//	Condition b. but this O(n^2)
            }
        }
        return true;
    }
};