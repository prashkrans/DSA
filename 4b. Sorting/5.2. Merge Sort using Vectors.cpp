/*  Sorting Algo #5.2. Merge Sort using Vectors
Arrays are faster than vectors in Divide and Conquer techniques such as merge sort, quick sort,
etc. So, prefer using arrays than vectors in D & C algorithms
*/

#include<bits/stdc++.h>
using namespace std;

int count = 0;

void print(vector<int> a) {
	for(auto i : a) cout<<i<<" ";
	cout<<"\n";
}

void merge(vector<int> &arr, int s, int mid, int e) {
	vector<int> res;
	int i=s, j=mid+1, n=mid+1, m=e+1, k=0;
	while(i<n && j<m) {
		if(arr[i] > arr[j]) {
			res.push_back(arr[j++]);
		}
		else res.push_back(arr[i++]);
	}
	while(j<m) res.push_back(arr[j++]);
	while(i<n) res.push_back(arr[i++]);
	for(int i=s; i<=e; i++) arr[i] = res[k++];
}

void mergeSort(vector<int> &arr, int s, int e) {
	if(s>=e) return;
	int mid = (s+e)/2;
	mergeSort(arr, s, mid);
	mergeSort(arr, mid+1, e);
	merge(arr, s, mid, e);
}

int main() {
    vector<int> a, b;
	a = {5, 7, 8, 1, 2, 10};
	b = {3, 4, 1, 2, 5};
	mergeSort(a, 0, a.size()-1);
	mergeSort(b, 0, b.size()-1);
	print(a);
	print(b);
	return 0;
}



