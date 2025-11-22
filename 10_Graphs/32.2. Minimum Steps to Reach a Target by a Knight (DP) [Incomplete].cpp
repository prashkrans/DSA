/* Graph Prob. 35.1. Minimum Steps to Reach a Target by a Knight
Given a square chessboard, the initial position of Knight and position of a target. Find out the minimum
steps a Knight will take to reach the target position.
Note:
The initial and the target position coordinates of Knight have been given according to 1-base indexing.

This problem could be solved using two methods:
1. BFS (Preferred as easier to understand): R.T. = O(n*m) or O(n^2) i.e. quadratic time
2. DP + Careful selection of direction to move in: R.T. = O(n*m) A.S. = O(n*m) or O(n^2)
*/

//  Incomplete

#include<bits/stdc++.h>
using namespace std;

int rec(int i, int j, int x, int y, int n) {
    cout<<"Check2\n";
    if(i<0 || i>=n || j<0 || j>=n) return INT_MAX-10000;
    if(i==x && j==y) return 0;
    int minMoves = INT_MAX-10000;;
    vector<vector<int>> dir = {{1, 2}, {2, 1}, {-1, -2}, {-2, -1}, {-1, 2}, {2, -1}, {1, -2}, {-2, 1}};
    for(int k=0; k<8; k++) {
        cout<<dir[k][0]<<" "<<dir[k][1]<<"\n";
        minMoves = min(minMoves, rec(i+dir[k][0], j+dir[k][1], x, y, n));
    }
    cout<<"Check3\n";
    return 1 + minMoves;
}
/*
int minSteps(pair<int, int> knightPosition, pair<int, int> targetPosition, int n) {
    int i = knightPosition.first, j = knightPosition.second;
    int x = targetPosition.first, y = targetPosition.second;
    return rec(i, j, x, y, n);
}
*/
int main() {
    int n, i, j, x, y;
    cin>>n>>i>>j>>x>>y;
    cout<<"Check1\n";
    cout<<rec(i, j, x, y, n);
    return 0;
}

/* Sample input:
4
2 3
1 2
*/
