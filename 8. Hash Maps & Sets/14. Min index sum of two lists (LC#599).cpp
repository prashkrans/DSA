/*	Hashmap Problem #13 - LC#599. Minimum Index Sum of Two Lists
Suppose Andy and Doris want to choose a restaurant for dinner, and they both have a list of favorite 
restaurants represented by strings. You need to help them find out their common interest with the least 
list index sum. If there is a choice tie between answers, output all of them with no order requirement. 
You could assume there always exists an answer.

Example 1:
Input: list1 = ["Shogun","Tapioca Express","Burger King","KFC"], list2 = ["Piatti","The Grill at Torrey 
Pines","Hungry Hunter Steakhouse","Shogun"]
Output: ["Shogun"]
Explanation: The only restaurant they both like is "Shogun".

Example 2:
Input: list1 = ["Shogun","Tapioca Express","Burger King","KFC"], list2 = ["KNN","KFC","Burger King",
"Tapioca Express","Shogun"]
Output: ["KFC","Burger King","Tapioca Express","Shogun"]
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


// 	My Method 3 - Without using hashmaps and somewhat similar to DP
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