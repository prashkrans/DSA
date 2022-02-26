/* Graph problem #21.1. Find the no. of islands
Given a grid consisting of '0's(Water) and '1's(Land). Find the number of islands.
Note: An island is surrounded by water and is formed by connecting adjacent lands horizontally or
vertically or diagonally i.e., in all 8 directions.
gfg - https://practice.geeksforgeeks.org/problems/find-the-number-of-islands/1#

There are three methods to solve this:
1.	Using a simple DFS
2.	Using a simple BFS
3.	Using disjoint sets i.e. union-find algorithm
*/

//	Method 1 - Using DFS traversal to mark a node visited in each island
//	Steps: Refer notes
//	Running time = O(DFS) = O(n*m) since we traverse the given matrix/grid
//	Auxiliary space = O(1) if the given matrix/grid itself is modified to keep track of visited nodes
//					or O(n*m) if we create a new visited matrix

#include<iostream>
#include<vector>
using namespace std;

class Solution {
    public:	
    int DFS(int i, int j, vector<vector<char>> &grid) {									//	It is better to use void type DFS here
        if(i<0||i>=grid.size()||j<0||j>=grid[0].size()||grid[i][j]!='1') return 0;		//	Five conditions for which we don't use DFS
        grid[i][j] = '2';		//	Marks the current cell as visited					//	First four makes sure that cell(i, j) is a valid cell and not out of bounds
        int val = 0;																	//	Fifth condition makes sure that if cell(i, j) == '0', we don't consider it a node in any island
        val = DFS(i, j+1, grid);			// 	Right									//	or if cell(i, j) == '2' it is already visited
        val = DFS(i+1, j, grid);			//	Down
        val = DFS(i, j-1, grid);			//	Left
        val = DFS(i-1, j, grid);			//	Up
        val = DFS(i+1, j+1, grid);			//	Bottom-right
        val = DFS(i-1, j-1, grid);			//	Top-left
        val = DFS(i+1, j-1, grid);			//	Bottom-left
        val = DFS(i-1, j+1, grid);			//	Top-right
        return 1;
    }
    //Function to find the number of islands.
    int numIslands(vector<vector<char>>& grid) {        //  Note - Here, the grid is of char data type so, make all the comparisons as grid[i][j] = '1' or '0'
        if(grid.size()==0 || grid[0].size()==0) return 0;
        int ans = 0;
        for(int i=0; i<grid.size(); i++) {				//	Iterate through all the cells
            for(int j=0; j<grid[0].size(); j++) {
                if(grid[i][j] == '1') {					//	If a cell has value '1' => it is not visited and land node in an undiscovered island
                    ans += DFS(i, j, grid);				//	DFS returns 1 if a newly discovered island is completely visited, thus ans is incremented by 1
                }
            }
        }
        return ans;
    }
};

int main(){
	int tc;
	cin >> tc;
	while(tc--){
		int n, m;
		cin >> n >> m;
		vector<vector<char>>grid(n, vector<char>(m, '#'));
		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++){
				cin >> grid[i][j];
			}
		}
		Solution obj;
		int ans = obj.numIslands(grid);
		cout<<"The no. of islands in the given grid are = ";
		cout << ans <<'\n';
	}
	return 0;
}

/* Sample input
1
2 7
0 1 1 1 0 0 0
0 0 1 1 0 1 0
*/
