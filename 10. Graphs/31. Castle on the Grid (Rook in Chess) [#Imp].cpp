/* Graph problem #34.1. Castle on the Grid (Like a rook in chess)
*/

//	Method 1. BFS using queue<pair<int, int>> Q but with a slight variation in movement / definition
//	of the neighbouring cells. Here, even though we can move in only four directions {R, D, L, U} but
//	we can move more than one cells at a time either horizontally or vertically like a rook in chess.
//	So, for each cell (i, j) we have (n-1) different steps available each horizontally and vertically
//	or (n-1) neighbours or adjacent nodes each horizontally and vertically. 
//	Running time = O(n^2 * 2(n-1)) but due to the visited array it reduces down to O(n^2) i.e. quadratic
//	Auxiliary space = O(n^2) 

#include <bits/stdc++.h>
using namespace std;

void printMat(vector<vector<int>> mat) {
    int n = mat.size();
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            if(mat[i][j] == INT_MAX) cout<<"INF"<<"\t";
            else cout<<mat[i][j]<<" \t";
        }
        cout<<"\n";
    }
}

bool isValid(vector<string> grid, int n, int i, int j) {
    if(i<0 || j<0 || i>=n || j>=n || grid[i][j] == 'X') return false;
    return true;
}

int minimumMoves(vector<string> grid, int startX, int startY, int goalX, int goalY) {
    int n = grid.size();
    vector<vector<int>> visited(n, vector<int>(n, 0));
    vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
    vector<pair<int, int>> dir = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    queue<pair<int, int>> Q;
    Q.push({startX, startY});
    visited[startX][startY] = 1;
    dist[startX][startY] = 0;
    while(!Q.empty()) {
        pair<int, int> u = Q.front();
        Q.pop();
        for(auto d : dir) {
            pair<int, int> v = u;
            v.first += d.first;
            v.second += d.second;
            while(isValid(grid, n, v.first, v.second)) {        //  This while loop inside the for loop enables
                if(!visited[v.first][v.second]) {               //  to mimic the movement of a rook in chess for the BFS
                    Q.push(v);									//	[#IMP] - Use of while loop - All the cells v either in horizontal or vertical line are adjacent to u
                    visited[v.first][v.second] = 1;
                    dist[v.first][v.second] = 1 + dist[u.first][u.second];		
                    if(v.first == goalX && v.second == goalY) return dist[v.first][v.second];	//	If the target cell is reached just return its dist
                }
                v.first += d.first;
                v.second += d.second;
            }
        }
    }
    //printMat(dist);
    //cout<<"Dist = "<<dist[goalX][goalY]<<"\n";
    return dist[goalX][goalY];
}

int main() {
    int n;
    cin>>n;
    vector<string> grid;
    string s;
    for(int i=0; i<n; i++) {
        cin>>s;
        grid.push_back(s);
    }
    int i, j, r, c;
    cin>>i>>j>>r>>c;
    cout<<minimumMoves(grid, i, j, r, c);
    return 0;
}

/* Sample inputs:
3
.X.
.X.
...
0 0 0 2

10
.X..XX...X
X.........
.X.......X
..........
........X.
.X...XXX..
.....X..XX
.....X.X..
..........
.....X..XX
9 1 9 6
*/