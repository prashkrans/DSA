/* Graph problem #33.1. Connected Cell in a Graph (DFS + 8 Directions)
https://www.hackerrank.com/challenges/ctci-connected-cell-in-a-grid/problem?h_l=interview&isFullScreen=true&playlist_slugs%5B%5D%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D%5B%5D=graphs
*/

//	Running time = O(n*m)
//	Auxiliary space = O(n*m) due to the visited table


void dfs(int i, int j, vector<vector<int>> grid, vector<vector<int>> &visited, int &numC) {
    if(i<0 || j<0 || i>=grid.size() || j>=grid[0].size() || visited[i][j]==1 || grid[i][j]==0)
        return;
    else {
        cout<<i<<", "<<j<<": "<<numC<<"|";
        visited[i][j] = 1;
        numC++;
        vector<pair<int, int>> dir = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {-1, 1}, {-1, -1}, {1, -1}};
        for(auto d : dir) {
            dfs(i+d.first, j+d.second, grid, visited, numC);
        }
    }
}

int maxRegion(vector<vector<int>> grid) {
    int n = grid.size(), m = grid[0].size();
    int maxVal = -1, numC = -1;
    vector<vector<int>> visited(n, vector<int>(m, 0));
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            if(grid[i][j]==1) {
                numC = 0;
                dfs(i, j, grid, visited, numC); cout<<"\n";
            }
            if(numC>maxVal) maxVal = numC;
        }
    }
    return maxVal;
}