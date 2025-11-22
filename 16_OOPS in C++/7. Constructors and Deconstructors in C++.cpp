OOPS Topic 7. Constructors and Deconstructors:

#7.1. Constructors:
A constructor is a special type of member function that is called automatically when an object is created. In C++, a constructor has the same name as that 
of the class, and it does not have a return type.

Example:
class D {
    public:
        // create a constructor
        D() {
            // code
        }
};
 
Here, the function D() is a constructor of the class D. Notice that the constructor:
1.	has the same name as the class,
2.	does not have a return type, and
3.	is public
4.	is executed when an object is created
5.	is used in classes to initialize data members of the class in order to avoid errors/segmentation faults.
 
Types of Constructors
There are three types of constructors in C++ they are:
7.1.1.	Default constructor
7.1.2.	Parameterized Constructor
7.1.3.	Copy Constructor

7.1.1.	Default Constructor:
The default constructor is the constructor that doesn’t take any argument. It has no parameters.  
Syntax to define a Default Constructor: 
Class_name() {
	// body of the constructor
}

Example:
#include <iostream>
using namespace std;
class construct {
    public:
        int a, b;
    // Default Constructor
    construct() {
        a = 10;
        b = 20;
    }
};

int main() {
    // Default constructor is called automatically when the
    // object is created
    construct c;
    cout << "a: " << c.a << endl <<
        "b: " << c.b;
    return 0;
}
Output:
a: 10
b: 20 

Note: If we have not defined a constructor in our class, then the C++ compiler will automatically create a default constructor with an empty code and 
no parameters.

Default constructor as created by the compiler: 

class Class_name() {
    public: 
	Class_name() {}
};

7.1.2. Parameterized Constructor
A constructor with parameters is known as a parameterized constructor. The parameterized constructor takes its arguments provided by the programmer. 
To create a parameterized constructor, simply add parameters to it the way you would to any other function. When you define the constructor’s body, 
use the parameters to initialize the object. 

If only a parameterized constructor is used and an object is created without parameters, then this results in an error;
Example:
#include <iostream>
#include <string>
using namespace std;

class A {
    int a;
    public:
        A(int i) {
            a = i;
        }
        void assign(int i) {
            a = i;
        }
        int getA() {
            return a;
        }
};

int main() {
    A obj;
    obj.assign(5);
    cout << obj.getA();
}
Output:
Error

Syntax to define a parameterized Constructor: 
Class_name(parameters) {
	// body of the constructor
}

Example:
#include <iostream>
using namespace std;
class construct {
    public:
        int a, b;
    // Default Constructor
    construct(int x, int y) {
        a = x;
        b = y;
    }
};
int main() {
    // Parameterized constructor is called
    construct c(40, 50);
    cout << "a: " << c.a << endl <<
        "b: " << c.b;
    return 0;
}
Output:
a: 40
b: 50 

7.1.3. Copy Constructor
A copy constructor is a member function that initializes an object using another object of the same class.
Syntax to define a copy constructor: 
Class_name(const Classname &old_object) {		//	Note the use of const(optional) and &(mandatory)
	// body of the constructor
}

Example: 
#include<iostream>
using namespace std;
class construct {
    private:
        int a, b;
    public:
        construct(int x, int y) {
            a = x;
            b = y;
        }
    // Copy constructor 
    construct(const construct & p2) {
        a = p2.a;
        b = p2.b;
    }
    int getX() {
        return a;
    }
    int getY() {
        return b;
    }
};
int main() {
    construct p1(10, 15); 	// Normal constructor is called here 
    construct p2 = p1; 		// Copy constructor is called here 
    // Let us access values assigned by constructors 
    cout << "p1.a = " << p1.getX() << ", p1.b = " << p1.getY();
    cout << "\np2.a = " << p2.getX() << ", p2.b = " << p2.getY();
    return 0;
}
Output:
p1.a = 10, p1.b = 15
p2.a = 10, p2.b = 15  

How are constructors different from a normal member function?
a.	A constructor has the same name as the class itself.
b.	Constructors don’t have a return type.
c.	A constructor is automatically called when an object is created.
d.	If we do not specify a constructor, the C++ compiler generates a default constructor for us (expects no parameters and has an empty body).

7.1.4. Constructor Overloading:
In C++, We can have more than one constructor in a class with the same name, as long as each has a different list of arguments. This concept 
is known as Constructor Overloading and is quite similar to function overloading.

a.	Overloaded constructors essentially have the same name (name of the class) and a different number of arguments.
b.	A constructor is called depending upon the number and type of arguments passed.
c.	While creating the object, arguments must be passed to let the compiler know which constructor needs to be called i.e. compile time polymorphism.

Example:
#include <iostream>
using namespace std;
class construct {
    public:
        float area;
    // Constructor with no parameters 
    construct() {
        area = 0;
    }
    // Constructor with two parameters 
    construct(int a, int b) {
        area = a * b;
    }
    void disp() {
        cout << area << endl;
    }
};
int main() {
    // Constructor Overloading 
    // with two different constructors 
    // of class name 
    construct o;
    construct o2(10, 20);
    cout << "Area using default constructor: ";
    o.disp();
    cout << "Area using parameterized constructor: ";
    o2.disp();
    return 0;
}
Output:
Area using default constructor: 0
Area using parameterized constructor: 200


#7.2. Destructors:
A destructor is a special member function that works just opposite to a constructor; unlike constructors that are used for initializing an object, destructors 
destroy (or delete) the object. 

Syntax of a destructor:
~class_name() {   
   //Some code   
}

Similar to the constructor, the destructor name should exactly match the class name. A destructor declaration should always begin with the tilde(~) symbol, as 
shown in the syntax above.

* When is a destructor called? 
Destructors are used in Classes to destroy an object after its lifetime is over (goes out of scope), i.e., it frees resources occupied by that object.
A destructor function is called automatically when the object goes out of scope i.e.:
a.	the function ends
b.	the program ends
c.	a block containing local variables ends
d.	a delete operator is called
 
Example:
#include <iostream>
using namespace std;
class HelloWorld{
public:
  //Constructor
  HelloWorld(){
    cout<<"Constructor is called"<<endl;
  }
  //Destructor
  ~HelloWorld(){
    cout<<"Destructor is called"<<endl;
   }
   //Member function
   void display(){
     cout<<"Hello World!"<<endl;
   }
};
int main(){
   //Object created
   HelloWorld obj;
   //Member function called
   obj.display();
   return 0;
}
Output:
Constructor is called
Hello World!
Destructor is called

Destructor rules:
a.	The name should begin with a tilde sign(~) and must match the class name.
b.	There cannot be more than one destructor in a class.
c.	Unlike constructors that can have parameters, destructors do not allow any parameters.
d.	They do not have any return type, just like constructors.
e.	When you do not specify any destructor in a class, the compiler generates a default destructor and inserts it into your code.
