/* Bit Manipulation problem: 14. AND product
Consider two non-negative long integers, a and b, where a<=b. The bitwise AND of all long integers in the 
inclusive range a between b and can be expressed as a & (a+1) & ... & (b-1) & b, where is the bitwise AND operator.
Given n pairs of long integers a,  and b, compute and print the bitwise AND of all natural numbers in the
inclusive range between a and b

hackerrank - https://www.hackerrank.com/challenges/and-product/problem

Example 1:
Input:
3
12 15
2 3
8 13
Output:
12 = 12 & 13 & 14 & 15
2 = 2 & 3
8 = 8 & 9 & 10 & 11 & 12 & 13

This problem could be solved by two methods:
1. 	Naive solution: andVal = a; for(i: a to b) andVal &= i; return andVal; R.T. = O(b-a) i.e linear and A.S. = O(1)
2.	Efficient solution: if(diff is > 2^i) bit = 0 else if(a_bit == 1 && b_bit == 1) bit = 1; R.T. = O(1) and A.S. = O(1)
*/

//	Method 2. Efficient solution: if(diff is > 2^i) bit = 0 else if(a_bit == 1 && b_bit == 1) bit = 1 
//	Running time = O(32 or 64) i.e. O(1) i.e. constant time
//	Auxiliary space = O(1) due to the variables one and diff

#include<iostream>
using namespace std;

long andProduct(long a, long b) {   
    long diff = b-a;
    long ans = 0;
    long one = 1;				//	Since long datatype used here, (1<<i) returns an int which gives an incorrect answer so, need to declare one as long with value == 1
    for(int i=0 ;i<64; i++) {
        if(diff>(one<<i)) continue;
        else {
            if((a&(one<<i))&&(b&(one<<i))) ans += (one<<i);
        }
    }
    return ans;
}

int main() {
	long a, b;
	cin>>a>>b;
	cout<<andProduct(a, b)<<"\n";
	return 0;
}