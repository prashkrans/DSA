/* DP Prob. #26. Max sum of a subset of non-adjacent elements
Given an array of integers, find the subset of non-adjacent elements with the maximum sum.
Calculate the sum of that subset. It is possible that the maximum sum is , the case when all elements are negative.
hr - https://www.hackerrank.com/challenges/max-array-sum/problem?h_l=interview&isFullScreen=true&playlist_slugs%5B%5D%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D%5B%5D=dynamic-programming
*/

//	Method 1. Recursion without memoization
//	Running time = O(2^n) i.e. exponential thus inefficient, where n is the size of the given array.
//	Auxiliary space = O(1) i.e. constant space
/*
#include<bits/stdc++.h>
using namespace std;

void rec(int i, vector<int> arr, int currSum, int &maxSum) {
	if(i>=arr.size()) {                                     //  It is important to use i>= than i== if(i==n-1) i+2 == n+1 thus going out of bounds
		maxSum = max(maxSum, currSum);
		return;
	}
	rec(i+2, arr, currSum+arr[i], maxSum);
	rec(i+1, arr, currSum, maxSum);
}

int maxSubsetSum(vector<int> arr) {
	int currSum = 0, maxSum = 0;
	rec(0, arr, currSum, maxSum);
	return maxSum;
}

int main() {
	int n;
	cin>>n;
	vector<int> arr(n);
	for(int i=0; i<n; i++)
		cin>>arr[i];
    int ans = maxSubsetSum(arr);
	//cout<<"Max sum of a subset = "<<ans;
	cout<<ans;
	return 0;
}
*/

//	Method 2. Using DP array
//	Running time = O(n) i.e. linear time thus much faster the method 1, where n is the size of the given array.
//	Auxiliary space = O(1) i.e. constant space

#include<bits/stdc++.h>
using namespace std;

void print(vector<vector<int>> mat) {
    for(auto i : mat) {
        for(auto j : i)
            if(j==INT_MIN) cout<<"-\t";
            else cout<<j<<"\t";
        cout<<"\n";
    }
}

int maxSubsetSum(vector<int> arr) {
	int n = arr.size();
	int incl = 0, excl = 0;
	for(int i=0; i<n; i++) {
        int temp = incl;
        incl = max(incl, excl+arr[i]);
        excl = temp;
	}
	return incl;
}

int main() {
	int n;
	cin>>n;
	vector<int> arr(n);
	for(int i=0; i<n; i++)
		cin>>arr[i];
    int ans = maxSubsetSum(arr);
	//cout<<"Max sum of a subset = "<<ans;
	cout<<ans;
	return 0;
}

/* Sample Input
5
3 7 4 6 5

5
3 5 -7 8 10

5
-2 1 3 -4 5
*/
