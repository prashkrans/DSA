/* DP Problem 23. LC#542. 01 Matrix
Given an m x n binary matrix mat, return the distance of the nearest 0 for each cell.
The distance between two adjacent cells is 1.

Example 1:
Input: mat = [[0,0,0],[0,1,0],[1,1,1]]
Output: [[0,0,0],[0,1,0],[1,2,1]]

Constraints:
m == mat.length;	n == mat[i].length
1 <= m, n <= 10^4;	1 <= m * n <= 10^4
mat[i][j] is either 0 or 1.
There is at least one 0 in mat.

This can be solved by using three methods
1. 	Brute force
	Time complexity: O((n*m)^2) as we iterate over the entire matrix for each 1 in the matrix.
	Space complexity: O(n*m) as no extra space required than the vector<vector<int>> dist
2.	DP
	Time complexity: O(2(n*m)) ~ O(n*m) as 2 passes of n*m each were made
	Space complexity: O(n*m) as no additional space required than dist vector<vector<int>> DP
3.	BFS
	Time complexity: O(2(n*m)) ~ O(n*m) as 2 passes of n*m each were made once to enqueue all the zeroes and then for the
	BFS where the new cells are added to the queue only if their current distance is greater than the calculated distance, => 
	cells are not likely to be added multiple times.
	Space complexity: O(n*m) as additional space required for queue other than vector<vector<int>> dist 
*/

//	Method 2. DP (2 passes)
//	The distance of a cell from 0 can be calculated if we know the nearest distance for all the neighbours, in which case 
//	the distance is minimum distance of any neightbour + 1. Hence, DP can be used here.

//	For each 1, the minimum path to 0 can be in any direction. So, we need to check all the 4 direction. In one iteration 
//	from top to bottom, we can check left and top directions, and we need another iteration from bottom to top to check for 
//	right and bottom direction.

class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int n = mat.size();
        if(n==0) return mat;
        int m = mat[0].size();
        vector<vector<int>> DP(n, vector<int>(m, INT_MAX-10000));
        for(int i=0; i<n; i++) {          			//	First pass: check for left and top
            for(int j=0; j<m; j++) {
                if(mat[i][j]==0) DP[i][j] = 0;
                else if(i==0&&j==0) continue;		//	IMP - for (0, 0) DP(0, 0) can be INT_MAX or 0	
                else if(i==0) DP[i][j] = min(DP[i][j], 1 + DP[i][j-1]);
                else if(j==0) DP[i][j] = min(DP[i][j], 1 + DP[i-1][j]);
                else DP[i][j] = min(DP[i][j], 1 + min(DP[i][j-1], DP[i-1][j]));
            }       
        }
        for(int i=n-1; i>=0; i--) {         		//	Second pass: check for bottom and right
            for(int j=m-1; j>=0; j--) {
                if(mat[i][j]==0) DP[i][j] = 0;
                else if(i==n-1&&j==m-1) continue;	//	IMP for (n-1, m-1) DP(n-1, m-1) can be the either 0 or (1 + min(DP(n-1, m-2), DP(n-2, m-1))
                else if(i==n-1) DP[i][j] = min(DP[i][j], 1 + DP[i][j+1]);
                else if(j==m-1) DP[i][j] = min(DP[i][j], 1 + DP[i+1][j]);
                else DP[i][j] = min(DP[i][j], 1 + min(DP[i][j+1], DP[i+1][j]));
            }       
        }
        return DP;
    }
};

//	Method 3. BFS (2 passes in average case)
//	Running time = O(n*m)
//	Auxiliary space = O(n*m) for the dist table

class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int n = mat.size();
        if(n==0) return {{}};
        int m = mat[0].size();
        int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
        queue<pair<int, int>> Q;        
        for(int i=0; i<n; i++) {
            for(int j=0; j<m; j++) if(mat[i][j] == 0) {
                dist[i][j] = 0;
                Q.push({i, j});
            }
        }
        while(!Q.empty()) {
            pair<int, int> u = Q.front();
            Q.pop();
            for(int i=0; i<4; i++) {
                //pair<int, int> v = {u.first + directions[i][0], u.second + directions[i][1]};
                int r = u.first + directions[i][0];
                int c = u.second + directions[i][1];
                if(r>=0 && r<n && c>=0 && c<m) {
                    //dist[r][c] = min(dist[r][c], 1 + dist[u.first][u.second]);    //  Don't use this as we need to push v in queue only when dist[r][c] is updated
                    if(dist[r][c] > 1 + dist[u.first][u.second]) {
                        dist[r][c] = 1 + dist[u.first][u.second];
                        Q.push({r, c});
                    }                   
                }
            }
            
        }
        return dist;
    }
};