Inheritance:
The capability of a class to derive properties and characteristics from another class is called Inheritance. Inheritance is one 
of the most important feature of Object Oriented Programming. 
Sub Class or Derived Class: The class that inherits properties from another class is called Sub class or Derived Class. 
Super Class or Base Class: The class whose properties are inherited by sub class is called Base Class or Super class. 

Implementing inheritance in C++: For creating a sub-class which is inherited from the base class we have to follow the below syntax. 
Syntax:
class subclass_name : access_mode_1 base_class_name1, access_mode_2 base_class_name2, ... {
  //body of subclass
};

Modes of Inheritance or access specifiers:
1.	Public mode: If we derive a sub class from a public base class. Then the public member of the base class will become public in the 
	derived class and protected members of the base class will become protected in derived class.
2.	Protected mode: If we derive a sub class from a Protected base class. Then both public member and protected members of the base class 
	will become protected in derived class.
3.	Private mode: If we derive a sub class from a Private base class. Then both public member and protected members of the base class will 
	become Private in derived class.
	Note: 
	a.	A derived class doesn’t inherit access to private data members. However, it does inherit a full parent object, which contains any 
		private members which that class declares.
	b.	The private members in the base class cannot be directly accessed in the derived class, while protected members can be directly 
		accessed. For e.g.:
		
// C++ Implementation to show that a derived class doesn’t inherit access to private data members.
// However, it does inherit a full parent object
class A {
public:
    int x;
protected:
    int y;
private:
    int z;
};
 
class B : public A {
    // x is public
    // y is protected
    // z is not accessible from B
};
 
class C : protected A {
    // x is protected
    // y is protected
    // z is not accessible from C
};
 
class D : private A {   // 'private' is default for classes
    // x is private
    // y is private
    // z is not accessible from D
};		

Base Class Member 				Type of inheritance
Access Specifier	1. public:		2. protected:	3. private:
public:				public			protected		private
protected:			protected		protected		private
private:			Not accessible	Not accessible	Not accessible 

Types of Inheritance in C++:
1. 	Single inheritance:
	In single inheritance, a class is allowed to inherit from only one class. i.e. one sub class is inherited by one base class only.
	Syntax: 
	class subclass_name : access_mode base_class {
		//body of subclass
	};
	
2.	Multiple inheritance:
	Multiple Inheritance is a feature of C++ where a class can inherit from more than one classes. i.e one sub class is inherited from more 
	than one base classes.
	Syntax: 
	class subclass_name : access_mode base_class1, access_mode base_class2, ... {
		//body of subclass
	};
	Here, the number of base classes will be separated by a comma (,) and access mode for every base class must be specified. 
	
3.	Multilevel inheritance:
	In this type of inheritance, a derived class is created from another derived class.
	
4.	Hierarchial inheritance:
	In this type of inheritance, more than one sub class is inherited from a single base class. i.e. more than one derived class is created 
	from a single base class.
	
5.	Hybrid (Virtual) inheritance:
	Hybrid Inheritance is implemented by combining more than one type of inheritance. For example: Combining Hierarchical inheritance and 
	Multiple Inheritance.
	
6.	A special case of hybrid inheritance: Multipath inheritance: [#IMP]
	A derived class with two base classes and these two base classes have one common base class is called multipath inheritance. An ambiguity 
	can arrise in this type of inheritance. 
	E.g. 	A
		  /   \
		 B     C
		   \  /
		     D

// C++ program demonstrating ambiguity in Multipath Inheritance and resolving it using the scope resolution operator.
#include <iostream>
using namespace std;

class ClassA {
public:
    int a;
};

class ClassB : public ClassA {
public:
    int b;
};
class ClassC : public ClassA {
public:
    int c;
};

class ClassD : public ClassB, public ClassC {	//	An ambiguity arises here as ClassD now has the variable a from both ClassB and ClassC.
public:
    int d;
};

int main() {
    ClassD obj;
    // obj.a = 10;                   	//	Statement 1, Error as the compiler couldn't identify which variable a is to be considered.
    // obj.a = 100;                 	//	Statement 2, Error as the compiler couldn't identify which variable a is to be considered.

    obj.ClassB::a = 10; 				// 	Statement 3, works fine as it represents the variable a derived from ClassB.
    obj.ClassC::a = 100; 				// 	Statement 4, works fine as it represents the variable a derived from ClassC.
										//	Syntax: obj.base_class_name::ambiguous_variable
    obj.b = 20;
    obj.c = 30;
    obj.d = 40;
    cout << "A from ClassB  : " << obj.ClassB::a << "\n";
    cout << "A from ClassC  : " << obj.ClassC::a << "\n";
    cout << "B : " << obj.b << "\n";;
    cout << "C : " << obj.c << "\n";
    cout << "D : " << obj.d << "\n";
    return 0;
}

Output:
A from ClassB  : 10
A from ClassC  : 100
B : 20
C : 30
D : 40

In the above example, both ClassB & ClassC inherit ClassA, they both have single copy of ClassA. However ClassD inherit both ClassB & ClassC, 
therefore ClassD have two copies of ClassA, one from ClassB and another from ClassC. 
If we need to access the data member a of ClassA through the object of ClassD, we must specify the path from which a will be accessed, whether 
it is from ClassB or ClassC, because a compiler can’t differentiate between two copies of ClassA in ClassD.

There are two ways to avoid this ambiguity: 
1.	Using a scope resolution operator (::) as shown in the above example
2.	Using virtual base class: 
	We need to make the access mode from the base classes due to which the ambiguity arises virtual. So, this results in, the derived class keeping
	only one copy of the ambiguous variable.	
	Syntax:
	class derived_className : virtual access_mode base_className {
		//body of subclass
	}
	
// C++ program demonstrating ambiguity in Multipath Inheritance and resolving it using virtual inheritance.
#include<iostream>
using namespace std;

class ClassA {
public:
	int a;
};

class ClassB : virtual public ClassA {		//	Since, the ambiguity arose due to the base classes B and C, they are inherited virtually.
public:
    int b;
};

class ClassC : virtual public ClassA {
public:
	int c;
};

class ClassD : public ClassB, public ClassC {
public:
	int d;
};

int main() {
	ClassD obj;
	obj.a = 10;        				//	Statement 3, works fine
	obj.a = 100;     				//	Statement 4, works fine as it overwrites the statement 3.
	obj.b = 20;
	obj.c = 30;
	obj.d = 40;
	cout<< "A : "<< obj.a;
	cout<< "\nB : "<< obj.b;
	cout<< "\nC : "<< obj.c;
	cout<< "\nD : "<< obj.d;
	return 0;
}

Output: 
A : 100
B : 20
C : 30
D : 40

In the above example, ClassD has only one copy of ClassA, therefore, statement 4 will overwrite the value of a, given at statement 3.