/* Binary Tree Prob # . Swap nodes at a given level/depth
Steps:
1. Convert 2D array to binary tree by creating an insert function.
2. Use maxDepth() function and level order traversal to reach the required depth.
3. Swap the left and right subtrees at the required depth
4. Use inorder traversal to traverse through the modified binary tree and insert it into an array
*/

//  Running time = O(n*t) where t is the number of queries
//  Auxiliary space = O(n*t)
#include <bits/stdc++.h>
using namespace std;

/*
 * Complete the 'swapNodes' function below.
 * The function is expected to return a 2D_INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. 2D_INTEGER_ARRAY indexes
 *  2. INTEGER_ARRAY queries
 */
struct node {
    int val;
    node *left, *right;
    node(int _val) : val(_val), left(nullptr), right(nullptr) {}
};

node *insertNode(node *root, int idx, int val, bool right) {
    if(val == -1 || root==NULL) return root;
    else {
        if(root->val == idx) {
            if(right) root->right = new node(val);
            else root->left = new node(val);
            return root;
        }
        root->left = insertNode(root->left, idx, val, right);
        root->right = insertNode(root->right, idx, val, right);
    }
    return root;
}

int maxDepth(node *root) {
    if(root==nullptr) return 0;
    else
        return 1 + max(maxDepth(root->left), maxDepth(root->right));
}

void printInorder(node *root, vector<int> &currRes) {
    if(root==NULL) return;
    printInorder(root->left, currRes);
    currRes.push_back(root->val);
    printInorder(root->right, currRes);
}

void swapNodesAtLevel(node *root, int depth, int currD) {
    if(root==NULL) return;
    if(currD==depth) {
        node *temp = root->left;
        root->left = root->right;
        root->right = temp;
    }
    swapNodesAtLevel(root->left, depth, currD+1);
    swapNodesAtLevel(root->right, depth, currD+1);
}

vector<vector<int>> swapNodes(vector<vector<int>> indexes, vector<int> queries) {
    int n = indexes.size(), m = queries.size();
    vector<vector<int>> res;
    vector<int> currRes;
    node *root = new node(1);
    for(int i=0; i<n; i++) {
        //cout<<"idx = "<<i+1<<" left = "<<indexes[i][0]<<" right = "<<indexes[i][1]<<"\n";
        root = insertNode(root, i+1, indexes[i][0], 0);
        root = insertNode(root, i+1, indexes[i][1], 1);
    }
    int maxD = maxDepth(root);
    for(int i=0; i<m; i++) {
        currRes.clear();
        for(int j=queries[i]; j<=maxD; j+=queries[i])
            swapNodesAtLevel(root, j, 1);
        printInorder(root, currRes);
        res.push_back(currRes);
    }
    return res;
}

int main() {
    int n, m;
    cin>>n;
    vector<vector<int>> indexes(n, vector<int>(2));
    for(int i=0; i<n; i++) cin>>indexes[i][0]>>indexes[i][1];
    cin>>m;
    vector<int> queries(m);
    for(int i=0; i<m; i++) cin>>queries[i];
    vector<vector<int>> res = swapNodes(indexes, queries);
    cout<<"Inorder print after swapping the nodes: \n";
    for(int i=0; i<res.size(); i++) {
        for(int j=0; j<res[0].size(); j++) cout<<res[i][j]<<" ";
        cout<<"\n";
    }
    return 0;
}

/* Sample input:
11
2 3
4 -1
5 -1
6 -1
7 8
-1 9
-1 -1
10 11
-1 -1
-1 -1
-1 -1
2
2
4
*/
