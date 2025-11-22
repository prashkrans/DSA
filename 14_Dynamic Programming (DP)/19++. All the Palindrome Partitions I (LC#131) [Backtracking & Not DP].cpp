/* All The Palindrome Partitions - (LC#131): Palindrome Partitioning
Given a string s, partition s such that every substring of the partition is a palindrome. Return all possible
palindrome partitioning of s.
A palindrome string is a string that reads the same backward as forward.
Eg 1. s = "aab"
Ans = [["a","a","b"],["aa","b"]]
Eg 2. s = "a"
Ans = [["a"]]

Soln: https://leetcode.com/problems/palindrome-partitioning/solution/   - Approach 1
*/
//  Running Time = O(n*2^n) ie linear*exponential (Accepted by leetcode)
//  Auxiliary Space = O(2^n)

#include<iostream>
#include<vector>
#include<string>
using namespace std;

class Solution {
public:
    bool isPalin(string s) {            //  Function 1 - isPalin()
        int n = s.size();               //  It checks whether the given string is a palindrome
        for(int i=0; i<n/2; i++) {
            if(s[i]!=s[n-1-i]) return 0;
        }
        return 1;
    }

    void palinPartition(string s, vector<string> currAns, vector<vector<string>> &ans) {
        if(s.size()==0) {               //  Function 2 - palinPartition() i.e. the main function
            ans.push_back(currAns);     //  When the string s is empty then currAns is pushed back to ans
        }                               //  This function basically performs a depth first search
        int n = s.size();
        for(int i=0; i<n; i++) {        //  As many branches as the no. of characters in a string
            string str = s.substr(0, i+1);
            if(isPalin(str)) {          //  Only if the substring is a palindrome we add it to the currAns
                currAns.push_back(str);
                palinPartition(s.substr(i+1), currAns, ans);    //  Advance the first position of the string by 1
                currAns.pop_back();     //  Note - Don't use currAns.clear(); as it empties the currAns completely
            }                           //  Also here pop_back() is used to not allow any changes say for i = i1 not affect i = i2
        }
    }

    vector<vector<string>> partition(string s) {    //  Function 3 - partition() - Merely a helper function
        vector<vector<string>> ans;                 //  Can do without this function too
        vector<string> currAns;                     //  ans is 2D vector of strings while currAns is a vector of strings
        palinPartition(s, currAns, ans);
        return ans;
    }
};

int main() {
    string s;
    cin>>s;
    Solution sol;
    vector<vector<string>> ans = sol.partition(s);
    for(int i=0; i<ans.size(); i++){                //  Since ans is a 2D vector of strings need 2 for loops to print it
        for(int j=0; j<ans[i].size(); j++) cout<<ans[i][j]<<" ";
        cout<<"\n";
    }
    return 0;
}
