/* String Matching - LC#28: Implement strStr().
Return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.

Clarification:
What should we return when needle is an empty string? This is a great question to ask during an interview.
For the purpose of this problem, we will return 0 when needle is an empty string. This is consistent to C's strstr() and Java's indexOf().

Example 1:
Input: haystack = "hello", needle = "ll"
Output: 2
Example 2:
Input: haystack = "aaaaa", needle = "bba"
Output: -1
Example 3:
Input: haystack = "", needle = ""
Output: 0

Constraints:
0 <= haystack.length, needle.length <= 5 * 104
haystack and needle consist of only lower-case English characters.

This problem could be solved using three methods:
1. 	Naive Solution: R.T. = O(mn) thus inefficient
2.	Knuth Morris Pratt (KMP) Algo: R.T. = O(m+n) 
3.	Tries: R.T. = ?? 
where m = |P| and n = |T|.
*/

//	Method 2. KMP Algo
//	Running time = O(m+n) 
//	Space complexity = O(m+n)

class Solution {
public:
vector<int> buildArrayLPS(string P) {
	int i=1, j=0, m = P.size();
	vector<int> lps(m, 0);
	while(i<m){
		if(P[i]==P[j]) {
			lps[i] = j+1;
			i++;
			j++;
		}
		else {
            if(j!=0) j = lps[j-1];
            else i++;          			//  lps[i] = 0 is already taken care initially
		}
	}
	return lps;
}

vector<int> KMPalgo(string T, string P, vector<int> lps) {
    int n = T.size(), m = P.size();
    int k = 0, i = 0;
    vector<int> foundAt;
    while(k<n) {
        if(T[k]==P[i]) {
            if(i==m-1) foundAt.push_back(k+1-m);
            k++;
            i = (i+1)%m;
        }
        else {
            if(i!=0) i = lps[i-1];
			else k++;
        }
    }
    return foundAt;
}
    int strStr(string haystack, string needle) {
        if(needle=="") return 0;
        vector<int> lps = buildArrayLPS(needle);
        vector<int> foundAt = KMPalgo(haystack, needle, lps);
        if(foundAt.empty()) return -1;
        else return foundAt[0];
    }
};