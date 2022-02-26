/* DP-Problem 5 : 0-1 Knapsack problem
Given the value and size/weight of n items and the capacity (m) of a knapsack. Maximise the
value of items picked in the knapsack.
*/

//  Running time = O(nm)
//  Space complexity = O(nm)

#include<iostream>
#include<vector>
using namespace std;

int zeroOneKnapsack(int n, vector<int> v, vector<int> w, int m) {
    vector<vector<int>> DP(n+1, vector<int>(m+1));
    vector<int> M(m+1);
    for(int j=0; j<m+1; j++) M[j] = j;
    for(int i=0; i<n+1; i++){
        for(int j=0; j<m+1; j++){
            if(i==0||j==0)          //  First row and column has value == 0 for all the cells
                DP[i][j] = 0;
            else if(w[i-1]<=M[j])
                DP[i][j] = max(DP[i-1][j], DP[i-1][j-w[i-1]]+v[i-1]);
            else if(w[i-1]>M[j])    //  Note - For a given (i,j) we use v[i-1] and w[i-1] and M[j]
                DP[i][j] = DP[i-1][j];  //  because we've not added 0 at the beginning of vectors v and w
        }                               //  while M[0]==0 for the vector M
    }
    return DP[n][m];
}

int main(){
	int n;
	cin>>n;
	vector<int> v(n);
	vector<int> w(n);
	int capacity;
	cin>>capacity;
	for(int i=0; i<n; i++) cin>>v[i];
	for(int i=0; i<n; i++) cin>>w[i];
    cout<<zeroOneKnapsack(n, v, w, capacity);
	return 0;
}
