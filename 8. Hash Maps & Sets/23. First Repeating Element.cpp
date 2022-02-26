/*	Hashmap Problem #21 -  First Repeating Element
Given an array arr[] of size n, find the first repeating element. The element should
occur more than once and the index of its first occurrence should be the smallest.
There may be multiple repeating elements so, return the index of the repeating element which
comes the earliest. Return -1 if no element repeats.
gfg - https://practice.geeksforgeeks.org/problems/first-repeating-element4018/1#

Example 1:
Input: n = 7 arr[] = {1, 5, 3, 4, 3, 5, 6}
Output: 2
Explanation:
5 is appearing twice and its first appearence is at index 2 which is less than 3 whose first
occuring index is 3.

This problem could be solved using three methods
1.	Naive solution: O(n^2), O(1)
2.	Sorting: O(nlog_base2(n)), O(n)
3.	Hashmap: O(n), O(n)
*/

//	Method 3. Hashmap
//	Running time = O(n)
//	Auxiliary space = O(n)

#include<iostream>
#include<unordered_map>
using namespace std;

class Solution{
public:
    int firstRepeated(int arr[], int n) {
        unordered_map<int, int> mp;
        int ans=INT_MAX;
        for(int i=0; i<n; i++) {
            if(mp.count(arr[i])==0) mp[arr[i]] = i;
            else ans = min(ans, mp[arr[i]]+1);
        }
        if(ans==INT_MAX) return -1;
        else return ans;
    }
};

int main(){
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        int arr[n];
        for(int i = 0 ; i < n ; ++i) cin >> arr[i] ;
        Solution ob;
        cout << ob.firstRepeated(arr,n) << "\n";
    }
    return 0;
}

/* Sample input
1
5
1 2 3 4 3
*/
