/* String Prob. #10. Reverse the words of a sentence
Reverse the given string word-wise. The last word in the given string should come at 1st place, the last-second
word at 2nd place, and so on. Individual words should remain as it is.
*/

//	Running time = O(n) i.e. linear time where n = size of the sentence
//	Auxiliary space = O(n) due to the vector<string> vec;

#include<iostream>
#include<vector>
using namespace std;

void reverse(vector<string> &vec) {
    int n = vec.size(), i = 0, j = n-1;
    while(i < j) {
        string temp = vec[i];
        vec[i] = vec[j];
        vec[j] = temp;
        i++; j--;
    }
}

string reverseStringWordWise(string s) {
	int n = s.size();
    vector<string> vec;
    string subS;
    for(int i=0; i<n; i++) {
        if(s[i]==' ') {
        	if(subS.size()) vec.push_back(subS);
            subS.clear();
        }
        else subS += s[i];
    }
    if(subS.size()) vec.push_back(subS);
    reverse(vec);
    s.clear();
    for(int i=0; i<vec.size(); i++) s += vec[i] + " ";
    return s;
}

int main() {
    string s;
    getline(cin, s);
    string ans = reverseStringWordWise(s);
    cout << ans << endl;
    return 0;
}
