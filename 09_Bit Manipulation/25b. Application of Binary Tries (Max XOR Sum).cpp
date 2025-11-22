/*	Bit Manipulation Prob. #25b. Application of Binary Tries (Maximum XOR Sum using a binary trie) [#IMP]
*/

//  Method 1: Naive Solution or Brute Force Method (Using nested loops)
//  Running time = O(m*n) i.e. quadratic time thus, inefficient
//  Auxiliary space = O(m) i.e. linear space where n = arr.size() and m = queries.size()

//  Method 2b: Efficient solution using binary trie of all the elements in the array, and then
//  finding an opposite element to each queries[i] s.t. the XOR sum is maximized.
//	It is exactly same as method 2 but instead of using val&(1<<i) to get the ith bit, used string
// 	and decToBin() & binToDec() reduntantly. 

//  Running time = O(m*log2(max(arr[i]))) ~ O(m*c*32) ~ O(m) i.e. linear thus efficient where c is a constant
//  Auxiliary space = O(m) i.e. linear space where n = arr.size() and m = queries.size()



#include<bits/stdc++.h>
using namespace std;

struct node {
    int val;                    //  There is no need of isCompleteVal = 0 or 1 as all the strings are of length 32
    node *left, *right;
    node() : val(0), left(nullptr), right(nullptr) {}
    node(int val_) : val(val_), left(nullptr), right(nullptr) {}
};

string decToBin(int val) {      //  Converts int to its binary equivalent in string
    string s;
    while(val) {
        char ch = (val%2)+'0';
        s = ch+s;               //  Note: s = s + ch is incorrect
        val /= 2;
    }
    int n = s.size();
    for(int i=0; i<32-n; i++) s = '0' + s;          //  It fixes the size of the string to 32 by prefixing zeroes
    return s;
}
/* Verify whether decToBin() is sufficient or decToBin2() is required
string decToBin2(int val) {
    string s;
    while(val) {
        char ch = (val%2)+'0';
        s = ch+s;
        val /= 2;
    }
    int n = s.size();
    for(int i=0; i<32-n; i++) s = '1' + s;      //  It fixes the size of the string to 32 by prefixing one (where it differs from decToBin()
    //cout<<s<<"\n";
    return s;
}
*/
int binToDec(string s) {                        //  Converts a binary string to its decimal equivalent in int
    int val = 0;
    for(int i=0; i<32; i++)
        if(s[31-i] == '1') val += (1<<i);
    return val;
}

void printTrie(node *root, string s) {          //  Helper program just to print all the binary strings possible from the binary trie
    if(root == nullptr) return;
    if(root->left==nullptr && root->right==nullptr) cout<<s<<" ";
    printTrie(root->left, s+'0');
    printTrie(root->right, s+'1');
}

node *insert(node *root, int val) {             //  It inserts an element into the binary trie
    string s = decToBin(val);
    //  string s = decToBin2(val);              //  It passes all the test cases however I think decToBin2(val) is totally correct
    node *curr = root;                          //  while decToBin(val) may fail if large numbers come into play [Verify]
    for(int i=0; i<32; i++) {
        if(s[i] == '0') {
            if(curr->left==nullptr) curr->left = new node(0);
            curr = curr->left;
        }
        else if(s[i] == '1'){
            if(curr->right==nullptr) curr->right = new node(1);
            curr = curr->right;
        }
    }
    return root;
}

node *makeTrie(vector<int> arr) {               //  It inserts each element arr[i] of the array and builds the binary trie
    node* root = new node;
    for(int i=0; i<arr.size(); i++)
        root = insert(root, arr[i]);
    return root;
}

string searchOpposite(node *root, int val) {    //  It searches the opposite of bits, of the query[i] in the binary trie as to maximize XOR sum
    string s = decToBin(val);                   //  If the opposite bit is found it adds it else goes the other way which is always an option
    string ans;
    bool goLeft = 0;
    node *curr = root;
    for(int i=0; i<32; i++) {
        if(s[i]=='0') {
            if(curr->right!=nullptr) goLeft = 0;
            else goLeft = 1;
        }
        else if(s[i]=='1') {
            if(curr->left!=nullptr) goLeft = 1;
            else goLeft = 0;
        }
        if(goLeft) {
            curr = curr->left;
            ans = ans + '0';
        }
        else {
            curr = curr->right;
            ans = ans + '1';
        }
    }
    return ans;
}

vector<int> maxXor(vector<int> arr, vector<int> queries) {  //  The main function which after retrieving the string with opposite bits, puts
    int n = arr.size(), m = queries.size();                 //  queries[i]^opp(queries[i]) into the result and finally returns the result.
    vector<int> res;
    node *root = makeTrie(arr);
    //cout<<"Printing trie:\n"; printTrie(root, ""); cout<<"\n";
    for(int i=0; i<m; i++) {
        string ans = searchOpposite(root, queries[i]);
        int val = binToDec(ans);
        res.push_back(val^queries[i]);
    }

    return res;
}

int main(){
    int n, m;
    cin>>n;
    vector<int> arr(n);
    for(int i=0; i<n; i++) cin>>arr[i];
    cin>>m;
    vector<int> queries(m);
    for(int i=0; i<m; i++) cin>>queries[i];
    vector<int> ans = maxXor(arr, queries);
    for(int i=0; i<ans.size(); i++) cout<<ans[i]<<"\n";
    cout<<"\n";
    return 0;
}
