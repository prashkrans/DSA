/* Bit Manipulation problem: 9. (XOR problem 5.) LC#137. Single Number II
Given an integer array nums where every element appears three times except for one, which appears exactly once. 
Find the single element and return it.
The same bit manipulation methods can be used to solve a problem in which every other element repeats k times.
Here, k == 3. 

Example 1:
Input: nums = [2,2,3,2]
Output: 3

Example 2:
Input: nums = [0,1,0,1,0,1,99]
Output: 99

Constraints:
1 <= nums.length <= 3 * 10^4
-2^31 <= nums[i] <= 2^31 - 1
Each element in nums appears exactly three times except for one element which appears once.

This method can be solved using four methods:
1.	Naive solution: O(n^2), O(1)
2.	Hashmap or unordered_set: O(n), O(n)
3.	Bit manipulation without using XOR: O(n), O(1)
4.	Bit mainpulation using bitwise XOR operator: O(n), O(1)
*/

//	Method 3a. Bit manipulation without using XOR:
//	Running time = O(n) as O(32*n) ~ O(n)
//	Auxiliary space = O(1) as O(32) ~ O(1)

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int n = nums.size();
        vector<int> bitCount(32, 0);				//	If the datatype is int then size of bitCount is 32
        for(int i=0; i<n; i++) {
            for(int j=0; j<32; j++) {
                bool bit=0;
                if(nums[i] & (1 << j)) bit = 1;		//	Returns 1 if posn (31-j) is set else returns 0
                bitCount[31-j] += bit;				//	Increment bitCount[31-j] iff the posn (31-j) is 1
            }
        }        
        int ans = 0;
        for(int j=0; j<32; j++) {
            bitCount[31-j] %= 3;					//	Here, every other number is repeated thrice => k = 3
            ans = ans + bitCount[31-j]*(1 << j);	//	Build the integer from the bitCount array
        }
        return ans;
    }
};

//	Method 3b. Bit manipulation without using XOR: (Same as Method 3a. but loops are reversed and no vector is used)
//	It is easier to understand that method 3a.
//	Running time = O(n) as O(32*n) ~ O(n)
//	Auxiliary space = O(1) as O(32) ~ O(1)

int Solution::singleNumber(const vector<int> &A) {
    int n = A.size();
    int ans = 0;
    for(int i=0; i<32; i++) {
        int count = 0;
        for(int j=0; j<n; j++) {
            if(A[j]&(1<<i)) count++;
        }
        count = count%3;
        if(count==1) ans = ans + (1<<i);
    }
    return ans;
}


//	Method 4. Bit mainpulation using bitwise XOR operator:
//	Explanation: To be done later
//	Running time = O(n)
//	Auxiliary space = O(1) as only two variabies are used.

class Solution {
public:
    int singleNumber(vector<int>& nums) {        
        int ones=0;
        int twos=0;        
        for(int i=0; i<nums.size(); i++) {
            ones = (nums[i] ^ ones) & (~twos);
            twos = (nums[i] ^ twos) & (~ones);
        }
        return ones;
    }
};

//	Method 2. Hashmap
//	Running time = O(n)
//	Auxiliary space = O(n)

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int n = nums.size();
        int ans;
        unordered_map<int, int> mp;
        for(int i=0; i<n; i++) mp[nums[i]]++;
        for(auto i : mp) if(i.second==1) ans = i.first;
        return ans;
    }
};