/* Stack Problem 3 - LC#739. Daily Temperatures
Given an array of integers temperatures represents the daily temperatures, return an array answer such that answer[i] 
is the number of days you have to wait after the ith day to get a warmer temperature. If there is no future day for 
which this is possible, keep answer[i] == 0 instead.

Example 1:
Input: temperatures = [73,74,75,71,69,72,76,73]
Output: [1,1,4,2,1,1,0,0]

Constraints:
1 <= t.length <= 10^5
30 <= t[i] <= 100
*/

//	Method 1 - Brute Force
//	Running time = O(n^2) for i : 0 to n-1 => j : i+1 to n-1
//	Auxiliary space = O(n) if a new vector is created else O(1) if the vector t is itself modified

//	Method 2 - Using a stack to store the index i.e. i of the value i.e. t[i]
//	There are three possible conditions
//		a.	if (S is empty) simply push the i into S
//		b. 	if (S is not empty and t[i] < t[S.top()]) we push i into the stack
//		c.	while (S is not empty and t[i] > t[S.top()]) we get ans[S.top()] = i - S.top() and then pop the top most element
//			when S becomes empty or t[i] is no longer > t[S.top()] we push i into the stack
//		So, for all the three conditions, we push i into S.
	
//	Running time = O(n) i.e. linear since we first traverse through the vector t once and then traverse in the stack from top to 
//	bottom i.e. R.T. = O(2*n) ~ O(n)
//	Auxiliary space = O(n) since the stack size may get as large as that of the vector t irrespective of the fact, whether
//	t is modified.

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& t) {
        int n = t.size();
        //vector<int> ans(n, 0);
        stack<int> S;						//	Stack stores the index i of each t[i]
        for(int i=0; i<n; i++) {
            while(!S.empty() && t[i] > t[S.top()]) {
                //ans[S.top()] = i - S.top();
                t[S.top()] = i - S.top();
                S.pop();
            }
            S.push(i);  					//  
        }               					//  b. if S is empty then we push i into the stack
        //return ans;     					//  c.
		while(!S.empty()) { 				//	Delete lines 39 to 43 if the ans vector is created separately
            t[S.top()] = 0;
            S.pop();
        }
        return t;
    }                    
};

//	Method 2b - Using a stack to store pairs as {t[i], i}. This is exactly same as method 2 except that stack here stores a pair instead of a value
//	Running time = O(n) 
//	Auxiliary space = O(n)

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& t) {
        int n = t.size();
        vector<int> ans(n, 0);
        stack<pair<int, int>> S;
        for(int i=0; i<n; i++) {
            while(!S.empty() && t[i] > S.top().first) {
                ans[S.top().second] = i - S.top().second;
                S.pop();
            }
            S.push({t[i], i});
        }
    return ans;
    }
};
