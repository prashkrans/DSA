/*Given the root of a binary tree, return the length of the diameter of the tree.
The diameter of a binary tree is the length of the longest path between any two nodes in a tree. 
# IMP - This path may or may not pass through the root.
The length of a path between two nodes is represented by the number of edges between them.

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
//	1. 	My Code - Without using a global varible and using the maxDepth() function (DFS approach)
//		Gfg - https://www.geeksforgeeks.org/diameter-of-a-binary-tree/
//		Running Time = O(n^2) ??
//		Extra Space = ??
class Solution {
public:
    int maxDepth(TreeNode* root){
        if(root==NULL) return 0;
        int left, right;
        left = 1 + maxDepth(root->left);
        right = 1 + maxDepth(root->right);
        return max(left, right);
    }
    
    int diameterOfBinaryTree(TreeNode* root) {
        if(root==NULL) return 0;
        int L, R, ans, Lans, Rans;
        L = maxDepth(root->left);
        R = maxDepth(root->right);
        ans = L+R;									//	Note - 	Diameter = 1 + maxDepth(root->left) - 1 + 1 + maxDepth(root->right) - 1
        Lans = diameterOfBinaryTree(root->left);	//			i.e. = maxDepth(root->left) + maxDepth(root->right);			
        Rans = diameterOfBinaryTree(root->right);
        return max(ans, max(Lans, Rans));
    }
};
//	2.	(Best soln by simply modifying method 1)
//		Using a global variable and using the maxDepth() function (DFS approach) (Faster)
//		Running Time = O(n)
//		Extra Space = O(n)
//		Leetcode solution - 
//		Gfg - https://www.geeksforgeeks.org/diameter-of-a-binary-tree-in-on-a-new-method/
class Solution {
    private:
    int diameter=0;	//	diameter = INT_MIN but we know diameter can be positive only thus use 0
    public:
    int maxDepth(TreeNode* root){
        if(root==NULL) return 0;
        int left, right;
        left = maxDepth(root->left);
        right = maxDepth(root->right);
        diameter = max(diameter, left+right);
        return 1 + max(left, right);
    }
    
    int diameterOfBinaryTree(TreeNode* root) {
        if(root==NULL) return 0;
        int val = maxDepth(root);
        return diameter;
    }
};