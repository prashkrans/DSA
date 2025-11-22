/* Bit Manipulation problem: 1. LC#191. Number of 1 Bits or Hamming Weight or No. of set bits
Write a function that takes an unsigned integer and returns the number of '1' bits it has (also known as 
the Hamming weight or set bits). 
Note: 
a.	A bit with value == 1 is known as a set bit.
b.	Note that in some languages, such as Java, there is no unsigned integer type. In this case, the input will 
be given as a signed integer type. It should not affect your implementation, as the integer's internal 
binary representation is the same, whether it is signed or unsigned.

Example 1:
Input: n = 00000000000000000000000000001011
Output: 3
Explanation: The input binary string 00000000000000000000000000001011 has a total of three '1' bits.

This problem can be solved using two methods
1.	n&(n-1) (Faster solution)
2.	Right shifting 
*/

//	Method 1. Using the fact that n&(n-1) reduces the no. of '1's by one.

//	Running time = O(no. of 1s in the bin reprn of n) which would become O(log_base2(n)) in worst cases where n is 
//	the given number. Thus, it performs better than method 2.
//	Auxiliary space = O(1) i.e. count is the only extra variable

class Solution {
public:
    int hammingWeight(uint32_t n) {		//	Note: the data type uint32_t which is used to represent an unsigned 32-bit integer
        int count = 0;
        while(n>0) {
            count++;
            n = n & (n-1);
        }
        return count;
    }
};

//	Method 2. Using the right shift operator
//	Here, we keep right shifting the given number and increment count by 1 if the current number has 1 
//	as its right most bit.

// 	Running time = O(log_base2(n)) in all the cases i.e. as (log_base2(n) + 1) is the no. of bits in n
//	Auxiliary space = O(1) i.e. count is the only extra variable

class Solution {
public:
	int hammingWeight(uint32_t n) {
		int count = 0;
		while(n>0) {
			if(n&1==1) count++;
			n = n >> 1;
		}
		return count;
	}
};
