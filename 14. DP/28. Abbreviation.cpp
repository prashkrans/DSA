/* DP Prob. #28. Abbreviation
Similar to edit distance
*/

//  Method 1. DP Table (Best solution)
//  Steps:
//  1.  Declare DP of size n+1 and m+1 due to the empty string "" as a prefix
//  2.  DP[0][0] = true
//  3.  All the cells of the first row is made false except DP[0][0]
//  4.  The cells of the first column are fed accordingly i.e. true if char is lower case and no upper case has been
//      encountered yet
//  5.  For i = 1 to n and For j = 1 to m we have four cases as defined below
//  6.  Return DP[n][m] which stores the final result true or false

//  Running time = O(n*m) where n = a.size() and m = b.size()
//  Auxiliary space = O(n*m)

#include<bits/stdc++.h>
using namespace std;

string abbreviation(string a, string b) {
    int n = a.size();
    int m = b.size();
    vector<vector<int>> DP(n+1, vector<int>(m+1, 0));
    DP[0][0] = 1;
    for(int i=1; i<=n; i++) {
        if(a[i-1]>='a' && a[i-1]<='z') DP[i][0] = 1;
        else if(a[i-1]>='A' && a[i-1]<='Z') {
            while(i<n) {
                DP[i][0] = 0;
                i++;
            }
        }
    }
    for(int j=1; j<=m;  j++) DP[0][j] = 0;
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=m; j++) {
            if(a[i-1]>='a' && a[i-1]<='z') {                    //  if both lower case
                if(a[i-1]-32 == b[j-1]) DP[i][j] = DP[i-1][j-1] || DP[i-1][j];  //  Case a. both match then DP[i][j] gets value from either advancing by 1 step in both a and b or just deleting the curr char of a.
                else DP[i][j] = DP[i-1][j];                                     //  Case b. both don't match then DP[i][j] gets value from only deleting the current char of a
            }
            else {
                if(a[i-1]==b[j-1]) DP[i][j] = DP[i-1][j-1];     //  if both upper case and match, advance by 1 step in both a & b
                else DP[i][j] = 0;                              //  if both upper case and don't match make DP[i][j] = false
            }
        }
    }
    if(DP[n][m]) return "YES";
    else return "NO";
}

int main() {
    int t;
    cin>>t;
    while(t--) {
        string a, b;
        cin>>a>>b;
        cout<<abbreviation(a, b)<<"\n";
    }
    return 0;
}

//  Method 2. Recursion with memoization (Incomplete)
//  Running time = O(n*m) [Verify]
//  Auxiliary space = O(n*m)
//  yt - https://www.youtube.com/watch?v=DW92IHf8KK8&ab_channel=code_report

//  Method 3. Recursion without memoization (Incomplete)
//  Running time = O(2^n) i.e. exponential thus, inefficient
//  Auxiliary space = O(1) i.e. constant space
/*
#include<bits/stdc++.h>
using namespace std;

bool rec(string a, string b) {
    if(a.empty() && b.empty()) return true;
    if(a.empty() && !b.empty()) return false;
    if(a.size() < b.size()) return false;
    if(!a.empty() && b.empty()) {
        for(int i=0; i<a.size(); i++) {
            if(a[i]>='A' && a[i]<='Z');
            return false;
        }
        return true;
    }
    bool left = 0, right = 0;
    cout<<a[0]<<" "<<b[0]<<"\n";
    if(a[0]>='a' && a[0]<='z') {
        left = rec(a.substr(1), b);
        if(left) return left;
        a[0] = a[0] - 32;
        right = rec(a, b);
        a[0] = a[0] + 32;
        if(right) return right;
    }
    else if(a[0]>='A' && a[0]<='Z') {
        if(a[0]!=b[0]) return false;
        else return rec(a.substr(1), b.substr(1));
    }
    return false;
}

string abbreviation(string a, string b) {
    if(rec(a, b)) return "YES";
    else return "NO";
}

int main() {
    int t;
    cin>>t;
    while(t--) {
        string a, b;
        cin>>a>>b;
        cout<<abbreviation(a, b)<<"\n";
    }
    return 0;
}
*/

/* Sample input
3
daBcd
ABC
beFgH
EFG
beFgH
EFH
*/
