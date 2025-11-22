/* DP Problem 20 - Minimum Path Sum (LC#64)
Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right,
which minimizes the sum of all numbers along its path.
Note: You can only move either down or right at any point in time.
Eg. 1 -	1 5 1
		2 3 1
		1 6 1
Ans - 8 i.e. 1->2->3->1->1 has the minimum path sum
*/

// 	Method 1 - Using recursion without memoization (My Method)
// 	Running Time = O(2^mn) i.e. exponential since each element (i, j) has two options either go left or go down
//	Auxiliary Space = O(mn) i.e. quadratic
//	Time limit gets exceeded in leetcode
/*
#include<iostream>
#include<vector>
using namespace std;

int minPathSum(int i, int j, int sum, vector<vector<int>> &c) {
	int m = c.size();
	int n = c[0].size();
	if(i==m-1 && j==n-1) return sum + c[i][j];
	else if(i==m-1 && j!=n-1) {
		sum+=c[i][j];
		return minPathSum(i, j+1, sum, c);
	}
	else if(i!=m-1 && j==n-1) {
		sum+=c[i][j];
		return minPathSum(i+1, j, sum, c);
	}
	else {
		sum+=c[i][j];
		return min(minPathSum(i, j+1, sum, c), minPathSum(i+1, j, sum, c));
	}
}

int main() {
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
*/

//	Method 2 - Tabular form of method 1 i.e. using recursion without memoization (My Method) - Ignore this
//	Both method 1 and 2 are not DP
// 	Running Time = O(2^mn) i.e. exponential since each element (i, j) has two options either go left or go down
//	Auxiliary Space = O(mn) i.e. quadratic
//	Time limit gets exceeded in leetcode
/*
#include<iostream>
#include<vector>
using namespace std;

void minPathSum(int i, int j, int sum, vector<vector<int>> &c, vector<vector<int>> &cmultvC) {
	int m = c.size();
    int n = c[0].size();
    int val;
    if(i==m-1 && j!=n-1) {
        sum+=c[i][j];
        cmultvC[i][j] =  min(cmultvC[i][j], sum);
        minPathSum(i, j+1, sum, c, cmultvC);
    }
    else if(i!=m-1 && j==n-1) {
        sum+=c[i][j];
        cmultvC[i][j] =  min(cmultvC[i][j], sum);
        minPathSum(i+1, j, sum, c, cmultvC);
    }
    else {
        sum+=c[i][j];
        cmultvC[i][j] =  min(cmultvC[i][j], sum);
        if(i==m-1 and j==n-1) return;
        minPathSum(i, j+1, sum, c, cmultvC);
        minPathSum(i+1, j, sum, c, cmultvC);
    }
}

int main() {
	cout<<"Enter the value of m and n = ";
	int m, n;
	cin>>m>>n;
	cout<<"Enter the values of matrix c = \n";
	vector<vector<int>> c(m, vector<int>(n));
	for(int i=0; i<m; i++) {
		for(int j=0; j<n; j++) cin>>c[i][j];
	}
	vector<vector<int>> cmultvC(m, vector<int>(n, INT_MAX));
	minPathSum(0, 0, 0, c, cmultvC);
	cout<<"The cumulative cost table = \n";
	for(int i=0; i<m; i++){
        for(int j=0; j<n; j++) cout<<cmultvC[i][j]<<" ";
        cout<<"\n";
	}
	cout<<"The minimum path sum = "<<cmultvC[m-1][n-1];
	return 0;
}
*/

//  Method 3 - Tabulation (Bottom up approach & not top down appraoach [Verify]) - DP (Best Solution)
//  It should be bottom up approach as we are building the table from {0, 0} to {m-1, n-1}
// 	Running Time = O(mn) i.e. quadratic since each value at DP(i, j) = min(DP(i, j-1), DP(i-1, j)) => O(1) * O(mn) = O(mn)
//	Auxiliary Space = O(mn) i.e. quadratic or O(1) if c itself is modified

#include<iostream>
#include<vector>
using namespace std;

