/* Bit manipulation problem 21. Palindromic Binary Representation
Given an integer n, find the nth number whose binary representation is a palindrome.
Note:
a.	Consider the 1st number whose binary representation is palindrome as 1, instead of 0
b.	Do not consider the leading zeros, while considering the binary representation.
*/

//	Method 1 - Using len and offset to identify and thus create the nth palindromic number
//	Running time = O(log2(n)) due to the while loop
//	Auxiliary space = O(1)

int reverseFromLeftMostBit(int x) {
    int rev = 0;
    while(x) {
        rev = rev | (x&1);
        rev = rev<<1;
        x = x>>1;
    }
    rev = rev>>1;	//	When the last set bit of n is put in rev, the result has been obtained but the loop left shifts result
    return rev;		//	so, we need to right shift rev once to get the correct result
}

int nthPalindromicNumber(int n) {
    int len = 1;									//	We need to know two parameters len and offset to get the nth palindromic number
	int ithNum = 1;									//	a.	len is the no. of bits in the binary represetation of a palindrome
	while(ithNum<n) {								//	b.	offset along with len is used to identify and thus create the nth palindromic number 
		len++;
		int palinElemsOfCurrLen = (1<<((len-1)/2));	//	Using the formula that a binary number of len no. of bits represents 2^((len-1)/2) palindromic numbers
		if(ithNum + palinElemsOfCurrLen > n) break;	
		else ithNum += palinElemsOfCurrLen;
	}
	int palin = 1<<(len-1);
	if(ithNum==n) palin = 2*palin-1;				//	If (ithNum == n) => offset == 11...1 i.e offset = n-4 or palin  = 100...0 then 2*palin - 1 = 1000...0 - 1 = 111...1 
	else {
		int offset = n-ithNum-1;					//	If (ithNum < n) => offset = n - ithSum - 1 (-1 since we start from 0...0 and not 0...1)
		palin = palin | offset<<(len/2);			//	Refer notes
		int rev = palin>>(len/2);
		rev = reverseFromLeftMostBit(rev);
		palin = palin | rev;
	}
	return palin;
}		