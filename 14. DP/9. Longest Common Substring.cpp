/* DP-Problem 9 - Longest Common Substring (not LC Subsequence)
Given two strings ‘X’ and ‘Y’, find the length of the longest common substring.
Example 1:
Input: s1 = “abcdxyz”, s2 = “xyzabcd”
Output: 3
Explanation:
The longest common substring is “abcd” and is of length 4.
GFG - https://www.geeksforgeeks.org/longest-common-substring-dp-29/
*/

//	1.	Tabulaton (Top Down Approach)
//		Running Time = O(m*n)
//		Space Complexity = O(m*n)

int LCSubstring(string s1, string s2){
	int m = s1.size();
	int n = s2.size();
	if(m<1||n<1) return 0;
	int maxVal = 0;
	int im, jn;
	vector<vector<int>> L(m+1, vector<int>(n+1));
	for(int i=0; i<=m; i++) L[i][0] = 0;
	for(int j=0; j<=n; j++) L[0][j] = 0;
	for(int i=1; i<=m; i++){
		for(int j=1; j<=n; j++){
			if(s1[i-1]==s2[j-1]){       //  Note the use of s1[i-1] & s2[j-1] for a given (i, j)
				L[i][j] = 1 + L[i-1][j-1];
				if(L[i][j]>maxVal){
					maxVal = L[i][j];
					im = i; jn = j;
				}
			}
			else L[i][j] = 0;
		}
	}
	return maxVal;
}
//	Topological Order
//	A. Either use a stack<char> or a vector/array to store the values and then print/reverse print
//	Now im and jn are known to be the position of the maxVal in the DP table
stack<char> s;
while(L[im][jn]){
	s.push(s1[im-1]);	//	or s.push(s2.[jn-1]
	im--; jn--;
}
while(!s.empty()){
	cout<<s.top();
	s.pop();
}
cout<<"\n";

//	B. Without using a stack/vector and instead using the s.substr(index, length) function
while(L[I][J]){
	I--;
	J--;
}
cout<<s.substr(I, maxVal)<<"\n";
