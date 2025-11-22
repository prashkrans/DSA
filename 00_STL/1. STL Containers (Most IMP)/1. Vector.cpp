#include<iostream>
#include<vector>
using namespace std;
/*
1. vector<int> v2(v1);
2. vectorName.push_back(valueToBePushed);
3. vectorName.pop_back();
4. vectorName.front();
5. vectorName.back();
6. vectorName.at(posValue);
7. vectorName.empty(); // Returns true or false
8. vector<dataType>::iterator iterName = vectorName.begin()+anyValue<Size or vectorName.end()-anyValue<=Size;
9. vector<dataType>::reverse_iterator ritName = vectorName.rend()-anyValue<=Size or vectorName.rbegin()+anyValue<Size;
*/

int main(){
int arr[] = {10, 20, 30, 40, 50};
vector<int> a; a.push_back(1); a.push_back(2); a.push_back(3);
vector<int> b(5, 0);                // vector<datatype> arrayName(size of the array, each value)
vector<int> copyA(a);               // Copies the vector a to copyA;
vector<int> copyA2; copyA2 = a;     // Copies the vector a to copyA2
vector<char> ch; ch.push_back('a'); ch.push_back('b'); ch.push_back('c');
vector<float> f; f.push_back(1.01); f.push_back(1.02); f.push_back(1.03);
vector<vector<int>> twoD; twoD.push_back(a); twoD.push_back({-3, -2, -1, 0}); // 2-D vector
// Using only vector<int> a;

vector<int>::iterator first = a.begin(); cout<<"Printing the value of pointer to the first element = "<<*first<<"\n";
vector<int>::iterator afterLast = a.end();       // Cannot print as it points to an element after the last element
cout<<"Shifting pointer afterLast leftwards by 1 and thus pointing to the last element = "<<*(afterLast-1)<<"\n";
vector<int>::reverse_iterator beforeFirst = a.rend();    // Cannot print as it points to an element before the first element
cout<<"Shifting pointer beforeFirst righwards by 1 and thus pointing to the first element = "<<*(beforeFirst-1)<<"\n"; // *(beforeFirst+1) is incorrect
vector<int>::reverse_iterator last = a.rbegin(); cout<<"Printing the value of pointer to the last element = "<<*last<<"\n";

a.push_back(4);cout<<"Size = "<<a.size()<<" Last element = "<<a[a.size()-1]<<"\n";
a.pop_back(); cout<<"Size = "<<a.size()<<" Last element = "<<a[a.size()-1]<<"\n";
int firstElement = a.front();
int firstElement2 = a[0];
int firstElement3 = a.at(0);
cout<<"First element = "<<firstElement<<"="<<firstElement2<<"="<<firstElement3<<"\n";
int lastElement = a.back();
int lastElement2 = a[a.size()-1];
int lastElement3 = a.at(a.size()-1);
cout<<"Last element = "<<lastElement<<"="<<lastElement2<<"="<<lastElement3<<"\n";
cout<<"Printing the elements of vector a = \n";
for(int i=0; i<a.size(); i++) cout<<a[i]<<" ";
cout<<"\n";
cout<<"Printing the elements of vector a in reverse order = \n";
while(!a.empty()){
    cout<<a.back()<<" ";
    a.pop_back();
}
cout<<"\n";
if(a.empty()) cout<<"The given array is empty \n";
else cout<<"The given array is not empty \n";
int* pos3arr = arr+2;
cout<<"Printing the third element of the array arr using a pointer = "<<*pos3arr<<"\n";
cout<<"Printing the second element of the array arr using a pointer = "<<*(pos3arr-1)<<"\n";
vector<int>::iterator iter = copyA.begin()+2;
cout<<"Printing the third element of vector copyA using an iterator pointer = "<<*iter<<"\n";
cout<<"Printing the second element of vector copyA using an iterator pointer = "<<*(iter-1)<<"\n";
cout<<"End of program";
return 0;
}
