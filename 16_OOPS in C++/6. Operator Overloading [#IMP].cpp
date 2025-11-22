/* Operator Overloading Prob. #1. Intro to Opereator Overloading
Reference: https://www.programiz.com/cpp-programming/operator-overloading
*/


#include<iostream>
using namespace std;

class complexNumbers {
    int real, imag;
public:
    complexNumbers() : real(0), imag(0) {}
    complexNumbers(int r, int i) : real(r), imag(i) {}
    /*
    void operator ++ () {
        this->real++;
        this->imag++;
    }
    */
    complexNumbers operator ++ () {                 //  prefix increment by 1
        this->real++;
        this->imag++;
        return *(this);                             //  We can either return the current object i.e. *(this) or create a new object and return it.
    }

    complexNumbers operator ++ (int) {              //  postfix increment by 10
        //real += 10;                               //  Note the use of int as argument for the change from prefix to postfix
        //imag += 10;                               //  The int inside the parentheses is the syntax used for using unary operators as postfix; it's not a function parameter.
        real++;
        imag++;
        complexNumbers temp(real, imag);            //  Postfix does not work as expected, so fix it later [#INCOMPLETE]
        return temp;

    }

    complexNumbers operator + (complexNumbers const &b) {                       //  using & makes our code efficient by referencing the b object instead of making a
        complexNumbers c;                                                       //  duplicate object inside the operator function.
        c.real = this->real + b.real;
        c.imag = this->imag + b.imag;
        return c;
    }

    complexNumbers operator - (complexNumbers const &b) {
        complexNumbers c;
        c.real = real - b.real;
        c.imag = imag - b.imag;
        return c;
    }

    complexNumbers operator * (complexNumbers const &second) const {			//	const after arguments makes sure this function does not modify this->real and this->imag
        complexNumbers prod;													//	while const inside the argument makes sure that second/b is not modified by this function
        int a = real, b = imag, c = second.real, d = second.imag;				//	Both const keywords are optional but considered a good practice to minimize chances of introducing errors.
        prod.real = (a*c - b*d);
        prod.imag = (a*d + b*c);
        return prod;
    }

    void print() {
        cout<<real;
        if(imag>=0) cout<<" + "<<imag<<"i\n";
        else cout<<" - "<<-1*imag<<"i\n";
    }
};

int main() {
    complexNumbers a(2, 5);
    complexNumbers b(4, 3);
    a.print();  b.print();
    complexNumbers c = a + b;   c.print();
    c = b - a;                  c.print();
    c = a * b;                  c.print();
    complexNumbers d = ++a;     d.print();
    ++a;                        a.print();
    complexNumbers e = a++;     e.print();                                      //  This is where postfix is not working correctly. value of e should be a and not ++a
    a++;                        a.print();
    return 0;
}
