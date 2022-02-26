/* Sorting Prob. # x.1. Counting Sort
Given an array of integers, sort it using counting sort.
Note - The range is smaller for sufficient storage.
Advantage of using a counting sort is that it sorts an array in O(n) instead of O(nlogn) given the size of
range {0,...,maxVal} i.e. k < n.
*/

//	Running time = O(n + k) ~ O(n) where n is the size of the given string and range k = maxVal+1 i.e. 0 to maxVal.
//	Auxiliary space = O(n + k)

#include <bits/stdc++.h>
using namespace std;

void print(vector<int> arr) {
    for(auto i : arr) cout<<i<<" "; cout<<"\n";
}

vector<int> countingSort(vector<int> arr) {     //  Just remember the easy four steps
    int n = arr.size(), maxVal = INT_MIN;
    for(int i=0; i<n; i++) {
        maxVal = max(maxVal, arr[i]);
        //minVal = min(minVal, arr[i]);
    }
    int range = maxVal+1;               //  Step 0: Range varies from 0 to maxVal => size = maxVal + 1
    vector<int> res(n);
	vector<int> idx(range, 0);
	//for(int i=0; i<range; i++) cout<<i<<" "; cout<<"\n";
    for(int i=0; i<n; i++)
        idx[arr[i]]++;                  //  print(idx); Step 1: Gets the count of values in arr
    for(int i=1; i<idx.size(); i++)
        idx[i] = idx[i-1] + idx[i];     //  print(idx); Step 2: Gets the cumulative values
    for(int i=idx.size()-1; i>0; i--)
		idx[i] = idx[i-1];              //  Step 3: Shifts the values rightwards
    idx[0]=0;                           //  [#IMP] - To make idx[0] = 0 due to the right shift
    //print(idx);
    for(int i=0; i<n; i++) {
        res[idx[arr[i]]] = arr[i];       //  Step 4: Place arr[i] in result array at index == count value of arr[i] in map arr
        idx[arr[i]]++;                   //  and increase the count of arr[i] by 1
    }
    return res;
}

int main() {
    int t;
    cin>>t;
    while(t--) {
        int n;
        cin>>n;
        vector<int> arr(n);
        for(int i=0; i<n; i++) cin>>arr[i];
        vector<int> res = countingSort(arr);
        cout<<"Sorted array = ";
        print(res);
    }
    return 0;
}

/* Sample Input
2
5
5 3 2 1 4
3
3 1 2
*/
