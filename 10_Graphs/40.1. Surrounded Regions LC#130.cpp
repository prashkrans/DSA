// LC#130. NCG6. Surrounded Regions

// Method 1: For each border 'O' (four for loops), run BFS/DFS and mark the neighbouring 'O's as '#'. 
// Then traverse through the board again and mark all the remaining 'O's as 'X' and revert '#' as 'O'.
// 0 ms beats 100%

// Running time: O(m*n) and not O(k*m*n) where k = number of 'O's at the border. 0 ms beats 100%
// Auxiliary space: O(m*n) due to the BFS queue or the DFS recursion stack

class Solution {
    public:
        void bfs(int i, int j, int &m, int &n, vector<vector<char>> &board) {
            if(board[i][j] != 'O') return; // Added the check condition inside bfs instead of outside 
            queue<pair<int, int>> q;
            q.push({i, j});
            board[i][j]='#'; // '#' represents that a cell with 'O' has been visited
            vector<int> dirH = {0, 1, 0, -1};   // Another way of using for directions
            vector<int> dirV = {1, 0, -1, 0};
            while(!q.empty()) {
                int ui =  q.front().first;
                int uj =  q.front().second;
                q.pop();
                for(int k=0; k<4; k++) {
                    int vi = ui + dirH[k];
                    int vj = uj + dirV[k];
                    if((vi >= 0 && vi < m && vj >= 0 && vj < n) && board[vi][vj] == 'O') {
                        q.push({vi, vj});
                        board[vi][vj] = '#';
                    }
                }
            }
        }
        
        void solve(vector<vector<char>>& board) {
            int m = board.size();   // Leetcode uses m x n instead of n x m
            int n = board[0].size();
    
            for (int j=0; j<n; j++) bfs(0, j, m, n, board);         // Topmost
            for (int i=0; i<m; i++) bfs(i, n-1, m, n, board);       // Rightmost  
            for (int j=0; j<n; j++) bfs(m-1, j, m, n, board);       // Bottomost
            for (int i=0; i<m; i++) bfs(i, 0, m, n, board);         // Leftmost
    
            // for(auto i: board) {
            //     for(auto j: i) {
            //         cout<<j<<" ";
            //     }
            //     cout<<endl;
            // }
    
            for(int i=0; i<m; i++){
                for(int j=0; j<n; j++) {
                    if(board[i][j] == 'O') board[i][j] = 'X';
                    else if(board[i][j] == '#') board[i][j] = 'O';
                }
            }
        }
    };