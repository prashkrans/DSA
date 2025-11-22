/* String Prob. #1. Count Words
For a given input string(str), find and return the total number of words present in it.
It is assumed that two words will have only a single space in between. Also, there wouldn't 
be any leading and trailing spaces in the given input string.

Sample Input 1:
"this is a sample string "
Sample Output 1:
5
*/
//	Running time = O(n) i.e. linear time where n = size of the sentence
//	Auxiliary space = O(1) 

#include <iostream>
#include <cstring>
using namespace std;

int countWords(string input) {
    int count = 0, n = input.size();
    for(int i=0; i<n; i++)
        if(input[i]==' ') count++;
	if(input[n-1]!=' ') count++;
    return count;
}

int main() {
    string input;
    getline(cin, input);
    int output = countWords(input);
    cout << "No. of words: " <<output << endl;
    return 0;
}
