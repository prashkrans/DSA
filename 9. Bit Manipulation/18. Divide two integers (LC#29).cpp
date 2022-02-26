/* Bit manipulation problem 18. LC#29. Divide Two Integers
Given two integers dividend and divisor, divide two integers without using multiplication, division, and mod operator.
Return the quotient after dividing dividend by divisor.
The integer division should truncate toward zero, which means losing its fractional part. 
For example, truncate(8.345) = 8 and truncate(-2.7335) = -2.
Note: Assume we are dealing with an environment that could only store integers within the 32-bit signed integer range: 
[−2^31, 2^31 − 1]. For this problem, assume that your function returns 2^31 − 1 when the division result overflows, 
i.e. INT_MIN = -2^31 while INT_MAX = 2^31-1 so, abs(INT_MIN) = 2^31 overflows int datatype.
To solve the problem of overflow we need long int datatype to work on as int datatype cannot hold the value 2^31.

Example 1:
Input: dividend = 7, divisor = -3
Output: -2
Explanation: 7/-3 = truncate(-2.33333..) = -2.

Constraints:
-2^31 <= dividend, divisor <= 2^31 - 1
divisor != 0 

This problem could be solved using two methods:
1.	Naive solution: dd = dr*q + r, so keep dividing dd until it becomes less than dr. So, R.T. = O(log_basedr(dd)) but 
in worst case i.e. when dd = INT_MAX and dr = 1 R.T. = O(log_base1(2^31-1)) = O(2^31) which is a huge number hence inefficient.
2.	Efficient solution: Incomplete
	R.T. = O(log_base2(dd)) [Verify it]
	A.S. = O(1)
*/

//	Method 1. 
class Solution {
public:
    int divide(int dividend, int divisor) {
        if(dividend == INT_MIN && divisor == -1) return INT_MAX;
        if(dividend == INT_MIN && divisor == 1) return INT_MIN;
        long int A = dividend;
        long int B = divisor;
        bool sign = ((A>=0)==(B>=0))?0:1;	//	If (sign == 1) => q is negative else positive
        if(A<0) A = -A;
        if(B<0) B = -B;
        int q = 0;
        while(A>=B) {
            int count = 0;
            long int bTemp = B;
            while(A>=bTemp) {
                count++;
                bTemp = bTemp << 1;
            }		
            count--;						//	IMP - reduce count by 1 as indexing of bits starts from 0 and not 1
            bTemp = bTemp >> 1;				//	Divide bTemp by 2
            A = A - bTemp; 		
            q += 1<<count;					//	quotient = quotient + 2^count
        }
        if(sign==1) return -q;
        else return q;
    }
};

 