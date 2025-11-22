/* DP Problem 19 - Palindrome Partitioning II (LC#132)
Given a string s, partition s such that every substring of the partition is a palindrome.
Return the minimum cuts needed for a palindrome partitioning of s.
If a string is a palindrome, then minimum 0 cuts are needed i.e. 1 partition
If a string of length n containing all different characters, then minimum n-1 cuts are needed i.e. total n partitions
Note - no. of partitions = no. of cuts + 1.
Eg. 1 - s = “ababbbabbababa”
Ans = “a|babbbab|b|ababa” as cuts = 3 (not “aba|b|bbabb|a|b|aba” as cuts = 5)
*/

//  Method 1 - Uses the same principle as of Matrix Chain Multiplication (MCM) i,e. len varies from 1 to n and for
//  each(i, j) k varies from i to j-1.

//	Running time = O(n^3) i.e. cubic
//	Auxiliary space = O(n^2)

#include<iostream>
#include<vector>
using namespace std;

bool isPalin(string s, int i, int j) {	//	Can also use a bool matrix storing the values if substr(i, j) is a palindrome as in method 2
    int n = j-i+1;
    string str = s.substr(i, n);
    for(int k=0; k<n/2; k++) {
		if(str[k]!=str[n-1-k]) return false;
	}
	return true;
}

int palinPartitionMin(string s) {
	int n = s.size();
	vector<vector<int>> DP(n, vector<int>(n));
	for(int len = 1; len<=n; len++) {
        for(int i=0; i<n-len+1; i++) {
            int j = i+len-1;
            if(len == 1) DP[i][j] = 0;
            else {
                if(isPalin(s, i, j)) DP[i][j] = 0;
				else {
					int minVal = INT_MAX;
					for(int k=i; k<j; k++) {
						int val = DP[i][k] + 1 + DP[k+1][j];
						if(val < minVal) minVal = val;
					}
				DP[i][j] = minVal;
				}
            }
        }
	}
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) cout<<DP[i][j]<<" ";
        cout<<"\n";
	}
	return DP[0][n-1];
}

int main() {
	string s;
	cin>>s;
	//vector<string> ans = palinPartitionMin(s);
	cout<<"Minimum no. of cuts required are = \n"<<palinPartitionMin(s);
	return 0;
}

/*
//  Not important
//  Method 2 - Instead of DP table, an array is used thus reducing total R.T = O(n^3) to O(n^2)
//  Also, isPalin() function is changed and a table P storing values that substr(i, j) is a palindrome, is used.

//  Running time = O(n^2) i.e. quadratic
//  Auxiliary space = O(n^2)

#include<iostream>
#include<vector>
using namespace std;
                                                                //  Thus, marginally reduces time
bool isPalin(string s, vector<vector<bool>> &P, int i, int j){  //  This reduces the time O(n) to O(1) to find whether substr(i to j) is palindrome
    if(i==j) P[i][j] = true;                        //  If len = 1 the it is already a palin and if len = 2 then compare s[i] = s[i+1] i.e. s[j]
    else if(j==i+1) P[i][j] = (s[i]==s[j]);         //  Uses the condition that a string is a palindrome iff
    else P[i][j] = (s[i]==s[j]) && P[i+1][j-1];     //  a. first and the last char match and
    return P[i][j];                                 //  b. the substr without the first and the last char is already a palindrome
}

int palinPartitionMin(string s) {
	int n = s.size();
	vector<int> DP(n);
	vector<vector<bool>> P(n, vector<bool>(n));
	for(int len = 1; len<=n; len++) {
        for(int i=0; i<n-len+1; i++) {
            int j = i+len-1;
            bool isPal = isPalin(s, P, i, j);
            }
    }
	cout<<"Table P = \n";
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) cout<<P[i][j]<<" ";
       cout<<"\n";

	}
	for(int i=0; i<n; i++) {
        if(P[0][i]==1) DP[i] = 0;
        else {
            int minVal = INT_MAX;
            for(int j=0; j<i; j++) {
                if(P[j+1][i]==1) {
                    if(1+DP[j]<minVal) minVal = 1 + DP[j];
                }
            }
            DP[i] = minVal;
        }
	}

	cout<<"Minimum no. of cuts required are = \n";
	return DP[n-1];
}

int main() {
	string s;
	cin>>s;
	cout<<palinPartitionMin(s);
	return 0;
}
*/
