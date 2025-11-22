/* Stack Prob. #14 (LC#84): Largest Rectangle in a Histogram
Given an array of integers heights representing the histogram's bar height where the width of each bar is 1, return the 
area of the largest rectangle in the histogram.

Uses the concept of "near smaller element" to the right and left i.e. nseL and nseR. Stack just helps to find nseL and nseR 
for an element at i in O(1) instead of O(n) for a regular search. 
*/


// 	Method 1: Naive Solution – R.T. = O(n^2)
//	Method 2: Using stacks to find left and right bounds in O(1) instead of O(N) thus R.T. =  O(3n) ~ O(n).
//	Steps: 
//	1. 	Get the left and right bound of the current index i
//		Traverse from l to r while finding left[i] and for each i do:
//		... two cases 1 - while | 2 - no while but +1  and both push[i]
//	2. 	Area with index i = (right[i] - left[i] + 1)*height[i] and print the maxArea.
//	Running time = O(3n) ~ O(n)
//	Auxiliary space = O(n) due to the stack

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);		//	Can ignore, but used for fast inputs and outputs
        int n = heights.size();
        vector<int> left(n, 0), right(n, 0);
        stack<int> S;
        for(int i=0; i<n; i++) {
            if(S.empty()) {
                left[i] = 0;
                S.push(i); 
            }
            else {
                while(!S.empty() && heights[S.top()]>=heights[i])
                    S.pop();
                if(S.empty()) left[i] = 0;
                else left[i] = S.top()+1;
                S.push(i);            
            }
        }
        while(!S.empty()) 
            S.pop();
        for(int i=n-1; i>=0; i--) {
            if(S.empty()) {
                right[i] = n-1;
                S.push(i); 
            }
            else {
                while(!S.empty() && heights[S.top()]>=heights[i])
                    S.pop();
                if(S.empty()) right[i] = n-1;
                else right[i] = S.top()-1;
                S.push(i);            
            }
        }
        //cout<<"Left = "; for(auto i : left) cout<<i<<" "; cout<<"\n";
        //cout<<"Right = "; for(auto i: right) cout<<i<<" "; cout<<"\n";
        int height, width, currArea, maxArea = -1;
        for(int i=0; i<n; i++) {
            width = right[i] - left[i] + 1;
            height = heights[i];
            int currArea = width*height;
            maxArea = max(maxArea, currArea);
        }
        return maxArea;
    }
};