/* Stack problem 12. LC#224. Basic Calculator (Hard)
Given a string s representing a valid expression, implement a basic calculator to evaluate it, and return the result of the evaluation.
Note: You are not allowed to use any built-in function which evaluates strings as mathematical expressions, such as eval().

Example 1:
Input: s = " 2-1 + 2 "
Output: 3

Example 2:
Input: s = "(1+(4+5+2)-3)+(6+8)"
Output: 23

Example 3:
Input: s = "-(1-3)"
Output: 2

It could be solved using two methods
1. Stack
2. Recursion (call stack)

Constraints:
1 <= s.length <= 3 * 105
s consists of digits, '+', '-', '(', ')', and ' '.
s represents a valid expression.
'+' is not used as a unary operation.
'-' could be used as a unary operation but it has to be followed by parentheses.
Every number and running calculation will fit in a signed 32-bit integer.
*/

//	Method 1a - Using two explicit stacks (My method)
//	This also uses the two functions stringToInt() and intToString(). However, it could be solved without the second function.
//	This method can be further consolidated. 

//	Running time = O(n) as we traverse the string s once and whenever ')' was encountered traversed backwards again
//	So, total two traversals of the string was made i.e O(2*n) ~ O(n) where n is the size of the given string s.
//	Auxiliary space = O(n) due to the size of the stack S which could be as large as n.


class Solution {
public:
    int stringToInt(string s) {
        int ans = 0;
        int sp=0; 
        if(s[0]=='-') sp = 1;
        for(int i = sp; i<s.size(); i++) {
            ans = ans*10 + (s[i] - '0');
        }
        if(s[0]=='-') ans = -1 * ans;
        return ans;
    }
    string intToString(int value) {
        string s;
        if(value==0) s = "0";
        int val = value;
        if(val<0) val = -1*val;
        while(val!=0) {
            int rem = val%10;
            char ch = '0' + rem;
            s = ch + s;
            val = val/10;
        }
        if(value<0) s = '-' + s;
        return s;
    }
    string charToString(char ch) {
        string s; 
        s = s + ch;
        return s;
    }    
    void print(stack<string> S) {
        cout<<"Printing S:\n";
        while(!S.empty()) {
            cout<<S.top()<<" ";
            S.pop();
        }
        cout<<"\n";
    }
    int calculate(string s) {
        s = '(' + s + ')';
        int n = s.size();
        stack<string> S;
        for(int i=0; i<n; i++) {
            if(s[i]==' ') continue;
            else if(s[i]=='('||s[i]=='+'||s[i]=='-') S.push(charToString(s[i]));
            else if(s[i]>='0'&&s[i]<='9') {
                if(S.empty()||S.top()=="("||S.top()=="+"||S.top()=="-") S.push(charToString(s[i]));
                else S.top() = S.top() + s[i];
            }
            else if(s[i]==')') {
                int val = 0;
                int op = 1;
                stack<string> S2;
                while(S.top()!="(") {
                    S2.push(S.top());
                    //cout<<S.top()<<" ";
                    S.pop();
                }
                //cout<<" = ";
                S.pop();
                while(!S2.empty()) {
                    if(S2.top()=="+") op = 1;
                    else if(S2.top()=="-") op = -1;
                    else val = val + op*stringToInt(S2.top());
                    S2.pop();
                }
                //cout<<val<<"\n";
                S.push(intToString(val));
                //print(S);
            }
        }
        return stringToInt(S.top());
    }
};

//	Method 2. Recursion (i.e call stack)
//	It demonstrates a mixed use of both for loop (iteration) and recursion.
//	Iteration works with elments in the current '(' opening parentheses.
//	Recursion moves the iteration from a current parentheses to the next.

//	Running time = O(n) 
//	Auxiliary space = O(n) if recursion stack is considered in space complexity

class Solution {
public:
	int recur(int &i, int n, string s) {    //  Note - It is important to pass i by reference as both for loop and recur are incrementing i
		int sign = 1;
		int ans = 0;
		for(; i<n; i++) {
			if(s[i]=='(') ans = ans + sign*recur(++i, n, s);
			else if(s[i]=='+') sign = 1;
			else if(s[i]=='-') sign = -1;
			else if('0' <= s[i] && s[i] <= '9') {
				int j = i;
				int strToInt = 0;
				while('0' <= s[j] && s[j] <= '9') {
					strToInt = strToInt*10 + (s[j]-'0');
                    j++;
				}
				i = j-1;
				ans = ans + sign*strToInt;
			}
			else if(s[i]==')') {
				return ans;
                //break;
			}
		}
        //cout<<"Ans = "<<ans<<"\n";
		return ans;
	}
	int calculate(string s) {
		int n = s.size();
		int i = 0;
		return recur(i, n, s);
	}
};
		