// Time Complexity (splitByComma):             O(n)                        // n = length of input string, each char read once
// Time Complexity (splitByCommaTraditional):  O(n)                        // Same as above, substring operations are efficient
// Space Complexity:                           O(k)                        // k = number of substrings, output stored in vector

#include<iostream>
#include<vector>
#include<sstream>
using namespace std;

vector<string> splitByComma(string s) {
    vector<string> ans;                                                  // Stores split substrings
    stringstream ss(s);                                                  // Create stream from input string
    string t;                                                            // Temporary buffer for substrings
    char delim = ',';                                                    // Delimiter character

    while(getline(ss, t, delim)) {                                       // Extract substrings separated by delimiter
        ans.push_back(t);                                                // Add each substring to result vector
    }
    return ans;                                                          // Return all substrings
}

vector<string> splitByCommaTraditional(string s) {
    vector<string> ans;                                                  // Stores split substrings
    int start = 0;                                                       // Start index of current substring
    for(int i=0; i<s.size(); i++) {                                      // Iterate through each character
        if(s[i] == ',') {                                                // If comma found, substring boundary detected
            ans.push_back(s.substr(start, i-start));                     // Extract substring from 'start' to current index
            start = i+1;                                                 // Update start to index after comma
        }
    }
    ans.push_back(s.substr(start));                                      // Add last substring after final comma
    return ans;                                                          // Return all substrings
}

int main() {
    string s = "comma,as,a,delimiter";                                   // Input string
    vector<string> strs = splitByComma(s);                               // Call first split function
    for(auto str: strs) cout<<str<<endl;                                 // Print each substring
    cout<<"###################"<<endl;                                   // Separator output
    strs = splitByCommaTraditional(s);                                   // Call second (manual) split function
    for(auto str: strs) cout<<str<<endl;                                 // Print each substring
    return 0;                                                            // Return success
}
