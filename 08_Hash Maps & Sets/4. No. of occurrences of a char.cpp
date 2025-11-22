/* Hashmap problem #2
Given a string, find the no. of occurrences of all the characters in the string
*/
//  1. Using an array of size 128 as ASCII has 128 characters
//  Here the array acts as a hashmap
//  Running time = O(n) if (n>128)
//  Extra space = O(128)

#include<iostream>
#include<unordered_map>
using namespace std;

// R.T. O(n)
// A.S. O(n)
void frequency(string s) {
    unordered_map<char, int> umap;
    for(int i=0; i<s.size(); i++)
        umap[s[i]]++;
        
    for(auto i: umap)
        cout<<"The character "<<i.first<<" occurs "<<i.second<<" time(s)\n";
}

int main() {
    string s;
    cout<<"Input the string (it should only contain alphabets) = \n";
    cin>>s;
    int n = s.size();
    int a[128] = {0};   //  Considering ASCII has 128 characters
    for(int i=0; i<n; i++) {
        a[s[i]]++;      // Note the use of a[s[i]] here
    }
    for(int i=0; i<128; i++) {
        if(a[i]>0) {    //  a[i] > 0 means that ith char is present
            char ch = i;
            cout<<"The character "<<ch<<" occurs "<<a[i]<<" time(s)\n";
        }
    }
    cout<<"##############"<<endl;
    frequency(s);
    return 0;
}
