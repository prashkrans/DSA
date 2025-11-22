//  Print all the subsequences of an array:

//  Running time = O(2^n)
//  Auxiliary space = O(n)

#include<iostream>
#include<vector>
using namespace std;

void subSequences(vector<int> a, int i, vector<int> ss) {
    if(i==a.size()) {
        for(int i=0; i<ss.size(); i++) cout<<ss[i]<<" "; cout<<"| ";
        return;
    }
    ss.push_back(a[i]);
    subSequences(a, i+1, ss);
    ss.pop_back();
    subSequences(a, i+1, ss);
}

int main() {
    int t;
    cin>>t;
    while(t--) {
        int n;
        cin>>n;
        vector<int> a(n);
        for(int i=0; i<n; i++) cin>>a[i];
        vector<int> ss;
        subSequences(a, 0, ss);
        cout<<"\n";
    }
    return 0;
}

/* Sample input
2
3
1 2 3
1
1
*/
