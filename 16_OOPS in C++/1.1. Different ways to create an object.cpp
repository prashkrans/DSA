#include <iostream>
using namespace std;
class Employee {
    public:
    int id; //data member
    string name; //data member
    float salary;
    Employee(int id, string name, float salary) {
        this -> id = id;
        this -> name = name;
        this -> salary = salary;
    }
    void display() {
        cout << id << "  " << name << "  " << salary << endl;
    }
};
int main(void) {
	Employee e1(102, "Nakul", 59000); 				// 	creating an object - Method 1
    Employee e2 = Employee(101, "Sonoo", 890000); 	// 	creating an object - Method 2
    e1.display();
    e2.display();
    return 0;
}
//  Output:
//  102  Nakul  59000
//  101  Sonoo  890000
