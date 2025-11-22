/* Graph Prob. 35.1b. Minimum Steps to Reach a Target by a Knight
Given a square chessboard, the initial position of Knight and position of a target. Find out the minimum
steps a Knight will take to reach the target position.

Note:
The initial and the target position coordinates of Knight have been given according to 1-base indexing.
This problem could be solved using two methods:
1. BFS (Preferred as easier to understand): R.T. = O(n*m) or O(n^2) i.e. quadratic time
2. DP + Careful selection of direction to move in: R.T. = O(n*m) A.S. = O(n*m) or O(n^2)

gfg - https://practice.geeksforgeeks.org/problems/steps-by-knight5927/1/
*/

//  Method 1.1. BFS but uses 2D vector for visited and dist
//  Running time = O(n^2 + c) ~ O(n^2)
//  Auxiliary space = O(n^2)
//  Passess all the the test cases

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isValid(pair<int, int> v, int n) {                 //  It validates whether i and j are not out of bounds
        int i = v.first, j = v.second;
        //if(i<0 || i>=n || j<0 || j>=n) return false;      //  if 0 based indexing is used
        if(i<1 || i>n || j<1 || j>n) return false;          //  if 1 based indexing is used
        return true;                                        //  I might have lost an opportunity with soroco because of not returning true here
    }

    int bfs(int i, int j, int x, int y, int n) {
        if(i==x && j==y) return 0;
        queue<pair<int, int>> Q;
        vector<vector<int>> visited(n, vector<int>(n, 0));  //  0 based indexing is used for visited and dist tables
        vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
        vector<vector<int>> dir = {{1, 2}, {2, 1}, {-1, -2}, {-2, -1}, {-1, 2}, {2, -1}, {1, -2}, {-2, 1}};
        Q.push({i, j});
        visited[i-1][j-1] = 1;
        dist[i-1][j-1] = 0;
        while(!Q.empty()) {
            pair<int, int> u = Q.front();
            Q.pop();
            for(int k=0; k<8; k++) {
                pair<int, int> v;
                v.first = u.first + dir[k][0];
                v.second = u.second + dir[k][1];
                if(isValid(v, n) && !visited[v.first-1][v.second-1]) {
                    Q.push(v);
                    visited[v.first-1][v.second-1] = 1;
                    dist[v.first-1][v.second-1] = 1 + dist[u.first-1][u.second-1];
                    if(v.first == x && v.second == y) return dist[x-1][y-1];
                }
            }
        }
        if(dist[x-1][y-1]==INT_MAX) return -1;
        else return dist[x-1][y-1];
    }

	int minStepToReachTarget(vector<int>&src, vector<int>&dest, int n) {
	    int i = src[0], j = src[1];
	    int x = dest[0], y = dest[1];
	    return bfs(i, j, x, y, n);
	}
};

int main() {
	int tc;
	cin >> tc;
	while(tc--){
		vector<int>KnightPos(2);
		vector<int>TargetPos(2);
		int N;
		cin >> N;
		cin >> KnightPos[0] >> KnightPos[1];
		cin >> TargetPos[0] >> TargetPos[1];
		Solution obj;
		int ans = obj.minStepToReachTarget(KnightPos, TargetPos, N);
		cout << ans <<"\n";
	}
	return 0;
}


//  Method 1.2. Same as 1.1. i.e. BFS but uses map instead of 2D vector for visited and dist
//  Running time = O(n^2 + nlogn) ~ O(n^2)
//  Auxiliary space = O(n^2)
//  Passes only 14 out 16 test cases

class Solution {
public:
    bool isValid(pair<int, int> v, int n) {                 //  It validates whether i and j are not out of bounds
        int i = v.first, j = v.second;
        //if(i<0 || i>=n || j<0 || j>=n) return false;      //  if 0 based indexing is used
        if(i<1 || i>n || j<1 || j>n) return false;          //  if 1 based indexing is used
        return true;                                        //  I might have lost an opportunity with soroco because of not returning true here
    }

    int bfs(int i, int j, int x, int y, int n) {
        if(i==x && j==y) return 0;
        queue<pair<int, int>> Q;
        //vector<vector<int>> visited(n, vector<int>(n, 0));  //  0 based indexing is used for visited and dist tables
        //vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
        map<pair<int, int>, int> visited;
        map<pair<int, int>, int> dist;
        vector<vector<int>> dir = {{1, 2}, {2, 1}, {-1, -2}, {-2, -1}, {-1, 2}, {2, -1}, {1, -2}, {-2, 1}};
        Q.push({i, j});
        //visited[i-1][j-1] = 1;
        //dist[i-1][j-1] = 0;
        visited[{i, j}] = 1;
        dist[{i, j}] = 0;
        while(!Q.empty()) {
            pair<int, int> u = Q.front();
            Q.pop();
            for(int k=0; k<8; k++) {
                pair<int, int> v;
                v.first = u.first + dir[k][0];
                v.second = u.second + dir[k][1];
                //if(isValid(v, n) && !visited[v.first-1][v.second-1]) {
                if(isValid(v, n) && !visited[v]) {
                    Q.push(v);
                    //visited[v.first-1][v.second-1] = 1;
                    //dist[v.first-1][v.second-1] = 1 + dist[u.first-1][u.second-1];
                    //if(v.first == x && v.second == y) return dist[x-1][y-1];
                    visited[v] = 1;
                    dist[v] = 1 + dist[u];
                    if(v.first == x && v.second == y) return dist[v];
                }
            }
        }
        //if(dist[x-1][y-1]==INT_MAX) return -1;
        //else return dist[x-1][y-1];
        return -1;
    }

	int minStepToReachTarget(vector<int>&src, vector<int>&dest, int n) {
	    int i = src[0], j = src[1];
	    int x = dest[0], y = dest[1];
	    return bfs(i, j, x, y, n);
	}
};
