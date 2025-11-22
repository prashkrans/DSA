/* Greedy Prob. #3. Greedy Florist
*/

//	Method 1: Greedy Algo - Sort the array in descending order and increase curr by 1 after each k steps
//	thus making the price = original price * (1 + curr)
//	Running time = O(nlog2n + n) ~ O(nlog2n) where n = arr.size()
//	Auxiliary space = O(1) i.e. constant space

#include <bits/stdc++.h>
using namespace std;

// Complete the getMinimumCost function below.
int getMinimumCost(int k, vector<int> cost) {
    int sum = 0, curr = 0, count = 0;
    sort(cost.begin(), cost.end(), greater<int>());
    for(int i=0; i<cost.size(); i++) {
        if(count==k) {
            count = 0;
            curr++;
        }
        sum += cost[i]*(1+curr);
        count++;        
    }
    return sum;
}

int main() {
    int n, k;
    cin>>n>>k;
    vector<int> arr(n);
    for(int i=0; i<n; i++) cin>>arr[i];
    cout<<getMinimumCost(k, arr);    
}