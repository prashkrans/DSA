/* Sorting Prob. # x.1. Counting Sort [Not Verified but 99% sure, it works]
Given an array of integers, sort it using counting sort.
Note - The range is smaller for sufficient storage.
*/

//	Running time = O(n + k) ~ O(n) where n is the size of the given string and range k = maxVal+1 i.e. 0 to maxVal.
//	Auxiliary space = O(n + k)

#include <bits/stdc++.h>
using namespace std;

void print(vector<int> arr) {
    for(auto i : arr) cout<<i<<" "; cout<<"\n";
}

vector<int> countingSort(vector<int> arr) {
    int n = arr.size(), maxVal = INT_MIN, minVal = INT_MAX;
    for(int i=0; i<n; i++) {
        maxVal = max(maxVal, arr[i]);
        minVal = min(minVal, arr[i]);
    }
    int range = maxVal+1;
    vector<int> res(n, -1);
	vector<int> idx(range, 0);
	//for(int i=0; i<range; i++) cout<<i<<" "; cout<<"\n";
    for(int i=0; i<n; i++)
        idx[arr[i]]++;                  //print(idx);
    for(int i=1; i<idx.size(); i++)
        idx[i] = idx[i-1] + idx[i];     //print(idx);
    for(int i=idx.size()-1; i>0; i--)
		idx[i] = idx[i-1];
    idx[0]=0;                       //  [#IMP] - To make idx[0] = 0 due to the right shift
    print(idx);
    for(int i=0; i<n; i++) {
        int currElem = arr[i];
        if(res[idx[currElem]]==-1)
			res[idx[currElem]] = currElem;
        else {
            int j = idx[currElem];
            while(res[j]!=-1) j++;
            res[j] = currElem;
        }
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
