/* Graph Prob. 36.1. Max Area of Island (LC#695) - BFS
You are given an n x m binary matrix grid. An island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.) 
You may assume all four edges of the grid are surrounded by water.

The area of an island is the number of cells with a value 1 in the island.
Return the maximum area of an island in grid. If there is no island, return 0.

This problem could be solved using two methods:
1. BFS: R.T. = O(n*m) | A.S. = O(n*m)
2. DFS: R.T. = O(n*m) | A.S. = O(n*m)

Note: Do not use keywords like static to define n and m 
*/

//	Method 1. BFS
//	Running time = O(n*m)
//	Auxiliary space = O(n*m) due to the visited vector or O(1) if the vector grid itself is modified

class Solution {
public:
    /*
    inline bool isValid(int i, int j, vector<vector<int>> grid) {      //  This marginally increases the running time by constant factor thus resulting in TLE so prefer using inline keyword or define the func within bfs
        int n = grid.size();
        int m = grid[0].size();
        if(i<0 || i>=n || j<0 || j>=m || grid[i][j] == 0) return false;
        return true;
    }
    */
    int bfs(int i, int j, vector<vector<int>> grid, vector<vector<int>> &visited) {
        int n = grid.size(), m = grid[0].size();
        int currSize = 0;
        vector<vector<int>> dir = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        queue<pair<int, int>> Q;
        Q.push({i, j});
        visited[i][j] = 1;
        currSize++;
        while(!Q.empty()) {
            pair<int, int> u = Q.front();
            Q.pop();
            for(int k=0; k<4; k++) {
                pair<int, int> v;
                v.first = u.first + dir[k][0];
                v.second = u.second + dir[k][1];
                int x = v.first;
                int y = v.second;
                //if(isValid(v.first, v.second, grid) && !visited[v.first][v.second]) {
                if(x>=0 && x<n && y>=0 && y<m && grid[x][y] == 1 && !visited[x][y]) {
                    Q.push(v);
                    visited[v.first][v.second] = 1;
                    currSize++;
                }
            }
        }
        return currSize;
    }
    
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        int currSize, maxSize = 0;
        vector<vector<int>> visited(n, vector<int>(m, 0));
        for(int i=0; i<n; i++) {
            for(int j=0; j<m; j++) {
                if(grid[i][j] == 1 && !visited[i][j]) {
                    currSize = bfs(i, j, grid, visited);
                    maxSize = max(currSize, maxSize);
                }
            }
        }
        return maxSize;
    }
};


// Method 2 without using any visited 2D vector or map and using the grid itself to mark nodes as visited

class Solution {
    public:
        bool isValid(pair<int, int> v, int n, int m, vector<vector<int>> &grid) {
                int i = v.first;
                int j = v.second;
                if(i<0 || i==n || j<0 || j==m || grid[i][j] == 0 || grid[i][j] == -1) return false;
                else return true;
            }
        
            int bfs(int i, int j, int n, int m, vector<vector<int>> &grid) {
                queue<pair<int, int>> q;
                pair<int, int> src = {i, j};
                q.push(src);
                grid[i][j] = -1;
                vector<pair<int, int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
                int currArea = 0;
                while(!q.empty()) {
                    pair<int, int> u = q.front();
                    q.pop();
                    currArea++;
                    for (int x = 0; x<4; x++) {
                        pair<int, int> v = {u.first+dirs[x].first, u.second+dirs[x].second};
                        if(isValid(v, n, m, grid)) {
                            q.push(v);
                            grid[v.first][v.second] = -1; // Mark v as visited
                        }
                    }
                }
                return currArea;
            }
        
            int maxAreaOfIsland(vector<vector<int>>& grid) {
                int maxArea = 0;
                int n = grid.size();
                int m = grid[0].size();
                for(int i=0; i<n; i++) {
                    for(int j=0; j<m; j++) {
                        if(grid[i][j] == 1) 
                            maxArea = max(maxArea, bfs(i, j, n, m, grid));
                    }
                }
                return maxArea;
            }
    };
