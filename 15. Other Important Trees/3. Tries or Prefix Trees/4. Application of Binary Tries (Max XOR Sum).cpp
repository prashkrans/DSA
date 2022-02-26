/*	Tries Prob. #4. Application of Binary Tries (Maximum XOR Sum using a binary trie) [#IMP]
*/

//  Method 1: Naive Solution or Brute Force Method (Using nested loops)
//  Running time = O(m*n) i.e. quadratic time thus, inefficient
//  Auxiliary space = O(m) i.e. linear space where n = arr.size() and m = queries.size()

//  Method 2: Efficient solution using binary trie of all the elements in the array, and then
//  finding an opposite element to each queries[i] s.t. the XOR sum is maximized

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

void printTrie(node *root, string s) {     	//  Helper program just to print all the binary strings possible from the binary trie
    if(root == nullptr) return;
    if(root->left==nullptr && root->right==nullptr) cout<<s<<" ";
    printTrie(root->left, s+'0');
    printTrie(root->right, s+'1');
}

node *insert(node *root, int val) {     	//  It inserts an element into the binary trie
    node *curr = root;
    for(int i=31; i>=0; i--) {
        bool isBitSet = val&(1<<i);
		if(isBitSet == 0) {
            if(curr->left==nullptr) curr->left = new node(0);
            curr = curr->left;
        }
        else {
            if(curr->right==nullptr) curr->right = new node(1);
            curr = curr->right;
        }
    }
    return root;
}

node *makeTrie(vector<int> arr) {         	//  It inserts each element arr[i] of the array and builds the binary trie
    node* root = new node;
    for(int i=0; i<arr.size(); i++)
        root = insert(root, arr[i]);
    return root;
}

int searchOpposite(node *root, int val) {   //  It searches the opposite of bits, of the query[i] in the binary trie as to maximize XOR sum
    int ans = 0;							//  If the opposite bit is found it adds it else goes the other way which is always an option
    bool goLeft = 0;
    node *curr = root;
    for(int i=31; i>=0; i--) {
		bool isBitSet = val&(1<<i);
        if(isBitSet==0) {
            if(curr->right!=nullptr) goLeft = 0;
            else goLeft = 1;
        }
        else {
            if(curr->left!=nullptr) goLeft = 1;
            else goLeft = 0;
        }
        if(goLeft)
            curr = curr->left;
        else {
            curr = curr->right;
            ans += (1<<i);
        }
    }
    return ans;
}

vector<int> maxXor(vector<int> arr, vector<int> queries) {  //  The main function which after retrieving the string with opposite bits, puts
    int n = arr.size(), m = queries.size();                 //  queries[i]^opp(queries[i]) into the result and finally returns the result.
    vector<int> res;
    node *root = makeTrie(arr);
    cout<<"Printing trie:\n"; printTrie(root, ""); cout<<"\n";
    for(int i=0; i<m; i++) {
        int val = searchOpposite(root, queries[i]);
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

/* Sample inputs:
4
1 3 5 7
2
17
6

3
0 1 2
3
3
7
2
*/
