/* Sorting Prob. # x.2. Counting Sort (String)
Given a string arr consisting of lowercase english letters, arrange all its letters in lexicographical order using Counting Sort.
gfg - https://practice.geeksforgeeks.org/problems/counting-sort/1/

Example 1:			Example 2:

Input:				Input:
N = 5               N = 13
S = "edsab"			S = "geeksforgeeks"

Output:				Output:
abdes				eeeefggkkorss

Expected Time Complexity: O(N).
Expected Auxiliary Space: O(N).

Constraints:
1 ≤ N ≤ 10^5
*/

//	Running time = O(n + k) ~ O(n) where n is the size of the given string and k = 26 i.e. constant as well as small.
//	Auxiliary space = O(n + k)

#include <bits/stdc++.h>
using namespace std;

class Solution{
    public:
    //  Function to arrange all letters of a string in lexicographical order using Counting Sort.
    string countSort(string arr){
        int n = arr.size();
        vector<int> mapChar(26, 0);
        for(int i=0; i<n; i++) {
            int val = arr[i]-'a';
            mapChar[val]++;
        }
        for(int i=1; i<26; i++)
            mapChar[i] = mapChar[i] + mapChar[i-1];
        for(int i=25; i>0; i--)
            mapChar[i] = mapChar[i-1];
        mapChar[0] = 0;         //  #IMP to have mapChar[0] = 0 due to the rightwards shift
        vector<int> res(n);
        for(int i=0; i<arr.size(); i++) {
            int val = arr[i] - 'a';
            res[mapChar[val]] = val;
            mapChar[val]++;
        }
        string s;
        for(int i=0; i<n; i++) s = s+char(res[i]+'a');
        return s;
    }
};

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        string s;
        cin>>s;
        Solution obj;
        cout<<obj.countSort(s)<<endl;
    }
    return 0;
}
