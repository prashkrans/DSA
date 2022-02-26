/* Graph problem - 29. LC#286. Walls and Gates
You are given a m x n 2D grid initialized with these three possible values.
	1.	-1:	A wall or an obstacle
	2.	0:	A gate
	3.	INF:Infinity means an empty room. We use the value 2^31 - 1 = 2147483647 to represent INF as
		you may assume that the distance to a gate is less than 2147483647
Fill each empty room with the distance to its nearest gate. If it is impossible to reach a gate, it should
be filled with INF.
Note - Traversal is allowed only in four directions
Hint: This problem can be solved exactly by the method used to solve the problem LC#542 01 Matrix

Example 1:
Grid:	INF	-1	0	INF
		INF	INF	INF	-1
		INF	-1	INF	-1
		0	-1	INF	INF

Output:	3	-1	0	1
		2	2	1	-1
		1	-1	2	-1
		0	-1	3	4

This problem can be solved using two methods
1. BFS (Best solution)
2. DFS
Both has R.T. = O(m*n) i.e. two traversals of the rooms matrix
*/

//	Method 1 - BFS
//	We first enqueue all cells containing the gates i.e. rooms[i][j] == 0 and loop till queue is not empty.
//	Note, here the visited array is not required as the if(rooms[vi][vj] > 1 + rooms[ui][uj]) => v is not visited
//	Running time = O(BFS) = O(m*n). However, note that 2 passes are made (1. for all the 0s and 2. for the BFS)
//	Auxiliary space = O(1) as the matrix rooms itself is modified and no visited array is used.

#include<iostream>
#include<vector>
#include<queue>
using namespace std;

#define INF INT_MAX

class Solution {
public:
	bool isValid(pair<int, int> v, int m, int n) {
		int i = v.first;
		int j = v.second;
		if(i<0||i>=m||j<0||j>=n) return false;
		else return true;
	}
    void wallsAndGates(vector<vector<int>> &rooms) {
        int m = rooms.size();
        if(m==0) return;
        int n = rooms[0].size();
        queue<pair<int, int>> Q;
        vector<pair<int, int>> dir = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                if(rooms[i][j] == 0)
                    Q.push({i, j});
            }
        }
        while(!Q.empty()) {
            pair<int, int> u = Q.front();
            Q.pop();
            for(int i=0; i<4; i++) {
                pair<int, int> v;
                v.first = u.first + dir[i].first;
                v.second = u.second + dir[i].second;
                if(isValid(v, m, n) && rooms[v.first][v.second] > 1 + rooms[u.first][u.second]) {
                    Q.push(v);
                    rooms[v.first][v.second] = 1 + rooms[u.first][u.second];
                }
            }
        }
    }
};

int main() {
	int m, n;
	cin>>m>>n;
	vector<vector<int>> rooms(m, vector<int>(n));
	for(int i=0; i<m; i++) {
		for(int j=0; j<n; j++) {
            cin>>rooms[i][j];
            if(rooms[i][j] == 2) rooms[i][j] = INF;
		}
	}
	cout<<"Rooms = \n";
	for(int i=0; i<m; i++) {
		for(int j=0; j<n; j++) cout<<rooms[i][j]<<"\t";
		cout<<"\n";
	}
	Solution obj;
	obj.wallsAndGates(rooms);
	cout<<"Ans = \n";
	for(int i=0; i<m; i++) {
		for(int j=0; j<n; j++) cout<<rooms[i][j]<<"\t";
		cout<<"\n";
	}
	return 0;
}

/* Sample input
4 4
2   -1  0   2
2   2   2   -1
2   -1  2   -1
0   -1  2   2
//  2 represents INF i.e. INT_MAX
*/

//	Method 2 - DFS
//  Incomplete
