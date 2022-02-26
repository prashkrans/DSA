/* DP Problem 21 - Unique Paths with obstacles on the grid (LC#63) - Unique Paths II
A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).
The robot can only move either down or right at any point in time. The robot is trying to reach the
bottom-right corner of the grid (marked 'Finish' in the diagram below).
Now consider if some obstacles are added to the grids. How many unique paths would there be?
An obstacle and space is marked as 1 and 0 respectively in the grid.
Note - (0, 0) denotes 'Start' and (m-1, n-1) denotes 'Finish'
*/

// 	Method 1 - Recursion without memoization (My Method)
//	Running Time = O(2^mn) i.e. exponential as at each element in the grid we have two options i.e. go right or go down
//	Auxiliary Space = O(1) i.e. constant extra space
//	Time limit gets exceeded in leetcode
/*
#include<iostream>
#include<vector>
using namespace std;

int uniquePaths(int i, int j, vector<vector<int>> c, int ans) {
	int m = c.size();
	int n = c[0].size();
	if(i==m-1 && j==n-1) {
        if(c[i][j] == 1) return 0;
        else return ++ans;
	}
	else if(c[i][j] == 1) return ans;
	else if(i==m-1 && j<n-1) return uniquePaths(i, j+1, c, ans);
	else if(i<m-1 && j==n-1) return uniquePaths(i+1, j, c, ans);
	else {
		ans = uniquePaths(i, j+1, c, ans);
		ans = uniquePaths(i+1, j, c, ans);
		return ans;
	}
}

int main() {
	cout<<"Enter the values m and n = ";
	int m, n;
	cin>>m>>n;
	vector<vector<int>> c(m, vector<int>(n));
	cout<<"Enter the values of the grid (only 0s and 1s) = \n";
	for(int i=0; i<m; i++) {
		for(int j=0; j<n; j++) cin>>c[i][j];
	}
	cout<<"Ans = "<<uniquePaths(0, 0, c, 0);
	return 0;
}
*/

//	Method 2 - Tabulation (Top Down Approach) [DP] - Best Solution
//	Running Time = O(mn) i.e. quadratic
//	Auxiliary Space = O(mn) i.e. quadratic or O(1) i.e. constant if we modify the table grid itself

#include<iostream>
using namespace std;                                                //  Exactly the same function but uses vector and breaks the for loop,
                                                                    //  if an obstacle is found in the 0th row and column thus marginally reducing time
int uniquePathswithObstacles(int m, int n, int grid[][1000]) {      //  int uniquePathsWithObstacles(vector<vector<int>> grid) {
	for(int i=0; i<m; i++) {                                        //      int R = grid.size();
        for(int j=0; j<n; j++) {                                    //      int C = grid[0].size();
            if(i==0 && j==0) {                                      //      vector<vector<int>> DP(R, vector<int>(C, 0));
                if(grid[0][0] == 1) return 0;                       //      if(grid[0][0] == 1) return 0;
                else grid[0][0] = 1;                                //      else DP[0][0] = 1;
            }                                                       //      for(int j=1; j<C; j++) {
            else if(grid[i][j] == 1) grid[i][j] = 0;                //          if(grid[0][j] == 1) break;      //  Note - break is used as no need to go further
            else if(i==0 and j>0) grid[0][j] = grid[0][j-1];        //          else DP[0][j] = DP[0][j-1];     //  in the 0th row and column after the first obstacle
            else if(i>0 and j==0) grid[i][0] = grid[i-1][j];        //      }
            else grid[i][j] = grid[i][j-1] + grid[i-1][j];          //      for(int i = 1; i<R; i++) {
        }                                                           //          if(grid[i][0] == 1) break;
	}                                                               //          else DP[i][0] = DP[i-1][0];
	for(int i=0; i<m; i++) {                                        //      }
		for(int j=0; j<n; j++) cout<<grid[i][j]<<" ";               //      for(int i=1; i<R; i++) {
		cout<<"\n";                                                 //          for(int j=1; j<C; j++) {
	}                                                               //              if(grid[i][j] == 1) DP[i][j] = 0;
	return grid[m-1][n-1];                                          //              else DP[i][j] = DP[i][j-1] + DP[i-1][j];
}                                                                   //          }
                                                                    //      }
int main() {                                                        //      return DP[R-1][C-1];
	cout<<"Enter the values m and n = ";                            //  }
	int m, n;
	cin>>m>>n;
	int grid[m][1000];
	cout<<"Enter the values of the grid (only 0s and 1s) = \n";
	for(int i=0; i<m; i++) {
		for(int j=0; j<n; j++) cin>>grid[i][j];
	}
	cout<<"Ans = \n"<<uniquePathswithObstacles(m, n, grid)<<"\n";
	return 0;
}

