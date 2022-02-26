/* Bit Manipulation problem: 13. LC#1318. Minimum Flips to Make a OR b Equal to c
Given 3 positives numbers a, b and c. Return the minimum flips required in some bits of a and b 
to make ( a OR b == c ). (bitwise OR operation). Flip operation consists of change any single bit 
1 to 0 or change the bit 0 to 1 in their binary representation.

Example 1:
Input: a = 2, b = 6, c = 5
Output: 3
Explanation: 
a = 2 = 0010
b = 6 = 0110
c = 5 = 0101
i = 0 => 1 flip made
i = 1 => 2 flips made
Total 3 flips made 
After flips a = 1 , b = 4 , c = 5 such that (a OR b == c)
*/

//	Method 1. Traverse the numbers bit by bit
//	Running time = O(32) or O(64) ~ O(1) i.e. constant time
// 	Auxiliary space = O(1) due the three variables

class Solution {
public:
    int minFlips(int a, int b, int c) {
        int res = 0;
        for(int i=0; i<32; i++) {
            bool aBit, bBit, cBit;
            aBit = 0; bBit = 0; cBit = 0;
            if(a & (1<<i)) aBit = 1;
            if(b & (1<<i)) bBit = 1;
            if(c & (1<<i)) cBit = 1;
            if(cBit==0) {
                if(aBit==1 && bBit==1) res+=2;
                else if(aBit==1 || bBit==1) res++;
            }
            else if(aBit==0 && bBit==0) res++;
        }
        return res;
    }
};
