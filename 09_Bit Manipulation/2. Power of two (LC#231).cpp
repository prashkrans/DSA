/* Bit Manipulation problem: 2. LC#231. Power of Two
Given an integer n, return true if it is a power of two. Otherwise, return false.
An integer n is a power of two, if there exists an integer x such that n == 2^x.

Example 1:
Input: n = 1
Output: true as 2^0 = 1
Explanation: 20 = 1

Example 2:
Input: n = 3
Output: false

Constraints:
-231 <= n <= 231 - 1

Note: if n<=0 => it cannot be a power of two as only positive integers can be a power of two.

This problem can be solved using two methods
1.	Using the inbuilt math function log2(n) 
2.	Using the relationship that if n&(n-1)==0 => n is a power of two and it is not otherwise (Best solution)
	R.T. for both methods 1 and 2 = O(1) i.e. constant time
3.	Keep dividing n by 2 until n becomes 1 => n is power of two and it is not otherwise
	R.T. for method 3 = O(log_base2(n)) as we keep dividing n by 2
*/

//	Method 1. Using the inbuilt math function log2(n)
//	Running time = O(1) i.e. constant time since we are only calculating log2(n) twice. 
//	Auxiliary space = O(1) i.e. constant space as we store log2(n)

class Solution {
public:
    bool isPowerOfTwo(int n) {
        if(n<=0) return false;
        double m = log2(n);     //  If n is a power of two => m would not have non-zero decimals
        int p = log2(n);        //  If n is power of two => m should be equal to p which is an int
        return (m==p);
    }
};

//	Method 2. Using the relationship that if n&(n-1)==0 => n is a power of two and it is not otherwise
//	Running time = O(1) i.e. constant time since we are only calculating n&(n-1) once.
//	Auxiliary space = O(1) i.e. constant space (But we are not using any extra space)

class Solution {
public:
    bool isPowerOfTwo(int n) {
        if(n<=0) return false;
        return((n&(n-1))==0); 		//	Note: Use parentheses before '=='
    }
};

//	Method 3. Keep dividing n by 2 until n becomes 1 => n is power of two and it is not otherwise
// 	Running time = O(log_base2(n)) as we keep dividing n till it becomes 0 or 1
//	Auxiliary space = O(1) i.e. constant space (But we are not using any extra space)

class Solution {
public:
    bool isPowerOfTwo(int n) {
        if(n<=0) return false;
        while(n) {
            if(n==1) return true;               //  Only when n becomes 1, return true
            else if((n&1) == 1) return false;   //  If n is odd, return false as an odd int cannot be a power of two
            //else if(n%2 == 1) return false;   //  Basic way to find if n is odd
            n = n >> 1;     //  n = n/2;
            //cout<<n<<"\n";
        }
    return false;
    }
};