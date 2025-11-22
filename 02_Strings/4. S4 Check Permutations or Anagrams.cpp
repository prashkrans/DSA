/* String Prob. #4. Check Permutation
Given two strings, s1 and s2, check whether they are a permutation/ an anagrams of each other or not.
*/

//	Running time = O(nlogn + mlogm) i.e. log-linear time due to sort() function used on both s1 and s2
//  where n = s1.size() and m = s2.size()
//	Auxiliary space = O(1)

#include <iostream>
#include <algorithm>
using namespace std;

bool isPermutation(string s1, string s2) {
    int n = s1.size(), m = s2.size();
    if(n!=m) return false;
    sort(s1.begin(), s1.end());
    sort(s2.begin(), s2.end());
    return (s1==s2);
}

int main() {
    string s1, s2;
    cin>>s1>>s2;
    cout<<(isPermutation(s1, s2) ? "true" : "false");
}
