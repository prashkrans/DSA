/*	Hashmap Problem #13 - LC#599. Minimum Index Sum of Two Lists
Given two arrays of strings list1 and list2, find the common strings with the least index sum.
A common string is a string that appeared in both list1 and list2.
A common string with the least index sum is a common string such that if it appeared at list1[i] and list2[j] 
then i + j should be the minimum value among all the other common strings.
Return all the common strings with the least index sum. Return the answer in any order.

Example 1:

Input: list1 = ["Shogun","Tapioca Express","Burger King","KFC"], list2 = ["Piatti","The Grill at Torrey Pines","Hungry Hunter Steakhouse","Shogun"]
Output: ["Shogun"]
Explanation: The only common string is "Shogun".
Example 2:

Input: list1 = ["Shogun","Tapioca Express","Burger King","KFC"], list2 = ["KFC","Shogun","Burger King"]
Output: ["Shogun"]
Explanation: The common string with the least index sum is "Shogun" with index sum = (0 + 1) = 1.
Example 3:

Input: list1 = ["happy","sad","good"], list2 = ["sad","happy","good"]
Output: ["sad","happy"]
Explanation: There are three common strings:
"happy" with index sum = (0 + 1) = 1.
"sad" with index sum = (1 + 0) = 1.
"good" with index sum = (2 + 2) = 4.
The strings with the least index sum are "sad" and "happy".
*/

//	Method 1 - Using a hashmap (Best solution)
//	Running time = O(n) i.e. linear (O(n)) therefore the fastest
//	Auxiliary space = O(n)

class Solution {
public:
    vector<string> findRestaurant(vector<string>& list1, vector<string>& list2) {
        vector<string> ans;
		unordered_map<string, int> mp;
		int minVal = INT_MAX;
        for(int i=0; i<list1.size(); i++) mp[list1[i]] = i;  	//	The map stores a string as the key and its index as the value 
        for(int i=0; i<list2.size(); i++) {						//	if the current string from list2 is not present in the map then just move to the next string		
            if(mp.find(list2[i]) != mp.end()) {					// 	i.e. the current string from list2 is present in the map				
                if(i + mp[list2[i]] < minVal) {					//	if sum of indices is the minimum then erase all the strings previously added		
                    minVal = i + mp[list2[i]];					//	and add the current string from list2
                    ans.clear();
					ans.push_back(list2[i]);
                }
				else if(i + mp[list2[i]] == minVal) 
					ans.push_back(list2[i]);					// if the sum of indices is equal to the minimum then just add the curr string
            }
        }
        return ans;
    }
};

//	My Method 2 - Using two hashmaps (Exactly same as the method 1 but slightly slower)
//	Running time = O(n) i.e. linear (O(2n))
//	Auxiliary space = O(n)

class Solution {
public:
    vector<string> findRestaurant(vector<string>& list1, vector<string>& list2) {
        unordered_map<string, int> mp;
        unordered_map<string, int> mp2;
        for(int i=0; i<list1.size(); i++) {
            mp[list1[i]] = i;
        }
        int minVal = INT_MAX;
        for(int i=0; i<list2.size(); i++) {
            auto key = mp.find(list2[i]);
            if(key != mp.end()) {
                if(i + mp[list2[i]] <= minVal) {
                    minVal = i + mp[list2[i]];
                    mp2[list2[i]] = minVal;
                }
            }
        }
        vector<string> ans;
        for(auto i : mp2) {
            if(i.second==minVal) ans.push_back(i.first);
        }
        return ans;
    }
};

//	My Method 3 - Using two hashmaps and iterators (Exactly same as the method 1 but slightly slower)
//  Wrote this way to practice iterators (Could ignore this)
//	Running time = O(n) i.e. linear (O(2n))
//	Auxiliary space = O(n)

class Solution {
    public:
        vector<string> findRestaurant(vector<string>& list1, vector<string>& list2) {
            unordered_map<string, int> uMap;
            unordered_map<int, vector<string>> mp;
            int index = 0;
            for(vector<string>::iterator it = list1.begin(); it != list1.end(); it++) uMap[*it] = index++; // First loop
            index = 0;
            for(vector<string>::iterator it = list2.begin(); it != list2.end(); it++) { // Second loop
                if(uMap.count(*it)) {
                    int sumIndex = index + uMap[*it];
                    mp[sumIndex].push_back(*it);
                }
                index++;
            }
            int min_index = INT_MAX;
            vector<string> ans; // This loop could actually included in the second loop itself.
            for(unordered_map<int, vector<string>>::iterator it = mp.begin(); it != mp.end(); it++) {
                if(it->first < min_index) {
                    min_index = it->first;
                    ans = it->second;
                }
            }
            return ans;        
        }
    };



// 	My Method 4 - Without using hashmaps and somewhat similar to DP
//	Running time = O(n^2) i.e. quadratic and thus not the best solution but an intuitive one
//	Auxiliary space = O(n^2)

class Solution {
public:
    vector<string> findRestaurant(vector<string>& list1, vector<string>& list2) {
        int n = list1.size();
        int m = list2.size();
        vector<vector<int>> c(n, vector<int>(m, INT_MAX));
        for(int i=0; i<n; i++) {
            for(int j=0; j<m; j++) {
                if(list1[i] == list2[j]) c[i][j] = i + j;
            }
        }
        int minVal = INT_MAX;
        for(int i=0; i<n; i++) {
            for(int j=0; j<m; j++) {
                if(c[i][j]<minVal) minVal = c[i][j];
            }
        }
        vector<string> ans;
        for(int i=0; i<n; i++) {
            for(int j=0; j<m; j++) {
                if(c[i][j] == minVal) ans.push_back(list1[i]);
            }
        }
        return ans;
    }
};