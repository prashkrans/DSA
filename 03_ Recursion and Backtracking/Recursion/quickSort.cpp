/*  quickSort() using array and s, mid, e [Verified]
gfg - https://practice.geeksforgeeks.org/problems/quick-sort/1/
hr - https://www.hackerrank.com/challenges/quicksort1/problem
LC#912 - It gets TLE maybe due to thinnest of the margins since for loop is used twice in its partition
while there is a compact version of quickSort which used single loop in partition
*/

//  Running time = O(nlog2n)
//  Auxiliary space = O(1) i.e. constant space

#include<iostream>
using namespace std;

void swap(int &a, int &b) {
    a = a+b;
    b = a-b;
    a = a-b;
}

int partition(int a[], int s, int e) {
    int x = a[s], count = 0;
    for(int i=s; i<e+1; i++)
        if(a[i] < x) count++;
    int p = s+count;
    if(count==0) return s;
    swap(a[s], a[p]);
    int i = s, j = p+1;     //  Both i and j vary from left to right
    while(i<p) {            //  My method								//	int i = s, j = e;     	//  i varies from left to right while j varies from right to left
        if(a[i] >= x) swap(a[i], a[j++]);                               //	while(i<p && j>p) {     //  gfg's method
        else i++;                                                       //	    while(a[i] < x) i++;
    }                                                                   //	    while(a[j] >= x) j--;
	return p;                                                           //	    if(i<p && j>p)
}                                                                       //	        swap(a[i++], a[j--]);
                                                                        //	}
void quickSort(int a[], int s, int e) {
    if(s>=e) return;
    int p = partition(a, s, e);
    quickSort(a, s, p-1);
    quickSort(a, p+1, e);
}

int main() {
    int t;
    cin>>t;
    while(t--) {
        int n;
        cin>>n;
        int a[n];
        for(int i=0; i<n; i++) cin>>a[i];
        quickSort(a, 0, n-1);
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


/* LC #912. Without TLE
class Solution {
    void bubbleSort(vector<int> &nums) {
        for(int i=0; i<nums.size(); i++) {
            for(int j=i+1; j<nums.size(); j++) {
                if(nums[i] > nums[j]) {
                    swap(nums[i], nums[j]);
                }
            }
        }
    }
    
    vector<int> mergeSort(vector<int> &nums, int start, int end) {
        if(start >= end) return vector<int>();

        vector<int> res(end-start, nums[start]);
        if(res.size() == 1) return res;
                
        // split
        int mid = start + (end-start)/2;
        auto l = mergeSort(nums, start, mid);
        auto r = mergeSort(nums, mid, end);

        // merge
        int i=0, j=0, k=0;
        while(i<l.size() && j<r.size()) {
            if(l[i] < r[j]) {
                res[k++] = l[i++];
            } else {
                res[k++] = r[j++];
            }
        }
        
        while(i<l.size()) res[k++] = l[i++];
        while(j<r.size()) res[k++] = r[j++];
        
        return res;
    }

    // 5 2 3 1
    // 1 5 2 3
    
    pair<int, int> partition(vector<int> &nums, int start, int end) {
        int right = end;
        int i = start;
        int pivot = start + (rand()%(end-start));
        int k = nums[pivot];

        while(i <= end) {
            if(nums[i] < k) {
                swap(nums[start++], nums[i++]);
            } else if(nums[i] > k) {
                swap(nums[end--], nums[i]);
            } else {
                i++;
            }
        }
        
        return make_pair(start, end);
    }
    
    void quickSort(vector<int> &nums, int start, int end) {
        if(start >= end || start < 0) return;
        
        auto b = partition(nums, start, end);
        quickSort(nums, start, b.first);
        quickSort(nums, b.second+1, end);
    }

public:
    vector<int> sortArray(vector<int>& nums) {
        // bubbleSort(nums);
        // return nums;
        
        // return mergeSort(nums, 0, nums.size());
        quickSort(nums, 0, nums.size()-1);
        return nums;
    }
};
*/