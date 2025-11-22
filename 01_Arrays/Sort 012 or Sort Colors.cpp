/* Array Prob. #x. (LC#75) Sort Colors or Sort 0, 1, 2
Given an array nums with n objects colored red, white, or blue, sort them in-place so that objects of the same color are adjacent,
with the colors in the order red, white, and blue.
We will use the integers 0, 1, and 2 to represent the color red, white, and blue, respectively.
You must solve this problem without using the library's sort function.

Example 1:
Input: nums = [2,0,2,1,1,0]
Output: [0,0,1,1,2,2]
Example 2:

Input: nums = [2,0,1]
Output: [0,1,2]

Constraints:
n == nums.length
1 <= n <= 300
nums[i] is either 0, 1, or 2.

Method 1: Two passes of the array.
R.T. = O(2n) ~ O(n) i.e. linear tim
A.S. = O(1) i.e. constant space

Method 2: Single pass (Best Solution)
R.T. = O(n) i.e. linear time
A.S. = O(1)
*/

//	Method 2: Single pass (Best Solution)
//	R.T. = O(n) i.e. linear time
//	A.S. = O(1)

#include<iostream>
#include<vector>
using namespace std;

void swap1(int &a, int &b) {        //  Always prefer swap1 over swap2
    int temp = a;
    a = b;
    b = temp;
}

void swap2(int &a, int &b) {         //  swap2 fails when both pointer points to the same variable x
    a = a+b;    //  a = x + x = 2x
    b = a-b;    //  b = 2x - 2x (not 2x - x) = 0
    a = a-b;    //  a = 0 - 0 = 0
}

void sort012(int arr[], int n) {
    int low = 0, mid = 0, high = n-1;
	while(mid <= high) {
		if(arr[mid]==0) swap1(arr[low++], arr[mid++]);
		else if(arr[mid]==1) mid++;
		else if(arr[mid]==2) swap1(arr[mid], arr[high--]);
	}
}

class Solution {            //  leetcode 75. Sort colors
public:
    void sortColors(vector<int>& arr) {
        int n = arr.size(), low = 0, mid = 0, high = n-1;
        while(mid <= high) {
            if(arr[mid]==0) swap1(arr[low++], arr[mid++]);
            else if(arr[mid]==1) mid++;
            else if(arr[mid]==2) swap1(arr[mid], arr[high--]);       //  Note here mid is not incremented
        }
    }
};

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int arr[n];
        for (int i = 0; i < n; i++) cin >> arr[i];
        vector<int> nums(n);
        for (int i = 0; i < n; i++) nums[i] = arr[i];
        sort012(arr, n);
        for (int i = 0; i < n; i++) cout << arr[i] << " "; cout<<"\n";
        Solution obj;
        obj.sortColors(nums);
        for (int i = 0; i < n; i++) cout << nums[i] << " "; cout<<"\n";
    }
    return 0;
}
/* Sample Input:
2
7
0 1 2 0 1 2 0
11
2 2 1 1 2 1 0 0 1 2 2 
*/

