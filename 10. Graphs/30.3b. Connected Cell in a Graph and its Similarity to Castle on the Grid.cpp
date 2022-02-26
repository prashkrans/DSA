/* Graph problem #33.3b. Connected Cell in a Graph and its similarity to Castle on the Grid (BFS + 4 Directions)
Given a grid of values '.' and 'X' where . represents a cell open to traversal and X represents an obstacle and 
the starting cell and the destination cell, find the shortest path from src to dest.
*/

//	Method 1. BFS + queue<pair<int, int>> Q;
//	This solution is just an extension of the solution of prob. 33.3. to print the path as well from the src to dest
//	Running time = O(n^2)
//	Auxiliary space = O(n^2) due to the visited array


#include <bits/stdc++.h>
using namespace std;

void printMat(vector<vector<int>> mat) {
    int n = mat.size();
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            if(mat[i][j] == INT_MAX) cout<<"INF"<<"\t";
            else cout<<mat[i][j]<<" \t";
        }
        cout<<"\n";
    }
}

bool isValid(vector<string> grid, int n, int i, int j) {
    if(i<0 || j<0 || i>=n || j>=n || grid[i][j] == 'X') return false;
    return true;

}

int minimumMoves(vector<string> grid, int startX, int startY, int goalX, int goalY) {
    int n = grid.size();
    vector<vector<int>> visited(n, vector<int>(n, 0));
    vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
    map<pair<int, int>, pair<int, int>> parent;
    vector<pair<int, int>> dir = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    queue<pair<int, int>> Q;
    Q.push({startX, startY});
    visited[startX][startY] = 1;
    dist[startX][startY] = 0;
    parent[{startX, startY}] = {startX, startY};
    while(!Q.empty()) {
        pair<int, int> u = Q.front();
        Q.pop();
        for(auto d : dir) {
            pair<int, int> v = u;
            v.first += d.first;
            v.second += d.second;
            if(isValid(grid, n, v.first, v.second)) {
                if(!visited[v.first][v.second]) {
                    Q.push(v);
                    visited[v.first][v.second] = 1;
                    dist[v.first][v.second] = 1 + dist[u.first][u.second];
                    parent[v] = u;
                    //dist[v.first][v.second] = dist[u.first][u.second];
                }
            }
        }
    }
    printMat(dist);
    cout<<"Dist = "<<dist[goalX][goalY]<<"\n";
    pair<int, int> u = {goalX, goalY};
    vector<pair<int, int>> path;
    while(parent[u] != u) {
         path.push_back(u);
         u = parent[u];
    }
    path.push_back(u);
    reverse(path.begin(), path.end());
    for(auto p : path) cout<<"("<<p.first<<", "<<p.second<<")"<< " -> "; cout<<"\n";
    int minMoves = 1, direc;
    if(path[0].first == path[1].first) direc = 0;
    else direc = 1;
    for(int i=1; i<path.size()-1; i++) {
        if((path[i].first == path[i+1].first) && direc == 1) {
            minMoves++;
            direc = 0;
        }
        else if((path[i].second == path[i+1].second) && direc == 0) {
            minMoves++;
            direc = 1;
        }
    }
    return minMoves;
}

int main() {
    int n;
    cin>>n;
    vector<string> grid;
    string s;
    for(int i=0; i<n; i++) {
        cin>>s;
        grid.push_back(s);
    }
    int i, j, r, c;
    cin>>i>>j>>r>>c;
    cout<<minimumMoves(grid, i, j, r, c);
    return 0;
}

/* Sample inputs:
3
.X.
.X.
...
0 0 0 2

10
.X..XX...X
X.........
.X.......X
..........
........X.
.X...XXX..
.....X..XX
.....X.X..
..........
.....X..XX
9 1 9 6
*/

