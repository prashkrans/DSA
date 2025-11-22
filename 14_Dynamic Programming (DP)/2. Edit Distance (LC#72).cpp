/*DP-Problem 2 (LC#72) :
Given two strings word1 and word2, return the minimum number of operations required to convert word1 to word2.
You have the following three operations permitted on a word:
Insert a character
Delete a character
Replace a character

Input: word1 = "horse", word2 = "ros"
Output: 3
Explanation: 
horse -> rorse (replace 'h' with 'r')
rorse -> rose (remove 'r')
rose -> ros (remove 'e')
*/

// 	Running time = O(mn) i.e. quadratic if memoization used
//  else R.T. = O(exponential) without memoization

//	1.	editDistance() using suffixes, 2 for loops & memoization(DP table).
// 	Bottom up approach
// 	Best Solution (0ms-100%, 7.2mb-89%)

class Solution {
public:
    int minOf3(int a, int b, int c){
        return min(a, min(b, c));
    }
	
    int minDistance(string word1, string word2) {
        int m = word1.size();
        int n = word2.size();
        int DP[m+1][n+1];
        for(int i=0; i<=m; i++) DP[i][n] = m-i;	//	DP matrix is initialised with base cases
        for(int j=0; j<=n; j++) DP[m][j] = n-j;
        for(int i=m-1; i>=0; i--){
            for(int j=n-1; j>=0; j--){
                if(word1[i]==word2[j]) DP[i][j] = DP[i+1][j+1];
                else DP[i][j] = 1 + minOf3(DP[i][j+1], DP[i+1][j], DP[i+1][j+1]);
            }
        }
        return DP[0][0];
    }
};

//	2.	editDistance() using suffixes, recursion & memoization.
// Bottom Up Approach
void printMatrix(int mat[1000][1000], int m, int n){
        for(int i=0; i<=m; i++){
            for(int j=0; j<=n; j++) cout<<mat[i][j]<<" ";
            cout<<"\n";
        }
    }
    
int minOf3(int a, int b, int c){
    return min(a, min(b, c));
}

int editDistance(string s1, string s2, int i, int j, int DP[1000][1000]){
    int m = s1.size();
    int n = s2.size();
    if(i==m||j==n) return DP[i][j];
    if(DP[i][j]!=-1) return DP[i][j];
    if(s1[i]==s2[j]) 
            DP[i][j] = editDistance(s1, s2, i+1, j+1, DP);

    else{
            int ins = editDistance(s1, s2, i, j+1, DP);
            int del = editDistance(s1, s2, i+1, j, DP);
            int rep = editDistance(s1, s2, i+1, j+1, DP);
            DP[i][j] = 1 + minOf3(ins, del, rep);
    }
    return DP[i][j];
}

int minDistance(string word1, string word2) {
    //vector<vector<int>> DP;
    int DP[1000][1000];		// 	Here can't use DP[m][n] as it wont pass through the function.
    int m = word1.size();	//	Therefore used the max size as required by the problem.
    int mCopy = m;
    int n = word2.size();
    int nCopy = n;
    for(int i=0; i<=m; i++){
        for(int j=0; j<=n; j++) DP[i][j] = -1;
    }
    for(int i=0; i<=m; i++) DP[i][n] = mCopy--;
    for(int j=0; j<=n; j++) DP[m][j] = nCopy--;       
    //printMatrix(DP, m, n);    // DP matrix is initialised with base cases
    //cout<<"Break\n";
    DP[0][0] = editDistance(word1, word2, 0, 0, DP);
    //printMatrix(DP, m, n);    // Final DP matrix
    return DP[0][0];
}

//	3.	editDistance() using prefixes, 2 for loops (nested) & memoization. (Best Solution)
// 		Using prefixes and 2 loops (nested)
// 		Here the "" i.e. empty string is considered before the first character in a string.
// 		Thus, we need to compare s1[i-1] with s2[j-1] for the current iteration of (i, j).
// 		If, we consider "" to be at the end we compare s1[i] with s2[j] for the (i, j).

int minOf3(int a, int b, int c){
    if(b<a) a = b;  // Storing the smallest in a
    if(c<a) a = c;
    return a;        
}

int minDistance(string s1, string s2) {
    int m = s1.size();
    int n = s2.size();
    int DP[m+1][n+1];
    for(int i=0; i<=m; i++) DP[i][0] = i;
    for(int j=0; j<=n; j++) DP[0][j] = j;
    for(int i=1; i<=m; i++){
        for(int j=1; j<=n; j++){
            if(s1[i-1]==s2[j-1]) DP[i][j] = DP[i-1][j-1];
            else DP[i][j] = 1 + minOf3(DP[i][j-1], DP[i-1][j], DP[i-1][j-1]);
        }
    }
    return DP[m][n];
}

//	4. editDistance() using prefixes, recursion & memoization.

//	5.	Without memoization i.e. no DP table created, thus inefficient. Order(exponential)
int minOf3(int a, int b, int c){
    int smallest = a;
    if(b<smallest) smallest = b;
    if(c<smallest) smallest = c;
    return smallest;
}

int editDist(string A, string B, int i, int j){
    int m = A.size();
    int n = B.size();
    if(i==m&&j==n) return 0;
    if(i==m&&j<n) return n - j;
    if(j==n&&i<m) return m - i;
    if(A[i] == B[j]) return editDist(A, B, i+1, j+1);
    else{
        return 1 + minOf3(editDist(A, B, i, j+1), editDist(A, B, i+1, j), editDist(A, B, i+1, j+1));
    }
}

int minDistance(string A, string B) {        
    return editDist(A, B, 0, 0);
}