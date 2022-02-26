/*	Hashmap Problem #19 - LC#771. Jewels and Stones
You're given strings jewels representing the types of stones that are jewels, and stones representing 
the stones you have. Each character in stones is a type of stone you have. You want to know how many 
of the stones you have are also jewels.
Letters are case sensitive, so "a" is considered a different type of stone from "A".

Example 1:
Input: jewels = "aA", stones = "aAAbbbb"
Output: 3

Example 2:
Input: jewels = "z", stones = "ZZ"
Output: 0
*/

//	Method 1 - Using a hashmap
//	Running time = O(m+n)
//	Auxiliary space = O(n);

class Solution {
public:
    int numJewelsInStones(string jewels, string stones) {
        unordered_map<char, int> mp;
        int sum = 0;
        for(int i=0; i<stones.size(); i++) mp[stones[i]]++;
        for(int i=0; i<jewels.size(); i++) {
            if(mp.count(jewels[i])) sum += mp[jewels[i]];
        }
        return sum;
    }
};