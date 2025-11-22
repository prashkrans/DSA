/* DP Problem 18 - Egg Dropping Problem (LC#887 - Super Egg Drop)
Given m identical eggs and a building with n floors labeled 1 to n. There exists a critical/threshold floor such that
any egg dropped at a floor higher than k will break & any egg dropped at or below floor k will not break.
If the egg breaks it cannot be used again but it may be reused if it does not break.
Return the minimum number of moves that we need to determine with certainty what the value of k is i.e. minimum no. of
moves for the worst case scenario.
Eg. for m = 3, n = 14 => ans = 4
Eg. for m = 2, n = 100 => ans = 14 (Popular puzzle)
*/
//  Running time = Exponential (Each pair of (m,n) has n branches i.e. k = 1 to n with each branch having 2 choices)
//  Extra space = O(1), as there was no use of any data structure for storing values.


#include<iostream>
#include<vector>
using namespace std;

int eggDrop(int m, int n){
    if(m==1) return n;
    if(n==0||n==1) return n;
    if(m>n) return eggDrop(m-1, n);
    int minVal = INT_MAX;
    for(int k=1; k<=n; k++){
        int kVal = 1+max(eggDrop(m-1, k-1), eggDrop(m, n-k));
        if(kVal<minVal) minVal = kVal;
    }
    return minVal;
}

int main(){
cout<<"Enter the value of m i.e. number of eggs = ";
int m; cin>>m;
cout<<"Enter the value of n i.e. number of floors = ";
int n; cin>>n;
cout<<"The minimum no. of tries for the worst case is = ";
cout<<eggDrop(m, n);
return 0;
}
