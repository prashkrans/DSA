/* Bit Manipulation problem: 4.1. Highest power of 2 less than or equal to given number

Given a number n, find the highest power of 2 that is smaller than or equal to n.
#IMP - This problem can also be redefined as: Given a number a n, return the most significant
bit (MSB) or the left most set bit.
Ex. 1:
Input : n = 10
Output : 8
Ex. 2:
Input : n = 32
Output : 32

This problem can be solved using three methods:
1. 	O(1) : Right shifting + bitwise OR operator
2.	O(n-x) where is x is the nearest power of 2 <= n : if(n & (n-1)==0) n is a power of 2
3.	O(log_base2(n)) : Starting from i = 1, keep checking if (i>n) then return i/2
*/

//	Method 1. Right shifting
//	If n is of int datatype => int has 32 bits => need to keep right shifting till 16 bits
//	If n is of long long int datatype => long long int has 64 bits => ... till 32 bits
//	Then finally add 1 and divide by 2 to obtain the solution
//	Trickier but faster than the rest methods
//	Running time = O(1) i.e constant time always since max R.T. = O(5) ~ O(1)
//	Auxiliary space = O(1) (No extra variables used)

class Solution {
  public:
    long long int nthPosition(long long int n){
        n = n | (n >> 1);
        n = n | (n >> 2);
        n = n | (n >> 4);
        n = n | (n >> 8);
        n = n | (n >> 16);
        n = n | (n >> 32);		//	Dont' use the line 33 if n is of int datatype
        return (n+1) >> 1;
    }
};

//	Method 2. If(n&(n-1)==0) => n is a power of two
//	So, starting n from its original value keep reducing it by one in each iteration until a it
//	becomes a power of two
//	Running time = O(n-x) where x is the nearest power of 2 <= n
//	Auxiliary space = O(1) (No extra variables used)

class Solution {
public:
	long long int nthPosition(long long int n) {
		while(n>1) {
			if((n&(n-1))==0) return n;		//	Note: n&(n-1)==0 won't work so, use parentheses before '==' i.e. (n&(n-1))==0
			n--;
		}
		return n;
	}
};

//	Method 3. Starting from i = 1, i takes values that are powers of 2, keep checking if (i>n) then return i/2
//	Running time = O(log_base2(n) i.e. we iterate as i = 1, 2, 4, 8, ... (i>n)
//	Auxiliary space = O(1) (No extra variables used)

class Solution {
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
