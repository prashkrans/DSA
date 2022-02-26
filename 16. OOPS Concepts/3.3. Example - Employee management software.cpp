/* Virtual function polymorphism problem #1.
Consider an employee management software for an organization.
Let the code has a simple base class Employee , the class contains virtual functions like raiseSalary(),
transfer(), promote(), etc. Different types of employees like Manager, Engineer, etc. may have their own
implementations of the virtual functions present in base class Employee.
In our complete software, we just need to pass a list of employees everywhere and call appropriate functions
without even knowing the type of employee. For example, we can easily raise the salary of all employees by
iterating through the list of employees. Every type of employee may have its own logic in its class, but we
don’t need to worry about them because if raiseSalary() is present for a specific employee type, only that
function would be called.
*/

#include<iostream>
using namespace std;

class employee {
public:
    virtual void raiseSalary() {
        cout<<"Calls the base class's raiseSalary()\n";
        //  common raise salary code
    }
    virtual void promote() {
        cout<<"Calls the base class's promote()\n";
        //   common promote code
    }
};

class manager: public employee {
    void raiseSalary() {
        cout<<"Calls the manager's (derived class) raiseSalary()\n";
        //  manager specific raise salary code
    }
    void promote() {
        cout<<"Calls the manager's (derived class) promote()\n";
        //  manager specific raise salary code
    }
};

class engineer: public employee {
    void raiseSalary() {
        cout<<"Calls the engineer's (derived class) raiseSalary()\n";
        //  engineer specific raise salary code
    }
    void promote() {
        cout<<"Calls the engineer's (derived class) promote()\n";
        //  engineer specific raise salary code
    }
};

//  We need a very simple function to increment the salary of all employees
//  Note that emp[] is an array of pointers and actual pointed objects can be any type of employees.
//  This function should ideally be in a class like Organization, we have made it global to keep things simple.
void globalRaiseSalary(int n, employee *emp[]) {
    for(int i=0; i<n; i++) {
        emp[i]->raiseSalary();  //  Polymorphic Call: Calls raiseSalary() according to the actual object, not
    }                           //  according to the type of pointer
}

int main() {
    int n;
    n = 5;
    employee *emp[n];           //  An array of base class pointers
    for(int i=0; i<n; i++) {
        if(i==0 || i==1) emp[i] = new manager;      //  Randomly alloted i = 0 and 1 to objects of a manager and others to objects of an engineer.
        else emp[i] = new engineer;
    }
    globalRaiseSalary(n, emp);
    return 0;
}
