/*	Prob. #x. Find all primes
Write a program to find the total number of a primes number in a given interval.
Given two integers S and E, count all primes between S and E.
*/

//	Running time = O(n*sqrt(n))
//	Auxiliary space = O(1)

#include <iostream>
using namespace std;

bool isPrime(int n) {
    for(int i=2; i*i<=n; i++) 			//	i varies from 2 to i*i
        if(n%i==0) return false;
    return true;
}

int totalPrime(int s, int e) {
    int count = 0;
    for(int i=s; i<=e; i++) 
        if(isPrime(i)) count++;
    return count;
}

int main() {
    int S, E;
    cin >> S >> E;
    cout << totalPrime(S, E);
    return 0;
}