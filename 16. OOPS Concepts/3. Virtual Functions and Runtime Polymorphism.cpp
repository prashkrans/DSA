Virtual Functions and Runtime Polymorphism in C++:

Polymorphism: The term Polymorphism means the ability to take many forms. It occurs if there is a hierarchy of classes 
which are all related to each other by inheritance.

Virtual function: A virtual function is a member function which is declared in the base class using the keyword virtual 
and is re-defined (Overriden) by the derived class. In C++, we may not be able to override functions if we use a pointer 
of the base class to point to an object of the derived class. Using virtual functions in the base class ensures that the 
function can be overridden in these cases. Thus, virtual functions actually fall under function overriding. 
Virtual functions are runtime polymorphism. 

Virtual functions in derived classes:
In C++, once a member function is declared as a virtual function in a base class, it becomes virtual in every class derived
from that base class. In other words, it is not necessary to use the keyword virtual in the derived class while declaring 
redefined versions of the virtual base class function.

Note: In C++ what this means is that if we call a member function (non-virtual) then it could cause a different member 
function to be executed instead depending on what type of object invoked it.

E.g.  Non-virtual function:

#include<iostream>
using namespace std;

class base {
public:
	void foo() {
		cout<<"Base class's function is called\n";
	}
};

class derived : public base {
public:
	void foo() {
		cout<<"Derived class's function is called\n";
	}
};

int main() {
	base  *b1, *b2, *b3;
	b1 = new base;      //  b1 points to a base object and thus calls the base class's foo()
	b1->foo();
    b2 = new derived;   //  Both b2 and b3 point to a derived object but still calls the base class's foo()
	b2->foo();			//	This happens due static linkage which means the call to foo() is getting set 
	derived d;			//	only once by the compiler which is in the base class.
	b3 = &d;
	b3->foo();
	return 0;
}

Output: 
Base class's function is called
Base class's function is called
Base class's function is called

Note:
Ideally, it should have called the respective foo() functions of the child/derived classes but instead it calls the foo() 
defined in the base class.
This happens due static linkage which means the call to foo() is getting set only once by the compiler which is in the base class.

E.g. Virtual function:

#include<iostream>
using namespace std;

class base {
public:
	virtual void foo() {    //  Using the virtual keyword before void foo() in the base class makes sure the appropriate foo() function is called.
		cout<<"Base class's function is called\n";
	}
};

class derived : public base {
public:
	void foo() {
		cout<<"Derived class's function is called\n";
	}
};

int main() {
	base  *b1, *b2, *b3;    //  Make sure to use asterisk before the pointer name i.e. base *b1, b2; => b1 is a pointer while b2 is an object
	b1 = new base;          //  b1 points to a base object and thus calls the base class's foo()
	b1->foo();
    b2 = new derived;       //  Both b2 and b3 point to a derived object and since the base class uses a virtual function,
	b2->foo();              //  both b2->foo() and b3->foo() calls the derived class's foo()
	derived d;
	b3 = &d;
	b3->foo();
	return 0;
}

Output:
Base class's function is called
Derived class's function is called
Derived class's function is called

Advantages of a using a virtual function:
a.	The idea is that virtual functions are called according to the type of the object instance pointed to or referenced, not according 
	to the type of the pointer or reference. In other words, virtual functions are resolved late, at runtime (Runtime polymorphism).
b.	Virtual functions allow us to create a list of base class pointers and call methods of any of the derived classes without even 
	knowing the kind of derived class object. 
c.	The main thing to note here is that the derived class’s function is called using a base class pointer.

How does the compiler perform runtime resolution?

The compiler maintains two things to serve this purpose:
a.	vtable: A table of function pointers (i.e. address of each method), maintained per class.  
b.	vptr: A pointer to vtable, maintained per object instance.

Compiler adds additional code at two places to maintain and use vptr.
1.)	Code in every constructor. This code sets the vptr of the object being created. This code sets vptr to point to the vtable of the class. 
2.)	Code with polymorphic function call (e.g. bp->show() in above code). Wherever a polymorphic call is made, the compiler inserts code to 
	first look for vptr using base class pointer or reference (In the above example, since pointed or referred object is of derived type, vptr 
	of derived class is accessed). Once vptr is fetched, vtable of derived class can be accessed. Using vtable, address of derived class function 
	foo() is accessed and called. 
	
Virtual functions along with the identifier override:
C++ 11 has given us a new identifier override that is very useful to avoid bugs while using virtual functions. This identifier specifies the member 
functions of the derived classes that override the member functions of the base class.

Syntax:
/*A.)
//	In derived classes:
class derivedClassName: public baseClassName override {
	//	base class body
}
[Verify] */

B.) In a derived class:
dataType functionName(parameters) override {
	//	function body
}

E.g. - 
class base {
public:
	virtual void foo() {
		// code
	}
};

class derived: public base {
public:
	void foo() override {
		// code
	}
};

If we use a function prototype in Derived class and define that function outside of the class, then we use the following code:

class Derived : public Base {
   public:
    void print() override;	// 	function prototype. Ends with a semi-colon instead of {}
};

void Derived::print() {		//	function definition outside the derived class
    // code
}

Syntax:
funcType className::functionName(arguments) {
	// body
}

Use of C++ override:
When using virtual functions, it is possible to make mistakes while declaring the member functions of the derived classes. Using the override identifier 
prompts the compiler to display error messages when these mistakes are made. Otherwise, the program will simply compile but the virtual function will not
be overridden.

Some of these possible mistakes are:
a.	Functions with incorrect names: For example, if the virtual function in the base class is named print(), but we accidentally name the overriding function
	in the derived class as pint().
b.	Functions with different return types: If the virtual function is, say, of void type but the function in the derived class is of int type. 
c.	Functions with different parameters: If the parameters of the virtual function and the functions in the derived classes don't match.
d.	No virtual function is declared in the base class.




