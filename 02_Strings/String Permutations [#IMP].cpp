//  Print all the permutations of a string:

//  Running time = O(n!) i.e. factorial time which is even slower than exponential time
//  Auxiliary space = O(n)

// There are two methods. Cover the second method later.

#include<iostream>
using namespace std;

void permutations(string s, string permS) {
    if(s.size()==0) {
        cout<<permS<<" | ";
        return;
    }
    for(int i=0; i<s.size(); i++) {
        string recString = s.substr(0, i) + s.substr(i+1);
        permutations(recString, permS+s[i]);
    }
}

int main() {
    int t;
    cin>>t;
    while(t--) {
        string s;
        cin>>s;
        permutations(s, "");
        cout<<"\n";
    }
    return 0;
}

/* Sample input
3
abc
aa
abcd
*/
