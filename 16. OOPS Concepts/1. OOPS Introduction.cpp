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
Class in C++ is a blue-print representing a group of objects which shares some common properties and behaviours.
For Example: Consider the Class of Cars. There may be many cars with different names and brand but all of them will share some common properties like 
all of them will have 4 wheels, Speed Limit, Mileage range etc. So here, Car is the class and wheels, speed limits, mileage are their properties.
Note:
a.	A Class is a user-defined data-type which has data members and member functions.
b.	Data members are the data variables and member functions are the functions used to manipulate these variables and together, these data members and 
	member functions define the properties and behaviour of the objects in a Class.
c.	In the above example of class Car, the data member will be speed limit, mileage, etc and member functions can apply brakes, increase speed, etc.

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
	Encapsulation also leads to data abstraction or hiding. As using encapsulation also hides the data. In the below example, the data of any of the section 
	like sales, finance or accounts are hidden from any other section.

	Consider a real-life example of encapsulation, in a company, there are different sections like the accounts section, finance section, sales section etc. 
	The finance section handles all the financial transactions and keeps records of all the data related to finance. Similarly, the sales section handles all 
	the sales-related activities and keeps records of all the sales. Now there may arise a situation when for some reason an official from the finance section 
	needs all the data about sales in a particular month. In this case, he is not allowed to directly access the data of the sales section. He will first have 
	to contact some other officer in the sales section and then request him to give the particular data. This is what encapsulation is. Here the data of the 
	sales section and the employees that can manipulate them are wrapped under a single name “sales section”.

#2.	Abstraction: 
	Abstraction means displaying only essential information and hiding the details. Data abstraction refers to providing only essential information 
	about the data to the outside world, hiding the background details or implementation. Data abstraction is one of the most essential and important features of 
	object-oriented programming in C++.
	There are two ways to implement data abstraction in C++
	a.	Abstraction using Classes: [#IMP] We can implement Abstraction in C++ using classes. The class helps us to group data members and member functions using available 
		access specifiers. A Class can decide which data member will be visible to the outside world and which is not.
		Access specifiers are the main pillar of implementing abstraction in C++. We can use access specifiers to enforce restrictions on class members. 
		For example: Members declared as public in a class, can be accessed from anywhere in the program.
					 Members declared as private in a class, can be accessed only from within the class and not allowed to be accessed from any part outside the class.		
	b.	Abstraction in Header files: One more type of abstraction in C++ can be header files. For example, consider the pow() method present in math.h header file. 
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
	C++ supports three types of polymorphism:
	a.	Operator Overloading: The process of making an operator to exhibit different behaviours in different instances is known as operator overloading. (Not Important)
	b.	Function Overloading: [#IMP]Function overloading is using a single function name to perform different types of tasks. In C++, we can use two or more functions 
		having the same name if they have different parameters ([#IMP] either types or number of arguments). And, depending upon the number/type of arguments, different 
		functions are called. It's a compile-time polymorphism because the compiler knows which function to execute before the program is even compiled.
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
		
	c.	Function Overriding: In C++ inheritance, we can have the same function in the base class as well as its derived classes.		
		a.1.)	Without using a virtual function: 
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
		
		a.2.) 	Using a virtual function:
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
	E.g. class animal (Base class) 
			-> a.) class cat 	
			-> b.) class dog
			-> c.) class cow
		Here, animal is a base class and cat, dog, cow are derived classes.
		
* Other concepts:
1.	Dynamic Binding: In dynamic binding, the code to be executed in response to function call is decided at runtime. C++ has virtual functions to support this.
	Note: There are two steps to execute a program i.e. we first compile the program and then run it. Thus, there are two different time slots a. Compile time and b. Run time.
	
	

