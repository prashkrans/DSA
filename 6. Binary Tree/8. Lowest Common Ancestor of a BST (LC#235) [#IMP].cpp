/* Binary Tree Prob #8. (LC#235) Lowest Common Ancestor of a Binary Search Tree [#IMP]
Given a binary search tree (BST), find the lowest common ancestor (LCA) of two given nodes in the BST.
According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes p and q as the 
lowest node in T that has both p and q as descendants (where we allow a node to be a descendant of itself) [#IMP].”

Example 1:
Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
Output: 6
Explanation: The LCA of nodes 2 and 8 is 6.

Example 2:
Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
Output: 2
Explanation: The LCA of nodes 2 and 4 is 2, since a node can be a descendant of itself according to the LCA definition.

Approach: For Binary search tree, while traversing the tree from top to bottom the first node which lies in between 
the two numbers n1 and n2 is the LCA of the nodes, i.e. the first node n with the lowest depth which lies in between 
n1 and n2 (n1<=n<=n2) n1 < n2. So just recursively traverse the BST in, if node’s value is greater than both n1 and 
n2 then our LCA lies in the left side of the node, if it’s is smaller than both n1 and n2, then LCA lies on the right 
side. Otherwise, the root is LCA (assuming that both n1 and n2 are present in BST).

Algorithm:
1. 	Create a recursive function that takes a node and the two values n1 and n2.
2. 	If the value of the current node is less than both n1 and n2, then LCA lies in the right subtree. Call the recursive 
	function for the right subtree.
3. 	If the value of the current node is greater than both n1 and n2, then LCA lies in the left subtree. Call the recursive 
	function for the left subtree.
4. 	If both the above cases are false then return the current node as LCA.
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 
//	Method 1. Recursive (Condensed than iterative)
//  Running time = O(log2n) i.e. the height of the given binary search tree
//  Auxiliary space = O(1)

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root==NULL) return root;
        if(root->val > p->val && root->val > q->val) 
            return lowestCommonAncestor(root->left, p, q);
        else if(root->val < p->val && root->val < q->val) 
            return lowestCommonAncestor(root->right, p, q);
        else return root;        
    }
};

//	Method 2. Iterative (Easier to understand)
//  Running time = O(log2n) i.e. the height of the given binary search tree
//  Auxiliary space = O(1)

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        while(root!=NULL) {
			if(root->val > p->val && root->val > q->val)
				root = root->left;
			else if(root->val < p->val && root->val < q->val) 
				root = root->right;
			else return root;
		}
		return root;
	}
};