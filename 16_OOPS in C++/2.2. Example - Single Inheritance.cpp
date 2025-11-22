/* OOPS Prob. #2.2. Example of single inheritance and protected mode
*/
//  Running time = O(1)
//  Auxiliary space = O(1)

#include <iostream>
using namespace std;

class Car {
protected:
	int noOfGear;
    string color;
public:
    Car(int nog, string clr) : noOfGear(nog), color(clr) {}
    void printCarInfo() {
        cout<<noOfGear<<" "<<color;
    }
};

class RaceCar: public Car {
    int maxSpeed;
public:
    RaceCar(int nog, string clr, int mS) : Car(nog, clr), maxSpeed(mS) {}           //  Constructor of base class called in the constructor of the derived class
    void printRaceCarInfo() {
        cout<<"noOfGear: "<<noOfGear<<"\ncolor: "<<color<<"\nmaxSpeed: "<<maxSpeed;
    }
};

int main() {
    int noOfGear, maxSpeed;
    string color;
    cin >> noOfGear >> color >> maxSpeed;
    RaceCar raceCar(noOfGear, color, maxSpeed);
    raceCar.printRaceCarInfo();
    return 0;
}

/* Sample input
5
Black
220
*/
