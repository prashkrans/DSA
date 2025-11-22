/* Bit Manipulation problem: 4.3. Highest power of 2 less than or equal to given number (Application)
Some people(n) are standing in a queue. A selection process follows a rule where people standing on even positions
are selected. Of the selected people a queue is formed and again out of these only people on even position are
selected. This continues until we are left with one person. Find out the position of that person in the original queue.

gfg - https://practice.geeksforgeeks.org/problems/finding-position2223/1

Example 1:
Input: n = 9
Output: 8
Explanation: 1,2,3,4,5,6,7,8,9 -> 2,4,6,8 -> 4,8 -> 8.

From the above example it can be easily concluded that this problem is exactly same as the Prob. 4
So, this problem can be solved using three methods:
1. 	O(1) : Right shifting + bitwise OR operator
2.	O(n-x) where is x is the nearest power of 2 <= n : if(n & (n-1)==0) n is a power of 2
3.	O(log_base2(n)) : Starting from i = 1, keep checking if (i>n) then return i/2
*/

#include <bits/stdc++.h>
using namespace std;

//	Method 1. Right shifting
class Solution {
  public:
    long long int nthPosition(long long int n){
        n = n | (n >> 1);
        n = n | (n >> 2);
        n = n | (n >> 4);
        n = n | (n >> 8);
        n = n | (n >> 16);
        n = n | (n >> 32);			//	Dont' use the line 33 if n is of int datatype
        return (n+1) >> 1;
    }
};

//	Method 2. If(n&(n-1)==0) => n is a power of two
class Solution2 {
public:
	long long int nthPosition(long long int n) {
		while(n>1) {
			if((n&(n-1))==0) return n;		//	Note: n&(n-1)==0 won't work so, use parentheses before '==' i.e. (n&(n-1))==0
			n--;
		}
		return n;
	}
};

//	Method 3. Starting from i = 1, keep checking if (i>n) then return i/2
class Solution3 {
public:
	long long int nthPosition(long long int n) {
		for(long long int i=1; ; i = i << 1) {
			if(i>n) {
			    n = (i >> 1);
			    break;
			}
		}
		return n;
	}
};

int main() {
    int t;
    cin >> t;
    while (t--) {
        long long int n;
        cin >> n;
        Solution ob;
        cout<<ob.nthPosition(n)<<endl;
    }
    return 0;
}
