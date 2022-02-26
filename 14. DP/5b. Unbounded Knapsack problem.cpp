/* DP-5b : Unbounded Knapsack Problem 
Given a knapsack weight W and a set of n items with certain value vi and weight wti, 
we need to calculate the maximum amount that could make up this quantity exactly such
that that sum of values of items selected is maximum. 
This is different from classical 0/1 Knapsack problem, as here we are allowed to use 
unlimited number of instances of an items i.e. repetitions of items are allowed.
*/
//	1.	DP - Tabulation (Top Down Approach)
//		Running Time = O(nm) or O(nW)
//		Extra Space = O(nm) or O(nW)
int unboundedKnapsack(vector<int> v, vector<int> w, int W) {
    int n = v.size();
    vector<vector<int>> DP(n+1, vector<int>(W+1));
    vector<int> arrW(W+1);
    for(int j=0; j<=W; j++) arrW[j] = j;
    for(int i=0; i<=n; i++){
        for(int j=0; j<=W; j++){
            if(i==0||j==0) 
                DP[i][j] = 0;
            else if(w[i-1]<=arrW[j]) 
                DP[i][j] = max(DP[i-1][j], DP[i][j-w[i-1]]+v[i-1]);
            else 
                DP[i][j] = DP[i-1][j];
        }
    }
    return DP[n][m];
}

//	1b. DP - Tabulation (Top Down Approach) 
//		Same as above but here the vector wi = vector vi i.e. the weight itself is the value
//		Running Time = O(nm) or O(nW)
//		Extra Space = O(nm) or O(nW)
#include<iostream>
#include<vector>
using namespace std;

int unboundedKnapsack(int m, vector<int> v) {
    int n = v.size();
    vector<vector<int>> DP(n+1, vector<int>(m+1));
    vector<int> W(m+1);
    for(int i=0; i<m+1; i++) W[i] = i;
    for(int i=0; i<n+1; i++){
        for(int j=0; j<m+1; j++){
            if(i==0||j==0) 
                DP[i][j] = 0;
            else if(v[i-1]<=W[j]) 
                DP[i][j] = max(DP[i-1][j], DP[i][j-v[i-1]]+v[i-1]);
            else 
                DP[i][j] = DP[i-1][j];
        }
    }
    return DP[n][m];
}

int main(){
    int T;
    cin>>T;
    while(T--){
        int n, m;
        cin>>n>>m;
        vector<int> v(n);
        for(int i=0; i<n; i++) cin>>v[i];
        cout<<unboundedKnapsack(m, v)<<"\n";
    }
}

//	2. DP as a vector 1D