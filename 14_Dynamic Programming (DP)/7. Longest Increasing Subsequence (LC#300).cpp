/* DP-Problem 7 (LC#300) - Longest Increasing Subsequence (LIS)
Given an integer array nums, return the length of the longest strictly increasing subsequence.
A subsequence is a sequence that can be derived from an array by deleting some or no elements without changing 
the order of the remaining elements. For example, [3,6,2,7] is a subsequence of the array [0,3,1,6,2,2,7].

Example 1:
Input: a = [10,9,2,5,3,7,101,18]
Output: 4
Explanation: The longest increasing subsequence is [2,3,7,101], therefore the length is 4.
*/

// 	1. 	Using DP 1-D array/vector.
//		Running time = O(n^2) 			// 	A faster method is by using binary search with R.T. = O(nlogn)
//		Space Complexity = O(n)
int lengthOfLIS(vector<int>& a) {
        int n = a.size();
        vector<int> DP(n, 1);           //  Creates a vector of size n with all the values = 1 i.e. the base case
        for(int i = 1; i<n; i++){
            for(int j = 0; j<i; j++){   // 	j varies from 0 to i-1 for all i in the range 0 to n-1
                if(a[j]<a[i]){          //  Since we need LIS (strictly increasing) thus a[j]<a[i] to constitute a IS
                    DP[i] = max(DP[i], DP[j]+1);
                }
            }
        }
        int maxVal = DP[0];
        for(int i=1; i<n; i++) if(DP[i]>maxVal) maxVal = DP[i];		// The ans is the largest value in the DP array and not the last cell
        return maxVal;
}

//	1b.	Same as 1 but includes topological sort. Using DP 1-D array to store the length of LIS and a 2D array to store and 
//		print the LIS (i.e. Topological Sort)

class Solution {
public:
    int lengthOfLIS(vector<int> &a) {
        int n = a.size();
        vector<int> DP(n, 1);           //  Creates a vector of size n with all the values = 1 i.e. the base case
		vector<vector<int>> L(n);       //  A 2D vector to store the subsequence i for a[i]
		for(int i=0; i<n; i++) L[i].push_back(a[i]);
        for(int i = 1; i<n; i++){
            int maxVal = 0;             //  To get the maxVal of DP[j]
			int pos = 0;               	//  To get the position of DP[j] i.e. j
			for(int j = 0; j<i; j++){   // 	j varies from 0 to i-1 for all i in the range 0 to n-1
                if(a[j]<a[i]&&DP[i]<DP[j]+1){          //  Since we need LIS (strictly increasing) thus a[j]<a[i] to constitute a IS
                    if(DP[j]+1>maxVal){
						maxVal = DP[j]+1;
						pos = j;
					}					
                }
            }
			if(maxVal>DP[i]){
				DP[i] = maxVal;
                vector<int> temp(maxVal);   		//  A temporary vector to help merge two vectors
                for(int i=0; i<maxVal-1; i++) temp[i] = L[pos][i];
                temp[maxVal-1] = L[i][0];          	//  The value at a[i] itself is appended at the end
				L[i] = temp;
			}
        }
        int maxVal = DP[0];
		int pos = 0;
        for(int i=1; i<n; i++){
			if(DP[i]>maxVal){
				maxVal = DP[i];						
				pos = i;
			}
		}
		int LIS = L[pos].size();
		for(int j=0; j<LIS; j++) cout<<L[pos][j]<<" ";
		cout<<"\n";
        return maxVal;
}
};

//	2.	Recursion without memoization.
//		Running time = O(2^n) i.e. exponential
//		Space Complexity = O(2^n) if all the subarrays are stored else O(n)

#include<iostream>
#include<vector>
using namespace std;

void printArr(int a[], int n){
    for(int i=0; i<n; i++) cout<<a[i]<<" ";
    cout<<"\n";
}

int LIS(int a[], int n, vector<int> b, int m){
       if(n==0){
            //for(int i=0; i<m; i++) cout<<b[i]<<" ";
            //cout<<"\n";
            return m;
       }
       int wo = LIS(a+1, n-1, b, m);
       int w = 0;
       if((!(b.empty())&&a[0]>b[m-1])||b.empty()){
           b.push_back(a[0]);
           w = LIS(a+1, n-1, b, m+1);
       }
       return max(wo, w);
}


int main(){
	int n = 6;
	int m = 0;
	int a[n];
	a[0] = 0; a[1] = 1; a[2] = 0; a[3] = 3;
	a[4] = 2; a[5] = 3;
	cout<<"The given array is = ";
	printArr(a, n);
	vector<int> b;
	int ans = LIS(a, n, b, m);
	cout<<"The length of the LIS = "<<ans<<"\n";
	char input = 'y';
	cout<<"Wanna input custom values? (y/n)\n";
    cin>>input;
    while(input=='y'){
        cout<<"Enter the the size of the array = \n";
        cin>>n;
        int a2[n];
        cout<<"Enter the values of the array = \n";
        for(int i=0; i<n; i++){
            int val;
            cin>>val;
            a2[i] = val;
        }
        ans = LIS(a, n, b, m);
        cout<<"The length of the LIS = "<<ans<<"\n";
        cout<<"Wanna continue? => (y/n) = \n";
        cin>>input;
    }
	return 0;
}
