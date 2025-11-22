4. Abstract Class or Interface in C++:

Interfaces in C++:
In C++ terminology, a class with atleast one pure virtual function can be termed as an abstract class.
We can implement Interfaces in C++ with the help of abstract classes. Interfaces are closely associated with classes and objects. 
Therefore, it is safe is to say that the term “Interfaces” and “Abstract Classes” more or less convey the same idea.

Note: It is important to note that abstract classes and data abstraction in C++ are two different concepts as data abstraction 
simply separates the essential data from its implementation techniques which can be done with or without abstract classes.

/*[Verify the exact definition of an interface]
An interface does not have an implementation of any of its methods. It can be considered as a collection of method declarations
only i.e. no definitions. 
In C++, an interface can be simulated by making all methods as pure virtual. 
Note - The only difference between an abstract class (atleast one pure virtual function) and interface (all pure virtual functions) in C++.
*/

Abstract classes are essential to providing an abstraction to the code to make it reusable and extendable.
a.	By definition, an abstract class in C++ is a class that has "at least one" pure virtual function (i.e., a function that has no 
	definition). 
	It may or may not have normal functions and variables along with pure virtual functions.

b.	[#IMP] Base class having a pure virtual function becomes abstract i.e. it cannot be instantiated or we cannot create objects 
	of an abstract class. However, we can derive classes from them, and use their data members and member functions (except pure 
	virtual functions).
	
c.	The classes inheriting the abstract class must provide a definition for the pure virtual function; otherwise, the subclass 
	would become an abstract class itself.

Virtual function:
A virtual function is a member function which is declared within a base class and is re-defined(Overriden) by a derived class. 
When you refer to a derived class object using a pointer or a reference to the base class, you can call a virtual function for 
that object and execute the derived class’s version of the function.

Pure virtual function / Abstract function:
A pure virtual function (or abstract function) in C++ is a virtual function for which we doesn’t have an implementation, i.e. we 
only declare it. A pure virtual function is declared by assigning 0 in the declaration.

Similarities between virtual function and pure virtual function:
a.	These are the concepts of Run-time polymorphism.
b.	Prototype or declaration of both the functions remains the same throughout the program.
c.	These functions can’t be global or static.

Difference between virtual function and pure virtual function in C++:
					Virtual function														Pure virtual function							
a. 	A virtual function is a member function of base class which 			a. 	A pure virtual function is a member function of base class 
	can be redefined by derived class.											whose only declaration is provided in base class & should be defined
																				in derived class otherwise derived class also becomes abstract.
b. 	Classes having virtual functions are not abstract.						b. 	Base class containing pure virtual function becomes abstract.
c. 	Syntax:	virtual<func_type><func_name>(param) {								c. 	Syntax: virtual<func_type><func_name>(param) = 0;
			// code
			}
d. 	Definition is given in base class.										d. 	No definition is given in base class.
e. 	[#IMP] Base class having virtual function can be instantiated        	e. 	Base class having pure virtual function becomes abstract i.e. it cannot 
	i.e. its object can be made.										   		be instantiated.
f. 	If a derived class does not redefine a virtual function of the      	f. 	If a derived class does not redefine virtual function of the base class, then we 
	base class, then it does not affect compilation.                        	don't get a compilation error but that derived class also becomes abstract just 
																				like the base class.
g. 	All derived classes may or may not redefine virtual function of			g. 	All derived classes must redefine pure virtual function of the base class otherwise 
	the base class.														   		that derived class also becomes abstract just like base class.
   
   
Properties of abstract classes:
#a.	A class is abstract if it has at least one pure virtual function. If a class is abstract it cannot be instantiated i.e. we cannot create its object.
//	It may or may not have normal functions and variables along with pure virtual functions.

#include<iostream>
using namespace std;

class test {
	int x;
public:
	test(int x_) : x(x_) {}
	virtual void foo() = 0;
	int getX() { return x; }
};

int main() {
	test t(5);						//	Gives an error, as we cannot instantiate an abstract class.
	t.getX();
	return 0;
} 

Output:
Compiler error: Cannot instantiate an abstract class.cpp|13|error: cannot declare variable 't' to be of abstract type 'test'|

#b.	We can have pointers and references of an abstract class but not an object. 
E.g. 
base *b = new derived;				//	Pointer of an abstract class but points to derived object.
b->foo();

#c.	If we do not override the pure virtual function in derived class, then derived class also becomes an abstract class. 

#include<iostream>
using namespace std;

class base {
public:
	virtual void foo() = 0;
};

class derived: public base {};		//	No definition given to the pure virtual function in the derived class, thus the derived class becomes abstract too.

int main() {
	//base b;
	derived d;                      //  Error as we cannot declare an object of an abstract class.
	return 0;
}

Output:
Compiler error: Cannot instantiate an abstract class (derived class).cpp|13|error: cannot declare variable 'd' to be of abstract type 'derived'|

#d.	An abstract class can have constructors. 

#include<iostream>
using namespace std;

class base {
protected:
	int x;                      //  x is not private hence, inherited
public:
	base(int x_): x(x_) {cout<<"Constructor of the base class called\n";}
	virtual void foo() = 0;
};

class derived: public base {
	int y;
public:
	derived(int x_, int y_): base(x_), y(y_) {}
	void foo() {
		cout<<"x = "<<x<<", y = "<<y<<"\n";
	}
};

int main() {
	derived d(2, 5);
	d.foo();
	base *b = new derived(1, 3);
	b->foo();
	return 0;
}

Output: 
Constructor of the base class called
x = 2, y = 5
Constructor of the base class called
x = 1, y = 3

Consider an example of a Shape base class with sub-classes (Triangle and Rectangle)​ that inherit the Shape class.

#include<iostream>
#include<vector>
#include<cmath>         //  for sqrt()
#include<time.h>        //  for time(0)
//#include<cstdlib>     //  (optional) for srand()

using namespace std;

class shape {
public:
	virtual int getNumOfSides() = 0;
	virtual double getArea() = 0;
};

class triangle: public shape {
	const int n = 3;
	double a, b, c;
public:
	triangle(double a_, double b_, double c_) : a(a_), b(b_), c(c_) {}
	int getNumOfSides() {
		return n;
	}
	double getArea() {
		double s = (a+b+c)/2;
		return sqrt(s*(s-a)*(s-b)*(s-c));
	}
};

class rectangle: public shape {
	const int n = 4;
	double l, b;
public:
	rectangle(double l_, double b_) : l(l_), b(b_) {}
	int getNumOfSides() {
		return n;
	}
	double getArea() {
		return l*b;
	}
};

int main() {
	int n = 5;
	vector<shape*> shapes(n);
	srand(time(0));																			//	Using time(0) to generate a pseudo-random number.
	for(int i=0; i<n; i++) {
		if(i%2==0) shapes[i] = new triangle((rand()%10)+5, (rand()%10)+7, (rand()%10)+6);	//	For even values of i, shapes[i] is alloted a triangle
		else shapes[i] = new rectangle(rand()%20+5, rand()%20+3);							//	For odd values of i, shapes[i] is alloted a rectangle
	}
	for(int i=0; i<n; i++) {
		if(shapes[i]->getNumOfSides() == 3) cout<<"The shape is a triangle with area = "<<shapes[i]->getArea()<<"\n";
		else cout<<"The shape is a rectangle with area = "<<shapes[i]->getArea()<<"\n";
	}
	return 0;
}
