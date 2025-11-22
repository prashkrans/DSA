/* Greedy Prob. #1. Minimum Absolute Difference in an Array
*/

//	Method 1: Naive Solution
//	Running time = O(n^2) where n = arr.size()
//	Auxiliary space = O(1) i.e. constant space

//	Method 2: Greedy Algo - Sorting the array and getting min difference between consecutive elements
//	Running time = O(nlog2n + n) ~ O(nlog2n) where n = arr.size()
//	Auxiliary space = O(1) i.e. constant space

#include <bits/stdc++.h>
using namespace std;

int minimumAbsoluteDifference(vector<int> arr) {
    sort(arr.begin(), arr.end());
    int minVal = INT_MAX;
    for(int i=1; i<arr.size(); i++) {
        minVal = min(minVal, arr[i]-arr[i-1]);
    }
    return minVal;
}

int main() {
    int n;
    cin>>n;
    vector<int> a(n);
    for(int i=0; i<n; i++) cin>>a[i];
    cout<<minimumAbsoluteDifference(a);
    return 0;    
}

