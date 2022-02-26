/* Greedy Prob. #2. Luck Balance
*/

//	Method 1: Greedy Algo - Sorting the array and getting min difference between consecutive elements
//	Running time = O(nlog2n + 2n) ~ O(nlog2n) where n = arr.size()
//	Auxiliary space = O(n) i.e. linear space

#include <bits/stdc++.h>
using namespace std;

int luckBalance(int k, vector<vector<int>> contests) {
    int sum = 0;
    vector<int> a;
    for(int i=0; i<contests.size(); i++) {
        if(contests[i][1]==0) sum+=contests[i][0];
        else a.push_back(contests[i][0]);
    }
    sort(a.begin(), a.end(), greater<int>());
    for(int i=0; i<a.size(); i++) {
        if(i<k) sum+=a[i];
        else sum-=a[i];
    }
    return sum;
}

int main() {
    int n, k; 
    cin>>n>>k;
    vector<vector<int>> arr(n, vector<int>(2));
    for(int i=0; i<n; i++) cin>>arr[i][0]>>arr[i][1];
    cout<<luckBalance(k, arr);   
}