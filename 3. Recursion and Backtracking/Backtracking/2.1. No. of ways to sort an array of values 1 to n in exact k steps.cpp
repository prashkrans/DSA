/* Backtracking #2. Find the no. of ways to sort an array of size 6 with values 1 to 6 with exact k swaps.
Additional problems:
1. Find the total number of exact k swaps that can be done on the given array of size 6: Ans = 6C2^k
2. Find the probability of success of sorting the given permutation.  [Asked by Polkadex in hackerearth coding round]
*/

//  Running time = O(6C2^k)
//  Auxiliary space = O(6) ~ O(1) i.e. constant space

#include<bits/stdc++.h>
using namespace std;

void print(vector<int> a) {
    for(auto i : a) cout<<i<<" ";
    cout<<"\n";
}

void swapVal(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void rec(int k, vector<int> A, int &cVal) {
    if(k==0) {
        for(int i=0; i<A.size(); i++) {
            if(i+1==A[i]) continue;
            else return;
        }
        cVal++;
        return;
    }
    for(int i=0; i<A.size(); i++) {
        for(int j=i+1; j<A.size(); j++) {
            vector<int> B = A;
            swapVal(B[i], B[j]);
            // print(A); print(B); cout<<"\n";
            rec(k-1, B, cVal);
       }
    }
    return;
}

int solve(int k, vector<int> A) {
    int cVal = 0, modVal = 1e9+7, gcd, n = A.size();
    int nC2 = (n*(n-1))/2;
    int denom = pow(nC2, k);
    rec(k, A, cVal);
    gcd = __gcd(cVal, denom);
    int ans = ((cVal/gcd)/(denom/gcd))%modVal;
    cout<<"cVal = "<<cVal<<"\n";
    cout<<"denom = "<<denom<<"\n";
    cout<<"ans = "<<ans<<"\n";
    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    for(int t_i = 0; t_i < T; t_i++) {
        int n, k;
        cin >> n >> k;
        vector<int> A(n);
        for(int i_A = 0; i_A < n; i_A++)
        	cin >> A[i_A];
        int out_;
        out_ = solve(k, A);
        cout << out_;
        cout << "\n";
    }
}

/* Sample Input
3
6 2
1 2 3 4 5 6
4 3
2 1 3 4
7 4
1 2 3 4 5 6 7
*/
