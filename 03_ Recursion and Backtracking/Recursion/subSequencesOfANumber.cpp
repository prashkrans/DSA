//  Print all the subsequences of an array:

//  Running time = O(2^n)
//  Auxiliary space = O(n)

#include<iostream>
#include<vector>
using namespace std;

void subSequences(int i, vector<int> a, vector<int> &ss) {
    if(i == a.size()) {
        for(int i=0; i<ss.size(); i++) cout<<ss[i]<<" "; cout<<"| ";
        return;
    }
    ss.push_back(a[i]);
    subSequences(i+1, a, ss);   
    ss.pop_back(); 
    subSequences(i+1, a, ss);
}

void subSequences2(int i, vector<int> a, vector<vector<int>> &ans) {
    if(i == a.size()) return;
    int currSize = ans.size();
    for(int j=0; j<currSize; j++) {
        vector<int> curr = ans[j];
        curr.push_back(a[i]);
        ans.push_back(curr);
    }
    subSequences2(i+1, a, ans);
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
        subSequences(0, a, ss);
        cout<<"\n";
        vector<vector<int>> ans;
        ans.push_back(vector<int>());
        subSequences2(0, a, ans);
        cout<<"! ";
        for(auto i: ans) {
            for(auto j: i) cout<<j<<" ";
            cout<<"! ";
        }
        cout<<"\nNo. of subsequences: "<<ans.size()<<"\n";
    }
    return 0;
}

/* Sample Input:
2
3
1 2 3
Then wait for the output before entering the next input
2
1 2
*/