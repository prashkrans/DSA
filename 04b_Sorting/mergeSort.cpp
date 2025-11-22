//  mergeSort() using array and s, mid, e [Verified]

#include<iostream>
using namespace std;

void merge(int a[], int s, int mid, int e) {
    int i=s, j=mid+1, n=mid+1, m=e+1, currSize=e-s+1, k=0;
    int b[currSize] = {};
    while(i<n && j<m) {
        if(a[i] <= a[j]) b[k++] = a[i++];
        else b[k++] = a[j++];
    }
    while(i<n) b[k++] = a[i++];
    while(j<m) b[k++] = a[j++];
    k = 0;
    for(int i=s; i<e+1; i++) a[i] = b[k++];
}

void mergeSort(int a[], int s, int e) {
    if(s>=e) return;
    int mid = (s+e)/2;
    mergeSort(a, s, mid);
    mergeSort(a, mid+1, e);
    merge(a, s, mid, e);
}

int main() {
    int t;
    cin>>t;
    while(t--) {
        int n;
        cin>>n;
        int a[n];
        for(int i=0; i<n; i++) cin>>a[i];
        mergeSort(a, 0, n-1);
        cout<<"The sorted array is: ";
        for(int i=0; i<n; i++) cout<<a[i]<<" ";
        cout<<"\n";
    }
    return 0;
}

/* Sample input
3
6
5 4 9 7 10 9
5
1 2 3 4 5
4
2 -1 1 -2
*/
