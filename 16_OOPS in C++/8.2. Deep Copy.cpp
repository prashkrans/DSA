/*#8.2. Deep Copy while creating an object:
(Applicable on only those data members which are pointers i.e. memory allocated from the heap section of the memory)
In a deep copy, first the pointer data members of the object created are dynamically allocated memory via user-defined default or copy constructor
then all the values of the data members of the original object are copied.

Note: In order to perform a deep copy, we need to explicitly define the copy constructor and assign dynamic memory as well if required. Also, it is
required to dynamically allocate memory to the pointer variables in the other constructors, as well.

Note: The default copy constructor (i.e. className obj2 = obj1;) and the default assignment operator (i.e. obj2 = obj1;) make a shallow copy.
a.	Default copy constructor: Copying of value at the time of initialization. => Gets overridden by user-defined copy constructor to allow a deep copy
b.	Assignment Operator: Copying of value after initialization. => Gets overridden by operator overloading to allow a deep copy
Example of deep copy in C++:
*/
// C++ program to demonstrate deep copy
#include <iostream>
using namespace std;

// Box Class
class box {
private:
	int length;     //  deep copy
	int *breadth;   //  deep copy instead of shallow copy
	int *height;    //  deep copy instead of shallow copy
public:
    box() : length(0), breadth(new int), height(new int) {}
    //  We just need to create a custom "copy constructor allocating memory to pointer variables" and then copy values i.e. *ptr instead of just ptr
    //  so that a deep copy could be made instead of a shallow copy
    box(const box &obj) {           //  This copy constructor just made the copy constructor a deep copy but assignment operator is still a shallow copy
        length = obj.length;
        breadth = new int;
        *breadth = *(obj.breadth);
        height  = new int;
        *height = *(obj.height);
    }

    void operator = (const box &b) {    //  This overrides the assignment operator to allow a deep copy instead of a shallow copy
        length = b.length;
        *(breadth) = *(b.breadth);
        *(height) = *(b.height);
    }

	// Function that sets the dimensions
	void set_dimensions(int length1, int *breadth1, int *height1) {
		length = length1;
        //breadth = new int;  height = new int;                         //  Could use line 34 but it gets redundant if a default/copy constructor has already allocated memory
		*breadth = *breadth1;
		*height = *height1;
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
	~box() {                            //  The destructor is optional. Used here just to demonstrate the working of a destructor
	    cout<<"Destructor called\n";    //  It is called each time an object of class box gets out of scope, here 3 times due 3 objects B1, B2 & B3
        delete breadth;
        delete height;
	}
};

// Driver Code
int main() {
	//  Object of class Box
	box B1, B3;

	//  Set dimensions of Box B1
	int l = 14;
	int *b = new int, *h = new int;
	*b = 1, *h = 5;
	B1.set_dimensions(14, b, h);
	B1.show_data();

	//  When data of object is copied at the time of initialization then the copy is made through the COPY CONSTRUCTOR
	box B2 = B1;		//	not a default copy constructor (shallow copy) but a user-defined copy constructor (deep copy)
	B2.show_data();

	//  When data of object is copied after the initialization then the copy is made through the DEFAULT ASSIGNMENT OPERATOR
	B3 = B1;			//	not a default assignment operator (shallow copy) but a user-defined assignment operator (deep copy)
	B3.show_data();

	//  Not only the length data member which is not a pointer is a deep copy, but also breadth and height data members are deep copies
	//  even though they are pointers due to dynamic memory allocated to them in the user-defined copy constructor

	B1.update(100);      //  Due to deep copy implementation updating B1, would not modify breadth and height of B2 and B3.
	B1.show_data();
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
Breadth = 1
Height = 5

Length = 14
Breadth = 1
Height = 5

Destructor called
Destructor called
Destructor called
*/
