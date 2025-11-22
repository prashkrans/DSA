/* Greedy Prob. #4. Min Diff of Max Min in a Sub-array of size k
*/

//	Method 1: Greedy Algo - Sort the array in ascending order and get the diff = subArr[k-1] - subArr[0]
//	and the ans = min(ans, diff), finally storing the min diff in the ans.

//	Running time = O(nlog2n + n) ~ O(nlog2n) where n = arr.size()
//	Auxiliary space = O(1) i.e. constant space

#include <bits/stdc++.h>
using namespace std;

int maxMin(int k, vector<int> arr) {
    int ans = INT_MAX;								//	First the array is sorted
    sort(arr.begin(), arr.end());					//	Then after sorting, i denotes the maxValue while j denotes the minValue in the current sub-array
    for(int i=k-1; i<arr.size(); i++)				//	Traversing from i = k-1 to n-1 and j = 0 to n-k and diff = arr[i] - arr[j]
        ans = min(arr[i] - arr[i-(k-1)], ans);			
    return ans;
}

int main() {
    int n, k;
    cin>>n>>k;
    vector<int> a(n);
    for(int i=0; i<n; i++) cin>>a[i];  
    cout<<maxMin(k, a);  
}
