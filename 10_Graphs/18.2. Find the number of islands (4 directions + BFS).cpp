/* Graph problem #21.2. Find the no. of islands
Given a grid consisting of '0's(Water) and '1's(Land). Find the number of islands.
Note: An island is surrounded by water and is formed by connecting adjacent lands horizontally or
vertically or diagonally i.e., in all 8 directions.

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

#include<iostream>
#include<vector>
#include<queue>
using namespace std;

class Solution {
    public:
	//	BFS helper just helps to check if a adjacent node is already visited, is a land and not out of bounds of the matrix
    void BFShelper(int i, int j, vector<vector<int>> &grid, queue<pair<int, int>> &Q) {			//	Five conditions for which we don't use BFS
        if(i<0||i>=grid.size()||j<0||j>=grid[0].size()||grid[i][j]!=1) return;		//	First four makes sure that cell(i, j) is a valid cell and not out of bounds
        grid[i][j] = 2;		//	Marks the current cell as visited					//	Fifth condition makes sure that if cell(i, j) == 0, we don't consider it a node in any island
		Q.push({i, j});     //	Pushes the current cell in the queue              	//	or if cell(i, j) == 2 it is already visited
	}
    void BFS(int i, int j, vector<vector<int>> &grid) {
		queue<pair<int, int>> Q;                //  Here, a cell denotes a node thus, we use a pair<int, int> to store a cell location
		Q.push(make_pair(i, j));                //  Since a queue in BFS stores nodes => we need the queue as queue of pairs
		grid[i][j] = 2;
		while(!Q.empty()) {
			int x, y;
			pair<int, int> currCell = Q.front();
			Q.pop();
			x = currCell.first;					//	all the neighbours of currCell are needed here hence, x = current i and y = current j
			y = currCell.second;
			BFShelper(x, y+1, grid, Q);			// 	Right
			BFShelper(x+1, y, grid, Q);			//	Down
			BFShelper(x, y-1, grid, Q);			//	Left
			BFShelper(x-1, y, grid, Q);			//	Up
		}
    }
    int numIslands(vector<vector<int>>& grid) {
        if(grid.size()==0 || grid[0].size()==0) return 0;
        int ans = 0;
        for(int i=0; i<grid.size(); i++) {				//	Iterate through all the cells
            for(int j=0; j<grid[0].size(); j++) {
                if(grid[i][j] == 1) {					//	If a cell has value 1 => it is not visited and land node in an undiscovered island
                    ans++;
					BFS(i, j, grid);					//	BFS is a void type function here and if a newly discovered island is completely visited, ans is incremented by 1
                }
            }
        }
        return ans;
    }
};

int main(){
	int n, m;
	cin >> n >> m;
	vector<vector<int>>grid(n, vector<int>(m, 0));
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) cin >> grid[i][j];
	}
	Solution obj;
	int ans = obj.numIslands(grid);
	cout<<"The no. of islands in the given grid are = "<<ans<<"\n";
	return 0;
}

/* Sample input
2 7
0 1 1 1 0 0 1
0 0 1 1 0 1 0
*/
