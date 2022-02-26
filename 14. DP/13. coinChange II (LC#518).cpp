/* DP-Problem 13 (LC#518) : Coin Change 2
Given an array of coins of different denominations and a total amount of money. Write a function to compute the 
number of combinations (not permutations) that make up that amount. You may assume that you have infinite number 
of each kind of coin.
Note - if A == 0 there is one way of making the amount that is to not pick any coins / pick the hypothetical coin
with value == 0

Example 1:
Input: amount = 5, coins = [1, 2, 5]
Output: 4
Explanation: there are four ways to make up the amount:
5=5
5=2+2+1
5=2+1+1+1
5=1+1+1+1+1
*/

//	1. 	DP (Tabulation) - 2D DP Table 
//		Best solution to understand the concept
//		Running time = O(nA) i.e. quadratic
//		Extra Space = O(nA)
class Solution {
public:
    int change(int A, vector<int>& c) {
        int n = c.size();
        vector<vector<int>> DP(n+1, vector<int>(A+1));
        for(int i = 0; i<=n; i++) DP[i][0] = 1;		//	Base case is slightly different here from unbounded knapsack problems
        for(int j=1; j<=A; j++) DP[0][j] = 0; 		// 	All except j==0
        for(int i=1; i<=n; i++){
            for(int j=1; j<=A; j++){
                if(c[i-1] <= j) DP[i][j] = DP[i-1][j] + DP[i][j-c[i-1]];
                else DP[i][j] = DP[i-1][j];
            }
        }
        return DP[n][A];
    }
};

//	2.	DP (Tabulation) - 2D DP Table (My Code)
//		Extra Base Case that if(A==0) return 1;
//		Running time = O(nA) i.e. quadratic
//		Extra Space = O(nA)
class Solution {
public:
    int change(int A, vector<int>& coins) {
        if(A==0) return 1;
        int n = coins.size();
        vector<vector<int>>DP(n+1, vector<int>(A+1));
        for(int i=0; i<=n; i++) DP[i][0] = 0;
        for(int j=0; j<=A; j++) DP[0][j] = 0;
        for(int i=1; i<=n; i++){
            for(int j=1; j<=A; j++){
                if(coins[i-1]<j)
                    DP[i][j] = DP[i-1][j] + DP[i][j-coins[i-1]];
                else if(coins[i-1]==j)
                    DP[i][j] = DP[i-1][j] + DP[i][j-coins[i-1]] + 1;
                else DP[i][j] = DP[i-1][j];
            }
        }
        return DP[n][A];
    }
};

//	3.	DP (Tabulation) - Uses only 1D array
//		However, the running time is still O(nA) i.e. O(nA/2) therefore slighty faster than methods 1 and 2.
//		Running time = O(nA) i.e. quadratic
//		Extra Space = O(nA)
//		Understand the solution however use the method 2 to solve this problem
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        vector<int> dp(amount + 1);
        dp[0] = 1;
        for (int c : coins) {
            for (int j = c; j <= amount; j++) dp[j] += dp[j - c];
        }
        return dp[amount];
    }
};