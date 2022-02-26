/* Bit Manipulation problem: xx. LC#190. Reverse Bits
Reverse bits of a given 32 bits unsigned integer.
Note: Reverse bits != Inverse bits
Reverse of (001101) = 101100
Inverse of (001101) = 110010

Example 1:
Input: n = 43261596 (00000010100101000001111010011100)
Output:	964176192 (00111001011110000010100101000000)

This problem could be solved three methods.
1. 	Traversing all the bits one by one: R.T. = O(1) as O(32 or 64) ~ O(1) where n is the max size of data type in use.
	So, size of int is 32, size of long long int is 64 and A.S. = O(1). (Best solution)
2.	Traversing all the bits one by one but using a left operator: R.T. = O(1) as O(32 or 64) ~ O(1) and A.S. = O(1) 
3.	Divide and conquer: R.T. = O(log2(32)) or O(log2(64) i.e. O(5) or O(6) ~ O(1) and A.S. = O(1).
*/

//	Method 1a - Traversing all the bits one by one without using a vector to store bits: (Best solution)
//	Running time = O(1) as O(32 or 64) ~ O(1) where n is the max size of data type in use.
//	Auxiliary space = O(1)

class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
		uint32_t ans = 0;
        for(int i=0; i<32; i++) {
            int j = 31-i;
            int power = 1 << j; 		//	power = 2^j
            if(n>=power) {				//	if(n<power) then the bit == 0
                ans += (1<<i);			//	ans = ans + 1*2^i i.e. the reverse order of j
                n = n%power;			//	if(n>=power) n = n%power and the bit == 1
            }
        }
        return ans;
    }
};

// or 

unsigned int Solution::reverse(unsigned int A) {
    int ans = 0;
    for(int i=0; i<32; i++) {			//	current pos is i then current pos for the reversed number is (31-i)
        if(A&(1<<i)) ans = ans + (1<<(31-i));
    }
    return ans;
}

//	Method 1b - Traversing all the bits one by one and using a vector to store bits:
//	Running time = O(1) as O(32 or 64) ~ O(1) where n is the max size of data type in use.
//	Auxiliary space = O(1)

class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        vector<int> a(32, 0);
        for(int i=0; i<32; i++) {
            int j = 31-i;
            int power = 1 << j;
            if(n>=power) {
                a[i] = 1;
                n = n%power;
            }
        }
        uint32_t ans = 0;
        for(int i=0; i<32; i++) ans += a[i]*(1<<i);
        return ans;
    }
}

//	Method 2 - Traversing all the bits one by one but using a left operator:
//	Running time = O(1) as O(32 or 64) ~ O(1)
//	Auxiliary space = O(1) 

class Solution {
public:
	uint32_t reverseBits(uint32_t n) {
		uint32_t rev = 0;
        for(int i=0; i<32; i++) {   //  Don't use while(n) {} instead of for loop here as it would stop as soon as when n becomes 0 and will not traverse all the 32 or 64 bits
			rev = rev | (n&1);
			if(i!=31) rev = rev << 1;	// Left shifting of rev should only be done for i = 0 to 30 as at i == 31, rev is the result and left shifting it would produce an incorrect ans
			n = n >> 1;
		}
		return rev;
	}
};

//	Method 3 - Divide and conquer: 
//	Explanation: Incomplete
//	Running time = O(log2(32)) or O(log2(64) i.e. O(5) or O(6) ~ O(1) 
//	Auxiliary space = O(1).

class Solution {
public:
    uint32_t reverseBits(uint32_t n) {								//	Usage of 0x00ff00ff, etc is unclear as of yet
        n = (n >> 16) | (n << 16);									//	This swaps bits 0 to 15 with 16 to 31
        n = ((n & 0xff00ff00) >> 8) | ((n & 0x00ff00ff) << 8);		//	This swaps bits 0 to 7 with 8 to 15 and 16 to 23 with 24 to 31
        n = ((n & 0xf0f0f0f0) >> 4) | ((n & 0x0f0f0f0f) << 4);		//	This swaps the first four bits with the last four bits in all the 4 parts of n each of length 8
        n = ((n & 0xcccccccc) >> 2) | ((n & 0x33333333) << 2);		//	This swaps the first two bits with the last two bits in all the 8 parts of n each of length 4
        n = ((n & 0xaaaaaaaa) >> 1) | ((n & 0x55555555) << 1);		//	This swaps the first bit with second bit in all the 16 parts of n each of length 2
        return n;
    }
};