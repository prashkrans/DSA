// LC#994 NCG4 Is Oranges Rotting


// Method 1. First add all the rotten oranges in a queue and count the no. of fresh oranges 
// and use BFS along with for loop for current level size to keep a track of minutes. 

// So, one additional loop to count fresh oranges and push rotten oranges apart from BFS is used here
// Running time: O(n*m) not O(k*n*m) where k = no. of rotten oranges
// Auxiliary space: O(n*m) due to queue

class Solution {
    public:
        int orangesRotting(vector<vector<int>>& grid) {
            int n = grid.size();
            int m = grid[0].size();
    
            queue<pair<int, int>> q;
            // vector<vector<int> time(grid); This 2D array is not required here as we need to return only min minutes spent but is useful in debugging
    
            int countFresh = 0;
            for (int i=0; i<n; i++) {
                for(int j=0; j<m; j++) {
                    if(grid[i][j] == 1) countFresh++;
                    else if(grid[i][j] == 2)
                        q.push({i, j});
                }
            }
    
            if (countFresh==0) return 0; // no fresh oranges found so time taken is zero
            
            int minutes = 0;
            vector<vector<int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
            while(!q.empty()) {
                int currLevelSize = q.size();                   // Get the current level queue size one line above the for loop
                for(int k=0; k<currLevelSize; k++) {            // Don't use for(int k=0; k<q.size(); k++) as q size would vary while in the for loop
                    int ui = q.front().first;
                    int uj = q.front().second;
                    q.pop();
                    for (auto dir: dirs) {
                        int vi = ui + dir[0];
                        int vj = uj + dir[1];
                        if(vi>=0 && vi<n && vj>=0 && vj<m && grid[vi][vj]==1) { // if isValid, traversable (if grid[vi][vj] == 0 or 2) and not visited (not -1)
                            q.push({vi, vj});
                            grid[vi][vj] = -1;  // marked as visited
                            // time[vi][vj] = minutes+1; // This is actually not required 
                            countFresh--;       // since a fresh orange has turned rotten reduce fresh oranges by 1
                        }
                    }
                }
                minutes++; // It gets increment by one at the last loop
            }
            minutes--;
            return (countFresh == 0) ? minutes : -1; 
            // if fresh oranges > 0 => no path exists from a rotten orange to one or many fresh oranges then return -1
        }
    };