int minPathSum(int m, int n, vector<vector<int>> c) {						//	Almost the same function but here we modify the table c itself instead of a new DP table
	vector<vector<int>> DP(m, vector<int>(n));								//	class Solution {
	for(int i=0; i<m; i++) {                                                //	public:
		for(int j=0; j<n; j++) {                                            //	    int minPathSum(vector<vector<int>>& c) {
			if(i==0&&j==0) DP[i][j] = c[i][j];                              //	        int m = c.size();
			else if(i==0&&j>0) DP[i][j] = DP[i][j-1] + c[i][j];             //	        int n = c[0].size();
			else if(i>0&&j==0) DP[i][j] = DP[i-1][j] + c[i][j];             //	        for(int i=0; i<m; i++) {
			else DP[i][j] = min(DP[i][j-1], DP[i-1][j]) + c[i][j];          //	            for(int j=0; j<n; j++) {
		}                                                                   //	                if(i==0&&j==0) continue;
	}                                                                       //	                else if(i==0&&j>0) c[i][j] = c[i][j-1] + c[i][j];
	for(int i=0; i<m; i++){                                                 //	                else if(i>0&&j==0) c[i][j] = c[i-1][j] + c[i][j];
		for(int j=0; j<n; j++) cout<<DP[i][j]<<" ";                         //	                else c[i][j] = min(c[i][j-1], c[i-1][j]) + c[i][j];
		cout<<"\n";                                                         //	            }
	}                                                                       //	        }
	cout<<"The minimum cost path sum = ";                                   //	        return c[m-1][n-1];
	return DP[m-1][n-1];                                                    //	    }
}                                                                           //	};

int main() {																// 	Exactly the same function as above except a different way to use the for loops
	cout<<"Enter the value of m and n = ";									//	class Solution {
	int m, n;                                                               //	public:
	cin>>m>>n;                                                              //	    int minPathSum(vector<vector<int>>& c) {
	cout<<"Enter the values of matrix c = \n";                              //	        int m = c.size();
	vector<vector<int>> c(m, vector<int>(n));                               //	        int n = c[0].size();
	for(int i=0; i<m; i++) {                                                //	        for(int j=1; j<n; j++) c[0][j] += c[0][j-1];
		for(int j=0; j<n; j++) cin>>c[i][j];                                //	        for(int i=1; i<m; i++) c[i][0] += c[i-1][0];
	}                                                                       //	        for(int i=1; i<m; i++) {
	cout<<minPathSum(m, n, c);                                              //	            for(int j=1; j<n; j++) c[i][j] += min(c[i][j-1], c[i-1][j]);
	return 0;                                                               //	        }
}                                                                           //	        return c[m-1][n-1];
                                                                            //	    }
                                                                            //	};
//	Here we were only allowed to move down or right
//	hence DP[i][j] = c[i][j] + min(c[i][j-1], c[i-1][j]);
//	However, if we are allowed to move down, right and diagonally right, a simple modification is required
//	thus DP[i][j] = c[i][j] + min(c[i-1][j-1], min(c[i][j-1], c[i-1][j]));
//	where i = 1 to n and j = 1 to n i.e. except the 0th row and column

//	Extension of method 3 i.e. when we even want to print the path of minimum sum along with the MPS
/*
#include<iostream>
#include<vector>
using namespace std;

int minPathSum(int m, int n, vector<vector<int>> c) {
	vector<vector<int>> DP(m, vector<int>(n));
	for(int i=0; i<m; i++) {
		for(int j=0; j<n; j++) {
			if(i==0&&j==0) DP[i][j] = c[i][j];
			else if(i==0&&j>0) DP[i][j] = DP[i][j-1] + c[i][j];
			else if(i>0&&j==0) DP[i][j] = DP[i-1][j] + c[i][j];
			else DP[i][j] = min(DP[i][j-1], DP[i-1][j]) + c[i][j];
		}
	}
	for(int i=0; i<m; i++){
		for(int j=0; j<n; j++) cout<<DP[i][j]<<" ";
		cout<<"\n";
	}
	int i = m-1;							//	From here
	int j = n-1;
	vector<vector<int>> p;
	while(i>=0) {
        p.push_back({i, j});
        int val = DP[i][j] - c[i][j];		// 	This prints the order of path with minimum path
        if(i==0&&j>0) j--;
        else if(i>0&&j==0) i--;
        else {
            if(DP[i][j-1]==val) j--;
            else i--;
        }
    }
    cout<<"The path with minimum sum = ";
    for(int i=p.size()-1; i>0; i--) cout<<c[p[i][0]][p[i][1]]<<"=>";
    cout<<c[0][0];
    cout<<"\n";								// Till Here
	cout<<"The minimum cost path sum = ";
	return DP[m-1][n-1];
}

int main() {
	cout<<"Enter the value of m and n = ";
	int m, n;
	cin>>m>>n;
	cout<<"Enter the values of matrix c = \n";
	vector<vector<int>> c(m, vector<int>(n));
	for(int i=0; i<m; i++) {
		for(int j=0; j<n; j++) cin>>c[i][j];
	}
	cout<<minPathSum(m, n, c);
	return 0;
}
*/
