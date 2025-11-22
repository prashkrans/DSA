/* Problem 20++ - [Not DP] Minimum Cost Path Sum with movenment in L, R, U, D (all 4 directions) allowed
Given a two dimensional grid of size m x n, each cell of which contains integer cost which represents a cost to
traverse through that cell, we need to find a path from top left cell to bottom right cell by which total cost 
incurred is minimum.
Note : It is assumed that negative cost cycles do not exist in input matrix.
This problem is an extension of the problem 20 i.e. Min Cost Path Sum with only right and bottom moves allowed.
Gfg - https://www.geeksforgeeks.org/minimum-cost-path-left-right-bottom-moves-allowed/

It is not possible to solve this problem using dynamic programming similar to previous problem because here current 
state depends not only on right and bottom cells but also on left and upper cells. 
We solve this problem using DJIKSTRA'S ALGORITHM 
*/
//	To be completed when revising graphs
#include<iostream>
#include<vector>
using namespace std;

int main(){
	cout<<"Enter the value of m and n = ";
	int m, n;
	cin>>m>>n;
	vector<vector<int>> c(m, vector<int>(n));
	for(int i=0; i<m; i++) {
		for(int j=0; j<n; j++) cin>>c[i][j];
	}
	cout<<"The minimum cost path sum = "<<minPathSum(0, 0, 0, c);
	return 0;
}