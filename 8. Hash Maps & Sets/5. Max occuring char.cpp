/* Hashmap problem #3
Given a string, find the character occurring the max no. of times
*/
//  1. Using an array of size 128 as ASCII has 128 characters
//  Here the array acts as a hashmap
//  Running time = O(n) if (n>128)
//  Extra space = O(128)

#include<iostream>
using namespace std;

int main() {
    string s;
    cout<<"Input the string (it should only contain alphabets) = \n";
    cin>>s;
    int n = s.size();
    int a[128] = {0};   //  Considering ASCII has 128 characters
    for(int i=0; i<n; i++) {
        a[s[i]]++;      // Note the use of a[s[i]] here
    }
    int maxVal=0;
    int pos = -1;
    for(int i=0; i<128; i++) {
        if(a[i]>maxVal) {
            maxVal = a[i];
            pos = i;
        }
    }
    char ch = pos;
    cout<<"The character "<<ch<<" occurs "<<maxVal<<" time(s)\n";
    return 0;
}
