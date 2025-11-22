/*DP-Problem 3 (LC#1143) :
Given two strings text1 and text2, return the length of their longest common subsequence. If there is no
common subsequence, return 0. A subsequence of a string is a new string generated from the original string
with some characters (can be none) deleted without changing the relative order of the remaining characters.
For example, "ace" is a subsequence of "abcde".
A common subsequence of two strings is a subsequence that is common to both strings.

Example 1:
Input: text1 = "abcde", text2 = "ace"
Output: 3
Explanation: The longest common subsequence is "ace" and its length is 3.
Theory + Solution link : https://www.youtube.com/watch?v=sSno9rV8Rhg&ab_channel=AbdulBari

#IMP - It is one of the most important DP problems which can be used to solve other DP problems such as
the longest palindromic sequence, etc.
*/
//  Running time = O(mn) i.e. quadratic if memoization is used
//	else R.T. = O(2^n) i.e. exponential without memoization

//	1.	With memoization - O(mn) i.e. quadratic
class Solution {
public:
    int longestCommonSubsequence(string s1, string s2) {
        int m = s1.size();
        int n = s2.size();
        int DP[m+1][n+1];
        for(int j=0; j<=n; j++) DP[0][j] = 0;
        for(int i=0; i<=m; i++) DP[i][0] = 0;
        for(int i=1; i<=m; i++){
            for(int j=1; j<=n; j++){
                if(s1[i-1]==s2[j-1])		//	#IMPORTANT - Comparisons done on (i-1, j-1) for (i, j)
                    DP[i][j] = 1 + DP[i-1][j-1];	//	because the empty string is placed before the first characters
                else
                    DP[i][j] = max(DP[i][j-1], DP[i-1][j]);
            }
        }
        return DP[m][n];
    }
};

//	Topological Order (from bottom to up)
//	After all values the DP table have been calculated
int i = m; int j = n;
        stack<char> st;                     //  Use a stack or a vector<char> and then print it in reverse
        while(i>0 && j>0){
	        if(DP[i][j]==DP[i-1][j]) i--;
            else if(DP[i][j]==DP[i][j-1]) j--;
            else {
		        st.push(s1[i-1]);         	//  Push s1[i-1] and not s1[i] as empty string "" is not actually added to s1 and s2
		        i--; j--;
	        }        
        }
        while(!st.empty()){ 
            cout<<st.top();
            st.pop();
        }
        cout<<"\n";

//	2.	Using recursion same as that of DP without memoization - O(2^n) Exponential
int lcs(string s1, string s2, int i, int j){
        int m = s1.size();
        int n = s2.size();
        if(i==m||j==n) return 0;
        if(s1[i]==s2[j]) return 1+lcs(s1, s2, i+1, j+1);
        else return max(lcs(s1, s2, i+1, j), lcs(s1, s2, i, j+1));
    }

    int longestCommonSubsequence(string s1, string s2) {
        return lcs(s1, s2, 0, 0);
    }

