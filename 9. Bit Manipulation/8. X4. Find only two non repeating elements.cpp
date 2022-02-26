/* Bit Manipulation problem: 8. (XOR problem 4.) Find the only two non repeating elements.
Given an array where every element repeats twice except two elements, find those two non
repeating elements.

Example 1:
Input: arr[] = {1, 2, 3, 2, 1, 4}
Output: 3 4
Explanation:
3 and 4 occur exactly once.

This problem could be solved by three methods
1.	Novice approach.
	R.T. = O(n^2)
2.	Hashmap or unordered_set
	R.T. = O(n)
3.	Bitwise XOR operator
	R.T. = O(n)
*/

//	Method 3a. Bitwise XOR operator and without using vectors v1 and v2
//	Running time = O(n) as we traverse the nums array two times
//	Auxiliary space = O(1) the vector a of size 2

class Solution {
public:
    vector<int> singleNumber(vector<int> nums) {
        vector<int> a(2, 0);
        int n = nums.size();
        for(int i=0; i<n; i++) a[0] = a[0]^nums[i];		//	Get the XOR of all the elements in a[0] which is 0 initially
        a[1] = a[0];									//	Copy the XOR value to a[1]
        //int rmOne = a[0] & (-a[0]); // or int rmOne = a[0] & ~(a[0]-1); 
		int rmOne = a[0]^(a[0]&(a[0]-1));				//	Use any one of the three ways to get the rightmost set bit in rmOne
        for(int i=0; i<n; i++) {						
            if(nums[i] & rmOne) a[0] ^= nums[i];		//	If ((nums[i] & rmOne) != 0) => a[0] = a[0] ^ nums[i]
            else a[1] ^= nums[i];						//	If ((nums[i] & rmOne) == 0) => a[1] = a[1] ^ nums[i]
        }												//	This implies that first non repeating value gets stored in a[0] and the second in a[1]
        sort(a.begin(), a.end());						//	sort() is not mandatory, however it only costs O(1) time as we are comparing only two elements
        return a;
    }
};

//	Method 3b. Bitwise XOR operator and using vectors v1 and v2
//	Running time = O(n) as we traverse the nums array three times
//	Auxiliary space = O(n) due to vector v1 and v2 as v1.size() + v2.size() == n i.e. nums.size()
/*
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Solution {
public:
    vector<int> singleNumber(vector<int> nums) {
        vector<int> a(2, 0);
        int n = nums.size();
        for(int i=0; i<n; i++) a[0] = a[0]^nums[i];		//	Get the XOR of all the elements in a[0] which is 0 initially
        a[1] = a[0];									//	Copy the XOR value to a[1]
        int rmOne = a[0] & (-a[0]); // or int rmOne = a[0] & ~(a[0]-1); // or int rmOne = a[0]^(a[0]&(a[0]-1);
		//	Use any one of the above three ways to get the rightmost set bit in rmOne
        vector<int> v1, v2;								//	The vector nums is split into two sets v1 and v2, both of which stores
        for(int i=0; i<n; i++) {						//	only one of the two elements which are non repeating
            int pos = nums[i]&rmOne;
            if(pos!=0) v1.push_back(nums[i]);			//	If (nums[i] & rmOne) != 0 => add it to v1
            else v2.push_back(nums[i]);					//	If (nums[i] & rmOne) == 0 => add it to v2
        }
        for(int i=0; i<v1.size(); i++) a[0] = a[0]^v1[i];	//	Find the first non repeating element in v1 using XOR operation
        for(int i=0; i<v2.size(); i++) a[1] = a[1]^v2[i];	//	Find the second non repeating element in v2 using XOR operation
        sort(a.begin(), a.end());							//	sort() is not mandatory, however it only costs O(1) time as we are comparing only two elements
        return a;
    }
};

int main(){
    int T;
    cin >> T;
    while(T--)
    {
    	int n;
    	cin >> n;
    	vector<int> v(2 * n + 2);
    	for(int i = 0; i < 2 * n + 2; i++) cin >> v[i];
    	Solution ob;
    	vector<int > ans = ob.singleNumber(v);
    	for(auto i: ans) cout << i << " ";
    	cout << "\n";
    }
	return 0;
}

/* Sample input
2
5
7 6 25 4 25 15 15 7 4 3 29 6
4
18 24 24 21 10 29 8 10 29 18
*/

//	Method 2a. Hashmap
//	Running time = O(n)
//	Auxiliary space = O(n)

//	Method 2b. Unordered set
//	Running time = O(n)
//	Auxiliary space = O(n/2) ~ O(n)
