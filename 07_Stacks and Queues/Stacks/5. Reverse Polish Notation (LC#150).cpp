/* Stack Problem 4 - LC#150. Evaluate Reverse Polish Notation
Evaluate the value of an arithmetic expression in Reverse Polish Notation.
Valid operators are +, -, *, and /. Each operand may be an integer or another expression.
Note that division between two integers should truncate toward zero.

Example 1:
Input: tokens = ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]
Output: 22
Explanation: ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
= ((10 * (6 / (12 * -11))) + 17) + 5
= ((10 * (6 / -132)) + 17) + 5
= ((10 * 0) + 17) + 5
= (0 + 17) + 5
= 17 + 5
= 22

Constraints:
1.	It is guaranteed that the given RPN expression is always valid. That means the expression would 
	always evaluate to a result, and there will not be any division by zero operation.
2.	1 <= s.length <= 10^4
3.	s[i] is either an operator: "+", "-", "*", or "/", or an integer in the range [-200, 200].

Example 1:
Input: temperatures = [73,74,75,71,69,72,76,73]
Output: [1,1,4,2,1,1,0,0]

Constraints:
1 <= t.length <= 10^5
30 <= t[i] <= 100
*/

//	Method 1 - Using a stack to store only the numbers in the given string and the numbers resulting from the
//	computation of an expression
//	Running time = O(n*m) i.e. quadratic as we traverse the vector of strings just once where n is total no. of strings
//	and m is the maximum size of a string in the vector of strings.
//	Auxiliary space = O(n) i.e. linear as the stack could be as large as the vector of strings

class Solution {
public:
    int strToInt(string s) {
    //int strToInt(string str) {
        //string s;
        //if(str[0]=='-') s = str.substr(1);
        //else s = str;
        bool negative = 0;
        int startIdx = 0;
        if(s[0] == '-') {
            negative = 1;
            startIdx = 1;   //  For a negative no. the digits start from index = 1;
        }
        int val = 0;
        for(int i=startIdx; i<s.size(); i++) {  //  This converts a string number into its int equivalent
            val = val*10 + (s[i]-'0');
        }
        //if(str[0]=='-') return -val;
        if(negative) return -val;       
        else return val;
    }    
    int evalRPN(vector<string>& s) {
        int n = s.size();
        stack<int> S;
        for(int i=0; i<n; i++) {
            if(s[i]=="+"||s[i]=="-"||s[i]=="*"||s[i]=="/") {
                int r = S.top(); 
                S.pop();
                int l = S.top();
                S.pop();
                int val;
                if(s[i]=="+") val = l+r;
                else if(s[i]=="-") val = l-r;
                else if(s[i]=="*") val = l*r;
                else if(s[i]=="/") val = l/r;
                S.push(val);
            }
            else {
                int val = strToInt(s[i]);
                S.push(val);
            }
        }
        return S.top();
    }
};