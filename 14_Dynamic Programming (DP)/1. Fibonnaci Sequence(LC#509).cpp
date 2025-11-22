/*DP-Problem 1 (LC#509) :
The Fibonacci numbers, commonly denoted F(n) form a sequence, called the Fibonacci sequence,
such that each number is the sum of the two preceding ones, starting from 0 and 1. That is,
F(0) = 0, F(1) = 1
F(n) = F(n - 1) + F(n - 2), for n > 1.
Given n, calculate F(n).
*/
//  Running time = O(n) i.e. linear if memoization used
//  else R.T. = O(2^n) i.e. exponential without memoization


#include<iostream>
using namespace std;

//  1.  Recursive DP algorithm. Required space = O(n) i.e. linear space
int fibonacci(int n, int DP[47]){
    if(DP[n]==-1){          //  If the fibonacci(i) == -1 then recursion is used else the value is directly used,
        if(n<2) DP[n] = n;  //  thus calculating fibonacci(i) only once for each i in the range 0 to n
        else DP[n] = fibonacci(n-1, DP) + fibonacci(n-2, DP);
    }
return DP[n];               // Stores the fibonacci(n)
}
//  2.  Bottom-up DP algorithm. Not recursive and required space = O(n) i.e. linear space
int fibBU(int n){
    if(n<2) return n;
    int DPBU[n+1];
    DPBU[0] = 0; DPBU[1] = 1;               //  Base cases
    for(int i=2; i<=n; i++) DPBU[i] = DPBU[i-1] + DPBU[i-2];    //  DP table i.e. memoization
    return DPBU[n];
}

//  3.  This is not a DP algo. Required space = O(1) i.e. constant space
int fib(int n){
    if(n<2) return n;
    else {
        int fibN, n2, n1;
        n2 = 0; n1 = 1;
        for(int i=2; i<=n; i++){
            fibN = n2 + n1;
            n2 = n1;
            n1 = fibN;
        }
        return fibN;
    }
}
int main(){
	char input = 'y';
	while(input=='y'){
        cout<<"Enter the value of n to get Fibonacci(n) where n varies from 0 to 46 \n";
        cout<<"As the max fibonacci value using int data type is fibonacci(46)\n";
        int n;
        cin>>n;
        int DP[47];     //  Since max(n) = 46 thus 0 to 46 => 47 values to be stored
        for(int i=0; i<47; i++) DP[i] = -1;     //  Initialisize all the values to -1 for memoization
        cout<<"The nth Fibonacci number is = "<<fibonacci(n, DP)<<"\n";
        cout<<"The list of Fibonacci numbers upto n = \n";
        cout<<"i    "<<"Fibonacci(i)\n";
        for(int i=0; i<=n; i++) cout<<i<<"   "<<DP[i]<<"\n";
        cout<<"fib(n) = "<<fib(n)<<"\n";
        cout<<"Wanna continue => fibonacci() (y/n) = \n";
        cin>>input;
	}
	return 0;
}
