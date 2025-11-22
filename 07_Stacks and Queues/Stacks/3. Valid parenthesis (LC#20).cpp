/* Stack Problem 2 - LC#20. Valid Parentheses
Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
An input string is valid if:
Open brackets must be closed by the same type of brackets.
Open brackets must be closed in the correct order.

Constraints:
1 <= s.length <= 10^4
s consists of parentheses only '()[]{}'.
*/

//	Method 1 - Using a vector to store the values of the minStack and a stack to store the minimum values only
//	Running time = O(n) since we traverse through S once
//	Auxiliary space = O(n) for the stack<char> S;

class Solution {
public:
    bool isValid(string s) {
        stack<char> S;
        for(int i=0; i<s.size(); i++) {
            if(S.empty()) {
                S.push(s[i]);
            }
            else {
                if(s[i]=='('||s[i]=='{'||s[i]=='[') S.push(s[i]);
                else if(S.top()=='(' && s[i]==')') S.pop();
                else if(S.top()=='{' && s[i]=='}') S.pop();
                else if(S.top()=='[' && s[i]==']') S.pop();
                else return false;
            }
        }
        return (S.empty());
    }
};

// 	Slightly compact:

string isBalanced(string s) {
    stack<char> st;
    for(int i=0; i<s.size(); i++) {
        if(st.empty()) st.push(s[i]);
        else {
            if((st.top()=='(' && s[i]==')')||(st.top()=='[' && s[i]==']')||(st.top()=='{'&&s[i]=='}'))
                st.pop();
            else st.push(s[i]);
        }
    }
    string ans;
    ans = (st.empty()) ? "YES" : "NO";
    return ans;
}
