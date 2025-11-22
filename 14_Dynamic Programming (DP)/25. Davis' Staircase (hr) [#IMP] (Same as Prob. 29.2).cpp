/* DP #25. Davis' Staircase
Davis has a number of staircases in his house and he likes to climb each staircase 1, 2, or 3 steps at a time.
Being a very precocious child, he wonders how many ways there are to reach the top of the staircase.
*/

//  Method 1. Using memoization or DP array
//  Running time = O(n) [Verify]
//  Auxiliary space = O(n) due to the dp array

#include <bits/stdc++.h>
using namespace std;

int rec(int n, vector<int> &dp) {
    if(n<0) return 0;
    else if(n>=0 && dp[n]==-1) {
        if(n==0) {
            dp[n] = 1;
            return 1;
        }
        dp[n] = rec(n-1, dp) + rec(n-2, dp) + rec(n-3, dp);
    }
    return dp[n];
}

int stepPerms(int n) {
    vector<int> dp(n+1, -1);
    dp[n] = rec(n, dp);
    //for(auto i : dp) cout<<i<<" "; cout<<"\n";
    return dp[n];
}

int main() {
    int t;
    cin>>t;
    while(t--) {
        int n;
        cin>>n;
        cout<<"No. of ways to climb = "<<stepPerms(n)<<"\n";
    }
    return 0;
}

//  Method 2. Recursion without memoization
//  Running time = O(3^n) i.e. exponential thus inefficient
//  Auxiliary space = O(1) i.e. constant space

int stepPerms(int n) {
    if(n<0) return 0;
    else if(n==0) return 1;
    else
        int val = stepPerms(n-1) + stepPerms(n-2) + stepPerms(n-3);
    return val;
}
