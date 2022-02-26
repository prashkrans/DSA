/* BST Problem LC#450. Delete Node in a BST
Given a root node reference of a BST and a key, delete the node with the given key in the BST. Return the root node
reference (possibly updated) of the BST.
Basically, the deletion can be divided into two stages:
a.  Search for a node to remove.
b.  If the node is found, delete the node.

Constraints:
The number of nodes in the tree is in the range [0, 10^4].
-10^5 <= Node.val <= 10^5
Each node has a unique value.
root is a valid binary search tree.
-10^5 <= key <= 10^5

//  Running time = O(log2(n)) in average cases but O(n) in the worst case
//  Auxiliary space = O(1) due to successor/predecessor and child variables

/**
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
    TreeNode* deleteNode(TreeNode* root, int key) {
        if(root==NULL) return root;
        if(root->val > key) root->left = deleteNode(root->left, key);
        else if(root->val < key) root->right = deleteNode(root->right, key);
        else {
            if(root->left==NULL && root->right==NULL) {
                delete root;        //  delete keyword destroys the value or memory block pointed by pointer and not the pointer itself.
                root=NULL;
            }
            else if(root->left==NULL || root->right==NULL) {
                TreeNode* child = (root->left==NULL)?root->right:root->left;    //  If left child is null, child takes the right child value or vice versa
                root->val = child->val;
                root->left = child->left;
                root->right = child->right;
                delete child;
            }
            else if(root->left!=NULL && root->right!=NULL) {
                TreeNode* successor = root->right;
                while(successor->left!=NULL) successor = successor->left;       //  Successor is the minimum value in the right subtree of the root
                root->val = successor->val;
                root->right = deleteNode(root->right, successor->val);
            }
        }
        return root;
    }
};
