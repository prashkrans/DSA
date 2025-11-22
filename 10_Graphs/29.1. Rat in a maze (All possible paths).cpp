/* Graph problem #32.1. Rat in a Maze Problem (All possible paths when movement in all possible directions (four) is allowed)
Consider a rat placed at (0, 0) in a square matrix m[ ][ ] of order n and has to reach the destination at (n-1, n-1). The task
is to find a sorted array of strings denoting all the possible directions which the rat can take to reach the destination at
(n-1, n-1). The directions in which the rat can move are ‘U'(up), ‘D'(down), ‘L’ (left), ‘R’ (right).

This problem could only be solved using backtracking:
Approach: Backtracking or Top Down Approach in Recursion.
1.  Start from the initial index (i.e. (0,0)) and look for the valid moves through the adjacent cells in the order Down->Left->Right->Up
    (so as to get the sorted paths) in the grid.
2.  If the move is possible, then move to that cell while storing the character corresponding to the move(D,L,R,U) and again start looking
    for the valid move until the last index (i.e. (n-1,n-1)) is reached.
3.  Also, keep on marking the cells as visited and when we traversed all the paths possible from that cell, then unmark that cell i.e mark it
    as not visited for other different paths and remove the character from the path formed.
4.  As the last index of the grid(bottom right) is reached, then store the traversed path.

Example 1:
Input:
4
1 0 1 0
1 1 1 1
0 1 1 0
0 1 1 1
Output: DRDDRR DRDRDR DRRDDR DRRDLDRR

Example 2:
Input:
3
1 0 0
1 0 0
1 0 1
Output: No path exists

Note: If the starting cell or the destination cell itself has value == 0, then no path exists.
*/

//  Method 1. Backtracking or Top Down Approach in Recursion.
//  Running time = O(4^(n^2)) i.e. exponential as for each cell there are four options D, L, R, U so, there are 4*4*...4 (n^2 times) possibilities.
//  Auxiliary space = O(4^(n^2)) same as the running time.
//  Note: If only two directions (R, D) are allowed then R.T. = A.S. = O(2^(n^2))

#include<iostream>
#include<map>
#include<vector>
using namespace std;

bool isValid(int r, int c, vector<vector<int>> maze) {
    int n = maze.size();
    return(r>=0 && r<n && c>=0 && c<n && maze[r][c] == 1);
}
//  Note: printAllPathsUtil is a DFS function which marks a node u(r, c) as visited when it visits it and then marks it as unvisited when DFS(u) is completed
void printAllPathsUtil(int r, int c, int n, vector<vector<int>> maze, vector<pair<int, int>> dir, vector<char> dirChar, map<pair<int, int>, int> &visited, string s, int &numOfPaths) {
    visited[{r, c}] = 1;        //  Since we are visiting (r, c) in a current path, mark it as visited
    //cout<<"r = "<<r<<" c = "<<c<<" s = "<<s<<"\n";
    if(r==n-1 && c==n-1) {
        cout<<s<<" ";
        // allPaths.push_back(s);
        numOfPaths++;
        visited[{r, c}] = 0;
        return;
    }
    for(int i=0; i<4; i++) {
        int newR = r + dir[i].first;
        int newC = c + dir[i].second;
        if(isValid(newR, newC, maze) && !visited[{newR, newC}])
            printAllPathsUtil(newR, newC, n, maze, dir, dirChar, visited, s+dirChar[i], numOfPaths);    //  Each node has 4 branches {D, L, U, R}
    }
    visited[{r, c}] = 0;    //  Since, the DFS for the current path has completed, mark (r, c) as unvisited again
}

void printAllPaths(int n, vector<vector<int>> maze) {
    if(maze[0][0]==0 || maze[n-1][n-1]==0) {
        cout<<"No path exists for the rat to escape the maze\n";
        return;
    }
	vector<pair<int, int>> dir = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}};    //  The order used here is Down, Left, Right, Up just to make sure a sorted order is maintained
	vector<char> dirChar = {'D', 'L', 'R', 'U'};                        //  However, it is not at all compulsory and we can use any order
	map<pair<int, int>, int> visited;
	string s;
	//vector<string> allPaths;
	int numOfPaths = 0;
	printAllPathsUtil(0, 0, n, maze, dir, dirChar, visited, s, numOfPaths); //  printAllPathsUtils(... ,allPaths);
	if(numOfPaths==0) cout<<"No path exists for the rat to escape the maze\n";
	else cout<<"\nSo, there are "<<numOfPaths<<" different paths.\n";
}

int main() {
	int n;
	cin>>n;
	vector<vector<int>> maze(n, vector<int>(n));
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) cin>>maze[i][j];
	}
	//cout<<"The different paths are: ";
	printAllPaths(n, maze);
	return 0;
}
