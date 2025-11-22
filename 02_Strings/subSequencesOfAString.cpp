//  Print all the subsequences of a string:

//  Running time = O(2^n)
//  Auxiliary space = O(n)

#include<iostream>
using namespace std;

void subSequences(string s, string subSeq) {
    if(s.size()==0) {
        cout<<subSeq<<" | ";
        return;
    }
    subSequences(s.substr(1), subSeq+s[0]);
    subSequences(s.substr(1), subSeq);
}

int main() {
    int t;
    cin>>t;
    while(t--) {
        string s;
        cin>>s;
        subSequences(s, "");
        cout<<"\n";
    }
    return 0;
}

/* Sample input
3
abc
a
aaaa
*/
