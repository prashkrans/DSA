/* Graph Prob. 36.2. Max Area of Island (LC#695) - DFS
You are given an n x m binary matrix grid. An island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.) 
You may assume all four edges of the grid are surrounded by water.

The area of an island is the number of cells with a value 1 in the island.
Return the maximum area of an island in grid. If there is no island, return 0.

This problem could be solved using two methods:
1. BFS: R.T. = O(n*m) | A.S. = O(n*m)
2. DFS: R.T. = O(n*m) | A.S. = O(n*m)

Note: Do not use keywords like static to define n and m 
*/

//	Method 2.1. DFS (Compact)
//	Running time = O(n*m)
//	Auxiliary space = O(n*m) even when modified the grid table due to the recursion stack

class Solution {
public:
    int dfs(int i, int j, vector<vector<int>> &grid) {
        if(i<0 || i>=grid.size() || j<0 || j>=grid[0].size() || grid[i][j] == 0) return 0;			//	This takes care of out of bounds as well as isVisited condition
        grid[i][j] = 0;																				//	[#IMP] to make grid[i][j] = 0 for marking it visited 
        return 1 + dfs(i, j+1, grid) + dfs(i+1, j, grid) + dfs(i, j-1, grid) + dfs(i-1, j, grid);	//	
    }
    
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int maxSize = 0;
        for(int i=0; i<grid.size(); i++) {
            for(int j=0; j<grid[0].size(); j++) {
                if(grid[i][j]==1) {
                    maxSize = max(maxSize, dfs(i, j, grid));
                }
            }
        }
        return maxSize;
    }
};

//	Method 2.2. DFS (Longer version)
//	Running time = O(n*m)
//	Auxiliary space = O(n*m) even when modified the grid table due to the recursion stack

class Solution {
public:
    /*
    bool isValid(int i, int j, int n, int m, vector<vector<int>> grid) {  // This slightly slows down the program
        if(i<0 || i>=n || j<0 || j>=m || grid[i][j]==0) return 0; 
        return 1;
    }
    */ 
    
    int dfs(int i, int j, vector<vector<int>> &grid) {
        int n = grid.size();
        int m = grid[0].size();        
        if(i<0 || i>=n || j<0 || j>=m || grid[i][j]==0) return 0; 
        int count = 1;
        grid[i][j] = 0;
        vector<vector<int>> dir = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        for(int k=0; k<4; k++) {
            int x = i + dir[k][0], y = j + dir[k][1];
            //if(isValid(x, y, n, m, grid) && !visited[x][y]) 
                count = count + dfs(x, y, grid);
        }
        return count;
    }
    
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        int maxSize = 0;
        for(int i=0; i<n; i++) {
            for(int j=0; j<m; j++) {
                if(grid[i][j]==1) {
                    int currSize = dfs(i, j, grid);
                    //cout<<"Curr size = "<<currSize<<"\n";
                    maxSize = max(currSize, maxSize);
                }
            }
        }
        return maxSize;
    }
};