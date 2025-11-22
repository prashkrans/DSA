/* #8.1. Shallow Copy while creating an object:
(Applicable on only those data members which are pointers i.e. memory allocated from the heap section of the memory)
In shallow copy, an object is created by simply copying the data of all variables of the original object. Here, the pointer will be copied but not the value it points to.
It means that the original object and the created copy will now point to the same memory address, which is generally not preferred. Since both objects will reference the
same memory location, then changes made by one will reflect those changes in another object. Since we wanted to create a replica of the object, this purpose will not be
filled by Shallow copy.

This works well if none of the variables of the object are defined in the heap section of memory i.e. none are pointer variables. If some variables are dynamically allocated
memory from heap section, then copied object variable will also reference then same memory location. This will create ambiguity and run-time errors dangling pointer. Since both
objects will reference to the same memory location, then change made by one will reflect those change in another object as well.

Note: The default copy constructor (i.e. className obj2 = obj1;) and the default assignment operator (i.e. obj2 = obj1;) make a shallow copy.
a.	Default copy constructor: Copying of value at the time of initialization.
b.	Assignment Operator: Copying of value after initialization.
Example of shallow copy in C++:
*/
// C++ program to demonstrate shallow copy
#include <iostream>
using namespace std;

// Box Class
class box {
private:
	int length;     //  deep copy
	int *breadth;   //  shallow copy
	int *height;    //  shallow copy
public:
	// Function that sets the dimensions
	void set_dimensions(int length1, int *breadth1, int *height1) {     //  length is a deep copy while breadth and height are shallow copies
		length = length1;
		breadth = breadth1;
		height = height1;
	}
    void update(int val) {
        length += val;
        *breadth += val;
        *height += val;
    }
	// Function to display the dimensions of the Box object
	void show_data() {
		cout << "Length = " << length
			<< "\nBreadth = " << *breadth
			<< "\nHeight = " << *height
			<< "\n\n";
	}
};

// Driver Code
int main() {
	// Object of class Box
	box B1, B3;

	// Set dimensions of Box B1
	int l = 14;
	int *b = new int, *h = new int;
	*b = 1, *h = 5;
	B1.set_dimensions(14, b, h);
	B1.show_data();

	// When data of object is copied at the time of initialization then the copy is made through the COPY CONSTRUCTOR
	box B2 = B1;		//	default copy constructor (shallow copy)
	B2.show_data();

	// When data of object is copied after the initialization then the copy is made through the DEFAULT ASSIGNMENT OPERATOR
	B3 = B1;			//	default assignment operator (shallow copy)
	B3.show_data();

	//  Only the length data member not a pointer is a deep copy, else breadth and height data members are shallow copies due to
	//  the use of default copy constructor and default assignment operator.

	B1.update(100);     //  So, updating just B1, also modifies breadth and height of B2 and B3 which ideally should not occur.
	B1.show_data();     //  Hence, we need to use deep copy when a data member is a pointer.
	B2.show_data();
	B3.show_data();
	return 0;
}

/* Output:
Length = 14
Breadth = 1
Height = 5

Length = 14
Breadth = 1
Height = 5

Length = 14
Breadth = 1
Height = 5

Length = 114
Breadth = 101
Height = 105

Length = 14
Breadth = 101
Height = 105

Length = 14
Breadth = 101
Height = 105
*/
