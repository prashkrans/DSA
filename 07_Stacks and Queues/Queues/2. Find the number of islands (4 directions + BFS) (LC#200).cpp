/* Graph problem #21.2b. LC#200. Number of islands
Queue problem #1. LC#200. Number of islands
Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return the number of islands.
An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically (4 directions).
You may assume all four edges of the grid are all surrounded by water.

There are three methods to solve this:
1.	Using a simple DFS
2.	Using a simple BFS
3.	Using disjoint sets i.e. union-find algorithm
*/

//	Method 2 - Using BFS traversal to mark a node visited in each island
//	Steps: Refer notes
//	Running time = O(BFS) = O(n*m) since we traverse through the given matrix/grid
//	Auxiliary space = O(1) if the given matrix/grid itself is modified to keep track of visited nodes
//					or O(n*m) if we create a new visited matrix

class Solution {
public:
    void BFShelper(int i, int j, vector<vector<char>> &grid, queue<pair<int, int>> &Q) {//	Five conditions for which we don't use DFS
        if(i<0||i>=grid.size()||j<0||j>=grid[0].size()||grid[i][j]!='1') return;		//	First four makes sure that cell(i, j) is a valid cell and not out of bounds
        grid[i][j] = '2';		//	Marks the current cell as visited					//	Fifth condition makes sure that if cell(i, j) == 0, we don't consider it a node in any island
		Q.push({i, j});                                                             	//	or if cell(i, j) == 2 it is already visited
	}
    void BFS(int i, int j, vector<vector<char>> &grid) {
		queue<pair<int, int>> Q;                //  Here, a cell denotes a node thus, we use a pair<int, int> to store a cell location
		Q.push(make_pair(i, j));                //  Since a queue in BFS stores nodes => here the queue of pairs is used
		grid[i][j] = 2;
		while(!Q.empty()) {
			int x, y;
			pair<int, int> currCell = Q.front();
			Q.pop();
			x = currCell.first;
			y = currCell.second;
			BFShelper(x, y+1, grid, Q);			// 	Right
			BFShelper(x+1, y, grid, Q);			//	Down
			BFShelper(x, y-1, grid, Q);			//	Left
			BFShelper(x-1, y, grid, Q);			//	Up
		}
    }

    int numIslands(vector<vector<char>>& grid) {
        if(grid.size()==0 || grid[0].size()==0) return 0;
        int ans = 0;
        for(int i=0; i<grid.size(); i++) {				//	Iterate through all the cells
            for(int j=0; j<grid[0].size(); j++) {
                if(grid[i][j] == '1') {					//	If a cell has value 1 => it is not visited and land node in an undiscovered island
                    ans++;
					BFS(i, j, grid);					//	BFS is a void type function here and if a newly discovered island is completely visited, ans is incremented by 1
                }
            }
        }
        return ans;
    }
};

//  Method 2. Using DFS
//  Running time = O(m*n) where m = num of rows and n = num of columns
//  Auxiliary space = O(m*n) due to the recursion stack

class Solution {
public:
    void dfs(int i, int j, int m, int n, vector<vector<char>> &grid) {
        if(i<0 || i>=m || j<0 || j>=n || grid[i][j]=='0') return;
        grid[i][j] = '0';
        dfs(i, j+1, m, n, grid);
        dfs(i+1, j, m, n, grid);
        dfs(i, j-1, m, n, grid);
        dfs(i-1, j, m, n, grid);
    }

    int numIslands(vector<vector<char>>& grid) {
        int ans = 0, m = grid.size(), n = grid[0].size();
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                if(grid[i][j]=='1') {
                    ans++;
                    dfs(i, j, m, n, grid);
                }
            }
        }
        return ans;
    }
};
