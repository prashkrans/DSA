/* 5. Special String Again
https://www.hackerrank.com/challenges/special-palindrome-again/problem?h_l=interview&isFullScreen=true&playlist_slugs%5B%5D%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D%5B%5D=strings
*/

//	Method 1 - Naive Solution
//	Running time = O(n^2*m) i.e. cubic
// 	Auxiliary space = O(1) or O(n^2)

//	Method 2 - Efficient Solution
//	Running time = O(n*m) where n = s.size() and m = the max size of a substring of type 2.
//	Auxiliary space = O(1) 

long substrCount(int n, string s) {
    long count = 0;
    for(int i=0; i<n; i++) {
        long cC = 1;                        //  cC = number of contiguous characters
        while(i+1<n && s[i]==s[i+1]) {      //  Case 1: All of the characters are the same, e.g. aaa.
            cC++;
            i++;
        }
        count += (cC*(cC+1))/2;             //  Case 2: All characters except the middle one are the same, e.g. aadaa.
        int j = 1;
        while(i-j>=0 && i+j<n && s[i-j]==s[i+j] && s[i-j] == s[i-1]) {
            count++;
            j++;
        }
    }
    return count;
}