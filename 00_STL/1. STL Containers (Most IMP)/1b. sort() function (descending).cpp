#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main() {
    vector<int> a = {2, 1, 5, 4, 3};
    int arr[] = {2, 1, 4, 6, 3, 5};
    string s = "abacddabe";
    sort(a.begin(), a.end(), greater<int>());
    sort(arr, arr+6, greater<int>());
    sort(s.begin(), s.end(), greater<char>());
    cout<<"Printing the arrays in sorted (descending) order = \na = ";
    for(int i=0; i<5; i++) cout<<a[i]<<" ";
    cout<<"\narr = ";
    for(int i=0; i<6; i++) cout<<arr[i]<<" ";
    cout<<"\n";
    cout<<"Printing the string in sorted (descending) order = \n";
    cout<<s;
    return 0;
}
