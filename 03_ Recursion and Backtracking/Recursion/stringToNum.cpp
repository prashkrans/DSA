#include<iostream>
using namespace std;

void strToNumRec(string s, int &ans) {
    if(s.size()==0) return;
    ans = ans*10 + (s[0]-'0');
    strToNumRec(s.substr(1), ans);
}

int strToNumIter(string s) {
    int ans = 0;
    for(int i=0; i<s.size(); i++)
        ans = ans*10 + (s[i]-'0');
    return ans;
}

int main() {
    string s;
    s = "123456";
    int ans = 0;
    strToNumRec(s, ans);
    cout<<"Ans = "<<ans<<" | "<<strToNumIter(s);
    return 0;
}
