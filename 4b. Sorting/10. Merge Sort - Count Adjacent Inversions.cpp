/* Sort Prob. #10. Merge Sort: Counting Inversions
*/

//  Method 1. Insertion Sort (Naive Solution)
//  Running time = O(n^2) i.e. quadratic thus inefficient
//  Auxiliary space = O(1) i.e. constant space

//  Method 2. Merge Sort (Best solution)
//  This problem is basically merge sort with a variable count to count the inversion of
//  adjacent elements. Inversion of adjacent elements only occurs if the an element in
//  the left half is greater than an element in the right half. So, if an element i in
//  the left half is greater than an element j in the right half => all the elements from
//  i to mid are greater than that element in the right half. Hence, number of inversions
//  would be (mid+1 - i).

//  Running time = O(merge sort) = O(nlog2n) i.e. log-linear thus efficient
//  Auxiliary space = O(1) i.e. constant space

#include<bits/stdc++.h>
using namespace std;

void print(vector<int> a) {
    for(auto i : a) cout<<i<<" ";
    cout<<"\n";
}

void merge(vector<int> &arr, int s, int mid, int e, long &count) {
    vector<int> res;
    int i=s, j=mid+1, n=mid+1, m=e+1, k=0;
    while(i<n && j<m) {
        if(arr[i] > arr[j]) {
            res.push_back(arr[j++]);
            count += (mid+1) - i;           //  This is the only condition required to increase count
        }
        else res.push_back(arr[i++]);
    }
    while(j<m) res.push_back(arr[j++]);
    while(i<n) res.push_back(arr[i++]);
    for(int i=s; i<=e; i++) arr[i] = res[k++];
}

void mergeSort(vector<int> &arr, int s, int e, long &count) {
    if(s>=e) return;
    int mid = (s+e)/2;
    mergeSort(arr, s, mid, count);
    mergeSort(arr, mid+1, e, count);
    merge(arr, s, mid, e, count);
}

int main() {
    int t;
    cin>>t;
    while(t--) {
        int n;
        cin>>n;
        vector<int> a(n);
        for(int i=0; i<n; i++) cin>>a[i];
        long count = 0;
        mergeSort(a, 0, n-1, count);
        //cout<<"The number of inversions to sort the array = ";
        cout<<count<<"\n";
    }
    return 0;
}

/* Sample Input
2
4
4 1 2 3
5
1 2 3 4 5
*/
