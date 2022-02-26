/* Stack Problem #6 - LC#94. Binary Tree Traversal
Given the root of a binary tree, return the inorder traversal of its nodes' values.
Note - All three traversals i.e. a. preOrder, b. inOrder, c. postOrder traversals can
by implemented using a DFS

Example 1:
Input: root = [1,null,2,3]
Output: [1,3,2]

Example 2:
Input: root = []
Output: []
*/

//	Method 1 - recursive DFS
//	Running time = O(n) where n is the no. of elements in the binary tree
//	Auxiliary space = O(n) as we store all the elements in a vector

/*
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<int> DFS(TreeNode* root) {
        static vector<int> ans;
        if(root==NULL) return;
        ans.pushDFS(root->left);
        ans.push_back(root->val);	//	Here, inOrder traversal is being used
        DFS(root->right);
    }
    vector<int> inorderTraversal(TreeNode* root) {
        if(root==NULL) return {};
        return DFS(root, ans);
    }
};

//	Method 2 - iterative DFS using an explicit stack
//	Running time = O(n)
//	Auxiliary space = O(n) as we store all the elements in a vector
//	Incomplete