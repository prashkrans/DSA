/* Graph problem #32.2. Rat in a Maze (Any path)
A Maze is given as N*N binary matrix of blocks where source block is the upper left most block i.e., maze[0][0] and destination block
is lower rightmost block i.e., maze[N-1][N-1]. A rat starts from source and has to reach the destination. The rat can move only in two
directions: forward and down. Print any path along which the rat can escape the maze.
In the maze matrix, 0 means the block is a dead end and 1 means the block can be used in the path from source to destination. Note that
this is a simple version of the typical Maze problem. For example, a more complex version can be that the rat can move in 4 directions
and a more complex version can be with a limited number of moves.

This problem could be solved using two methods:
1.  Backtracking: R.T. = A.S. = O(2^(n^2)) i.e. exponential thus, inefficient
2.  BFS or DFS: R.T. = A.S. = O(n^2)
*/

//  Method 2. Using BFS or DFS to find any single path in which the rat could escape the maze. Here, BFS is used.
//  Note: This method only gives a single and does not give all the paths along which the rat could escape the maze.
//  However: This method is faster O(n^2) than backtracking O(c^(n^2)) where c is the no. of directions allowed. So, when just a
//  single path is required it is better to use BFS or DFS than backtracking.
//  Also, no concept of shortest path exists here when only two (R, D) directions are allowed, i.e. all the paths are
//  the shortest paths from (0, 0) to (n-1, n-1) of equal lengths = ((n-1)-0 + (n-1)-0) = 2n-2. Eg. n = 3 => length = 2*3-2 = 4.

//  Running time = O(BFS or DFS) = O(n^2) = O(V) since we are using a matrix to represent the maze where each cell acts as a node.
//  Auxiliary space = O(number of cells) = O(n^2) or O(V) due to the queue, visited and the parent array.

#include<iostream>
#include<vector>
#include<queue>
#include<map>
using namespace std;

bool isValid(pair<int, int> v, vector<vector<int>> maze) {
    int n = maze.size();
    int r = v.first;
    int c = v.second;
    return(r>=0 && r<n && c>=0 && c<n && maze[r][c] == 1);
}

vector<pair<int, int>> findPath(int n, vector<vector<int>> maze) {
	vector<pair<int, int>> path;
	queue<pair<int, int>> Q;
	map<pair<int, int>, int> visited;
	map<pair<int, int>, pair<int, int>> parent;
	vector<pair<int, int>> dir = {{0, 1}, {1, 0}};      //  Here, only two directions are allowed 1. Right and 2. Downwards
	pair<int, int> src = {0, 0};
	Q.push(src);
	visited.insert({src, 1});
	parent.insert({src, src});
	while(!Q.empty()) {
		pair<int, int> u = Q.front();
		Q.pop();
		for(auto d : dir) {
			pair<int, int> v = {u.first + d.first , u.second + d.second};
			if(isValid(v, maze) && !visited[v]) {
				Q.push(v);
				visited.insert({v, 1});                 //  Using insert here instead of [] which could also be used here
				parent.insert({v, u});
			}
		}
	}
	if(visited.count({n-1, n-1})==0) return path;       //  If the cell (n-1, n-1) is not visited => there exists no path along which the rat could escape the maze
	pair<int, int> u = {n-1, n-1};                      //  Else if the cell (n-1, n-1) is visited => reverse the order of path from dest to src.
	while(parent[u]!=u) {
		path.push_back(u);
		u = parent[u];
	}
	path.push_back(u);
	int pSize = path.size();
	for(int i=0; i<pSize/2; i++) {                      //  Here, we have used a vector to store the path from dest to src and then reverse it to get the path from src to dest.
		pair<int, int> temp;                            //  Alternatively a stack could also be used to reverse the path.
		temp = path[i];
		path[i] = path[pSize-i-1];
		path[pSize-i-1] = temp;
	}
	return path;
}

int main() {
	int n;
	cin>>n;
	vector<vector<int>> maze(n, vector<int>(n));
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) cin>>maze[i][j];
	}
	vector<pair<int, int>> path = findPath(n, maze);
	if(path.empty()) cout<<"No path exist\n";
	else {
        cout<<"The path along which the rat escapes the maze is:\n";
        vector<pair<int, int>>::iterator it = path.begin();
        cout<<"("<<it->first<<", "<<it->second<<")";
        for(it = next(path.begin(),1); it!=path.end(); it++) cout<<" -> ("<<it->first<<", "<<it->second<<")"; cout<<"\n";   //  Printing the path as a vector
        vector<vector<int>> pathMatrix(n, vector<int>(n, 0));
        for(int i=0; i<path.size(); i++) pathMatrix[path[i].first][path[i].second] = 1;                                     //  Printing the path as a matrix
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) cout<<pathMatrix[i][j]<<" ";
            cout<<"\n";
        }
	}
	return 0;
}

/* Sample Input
5
1 0 1 0 1
1 1 1 0 1
0 1 0 1 0
0 1 1 1 0
0 0 1 1 1
*/
