/* DP-Problem 8 (LC#516) - Longest Palindromic Subsequence (LPS)
Given a string s, find the longest palindromic subsequence's length in s.

Example 1:
Input: s = "bbbab"
Output: 4
Explanation: One possible longest palindromic subsequence is "bbbb".
*/
	
	
//	1. 	Tabulation (Top Down Approach) 
//		Running Time = O(n^2)
//		Space Complexity = O(n^2)
int lengthOfLPS(string s){
	int n = s.size();
	    vector<vector<int>> L(n, vector<int>(n, 0));
	    for(int i=0; i<n; i++) L[i][i] = 1;
        //for(int i=1; i<n; i++) L[i][i-1] = 0; 		//	Important when the vector is not initialized with all values = 0
	    for(int diff = 1; diff<n; diff++){				//	As it gives values to L[i][j] = 2 + L[i+1][j-1] when j-i = 1. 
            for(int i=0; i<n-diff; i++){				//	For eg. L[0][1] = 2 + L[1][0]  which is below the main diagonal
		        int j = i + diff;						// 	diff = j - i varies from 1 to n
                if(s[i]==s[j]) L[i][j] = 2 + L[i+1][j-1];
		        else L[i][j] = max(L[i][j-1], L[i+1][j]);
            }            
	    }
	    return L[0][n-1];
    }
}

// 	Topological Order (for method 1 only as method 2 uses the topological order for LCS instead of LPS)
//	Either use a stack & queue combination or use a vector<int> to store whether a char is included in the LPS or not.
//	After the DP table, here L has been filled
		int i = 0; int j = n-1;
        vector<int> printLPS(n, 1);
        while(j>i){
            if(L[i][j] == L[i][j-1]){
                printLPS[j] = 0;
                j--;
            }
            else if(L[i][j] == L[i+1][j]){
                printLPS[i] = 0;
                i++;
            }
            else if(L[i][j] == 2 + L[i+1][j-1]){
                i++;
                j--;
            }
        }
        for(int i=0; i<n; i++){
            if(printLPS[i]==1)
                cout<<s[i]<<" ";
        }
        cout<<"\n";

//	2.	LPS(s) = LCS(s, reverse(s))
//		Using LCS (Longest Common Subsequence) function to get the length of the LPS.
//		Following is the two step solution that uses LCS to get the length of LPS.
//		1) Reverse the given sequence and store the reverse in another array say rev[0..n-1]
//		2) LCS of the given sequence and rev[] will be the longest palindromic sequence.
//		Running time = O(n^2) but negligibly faster than method 1
//		Space Complexity = O(n^2) 
		string reverse(string s){
			if(s.size()==0||s.size()==1) return s;
			char temp;
			for(int i=0; i<s.size()/2; i++){
				temp = s[i];
				s[i] = s[s.size()-1-i];
				s[s.size()-1-i] = temp;
			}
			return s;
		}
		int LCS(string s1, string s2){
			int m = s1.size();
			int n = s2.size();
			int lcs[m+1][n+1];
			for(int i=0; i<=m; i++) lcs[i][0] = 0;
			for(int j=0; j<=n; j++) lcs[0][j] = 0;
			for(int i=1; i<=m; i++){				//	Note that i and j begin from (1,1)
				for(int j=1; j<=n; j++){
					if(s1[i-1]==s2[j-1]) lcs[i][j] = 1 + lcs[i-1][j-1];
					else lcs[i][j] = max(lcs[i][j-1], lcs[i-1][j]);
				}
			}
			return lcs[m][n];
		}

		int longestPalindromeSubseq(string s) {
			string s2 = reverse(s);
			cout<<s<<" "<<s2<<"\n";
			return LCS(s, s2);
		}

//	3.	Using recursion with memoization i.e. DP Bottom Up approach
//		Running time = O(n^2)
//		Space Complexity = O(n^2)
	int LPS(string s, int i, int j, vector<vector<int>> &DP){
		if(DP[i][j]!=-1) return DP[i][j];
		if(i==j){
			DP[i][j] = 1;
			return DP[i][j];
		}
		if(s[i]==s[j]&&j==i+1){				//or	if(j==i-1){										
			DP[i][j] = 2;					//			DP[i][j] = 0;													
			return DP[i][j];				//			return DP[i][j];												
		}	                        		//		}					
		if(s[i]==s[j]) DP[i][j] = 2 + LPS(s, i+1, j-1, DP);
		else DP[i][j] = max(LPS(s, i, j-1, DP), LPS(s, i+1, j, DP));
		return DP[i][j];
	}
	
	int lengthOfLPS(string s){
		int n = s.size();
		vector<vector<int>> DP(n, vector<int>(n, -1));
		return LPS(s, 0, n-1, DP);
	}


//	4.	Differect recursion than what used in DP without using memoization
//		Steps :
//				a.	Find and store all the subsequences of the string s
//				b.	Check which of those subsequences are actually palindromes
//				c. 	If a subsequence is a palindrome store its length else move on to the next subsequence
//				d. 	Finally return the length of the longest palindrome
//		Running time = O(2^n) i.e. exponential
//		Space Complexity = O(2^n) i.e. exponential
bool isPalin(string s){											//	Checks whether a string is a palindrome
    int n = s.size();											//	It gets called 2^n times as there are 2^n no. of subsequences
    if(n==0||n==1) return true;									
    for(int i=0; i<n/2; i++){
	    if(s[i]!=s[n-1-i]) return false;
    }
	return true;
}

int createSubSeq(string s, vector<string> &subSeq){
    if(s.size()==1){
	    subSeq.push_back("");
	    subSeq.push_back(s);
	    return 2;
    }
    int rec = createSubSeq(s.substr(1), subSeq);				//	Each character s[i] has two options 
    vector<string> temp = subSeq;								// 	a. to get picked
    for(int i=0; i<rec; i++) temp[i] = s[0] + temp[i];			//	b. or not get picked
    for(int i=0; i<rec; i++) subSeq.push_back(temp[i]);			//	vector<string> subSeq stores all the subsequences of the string s
    return 2*rec;												//	Each recurive call the size of the subSeq gets doubled 
}

int LPS(vector<string> subSeq){		
    vector<int> length(subSeq.size());							//	This vector stores the length of subsequences that are palindromes
    int maxVal = -1;
    for(int i=0; i<subSeq.size(); i++){
	    if(isPalin(subSeq[i])) length[i] = subSeq[i].size();	//	If the given subsequence is a palindrome, its length is stored
	    else length[i] = 0;										//	else its length is recorded as 0
	    if(length[i]>maxVal) maxVal = length[i];
    }
    return maxVal;												//	It returns the maximum length stored in the vector length i.e. the ans
}

int longestPalindromeSubseq(string s) {
    vector<string> subSeq;
    int size = createSubSeq(s, subSeq);
    return LPS(subSeq);
}
		