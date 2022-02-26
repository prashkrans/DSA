/* DP-Problem 10 (LC#5) - Longest Palindromic Substring
Given a string s, return the longest palindromic substring in s.
Example 1:

Input: s = "babad"
Output: "bab"
Note: "aba" is also a valid answer.
*/
//	1.	DP - Tabulation (Bottom Up approach) including the topological order.
//		Running Time = O(n^2)
//		Extra Space = O(n^2)
class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();
        vector<vector<int>> DP(n, vector<int>(n));	// 	No extra 0th row or column needed
        for(int i=0; i<n; i++){             //  Note the use of if(i>0) DP[i][i-1] = 1;
            DP[i][i] = 1;                   //  Base Case 1 : Minimum length of a palindrome is 1 i.e. DP(i,i)
            if(i>0) DP[i][i-1] = 1;         //  Base Case 2 : Since for diff==1 if s[i]==s[j] then DP(i, j) = 1 
        }                                   //                as no DP(i+1, j-1) exist. Thus this base case basically 
        int maxLen = 1;                     //                shortens the code length by covering for both cases i.e. diff==1 and diff>1
        int I = 0;                          //  #IMP : that min(maxLen)==1 and min(I)==0 i.e. Base Case 1. Hence their initialization as such
        for(int diff = 1; diff<n; diff++){  //  is really important to make sure to return first char of s, if no palindrome of length > 1 is found.
            for(int i=0; i<n-diff; i++){	//	diff varies from 1 to n-1, i varies from 0 to n-diff for each diff and j = i+diff
                int j = i+diff;
                if((s[i] == s[j]) && DP[i+1][j-1]==1){      //  DP formula :
                    DP[i][j] = 1;                           //  if(s[i]==s[j] && DP(i+1, j-1)) DP(i, j) = true else DP(i, j) = false
                    if(diff+1 > maxLen){
                        maxLen = diff+1;
                        I = i;
                    }
                }
                else DP[i][j] = 0;
            }
        }
        return s.substr(I, maxLen);
    }
};

//	1b. Tabulation (Bottom Up) without topological order i.e. just returns the length of the LPSubstring
int LPSubstring(string s) {
        int n = s.size();
        vector<vector<int>> DP(n, vector<int>(n));
        for(int i=0; i<n; i++){
            DP[i][i] = 1;
            if(i>0) DP[i][i-1] = 1;
        }
        int maxLen = 1;
        for(int diff = 1; diff<n; diff++){
            for(int i=0; i<n-diff; i++){
                int j = i+diff;
                if((s[i] == s[j]) && DP[i+1][j-1]==1){
					DP[i][j] = 1;
                    if(diff+1>maxLen) maxLen = diff+1;	// 	The current length of the substr is = diff+1;
                }										//	Thus, maxLen stores the max length of the LPSubstring
                else 
					DP[i][j] = 0;
            }
        }
        return maxLen;
    }
	
//	2. 	Manacher's Algorithm (not DP) - Later
//		Running Time = O(n)
//		Extra Space = O(n)