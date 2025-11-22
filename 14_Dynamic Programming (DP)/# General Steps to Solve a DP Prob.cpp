#General steps to solve a DP problem:
1. 	Figure out the most straightforward approach for solving a problem using recursion (generally, top down approach).
2. 	Now, try to optimize the recursive approach by storing the previous answers using memoization (generally, top down approach).
3. 	Finally, replace recursion by iteration using (generally bottom up) dynamic programming. (It is preferred to be done 
	in this manner because recursion generally has an increased space complexity as compared to iteration methods.)

i.e. 1. Rec w/o memo (TD)  ->  2. Rec with memo (Recursive DP) (TD)  ->  3. Iterative DP (BU)
	
Example: LCS (Longest common subsequence) (Leetcode #1143)

//	Method 1: Recursion without memoization (Top Down Approach)
//	Running time = O(2^n) i.e. exponential as we have either one (equal) or two (not equal) choices at each recursive call 
//	where n = s.size() and m = t.size() and n > m
//	Auxiliary space = O(2^n) due to the recursion stack
//	Test cases passed 16/44, gets TLE for rest

class Solution {
public:
    int rec(int n, int m, string s, string t) {
        if(n==0 || m==0) return 0;
        if(s[n-1]==t[m-1]) return 1 + rec(n-1, m-1, s, t);
        else return max(rec(n, m-1, s, t), rec(n-1, m, s, t));
    }
    
    int longestCommonSubsequence(string s1, string s2) {
        return rec(s1.size(), s2.size(), s1, s2);
    }
};

//	Method 2: Recursion with memoization i.e. Recursive DP (Top Down Approach)
//	Running time = O(n*m) i.e. quadratic as state depends on two variables i and j which vary from 0 to n-1 and 0 to m-1 
//	where n = s.size() and m = t.size() and n > m
//	Auxiliary space = O(n*m) due to the dp table as well as recursion stack
//	Test cases passed 42/44, but gets TLE for the rest

class Solution {		//	Method 2.1. DP table as a vector
public:
    int recDP(int n, int m, string s, string t, vector<vector<int>> &dp) {
        if(n==0 || m==0) return 0;
        if(dp[n-1][m-1]!=-1) return dp[n-1][m-1];
        if(s[n-1]==t[m-1]) dp[n-1][m-1] = 1 + recDP(n-1, m-1, s, t, dp);
        else dp[n-1][m-1] = max(recDP(n, m-1, s, t, dp), recDP(n-1, m, s, t, dp));
		return dp[n-1][m-1];
    }
    
    int longestCommonSubsequence(string s1, string s2) {
        int n = s1.size(), m = s2.size();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        return recDP(n, m, s1, s2, dp);
    }
};

class Solution {		//	Method 2.2. DP table as a map of pair<int,int> and int
public:
    //int recDP(int n, int m, string s, string t, vector<vector<int>> &dp) {
    int recDP(int n, int m, string s, string t, map<pair<int, int>, int> &dp) {
        if(n==0 || m==0) return 0;
        //if(dp[n-1][m-1]!=-1) return dp[n-1][m-1];
        if(dp.count({n-1, m-1})>0) return dp[{n-1, m-1}];
        if(s[n-1]==t[m-1]) //dp[n-1][m-1] = 1 + recDP(n-1, m-1, s, t, dp);
            dp[{n-1, m-1}] = 1 + recDP(n-1, m-1, s, t, dp);
        else //dp[n-1][m-1] = max(recDP(n, m-1, s, t, dp), recDP(n-1, m, s, t, dp));
            dp[{n-1, m-1}] = max(recDP(n, m-1, s, t, dp), recDP(n-1, m, s, t, dp));
        return dp[{n-1, m-1}];
    }
    
    int longestCommonSubsequence(string s1, string s2) {
        int n = s1.size(), m = s2.size();
        //vector<vector<int>> dp(n, vector<int>(m, -1));
        map<pair<int, int>, int> dp;
        return recDP(n, m, s1, s2, dp);
    }
};

//	Method 3.1.: Iterative DP (Bottom Up Approach) - Best Solution but slightly difficult to understand
//	Running time = O(n*m) due to the nested loop
//	Auxiliary space = O(n*m)
//	Passes all the test cases

class Solution {
public:
    int itrDP(string s, string t, vector<vector<int>> &dp) {
        int n = s.size(), m = t.size();
        for(int i=0; i<n; i++) dp[i][0] = 0;    //  When (i==0 || j==0) dp[i][j] = 0 which helps
        for(int j=0; j<m; j++) dp[0][j] = 0;    //  take care of base cases i.e. first row and column has value 0
        for(int i=1; i<=n; i++) {
            for(int j=1; j<=m; j++) {
                if(s[i-1]==t[j-1]) dp[i][j] = 1 + dp[i-1][j-1];
                else dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
            }
        }
        return dp[n][m];						//	Make sure to return dp[n][m] and not dp[n-1][m-1] as size of dp here is not n*m but (n+1)*(m+1)
    }
    
    int longestCommonSubsequence(string s1, string s2) {
        int n = s1.size(), m = s2.size();				//	Note that vector dp has size (n+1) * (m+1) 
        vector<vector<int>> dp(n+1, vector<int>(m+1));  //  No need to initialize each dp[i][j] = -1
        return itrDP(s1, s2, dp);                       //  There's no need of a separate function itrDP since its not recursive 
    }
};

//	Method 3.2.: Iterative DP (Not sure whether it is Top Down Approach or just Bottom Up Approach from the reverse)
//	Running time = O(n*m) due to the nested loop
//	Auxiliary space = O(n*m)
//	Passes all the test cases

class Solution {
public:
    int itrDP(string s, string t, vector<vector<int>> &dp) {
        int n = s.size(), m = t.size();
        for(int i=n; i>=0; i--) dp[i][m] = 0; 	//  When (i==n || j==m) dp[i][j] = 0 which helps
        for(int j=m; j>=0; j--) dp[n][j] = 0;   //  take care of base cases i.e. last row and column has value 0
        for(int i=n-1; i>=0; i--) {
            for(int j=m-1; j>=0; j--) {
                if(s[i]==t[j]) dp[i][j] = 1 + dp[i+1][j+1];
                else dp[i][j] = max(dp[i][j+1], dp[i+1][j]);
            }
        }
        return dp[0][0];						//	Make sure to return dp[0][0] and not dp[n][m] as it is a top down approach
    }
    
    int longestCommonSubsequence(string s1, string s2) {
        int n = s1.size(), m = s2.size();				//	Note that vector dp has size (n+1) * (m+1) 
        vector<vector<int>> dp(n+1, vector<int>(m+1));  //  No need to initialize each dp[i][j] = -1
        return itrDP(s1, s2, dp);
    }
};
