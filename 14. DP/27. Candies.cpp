/* DP Prob. #27. Candies
Alice is a kindergarten teacher. She wants to give some candies to the children in her class.
All the children sit in a line and each of them has a rating score according to his or her
performance in the class.  Alice wants to give at least 1 candy to each child. If two children
sit next to each other, then the one with the higher rating must get more candies. Alice wants
to minimize the total number of candies she must buy.
*/

//  Method 1. DP array but two traversals are used 1. forward and 2. backward.
//  DP formula is used while traversing backwards.
//  Running time = O(n) where n = arr.size();
//  Auxiliary space = O(n) due to the DP array

#include<bits/stdc++.h>
using namespace std;

long candies(int n, vector<int> arr) {
    long sum = 0;
    vector<int> numC(n, 1);
    if(n==1) return 1;
    for(int i=1; i<n; i++) {
        if(arr[i] > arr[i-1]) numC[i] = numC[i-1]+1;
    }
    for(int i=n-2; i>=0; i--) {
        if(arr[i] > arr[i+1]) numC[i] = max(numC[i], numC[i+1]+1);
    }
    for(int i=0; i<n; i++) sum += numC[i];
    return sum;
}


int main() {
    int n;
    cin>>n;
    vector<int> arr(n);
    for(int i=0; i<n; i++) cin>>arr[i];
    long ans = candies(n, arr);
    cout<<"The minimum number of candies to be bought = "<<ans;
    return 0;
}


/* Sample Inputs
10
2
4
2
6
1
7
8
9
2
1


8
2
4
3
5
2
6
4
5
*/
