OOPS - Object Oriented Programming System

* OOPS Concepts:
1. 	Object
2.	Class
3.	Encapsulation
4.	Abstraction
5.	Polymorphism
6.	Inheritance

* Introduction:
Object-oriented programming – As the name suggests uses objects in programming. Object-oriented programming aims to implement real-world entities like 
inheritance, hiding information, polymorphism, etc in programming. The main aim of OOP is to bind together the data and the functions that operate on 
them so that no other part of the code can access this data except that function known as a method.

* Class:
The building block of C++ that leads to Object-Oriented programming is a Class. It is a user-defined data type, which holds its own data members and 
member functions, which can be accessed and used by creating an instance of that class. A class is like a blueprint for an object. We can say that a 
Class in C++ is a blue-print representing a group of objects which shares some common properties and behaviours. A class is a logical entity while
an object is a physical entity.
For Example: Consider the Class of Cars. There may be many cars with different names and brands but all of them will share some common properties like 
all of them will have 4 wheels, Speed Limit, Mileage range etc. So here, Car is the class and wheels, speed limits, mileage are their properties.
Note:
a.	A Class is a user-defined data-type which has data members and member functions.
b.	Data members are the data variables and member functions are the functions used to manipulate these variables and together, these data members and 
	member functions define the properties and behaviour of the objects in a Class.
c.	In the above example of class Car, the data member will be speed limit, mileage, etc and member functions can apply brakes, increase speed, etc.
d. 	A member function or method that does not change the value of data members of a class is known an accessor function (getter) while a member function 
	that modifies the value of data members of a class is known as a mutator function (setter).

* Object:
An Object is an identifiable entity with some characteristics and behaviour. An Object is an instance of a Class. When a class is defined, no memory 
is allocated but when it is instantiated (i.e. an object is created) memory is allocated. E.g. - 

class person {				//	person is a class
    char name[20];
    int id;
public:
    void getdetails(){
		cout<<"Name = "<<name<<"\n";
		cout<<"ID = "<<id<<"\n";		
	}
};
  
int main() {
   person p1; 				// 	p1 is an object of class person
}

* The four basic concepts of OOPS are:

#1.	Encapsulation:
	In normal terms, Encapsulation is defined as wrapping up of data and information under a single unit. 
	In Object-Oriented Programming, Encapsulation is defined as binding together the data and the functions that manipulate them.
	Encapsulation in C++ = A Class = (data members + member functions or methods)
	We can create a fully encapsulated class by making all the data members private. If the data members are private, it can only be accessible within the 
	class; no other class can access that class’s data members except via public methods.
	Encapsulation also leads to data abstraction or hiding. As using encapsulation also hides the data. In the below example, the data of any of the section 
	like sales, finance or accounts are hidden from any other section.
	
	Consider a real-life example of encapsulation, in a company, there are different sections like the accounts section, finance section, sales section etc. 
	The finance section handles all the financial transactions and keeps records of all the data related to finance. Similarly, the sales section handles all 
	the sales-related activities and keeps records of all the sales. Now there may arise a situation when for some reason an official from the finance section 
	needs all the data about sales in a particular month. In this case, he is not allowed to directly access the data of the sales section. He will first have 
	to contact some other officer in the sales section and then request him to give the particular data. This is what encapsulation is. Here the data of the 
	sales section and the employees that can manipulate them are wrapped under a single name “sales section”.
	
	Advantages of encapsulation:
	a.	Encapsulation is a way to achieve data abstraction/hiding because other classes will not be able to access the data through the private data members.
	b.	By encapsulation, we can make the class read-only. The code reusability is also an advantage of encapsulation.
	c.	Encapsulated code is better for unit testing.

#2.	Abstraction: 
	Abstraction means displaying only essential information and hiding the details. Data abstraction refers to providing only essential information 
	about the data to the outside world, hiding the background details or implementation. Data abstraction is one of the most essential and important features of 
	object-oriented programming in C++.
	There are two ways to implement data abstraction in C++
2.1.) Abstraction using Classes: [#IMP] We can implement Abstraction in C++ using classes. The class helps us to group data members and member functions using available 
		access specifiers. A Class can decide which data member will be visible to the outside world and which is not using access specifiers.
		Access specifiers are the main pillar of implementing abstraction in C++. We can use access specifiers to enforce restrictions on class members. 
		For example: 
	2.1.1.)	Members declared as public in a class, can be accessed from anywhere in the program.
	2.1.2.) Members declared as protected in a class, can be accessed only by the derived classes.
	2.1.2.) Members declared as private in a class, can be accessed only from within the class and not allowed to be accessed from any part outside the class except
			a friend function or a friend class.
