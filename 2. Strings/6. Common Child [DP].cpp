/* 6. Common Child
A string is said to be a child of a another string if it can be formed by deleting 0 or more characters from the other string. 
Letters cannot be rearranged. Given two strings of equal length, what's the length of the longest string that can be constructed 
such that it is a child of both?

Note: This is the exact problem of longest common subsequence (LCS).

Example 1:
s1 = "ABCD";
s2 = "ABDC";
These strings have two children with maximum length 3, ABC and ABD. They can be formed by eliminating either the D or C from 
both strings => Return 3.
*/

//	Method 1. Recursion without memoization (In this problem we get TLE)
//	Running time = O(2^n) if n > m where n = s1.size() and m = s2.size(); Thus, inefficient.
//	Auxiliary space = O(1)

int lcs(string s1, string s2, int i, int j) {
        int m = s1.size();
        int n = s2.size();
        if(i==m||j==n) return 0;
        if(s1[i]==s2[j]) return 1+lcs(s1, s2, i+1, j+1);
        else return max(lcs(s1, s2, i+1, j), lcs(s1, s2, i, j+1));
}

int commonChild(string s1, string s2) {
    return lcs(s1, s2, 0, 0);
}

//	Method 2. DP (Best Solution)
//	Running time = O(n*m) where n = s1.size() and m = s2.size();
//	Auxiliary space = O(n*m) due to the DP table

int commonChild(string s1, string s2) {
     int n = s1.size(), m = s2.size();
     vector<vector<int>> DP(n+1, vector<int>(m+1, 0));
     for(int i=1; i<n+1; i++) {
         for(int j=1; j<m+1; j++) {
             if(s1[i-1]==s2[j-1]) DP[i][j] = 1 + DP[i-1][j-1];
             else DP[i][j] = max(DP[i-1][j], DP[i][j-1]);
         }
     }
     return DP[n][m];
}
