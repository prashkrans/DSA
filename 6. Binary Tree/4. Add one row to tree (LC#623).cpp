/* Given the root of a binary tree, then value v and depth d, you need to add a row of nodes with value v 
at the given depth d. The root node is at depth 1. 
The adding rule is: given a positive integer depth d, for each NOT null tree nodes N in depth d-1, create two 
tree nodes with value v as N's left subtree root and right subtree root. And N's original left subtree should 
be the left subtree of the new left subtree root, its original right subtree should be the right subtree of the 
new right subtree root. If depth d is 1 that means there is no depth d-1 at all, then create a tree node with 
value v as the new root of the whole original tree, and the original tree is the new root's left subtree.

Input: 										
A binary tree as following:
       4
     /   \
    2     6
   / \   / 
  3   1 5   

v = 1

d = 2

Output: 
       4
      / \
     1   1
    /     \
   2       6
  / \     / 
 3   1   5  
 
 Input: 
A binary tree as following:
      4
     /   
    2    
   / \   
  3   1    

v = 1

d = 3

Output: 
      4
     /   
    2
   / \    
  1   1
 /     \  
3       1
 */
 
class Solution {
public:
    TreeNode* addRow(TreeNode* root, int v, int d){
        if(root==NULL) return NULL;			//	#IMP - Seem to forget writing the base case
		if(d>1){
			root->left = addRow(root->left, v, d-1);
            root->right = addRow(root->right, v, d-1);
        }
        else if(d==1){
            TreeNode* LST = root->left;
            TreeNode* RST = root->right;
                TreeNode* newLeft = new TreeNode(v);
                newLeft->left = LST;
                root->left = newLeft;
                TreeNode* newRight = new TreeNode(v);
                newRight->right = RST;
                root->right = newRight;
        }
        return root;
    }
    
    TreeNode* addOneRow(TreeNode* root, int v, int d) {
        if(d==1) {
            TreeNode* newRoot = new TreeNode(v);
            newRoot->left = root;
            return newRoot;
        }
        else{
            root = addRow(root, v, d-1);
            return root;
        }
    }
};