2.2.) Abstraction in Header files: One more type of abstraction in C++ can be header files. For example, consider the pow() method present in math.h header file. 
		Whenever we need to calculate the power of a number, we simply call the function pow() present in the math.h header file and pass the numbers as arguments 
		without knowing the underlying algorithm according to which the function is actually calculating the power of numbers.
	Advantages of Data Abstraction:
	a.	Avoids code duplication and increases reusability.
	b.	Can change internal implementation of class independently without affecting the user.
	c.	Helps to increase security of an application or program as only important details are provided to the user.

#3.	Polymorphism: 
	The word polymorphism means having many forms. In simple words, we can define polymorphism as the ability of a message to be displayed in more than one form.
	E.g. A person at the same time can have different characteristic. Like a man at the same time is a father, a husband, an employee. So the same person possesses 
	different behaviour in different situations. This is called polymorphism. Polymorphism is extensively used in implementing inheritance.
	Similarly, an operation may exhibit different behaviours in different instances. The behaviour depends upon the types of data used in the operation.
	There are two categories of polymorphism:
	1.	Compile time polymorphism:
	2. 	Runtime polymorphism
	
	1. 	Compile time polymorphism:
		Compile-time polymorphism is also known as static polymorphism. This type of polymorphism can be achieved through operator overloading or function overloading.
	2.	Runtime polymorphism
		Runtime polymorphism is also known as dynamic polymorphism. Function/method overriding is a way to implement runtime polymorphism.
		
	C++ supports three types of polymorphism: 
	a.	Operator Overloading (Compile time polymorphism)	
	b.	Function Overloading (Compile time polymorphism)
	c.	Function/method Overriding (Runtime polymorphism)
	
	Note: 
	a.	a & b are e.g. of compile time polymorphism while c is an e.g. of runtime polymorphism
	b.	Functions can not be overloaded if they differ only in the return type. [#IMP]
		Example: 
		int test(int a) {}
		double test(int b) {}
		Here, both functions have the same name, same type of arguments and the same number of arguments. Hence, the compiler will throw an error.
	c. 	Ways to overload a function: There are two ways to overload a function, and they are:
		i)	By Changing the number of arguments.
		ii)	By Changing the data type of arguments.
	--------------------------------------------------------------------------------------------------------------------------------------------------------------------
3.1.)	Operator Overloading: The process of making an operator to exhibit different behaviours in different instances is known as operator overloading. (#Important)
		E.g. s = s + 'a'; int c = a + b; So, the operator + is used in two different forms. Plus, we can even define custom usage of operator +.
		
		Points to remember while overloading an operator:
		1.)	It can be used only for user-defined operators(objects, structures) but cannot be used for in-built operators(int, char, float, etc.).
		2.)	Two operators = and & are already overloaded by default in C++. For example, to copy objects of the same class, we can directly use the = operator. We do not need to create 
			an operator function except for deep copy.
		3.)	Operator overloading cannot change the precedence and associativity of operators. However, if we want to change the order of evaluation, parentheses should be used.
		
		There are four operators that cannot be overloaded in C++. They are:
		1.)	:: (scope resolution)
		2.)	. (member selection)
		3.)	.* (member selection through pointer to function)
		4.)	?: (ternary operator)
		
		Note: 
		a.	The destructor of a class cannot be overloaded in C++ programming. Increment operator, constructor, and new and delete can be overloaded.
		b.	Syntax for overloading unary operators is different from that for overloading binary operators
		
		E.g.
		//	Reference: https://www.programiz.com/cpp-programming/operator-overloading

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
		
