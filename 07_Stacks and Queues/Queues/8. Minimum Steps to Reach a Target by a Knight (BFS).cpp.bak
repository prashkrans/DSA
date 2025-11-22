/* Graph Prob. 35.1. Minimum Steps to Reach a Target by a Knight
Given a square chessboard, the initial position of Knight and position of a target. Find out the minimum
steps a Knight will take to reach the target position.
Note:
The initial and the target position coordinates of Knight have been given according to 1-base indexing.

This problem could be solved using two methods:
1. BFS (Preferred as easier to understand): R.T. = O(n*m) or O(n^2) i.e. quadratic time
2. DP + Careful selection of direction to move in: R.T. = O(n*m) A.S. = O(n*m) or O(n^2)
*/

#include<bits/stdc++.h>
using namespace std;

bool isValid(pair<int, int> v, int n) {                 //  It validates whether i and j are not out of bounds
    int i = v.first, j = v.second;
    //if(i<0 || i>=n || j<0 || j>=n) return false;      //  if 0 based indexing is used
    if(i<1 || i>n || j<1 || j>n) return false;          //  if 1 based indexing is used
    return true;                                        //  I might have lost an opportunity with soroco because of not returning true here
}

int bfs(int i, int j, int x, int y, int n) {
    if(i==x && y==j) return 0;                          //  [#IMP]
    queue<pair<int, int>> Q;
    map<pair<int, int>, int>visited;
    map<pair<int, int>, int> dist;
    vector<vector<int>> dir = {{1, 2}, {2, 1}, {-1, -2}, {-2, -1}, {-1, 2}, {2, -1}, {1, -2}, {-2, 1}};
    Q.push({i, j});
    visited[{i, j}] = 1;
    dist[{i, j}] = 0;
    while(!Q.empty()) {
        pair<int, int> u = Q.front();
        Q.pop();
        for(int k=0; k<8; k++) {
            pair<int, int> v;
            v.first = u.first + dir[k][0];
            v.second = u.second + dir[k][1];
            if(isValid(v, n) && !visited[v]) {
                Q.push(v);
                visited[v] = 1;
                dist[v] = 1 + dist[u];
                if(v.first == x && v.second == y) return dist[v];
            }
        }
    }
    return -1;
}

/*
int minSteps(pair<int, int> knightPosition, pair<int, int> targetPosition, int n) {     //  If positions are given in terms of pair
    int i = knightPosition.first, j = knightPosition.second;
    int x = targetPosition.first, y = targetPosition.second;
    return bfs(i, j, x, y, n);
}
*/

int main() {
    int n, i, j, x, y;
    cin>>n>>i>>j>>x>>y;
    cout<<"Min no. of steps = "<<bfs(i, j, x, y, n);
    return 0;
}

/* Sample input:
4
2 3
1 2
*/
