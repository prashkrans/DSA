/*	Hashmap Problem #18 - LC#652. Find Duplicate Subtrees
Given the root of a binary tree, return all duplicate subtrees.
For each kind of duplicate subtrees, you only need to return the root node of any one of them.
Two trees are duplicate if they have the same structure with the same node values

Example 1:
Input: root = [1,2,3,4,null,2,4,null,null,4]
Output: [[2,4],[4]]

Example 2:
Input: root = [2,1,3]
Output: [[]] as there are none

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

//	Method 1 - Serializing the binary tree into a string (Convert binary tree to a serialized string)
//	Running time = O(n) i.e. O(DFS)
//	Auxiliary space = O(n)

class Solution { // Prefer this solution
public:
    string serialize(TreeNode* root, unordered_map<string, int> &mp, vector<TreeNode*> &ans) {
        if(root==NULL) return "X"; // Base case
        
        string LST = serialize(root->left, mp, ans);    // Left Subtree
        string RST = serialize(root->right, mp, ans);   // Right subtree
        
        // Small Calculation
        string currST = to_string(root->val) + "," + LST + "," + RST; // Preorder traversal i.e. root, leftST, rightST
        if(mp[currST]==1) ans.push_back(root);
        mp[currST]++;
        return currST;
    }
    
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        unordered_map<string, int> mp;
        vector<TreeNode*> ans;
        string s = serialize(root, mp, ans);
        //cout<<s<<"\n";
        return ans;
    }
};

// Same as above except three changes:
// 1. Changed the tranversal order from preorder to inorder (any traversal order works fine)
// 2. Changed string pattern from "," to "[]"
//      Note that string currString = lst + to_string(root->val) + rst; fails for a few cases 
//      so, its better to use a bracket or a comma
// 3. Check if count == 1 (add later) instead of (add before) count == 2 
// Also, to_string() built in function is used here
class Solution {
    public:
        string serialize(TreeNode* root, unordered_map<string, int> &mp, vector<TreeNode*> &ans) {
            if(root == nullptr) return "X";
            string lst = serialize(root->left, mp, ans);
            string rst = serialize(root->right, mp, ans);
            string currString = "[" + lst + to_string(root->val) + rst + "]";
            mp[currString]++;
            if(mp[currString]==2) ans.push_back(root);
            return currString;
        }
    
        vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
            unordered_map<string, int> mp;
            vector<TreeNode*> ans;
            string s = serialize(root, mp, ans);
            cout<<"Serialized string:"<<s;
            return ans;
        }
    };