3.2.)	Function Overloading: [#IMP]Function overloading is using a single function name to perform different types of tasks. In C++, we can use two or more functions 
		having the same name if they have different parameters ([#IMP] either types or number of arguments). And, depending upon the number/type of arguments, different 
		functions are called. It's a compile-time polymorphism because the compiler knows which function to execute before the program is fully compiled [Verified].
		i) 	Function overloading with different numbers of arguments: E.g. sum(int a, int b) and sum(int a, int b, int c)
		ii)	Function overloading with different types of arguments:	E.g. sum(int a, int b) and sum(float a, float b)
		E.g. - Three different forms of the function sum
		
		#include<iostream>
		using namespace std;
		
		int sum(int a, int b) {
			return a+b;
		}
		
		double sum(double a, double a) {
			return a+b;
		}
		
		int sum(int a, int b, int c) {
			return a+b+c;
		}
		
		int main() {
			cout<<sum(2,5)<<" "<<sum(1.5, 2.6)<<" "<<sum(1, 2, 3)<<"\n";
			return 0;
		}
		
		Default Arguments: Another way of function overloading only while calling can be done by using default arguments i.e. defined once, but called in multiple ways.
		A default argument is a value provided in a function declaration automatically assigned by the compiler if the caller of the function doesn’t provide a value 
		for the argument with a default value. However, if arguments are passed while calling the function, the default arguments are ignored. 

		Example: A function with default arguments can be called with 2 or 3 or 4 arguments.
		#include<iostream>
		using namespace std;
		int add(int x, int y, int z = 0, int w = 0) {
			return (x + y + z + w);
		}
		int main() {
			cout << add(10, 20) << endl;
			cout << add(10, 20, 30) << endl;
			cout << add(10, 20, 30, 40) << endl;
			return 0;
		}
		Output:
		30
		60
		100
		
		Note:
		Default parameters are defined to the "rightmost side of the parameter list" in a function to differentiate between the normal and default parameters; for example, 
		if a function is defined as fun(int x = 5, int y), then if we call fun(10) then 10 should be given to x or y because one can apply both logics like x = 10 already
		defined and 10 passed is for y but if compiler reads it from left to right it will think it is for x and no parameter is given for y; therefore, the compiler will 
		give an error.
		
3.3.)	Function/Method Overriding: In C++ inheritance, we can have the same function in the base class as well as its derived classes.	
		Function/Method overriding is a feature that allows you to redefine the base class method in the derived class based on its requirement. In other words, whatever 
		methods the base class has by default are available in the derived class. But, sometimes, a derived class may not be satisfied with base class method implementation. 
		The derived class is allowed to redefine that method as per on its own requirement. This process is called function/method overriding. 
 
		Rules for method overriding:
		a.	The method of the base class and the method of the derived class must have the same name.
		b.	The method of the base class and the method of the derived class must have the same parameters.
		c.	It is possible through inheritance only. [#IMP]
		
		3.3.1.)	Without using a virtual function: 
				When we call the function using an object of the derived class, the function of the derived class is executed instead of the one in the base class. 
				So, different functions are executed depending on the object calling the function. This is known as function overriding in C++. It's a runtime polymorphism 
				because the function call is not resolved by the compiler, but it is resolved in the runtime instead.
				E.g. - // C++ program to demonstrate function overriding

				#include <iostream>
				using namespace std;
				
				class Base {
				public:
					virtual void print() {
						cout << "Base Function" << endl;
					}
				};
				
				class Derived : public Base {
				public:
					void print() {
						cout << "Derived Function" << endl;
					}
				};
				
				int main() {
					Base base1;
					base1.print();			// 	Calls print() function of the Base class
					Derived derived1;				
					derived1.print();		// 	Calls print() function of the Derived class
					return 0;
				}
				
				Output:
				Base Function
				Derived Function
				
				Rules for method overriding without using a virtual function:
				a.	The parent class method and the method of the child class must have the same name.
				b.	The parent class method and the method of the child class must have the same parameters. 
					(If they don't have the same parameters then, it would become a case of function overloading and not overriding)
				c.	It is possible through inheritance only.
		
		3.3.2.)	Using a virtual function:
				In C++, we may not be able to override functions if we use a pointer of the base class to point to an object of the derived class. Using virtual functions in the 
				base class ensures that the function can be overridden in these cases. Thus, virtual functions actually fall under function overriding. Virtual functions are 
				runtime polymorphism.
	
#4.	Inheritance:
	The capability of a class to derive properties and characteristics from another class is called Inheritance. Inheritance is one of the most important features of 
	Object-Oriented Programming. 
	Key Terms related to inheritance are:
	a.	Sub Class or Derived Class: The class that inherits properties from another class is called a Sub class or Derived Class.
	b.	Super Class or Base Class: The class whose properties are inherited by a sub class is called a Base Class or Super class.
	c.	Reusability: Inheritance supports the concept of “reusability”, i.e. when we want to create a new class and there is already a class that includes some of the 
		code that we want, we can derive our new class from the existing class. By doing this, we are reusing the fields and methods of the existing class.
	C++ inheritance syntax:
	class base_class {
		//Body of base_class
	};
	class subclass_name : access_mode_1 base_class_name1, access_mode_2 base_class_name2, ... {
		//body of sub_class
	}
	
	E.g. class animal (Base class) 
			-> a.) class cat 	
			-> b.) class dog
			-> c.) class cow
		Here, animal is a base class and cat, dog, cow are derived classes.
		
	Advantages of inheritance:
	a.	The main advantage of inheritance is code reusability. We can reuse the code when we inherit the existing class’s methods and fields into a new class.
	b.	The runtime polymorphism (method overriding w or w/o virtual functions) can be achieved by inheritance only.
		
* Other concepts:
1.	Dynamic Binding: In dynamic binding, the code to be executed in response to function call is decided at runtime. C++ has virtual functions to support this.
	
Note: There are two steps to execute a program i.e. we first compile the program and then run it. Thus, there are two different time slots a. Compile time and b. Run time.
Compile time polymorphism is also known as static polymorphism while runtime polymorphism is also known as dynamic polymorphism.
	
	

