/* Graph problem #21.1b. LC#200. Number of islands
Stack problem #5. LC#200. Number of islands
Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return the number of islands.
An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically (4 directions). 
You may assume all four edges of the grid are all surrounded by water.

There are three methods to solve this:
1.	Using a simple DFS
2.	Using a simple BFS
3.	Using disjoint sets i.e. union-find algorithm
*/

//	Method 1b - Using DFS traversal to mark a node visited in each island
//	With a visited matrix
//	Steps: Refer notes
//	Running time = O(DFS) = O(n*m) since we traverse the given matrix/grid
//	Auxiliary space = O(1) if the given matrix/grid itself is modified to keep track of visited nodes
//					or O(n*m) if we create a new visited matrix

class Solution {
public:
    void DFS(int i, int j, vector<vector<int>> &visited, vector<vector<char>> &grid) {	//	Here we are using a visited matrix instead of modifying grid itself
        int n = grid.size();
        int m = grid[0].size();
        if(i<0||i>=n||j<0||j>=m||grid[i][j]=='0'||visited[i][j]==1) return;
        visited[i][j] = 1;
        DFS(i, j+1, visited, grid);		// 	Right
        DFS(i+1, j, visited, grid);     //	Down
        DFS(i, j-1, visited, grid);     //	Left
        DFS(i-1, j, visited, grid);     //	Up
    }
    
    int numIslands(vector<vector<char>> &grid) {
        int n = grid.size();
        if(n==0) return 0;
        int m = grid[0].size();
        vector<vector<int>> visited(n, vector<int>(m, 0));
        int ans = 0;
        for(int i=0; i<n; i++) {
            for(int j=0; j<m; j++) {
                if(grid[i][j] == '1' && !visited[i][j]) {
                    ans++;
                    DFS(i, j, visited, grid);
                }
            }
        }
        return ans;        
    }
};

//	Method 1c - Without a visited matrix. Here, the grid itself is modified to work as a visited matrix

class Solution {
public:
    void DFS(int i, int j, vector<vector<char>> &grid) {
        int n = grid.size();
        int m = grid[0].size();
        if(i<0||i>=n||j<0||j>=m||grid[i][j]!='1') return;
        grid[i][j] = '2';
        DFS(i, j+1, grid);				// 	Right
        DFS(i+1, j, grid);              //	Down
        DFS(i, j-1, grid);              //	Left
        DFS(i-1, j, grid);              //	Up
    }
    
    int numIslands(vector<vector<char>> &grid) {
        int n = grid.size();
        if(n==0) return 0;
        int m = grid[0].size();
        int ans = 0;
        for(int i=0; i<n; i++) {
            for(int j=0; j<m; j++) {
                if(grid[i][j] == '1') {
                    ans++;
                    DFS(i, j, grid);
                }
            }
        }
        return ans;        
    }
};