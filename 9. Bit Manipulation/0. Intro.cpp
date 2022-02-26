/* Bit Manipulation or Bit Magic or Bit Masking

I.	Introduction:
Operations with bits are used in Data compression (data is compressed by converting it from one representation to another, 
to reduce the space), Exclusive-Or Encryption (an algorithm to encrypt the data for safety issues). In order to encode, 
decode or compress files we have to extract the data at bit level. Bitwise Operations are faster and closer to the system 
and sometimes optimize the program to a good level.

We all know that 1 byte comprises of 8 bits and any integer or character can be represented using bits in computers, which 
we call its binary form(contains only 1 or 0) or in its base 2 form.

Example:
1) 14 = {1110}
= 1 * 23 + 1 * 22 + 1 * 21 + 0 * 20
= 14.

2) 20 = {10100}
= 1 * 24 + 0 * 23 + 1 * 22 + 0 * 21 + 0 * 20
= 20.


For characters, we use ASCII representation, which are in the form of integers which again can be represented using bits as 
explained above.

char to ASCII int to bits

II.	Bitwise Operators:

Bitwise operators are good for saving space and sometimes to cleverly remove dependencies. There are different bitwise 
operations used in the bit manipulation. These bit operations operate on the individual bits of the bit patterns. Bit 
operations are fast and can be used in optimizing time complexity. Some common bit operators are:

1.	NOT ( ~ ): Bitwise NOT is an unary operator that flips the bits of the number i.e., if the ith bit is 0, it will change it 
to 1 and vice versa. Bitwise NOT is nothing but simply the one’s complement of a number. 
Lets take an example.
N = 5 = (101)2
~N = ~5 = ~(101)2 = (010)2 = 2

2.	AND ( & ): Bitwise AND is a binary operator that operates on two equal-length bit patterns. If both bits in the compared 
position of the bit patterns are 1, the bit in the resulting bit pattern is 1, otherwise 0.
A = 5 = (101)2 , B = 3 = (011)2 A & B = (101)2 & (011)2= (001)2 = 1

3.	OR ( | ): Bitwise OR is also a binary operator that operates on two equal-length bit patterns, similar to bitwise AND. If 
both bits in the compared position of the bit patterns are 0, the bit in the resulting bit pattern is 0, otherwise 1.
A = 5 = (101)2 , B = 3 = (011)2
A | B = (101)2 | (011)2 = (111)2 = 7

4.	XOR ( ^ ): Bitwise XOR also takes two equal-length bit patterns. If both bits in the compared position of the bit patterns 
are 0 or 1, the bit in the resulting bit pattern is 0, otherwise 1. (1^1 or 0^0 = 0 and 0^1 or 1^0 = 1)
A = 5 = (101)2 , B = 3 = (011)2
A ^ B = (101)2 ^ (011)2 = (110)2 = 6
Note: The bitwise XOR operator is the most useful operator from a technical interview perspective.

5.	Left Shift (x << k): Left shift operator is a binary operator which shifts the given bit pattern x to the left and appends 0 0
at the end, k times. Left shift is equivalent to multiplying the bit pattern with 2^k ( if we are shifting k bits ).
1 << 1 = 2 = 2^1
1 << 2 = 4 = 2^2
1 << 3 = 8 = 2^3
1 << 4 = 16 = 2^4
…
1 << n = 2^n

6	Right Shift (x >> k): Right shift operator is a binary operator which shifts the given bit pattern x to the right and appends 1 
at the end, k times. Right shift is equivalent to dividing the bit pattern with 2^k ( if we are shifting k bits ).
4 >> 1 = 4/2^1 = 2
6 >> 1 = 6/2^1 = 3
5 >> 1 = 5/2^1 = 2
16 >> 4 = 16/2^4 = 1

Note: The left shift and right shift operators should not be used for negative numbers

Differences between a logical AND(&&) and a bitwise AND(&) operator:
1.	A logical operator is represented as ‘&&’.							
	A Bitwise And operator is represented as ‘&’
2.	The logical AND(&&) operator works on boolean expressions, and returns boolean values only.
	The bitwise AND(&) operator works on on integral values (i.e. short, int, unsigned, char, bool, unsigned char, long) and returns 
	that integral value. 
	Note - Bitwise AND/OR does not work on non-integer datatypes like float, double, etc.
	
The same differences are there between logical OR ‘||’ and bitwise OR ‘|’.

Bitwise operators table

X		Y		X&Y		X|Y		X^Y		~X
0		0		0		0		0		1
0		1		0		1		1		1
1		0		0		1		1		0
1		1		1		1		0		0

On int values
X		Y		X&Y		X|Y		X^Y		~X
101		100		100		101		001		010

III.	Bit masking

1. Set bit
A bit is said to be set iff it is 1.

2. Get ith bit: It returns the ith bit value for given number x

bool getBit(int x, int i) {
	return (x & (1 << i));
}

3. Set ith bit

4a. x & (-x)
4b. x & (~(x-1))
4c. x ^ (x & (x-1))
All the three expression return the right most set bit.

5.	if(x&1) cout<<"x is a odd number\n";
	else cout<<"x is an even number\n";

6.	x & (x-1); (x-1) can be obtained from x by inversing all the bits right of the rightmost set bit including the rightmost set bit.



Note: 
1. 	Use parentheses before using == operator
2.	If long data type as used, then (1<<i) returns int 2^i which leads to incorrect answers so it is better to declare 
	a variable long one = 1; and then use (one<<i) to get long 2^i thus getting the correct answer.



