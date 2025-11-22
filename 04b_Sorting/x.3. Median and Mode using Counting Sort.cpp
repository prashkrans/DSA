/* Sorting Prob. # x.1. Median and Mode using Counting Sort
Given an array of integers, find its median and mode.
Note - The range is smaller for sufficient storage in order to use counting sort.

Time taken to find median of an unsorted array takes O(nlog2n) time as we have to first sort the array
and then find the middle element.
However, by using counting sort one can find the median of an unsorted array in O(n) time given counting
sort is feasible i.e. k < n where k = the range of values and n is the size of the array.

*/

//	Running time = O(n + k) ~ O(n) where n is the size of the given string and range k = maxVal+1 i.e. 0 to maxVal.
//	Auxiliary space = O(n + k)

#include <bits/stdc++.h>
using namespace std;

void print(vector<int> arr) {
    for(auto i : arr) cout<<i<<" "; cout<<"\n";
}

vector<int> countingSort(vector<int> arr, int &mode) {
    int n = arr.size(), maxVal = INT_MIN, maxFreq = 0;
    for(int i=0; i<n; i++) maxVal = max(maxVal, arr[i]);
    int range = maxVal+1;
    vector<int> res(n);
	vector<int> idx(range, 0);
	//for(int i=0; i<range; i++) cout<<i<<" "; cout<<"\n";
    for(int i=0; i<n; i++) {
        idx[arr[i]]++;
        if(idx[arr[i]] > maxFreq) {
            maxFreq = idx[arr[i]];
            mode = arr[i];
        }
    }
    for(int i=1; i<idx.size(); i++)
        idx[i] = idx[i-1] + idx[i];
    for(int i=idx.size()-1; i>0; i--)
		idx[i] = idx[i-1];
    idx[0]=0;                                           //  [#IMP] - To make idx[0] = 0 due to the right shift
    //print(idx);
    for(int i=0; i<n; i++) {
        res[idx[arr[i]]] = arr[i];
        idx[arr[i]]++;
    }
    return res;
}

pair<double, int> findMedian (vector<int> arr) {        //  Note - Median need not be integral if the size of the array is even
    int n = arr.size(), mode;                           //  So, prefer using double for median
    pair<double, int> mM;
    vector<int> res = countingSort(arr, mode);
    cout<<"The sorted array is: ";
    print(res);
    if(n%2==0) mM.first = (res[n/2-1] + res[n/2] + 0.0)/2;
    else mM.first = res[n/2];
    mM.second = mode;
    return mM;
}

int main() {
    int t;
    cin>>t;
    while(t--) {
        int n, mode;
        double med;
        cin>>n;
        vector<int> arr(n);
        for(int i=0; i<n; i++) cin>>arr[i];
        pair<double, int> mM = findMedian(arr);
        med = mM.first;
        mode= mM.second;
        cout<<"Median and mode of the given array is: ";
        cout<<"Median = "<<med<<" | ";
        cout<<"Mode = "<<mode<<"\n";
    }
    return 0;
}

/* Sample input
2
10
2 3 4 2 5 5 4 2 5 5
5
2 4 3 4 1
*/
