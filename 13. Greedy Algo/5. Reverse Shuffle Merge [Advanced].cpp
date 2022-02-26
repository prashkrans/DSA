/* Greedy Prob. #5. Reverse Shuffle Merge [Advanced]
*/

//	Method 1: Greedy Algo
/*	Steps:
If the input string is S and the required answer is A, then the basic idea is as follows :
1) Store the count of each character (a to z) in S.
2) Update the count of characters required for A by dividing by 2.
3) Select each character for A by parsing S from right to left.
4) One "can" afford to "not select" a character, if its required-count for A will be fulfilled even after leaving it.
5) Considering point 4, always select smallest character if possible [Use of stack and pop() && count + used > req].
6) If a character can't be left (point 4 invalid), select the smallest character seen so far (even if it is not smallest for the entire string).
7) Ignore characters not required for A anymore.
*/
//	Running time = O(n) i.e. linear time where n = arr.size()
//	Auxiliary space = O(1) i.e. constant space

#include<bits/stdc++.h>
using namespace std;

void printMap(unordered_map<char, int> mp) {
    for(auto i : mp) cout<<i.first<<" "<<i.second<<"\n";
}

string reverseShuffleMerge(string s) {
    string res;
    unordered_map<char, int> count, used, req;
    stack<char> st;
    int n = s.size();
    for(int i=0; i<n; i++) count[s[i]]++;
    for(auto i : count) {
        used[i.first] = 0;
        req[i.first] = i.second/2;
    }
    //printMap(count); printMap(used); printMap(req);
    for(int i=n-1; i>=0; i--) {
        //cout<<" i = "<<i<<" s[i] = "<<s[i]<<"\n";
        if(used[s[i]]<req[s[i]]) {
            if(st.empty() || s[i] >= st.top()) {
                st.push(s[i]);
                used[s[i]]++;
                count[s[i]]--;
            }
            else {
                while(s[i] < st.top() && count[st.top()]+used[st.top()]>req[st.top()]) {    //  [#IMP] - if(count + used > req) only then we pop the top most element
                    char ch = st.top();
                    st.pop();
                    used[ch]--;
                    //cout<<"Popping out ch = "<<ch<<"\n";
                    if(st.empty()) break;
                }
                st.push(s[i]);
                used[s[i]]++;
                count[s[i]]--;
            }
        }
        else count[s[i]]--;
    }
    while(!st.empty()) {
        res = st.top() + res;
        st.pop();
    }
    return res;
}

int main() {
    string s;
    cin>>s;
    cout<<reverseShuffleMerge(s);
}

/* Sample Input
eggegg

abcdefgabcdefg

aegeaggg
*/
