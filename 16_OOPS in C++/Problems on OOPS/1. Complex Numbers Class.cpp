/* OOPS Prob. #1. Complex Number Class
Problem Statement:
A ComplexNumber class contains two data members: one is the real part (R) and the other is imaginary (I) (both integers).
Implement the Complex numbers class that contains the following functions -
1. Constructor
You need to create the appropriate constructor.

2. Plus - This function adds two given complex numbers and updates the first complex number.
e.g.
if C1 = 4 + i5 and C2 = 3 +i1
C1.plus(C2) results in:
C1 = 7 + i6 and C2 = 3 + i1

3. Multiply - This function multiplies two given complex numbers and updates the first complex number.
e.g.
if C1 = 4 + i5 and C2 = 1 + i2
C1.multiply(C2) results in:
C1 = -6 + i13 and C2 = 1 + i2

4. Print - This function prints the given complex number in the following format :
a + ib

Sample Input 1 :
4 5
6 7
1
Sample Output 1 :
10 + i12
*/

//	Running time = O(1)
//	Auxiliary space = O(1)

#include<iostream>
using namespace std;

class ComplexNumbers {
   	int real, imag;
public:
    ComplexNumbers(int r, int i) : real(r), imag(i) {}
    void plus(ComplexNumbers cNum) {
        real += cNum.real;
        imag += cNum.imag;
    }
    void multiply(ComplexNumbers cNum) {
        int a = real, b = imag, c = cNum.real, d = cNum.imag;
        real = (a*c - b*d);
        imag = (a*d + b*c);
    }
    void print() {
    	cout<<real<<" + i"<<imag;
    }


};

int main() {
    int real1, imaginary1, real2, imaginary2;
    cin >> real1 >> imaginary1;
    cin >> real2 >> imaginary2;
    ComplexNumbers c1(real1, imaginary1);
    ComplexNumbers c2(real2, imaginary2);
    int choice;
    cin >> choice;
    if (choice == 1) {
        c1.plus(c2);
        c1.print();
    }
    else if (choice == 2) {
        c1.multiply(c2);
        c1.print();
    }
    else
    	return 0;
}
