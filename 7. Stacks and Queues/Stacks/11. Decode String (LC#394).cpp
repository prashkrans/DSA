/* Stack problem - 10. LC#394. Decode String
Given an encoded string, return its decoded string. The encoding rule is: k[encoded_string], where the encoded_string 
inside the square brackets is being repeated exactly k times. Note that k is guaranteed to be a positive integer.
You may assume that the input string is always valid; No extra white spaces, square brackets are well-formed, etc.
Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat 
numbers, k. For example, there won't be input like 3a or 2[4].

Example 1:
Input: s = "3[a2[c]]"
Output: "accaccacc"

Example 2:
Input: s = "abc3[cd]xyz"
Output: "abccdcdcdxyz"

Constraints:
1 <= s.length <= 30
s consists of lowercase English letters, digits, and square brackets '[]'.
s is guaranteed to be a valid input.
All the integers in s are in the range [1, 300].
*/

//	Method 1 - S1 stores a string here instead of a single char as in method 2
//	Running time - O(n) where n is the total number of characters in the input string
//	so this performs better than method 2 which takes O(N)
//	Auxiliary space - O(n) due to the stack S1

class Solution {
public:
    int stringToInt(string s) {
        int n = s.size(); 
        int val = 0;
        for(int i=0; i<n; i++) {
            val = val*10 + (s[i]-'0');
        }
        return val;
    }
    string charToString(char ch) {
        string s;
        s = s + ch;
        return s;
    }
    string decodeString(string s) {
        int n = s.size();
        stack<string> S1;                   //  S1 stores strings
        stack<int> S2;                      //  S2 stores the number of time a current string is required to be repeated
        for(int i=0; i<n; i++) {
            if(s[i]>='a'&&s[i]<='z') {
                if(S1.empty()) S1.push(charToString(s[i]));
                else if(S1.top()!="[") S1.top() = S1.top() + s[i];
                else S1.push(charToString(s[i]));
            }
            else if(s[i]>='1' && s[i]<='9') {
                int j = i;
                string number;
                while(s[j]>='0' && s[j]<='9') {
                    number = number + s[j];
                    j++;
                }
                j--;                            //  This means that s[i] to s[j] makes a number which needs to be converted to an iteger
                i = j;                          //  IMP - it is important to make reduce j by 1 as s[j] is not a 'digit'.
                int num = stringToInt(number);  //  So, i is advanced to j, since s[i] to s[j] is a number
                S2.push(num);
            }
            else if(s[i]=='[') S1.push(charToString(s[i]));
            else if(s[i]==']') {                //  This implies to repeat the current string its reqd. no. of times
                string str;
                while(S1.top()!="[") {
                    str = S1.top() + str;
                    S1.pop();
                }
                S1.pop();
                int num = S2.top();
                S2.pop();
                string str2;
                for(int i=1; i<=num; i++) str2 = str2 + str;
                S1.push(str2);
            }
        }
        string str;
        while(!S1.empty()) {
            str = S1.top() + str;
            S1.pop();
        }
        return str;	
    }
};

//	Method 2 - S1 stores a char here instead of a string as in method 1
//	Running time - O(N) where N is the total number of characters in the final string
//	so this performs worse than method 1
//	Auxiliary space - O(N) due to the stack S1

class Solution {
public:
    int stringToInt(string s) {
        int n = s.size(); 
        int val = 0;
        for(int i=0; i<n; i++) {
            val = val*10 + (s[i]-'0');
        }
        return val;
    }
    string decodeString(string s) {
        int n = s.size();
        if(n==1||n==2) return s;
        stack<char> S1;
        stack<int> S2;
        for(int i=0; i<n; i++) {
            if(s[i]>='a'&&s[i]<='z') {
                S1.push(s[i]);
            }
            else if(s[i]>='0' && s[i]<='9') {
                int j = i;
                string number;
                while(s[j]>='0' && s[j]<='9') {
                    number = number + s[j];
                    j++;
                }
                i = j-1;
                int num = stringToInt(number);
                // or int num = stoi(number);   //  stoi(num) is an inbuilt function to convert a string to a number
                S2.push(num);
            }
            else if(s[i]=='[') S1.push(s[i]);
            else if(s[i]==']') {
                int num = S2.top();
                S2.pop();
                vector<char> curr;
                while(S1.top()!='[') {
                    curr.push_back(S1.top());
                    S1.pop();
                }
                S1.pop();
                for(int k=1; k<=num; k++) {
                    for(int j=curr.size()-1; j>=0; j--) S1.push(curr[j]);
                }
            }
        }
        string str;
        while(!S1.empty()) {
            str = S1.top() + str;
            S1.pop();
        }
        return str;	
    }
};