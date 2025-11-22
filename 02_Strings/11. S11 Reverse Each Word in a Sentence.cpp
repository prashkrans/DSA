/* String Prob. #11. Reverse Each Word in a Sentence
Given a sentence where each word is separated by a " ", reverse its each word.

Input 1
Always indent your code
Output 1
syawlA tnedni ruoy edoc
*/

//	Running time = O(n) i.e. linear time where n is the size of the sentence
//	Auxiliary space = O(maxWordSize) or O(n) in the worst case when the sentence contains one word

#include <iostream>
#include <algorithm>
using namespace std;

string reverseWord(string s) {
    int i = 0, j = s.size()-1;
    while(i<j) {
        char temp = s[i];
        s[i] = s[j];
        s[j] = temp;
        i++; j--;
    }
    return s;
}

string reverseEachWord(string s) {
	int n = s.size();
    string ans, subS;
    for(int i=0; i<n; i++) {
        if(s[i]==' ') {
            if(subS.size()) ans += reverseWord(subS) + " ";
            subS.clear();
        }
        else subS += s[i];
    }
   	if(subS.size()) ans += reverseWord(subS) + " ";         //  Since the last word is not inserted by the loop
    return ans;
}

string reverseEachWord2(string s) {                         //  Verified
	int n = s.size();
    string ans, subS;
    for(int i=0; i<n; i++) {                                //  The loop itself takes care of the last word
        if(s[i]==' ' || (i==n-1 && s[i]!=' ')) {
            if(i==n-1 && s[i]!=' ') subS += s[i];
            if(subS.size()) ans += reverseWord(subS) + " ";
            subS.clear();
        }
        else subS += s[i];
    }
    return ans;
}

int main() {
    string str;
    getline(cin, str);
    string ans = reverseEachWord(str);
    cout << ans << endl;
    return 0;
}
