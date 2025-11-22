/* String Prob. #5. Remove Consecutive Duplicates
Given a sorted string, remove all the consecutive duplicates without using a hashmap
Note: The below code only works for a sorted string. So, if a string is not sorted, it
needs to be sorted first in ascending order using sort(str.begin(), str.end());
*/

//	Running time = O(n) i.e. linear time where n = s.size();
//	Auxiliary space = O(n) due to the string ans

#include <iostream>
#include <cstring>
using namespace std;

string removeConsecutiveDuplicates(string s) {
    int n = s.size();
    string ans;
    for(int i=0; i<n-1; i++)
        if(s[i]!=s[i+1]) ans += s[i];   //  Inserting the last occurrence of a duplicate character to ans
    ans += s[n-1];                      //  Since, the loop does not insert the last character of string s
    return ans;
}

int main() {
    string str;
    cin >> str;
    string ans = removeConsecutiveDuplicates(str);
    cout << ans << endl;
}
