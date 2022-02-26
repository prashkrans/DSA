/* Graph problem 31c. LC#909. Snakes and Ladders
Given a 5x6 snakes and ladders board, find the minimum number of dice throws required to reach the destination or last cell
(30th cell) from the source (1st cell).
You are given an integer N denoting the total number of snakes and ladders and an array arr[] of 2*N size where 2*i and (2*i + 1)th 
values denote the starting and ending point respectively of ith snake or ladder. The board looks like the following.
https://practice.geeksforgeeks.org/problems/snake-and-ladder-problem4816/1#

Example 1:
Input:
N = 8
arr[] = {3, 22, 5, 8, 11, 26, 20, 29, 17, 4, 19, 7, 27, 1, 21, 9}
Output: 3
Explanation:
The given board is the board shown
in the figure. For the above board 
output will be 3. 
a) For 1st throw get a 2. 
b) For 2nd throw get a 6.
c) For 3rd throw get a 2.

Constraints:
1 ≤ N ≤ 10
1 ≤ arr[i] ≤ 30  
*/

//	Method 1. Conversion & BFS + Level Array 
//	Runnning time = O(31) 
//	Auxiliary space = O(31)

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minThrow(int n, int arr[]) {
        vector<int> flatBoard(31, -1);
        for(int i=0; i<2*n-1; i+=2) {
            flatBoard[arr[i]] = arr[i+1];
        }
        //for(int i=1; i<=30; i++) cout<<flatBoard[i]<<" "; cout<<"\n";
        queue<int> Q;
        vector<int> visited(31, 0);
        vector<int> level(31, 0);
        Q.push(1);
        visited[1]=1;
        level[1]=0;
        while(!Q.empty()) {
            int u = Q.front();
            Q.pop();
            if(u==30) return level[30];
            for(int j = u+1; j <= min(u+6, 30); j++) {
                int v = (flatBoard[j]==-1) ? j : flatBoard[j];
                if(!visited[v]) {
                    Q.push(v);
                    visited[v] = 1;
                    level[v] = level[u] + 1;
                }
            }
        }
        return -1;
    }
};

int main(){
    int t;
    cin>>t;
    while(t--){
        int N;
        cin>>N;
        int arr[2*N];
        for(int i = 0;i < 2*N;i++)
            cin>>arr[i];
        
        Solution ob;
        cout<<ob.minThrow(N, arr)<<"\n";
    }
    return 0;
}