#include<iostream>
using namespace std;

// 1. Recursive approach
// Time Complexity: O(n)
// Space Complexity: O(n) due to recursion stack

bool isPalinRec(string s, int i, int j) { // Note: Recursive approach requires i and j
    if(i>=j) return 1;
    if(s[i]!=s[j]) return 0;
    return isPalinRec(s, i+1, j-1);
}
// 2. Iterative approach (Prefer this)
// Time Complexity: O(n)
// Space Complexity: O(1)

bool isPalin(string s) {    
    int l = 0, r = s.size()-1;
    while(l<r) {
        if(s[l]!=s[r]) return 0;
        l++;
        r--;
    }
    return 1;
}

int main() {
    int t;
    cout<<"Enter number of test cases: ";
    cin>>t;
    while(t--) {
        string s;
        cout<<"Enter a string: ";
        cin>>s;
        int i = 0, j = s.size()-1;
        if(isPalinRec(s, i, j)) cout<<s<<" is a palindrome\n";
        else cout<<s<<" is not a palindrome\n";
        if(isPalin(s)) cout<<s<<" is a palindrome\n";
        else cout<<s<<" is not a palindrome\n";
    }
    return 0;
}

/* Sample input
5
abc
abccba
abcba
abcde
aaaaa
*/
