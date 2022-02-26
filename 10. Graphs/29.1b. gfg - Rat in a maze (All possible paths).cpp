/* Graph problem #32.1. Rat in a Maze Problem - I
Consider a rat placed at (0, 0) in a square matrix of order N * N. It has to reach the destination at (N - 1, N - 1).
Find all possible paths that the rat can take to reach from source to destination. The directions in which the rat can
move are 'U'(up), 'D'(down), 'L' (left), 'R' (right). Value 0 at a cell in the matrix represents that it is blocked and
rat cannot move to it while value 1 at a cell in the matrix represents that rat can be travel through it.
gfg - https://practice.geeksforgeeks.org/problems/rat-in-a-maze-problem/1

Note:
a.  In a path, no cell can be visited more than one time.
b.  Source node as well as destination node may have value == 0.
*/

//  Method 1. Backtracking or Top Down Approach in Recursion
//  Running time = O(4^(n^2))
//  Auxiliary space = O(4^(n^2))

#include <bits/stdc++.h>
using namespace std;

class Solution {
    public:
    bool isValid(int r, int c, vector<vector<int>> maze) {
        int n = maze.size();
        return(r>=0 && r<n && c>=0 && c<n && maze[r][c] == 1);
    }
    void printAllPathsUtil(int r, int c, int n, vector<vector<int>> maze, vector<pair<int, int>> dir, vector<char> dirChar, map<pair<int, int>, int> &visited, string s, int &numOfPaths, vector<string> &allPaths) {
        visited[{r, c}] = 1;        //  Since we are visiting (r, c) in a current path, mark it as visited
        //cout<<"r = "<<r<<" c = "<<c<<" s = "<<s<<"\n";
        if(r==n-1 && c==n-1) {
            //cout<<s<<" ";
            allPaths.push_back(s);
            numOfPaths++;
            visited[{r, c}] = 0;
            return;
        }
        for(int i=0; i<4; i++) {
            int newR = r + dir[i].first;
            int newC = c + dir[i].second;
            if(isValid(newR, newC, maze) && !visited[{newR, newC}])
            printAllPathsUtil(newR, newC, n, maze, dir, dirChar, visited, s+dirChar[i], numOfPaths, allPaths);    //  Each node has 4 branches {D, L, U, R}
        }
        visited[{r, c}] = 0;    //  Since, the DFS for the current path has completed, mark (r, c) as unvisited again
    }
    vector<string> findPath(vector<vector<int>> &maze, int n) {
        vector<pair<int, int>> dir = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}};    //  The order used here is Down, Left, Right, Up just to make sure a sorted order is maintained
	    vector<char> dirChar = {'D', 'L', 'R', 'U'};                        //  However, it is not at all compulsory and we can use any order
	    map<pair<int, int>, int> visited;
	    string s;
	    vector<string> allPaths;
	    int numOfPaths = 0;
	    if(maze[0][0]==0 || maze[n-1][n-1]==0) allPaths.push_back("-1");
	    elseprintAllPathsUtil(0, 0, n, maze, dir, dirChar, visited, s, numOfPaths, allPaths);
    	//cout<<"\nSo, there are "<<numOfPaths<<" different paths.\n";
    	return allPaths;
    }
};

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<vector<int>> m(n, vector<int> (n,0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> m[i][j];
            }
        }
        Solution obj;
        vector<string> result = obj.findPath(m, n);
        if (result.size() == 0)
            cout << -1;
        else
            for (int i = 0; i < result.size(); i++) cout << result[i] << " ";
        cout << endl;
    }
    return 0;
}
