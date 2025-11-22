/*	Hashmap Problem #10 - LC#202. Happy Number
Write an algorithm to determine if a number n is happy.
A happy number is a number defined by the following process:
Starting with any positive integer, replace the number by the sum of the squares of its digits.
Repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1.
Those numbers for which this process ends in 1 are happy.
Return true if n is a happy number, and false if not.

Example 1:
Input: n = 19
Output: true
Explanation:
1^2 + 9^2 = 82
8^2 + 2^2 = 68
6^2 + 8^2 = 100
1^2 + 0^2 + 0^2 = 1
*/
// 	Running time = ?? (0ms i.e. faster than 100% in leetcode)
//	Auxiliary space = same as running time ??
//	My method - It does not use a hashmap or a hashset
class Solution {
public:
    bool isHappy(int n) {
        if(n==1) return 1;
        else if(n>1&&n<5) return 0; 	//	As n = 2, 3, 4 are not happy numbers
        vector<int> digits;
        while(n>0) {
            int rem = n%10;
            n=n/10;
            digits.push_back(rem);
        }
        int m = 0;
        for(int i=0; i<digits.size(); i++) {
            m += digits[i]*digits[i];
        }
        cout<<m<<endl;
        return isHappy(m);
    }
};