// Premium LeetCode Question
// LintCode#663 · Walls and Gates
// https://neetcode.io/problems/islands-and-treasure

// Method 1. BFS + Update distance of child as distance of parent + 1
// Running time: O(number of zeroes * BFS) = O(k*n*m)[Incorrect] but O(n*m) as k doesn't matter here 
// Auxiliary space: O(n) due to the BFS queue
// where n = number of rows
// m = number of columns
// k = number of zeroes
// Note: Thus, the actual time complexity is still O(n * m), not O(k * n * m). 
// The number of 0s affects only the starting conditions but does not multiply the complexity.


class Solution {
public:
    bool isValid(pair<int, int> v, int n, int m, vector<vector<int>> &rooms) {
        int i = v.first;
        int j = v.second;
        if(i<0 || i==n || j<0 || j==m) return false;    // is not valid
        else if(rooms[i][j] == 0 || rooms[i][j] == -1) return false;    // is not traversable
        else return true;   // is valid and traversable
    }

    void bfs(int i, int j, int n, int m, vector<vector<int>> &rooms) {
        queue<pair<int, int>> q;
        q.push({i, j});
        vector<vector<int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        while(!q.empty()) {
            pair<int, int> u = q.front();
            q.pop();
            for(auto dir: dirs) {
                pair<int, int> v = { u.first + dir[0], u.second + dir[1] };
                if(isValid(v, n, m, rooms) && rooms[v.first][v.second] > rooms[u.first][u.second] + 1) {
                    q.push(v);
                    rooms[v.first][v.second] = rooms[u.first][u.second] + 1; // Don't use min of (dist[v], dist[u]+1) as it would be redundant
                }
            }
        }
    }

    void islandsAndTreasure(vector<vector<int>> &rooms) {
        // write your code here
        int n = rooms.size();
        int m = rooms[0].size();
        for(int i=0; i<n; i++) {
            for(int j=0; j<m; j++) {
                if(rooms[i][j] == 0) {
                    bfs(i, j, n, m, rooms);
                }
            }
        }
    }
};