/* String Prob. #2. Print All Substrings
For a given input string(str), write a function to print all the possible substrings.
A substring is a contiguous sequence of characters within a string. 
Example: "cod" is a substring of "coding". Whereas "cdng" is not as the characters taken
are not contiguous

Sample Input 1:
abc
Sample Output 1:
a 
ab 
abc 
b 
bc 
c
*/
//	Running time = O(n) i.e. linear time where n = size of the sentence
//	Auxiliary space = O(1) 

#include <iostream>
#include <cstring>
using namespace std;

//	Method 1. Without using s.substr(starting_index, lenght)
//	Running time = O(n) i.e. linear time where n = s.size();
//	Auxiliary space = O(n) due to the string subS

void printSubstrings(string s) {
    string subS;
    int n = s.size();
    for(int i=0; i<n; i++) {
        subS.clear();
        for(int j=i; j<n; j++) {
            subS += s[j];					//	Method 2. Line 35 instead of line 34
			subS = s.substr(i, j-i+1); 		//	Method 2. Using the substr method of string 
            cout<<subS<<"\n";
        }
    }
}

int main() {
    string s;
    getline(cin, s);
    printSubstrings(s);
    return 0;
}