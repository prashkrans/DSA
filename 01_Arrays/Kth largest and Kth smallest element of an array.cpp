#include <iostream>
#include<algorithm>
using namespace std;

void kthSmallestLargest(int arr[], int n, int k) {
    sort(arr, arr+n);
    int brr[n], j=0;									//	arr may contain duplicate elements so we create an array brr which does not contain any duplicate elements
    for(int i=0; i<n-1; i++)
        if(arr[i] != arr[i+1]) brr[j++] = arr[i];       //  brr stores only distinct elements of arr
    brr[j++] = arr[n-1];                                //  Since we are adding the last occurrence of a number, arr[n-1] is always added after the loop
    if(k<=j) cout<<brr[j-k]<<" "<<brr[k-1]<<"\n";       //  if k>j then kth largest or smallest numbers do not exist
    else cout<<-1<<" "<<-1<<"\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        int arr[n];
        for (int i = 0; i < n; i++)  cin >> arr[i];
        kthSmallestLargest(arr, n, k);
    }
    return 0;
}
