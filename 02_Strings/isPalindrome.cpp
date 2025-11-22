#include<iostream>
using namespace std;

bool isPalin(string s, int i, int j) {
    if(i>=j) return 1;
    if(s[i]!=s[j]) return 0;
    return isPalin(s, i+1, j-1);
}

int main() {
    int t;
    cin>>t;
    while(t--) {
        string s;
        cin>>s;
        int i = 0, j = s.size()-1;
        if(isPalin(s, i, j)) cout<<s<<" is a palindrome\n";
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
