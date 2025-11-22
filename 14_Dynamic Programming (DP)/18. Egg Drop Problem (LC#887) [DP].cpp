/* DP Problem 18 - Egg Dropping Problem (LC#887 - Super Egg Drop)
Given m identical eggs and a building with n floors labeled 1 to n. There exists a critical/threshold floor such that
any egg dropped at a floor higher than k will break & any egg dropped at or below floor k will not break.
If the egg breaks it cannot be used again but it may be reused if it does not break.
Return the minimum number of moves that we need to determine with certainty what the value of k is i.e. minimum no. of
moves for the worst case scenario.
Eg. for m = 3, n = 14 => ans = 4
Eg. for m = 2, n = 100 => ans = 14 (Popular puzzle)
*/
//  Running time = O(mn^2) i.e. cubic
//  Extra space = O(m*n)


#include<iostream>
#include<vector>
using namespace std;

int eggDrop(int m, int n){
    vector<vector<int>> DP(m+1, vector<int>(n+1));
        for(int i=1; i<=m; i++){
            for(int j=1; j<=n; j++){
                if(i==1) DP[i][j] = j;
                else if(i>j) DP[i][j] = DP[i-1][j];
                else{
                    int minVal = INT_MAX;
                    for(int k=1; k<=j; k++){
                        int kVal = 1 + max(DP[i-1][k-1], DP[i][j-k]);
                        if(kVal < minVal) minVal = kVal;
                    }
                    DP[i][j] = minVal;
                }
            }
        }
    for(int i=0; i<=m; i++){
        for(int j=0; j<=n; j++) cout<<DP[i][j]<<" ";
        cout<<"\n";
    }
    return DP[m][n];
}

int main(){
cout<<"Enter the value of m i.e. number of eggs \nand n i.e. number of floors = ";
int m, n; cin>>m>>n;
cout<<"The DP table is = \n";
int ans = eggDrop(m, n);
cout<<"The minimum no. of tries for the worst case is = \n";
cout<<ans;
return 0;
}
