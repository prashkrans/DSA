#include<iostream>
#include<vector>
#include<cmath>         //  for sqrt()
#include<time.h>        //  for time(0)
//#include<cstdlib>     //  (optional) for srand()

using namespace std;

class shape {
public:
	virtual int getNumOfSides() = 0;
	virtual double getArea() = 0;
};

class triangle: public shape {
	const int n = 3;
	double a, b, c;
public:
	triangle(double a_, double b_, double c_) : a(a_), b(b_), c(c_) {}
	int getNumOfSides() {
		return n;
	}
	double getArea() {
		double s = (a+b+c)/2;
		return sqrt(s*(s-a)*(s-b)*(s-c));
	}
};

class rectangle: public shape {
	const int n = 4;
	double l, b;
public:
	rectangle(double l_, double b_) : l(l_), b(b_) {}
	int getNumOfSides() {
		return n;
	}
	double getArea() {
		return l*b;
	}
};

int main() {
	int n = 5;
	vector<shape*> shapes(n);
	srand(time(0));								//	Using time(0) to generate a pseudo-random number.
	for(int i=0; i<n; i++) {
		if(i%2==0) shapes[i] = new triangle((rand()%10)+5, (rand()%10)+7, (rand()%10)+6);	//	For even values of i, shapes[i] is alloted a triangle
		else shapes[i] = new rectangle(rand()%20+5, rand()%20+3);			//	For odd values of i, shapes[i] is alloted a rectangle
	}
	for(int i=0; i<n; i++) {
		if(shapes[i]->getNumOfSides() == 3) cout<<"The shape is a triangle with area = "<<shapes[i]->getArea()<<"\n";
		else cout<<"The shape is a rectangle with area = "<<shapes[i]->getArea()<<"\n";
	}
	return 0;
}
