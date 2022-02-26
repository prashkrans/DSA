/* DP Problem 18 - Egg Dropping Problem (LC#887 - Super Egg Drop)
Given m identical eggs and a building with n floors labeled 1 to n. There exists a critical/threshold floor such that
any egg dropped at a floor higher than k will break & any egg dropped at or below floor k will not break.
If the egg breaks it cannot be used again but it may be reused if it does not break.
Return the minimum number of moves that we need to determine with certainty what the value of k is i.e. minimum no. of
moves for the worst case scenario.
Eg. for m = 3, n = 14 => ans = 4
Eg. for m = 2, n = 100 => ans = 14 (Popular puzzle)
*/
//  Running time = O(mn*logn) i.e. faster than cubic (accepted by leetcode)
//  Extra space = O(m*n)


#include<iostream>
#include<vector>
using namespace std;

int eggDrop(int m, int n) {
    vector<vector<int>> DP(m+1, vector<int>(n+1));
        for(int j=1; j<=n; j++) DP[1][j] = j;
        for(int i=2; i<=m; i++) {
            for(int j=1; j<=n; j++){
                if(i>j) DP[i][j] = DP[i-1][j];
                else {                              //  Instead of varying k from 1 to j i.e. O(n)
                    int low = 1;                    //  we use binary search to find midK such that 1+max(DP[i-1][k-1], DP[i][j-k]) is minimum
                    int high = j;                   //  thus O(n) for linear search is reduced to O(logn) for a binary search
                    while(low+1<high){
                        int midK = (low+high)/2;
                        int t1 = DP[i-1][midK-1];    //  t1 is an increasing function
                        int t2 = DP[i][j-midK];      //  t2 is an decreasing function
                        if(t1<t2) low = midK;
                        else if(t1>t2) high = midK;
                        else if(t1==t2) low = high = midK;  //  Note - midK is value of k s.t. 1+max() is minimum
                    }                                       //  But what if there are only two values of k, then midK is always low which is incorrect
                    DP[i][j] = 1 + min(max(DP[i-1][low-1], DP[i][j-low]), max(DP[i-1][high-1], DP[i][j-high]));
                }   //  when there are only two possible values of midK, we need to check both.
            }       //  thus using the above formula instead of DP[i][j] = 1 + max(DP[i-1][midK-1], DP[i][j-midK]);
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
