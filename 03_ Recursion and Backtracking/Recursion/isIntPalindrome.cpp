// Prefer this

#include<iostream>
using namespace std;

bool isPalin(int n) {
    int a = n, b = 0;
    while(n) {
        int rem = n%10;
        b = b*10+rem;
        n = n/10;
    }
    return (a==b);
}

int main() {
    int t;
    cin>>t;
    while(t--) {
        int n;
        cin>>n;
        if(isPalin(n)) cout<<n<<" is a palindrome\n";
        else cout<<n<<" is not a palindrome\n";
    }
    return 0;
}

/* Sample input
5
121
123212
12321
1234
123321
*/


#include<bits/stdc++.h>
using namespace std;

int reverseInt(int a) {
    int b = 0;
    while(a) {
        int rem = a%10;
        b = b*10 + rem;
        a /= 10;
    }
    return b;
}

int main() {
    int a;
    cout<<"Enter an integer (a): ";
    cin>>a;
    int b = reverseInt(a);
    cout<<"a: "<<a<<" b: "<<b<<endl;
    // if (a==b) cout<<"It is a palindrome.";
    // else cout<<"It is not a palindrome.";
    bool isPalindrome = (a == b) ? true : false;
    cout<<"Is Palindrome: "<<isPalindrome;
    cout<<endl;
    return 0;
}

