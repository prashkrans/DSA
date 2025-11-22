/*  Prob. #x. Round the given number
Given a number in float or double, round the number
*/

#include<iostream>
#include<math.h>
using namespace std;

template<typename T>                //  Function template
int round(T a) {
    if (a>=0) {
        int val = floor(a);         //  or int val = a; also works fine but don't prefer this
        T dec = a - val;
        if(dec>=0.5) return a-dec+1;
        else return a-dec;
    }
    else {
        int val = ceil(a);          //  or int val = a; also works fine but don't prefer this
        T dec = -1*(a - val);
        if(dec>=0.5) return a+dec-1;
        else return a+dec;
    }
}

int main() {
    float a = 1.39, b = 2.51;
    double c = 3.333333, d = 0.5, e = 0.999999;
    float f = -1.23, g = -1.52, h = -1.50;
    double i = -100, j = -16.6667, k = -3.3333;
    cout<<a<<" -> "<<round<float>(a)<<" == "<<round(a)<<"\n";   //  round(val) is a built-in function to round a float or double number
    cout<<b<<" -> "<<round<float>(b)<<" == "<<round(b)<<"\n";
    cout<<c<<" -> "<<round<float>(c)<<" == "<<round(c)<<"\n";
    cout<<d<<" -> "<<round<float>(d)<<" == "<<round(d)<<"\n";
    cout<<e<<" -> "<<round<float>(e)<<" == "<<round(e)<<"\n";
    cout<<f<<" -> "<<round<float>(f)<<" == "<<round(f)<<"\n";
    cout<<g<<" -> "<<round<float>(g)<<" == "<<round(g)<<"\n";
    cout<<h<<" -> "<<round<float>(h)<<" == "<<round(h)<<"\n";
    cout<<i<<" -> "<<round<float>(i)<<" == "<<round(i)<<"\n";
    cout<<j<<" -> "<<round<float>(j)<<" == "<<round(j)<<"\n";
    cout<<k<<" -> "<<round<float>(k)<<" == "<<round(k)<<"\n";
    return 0;
}
