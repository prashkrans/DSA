/* DP Problem 21b - Unique paths without any obstacles on the grid (LC#62) - Unique Paths
A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).
The robot can only move either down or right at any point in time. The robot is trying to reach
the bottom-right corner of the grid (marked 'Finish' in the diagram below).
How many possible unique paths are there?
Note: There are no obstacles.

Eg. 1. m = 3, n = 7
Ans = 28

Eg. 2. m = 3, n = 3
Ans = 6
1. Right -> Right -> Down -> Down
2. Right -> Down -> Right -> Down
3. Down -> Right -> Right -> Down
4. Down -> Right -> Down -> Right
5. Down -> Down -> Right -> Right
6. Right-> Down -> Down -> Right
*/
//	Method 1 - Mathematics (Permutations) (My method)
//  It only requires the values of m and n and not grid[][]
//	So, it seems that no. of unique paths = total no. of arrangements of m-1 down steps and n-1 right steps
//	hence the ans   =
//	                = (m-1 + n-1)! / (m-1)! / (n-1)!
//	                = (m+n-2)! / (m-1)! / (n-1)!

//	Running time = O(m+n) i.e. linear
//	Auxiliary space = O(1) i.e. constant extra space

#include<iostream>
using namespace std;

class Solution {
public:
    int uniquePaths(int m, int n) {
        --m;    //  No. of downs
        --n;    //  No. of rights
        int N = m+n;
        int l = (m>=n)?m:n;     //  l stores the larger of m and n
        int s = (l==m)?n:m;     //  s stores the smaller of m and n
        long long int ans = 1;  //  int is not sufficient here
        for(int i=l+1; i<=N; i++) ans = ans*i;
        for(int i=1; i<=s; i++) ans = ans/i;    //  after dividing by s int can now hold the ans
        int ansCopy = ans;      //  copying the ans of data type long long int to data type int
        return ansCopy;
    }
};

int main() {
	cout<<"Enter the values m and n (both >= 1)= ";
	int m, n;
	cin>>m>>n;
	Solution sol;
	cout<<"No. of unique paths = \n"<<sol.uniquePaths(m, n)<<"\n";
	return 0;
}

//  Method 2 - Recursion without memoization (O(2^mn), O(1))
//  Method 3 - Tabulation (Top Down Approach) - [DP] (O(mn), O(1))

//  Both methods 2 & 3 could be exactly same as that in Problem 21. Unique Paths With Obstacles
//  but would then need to create the table grid[][] too.
//  Also both these methods would be slower than method 1.
