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

//	Method 1 - Serializing the binary tree
//	Running time = O(n) i.e. O(DFS)
//	Auxiliary space = O(n)

class Solution {
public:
    string serialize(TreeNode* root, unordered_map<string, int> &mp, vector<TreeNode*> &ans) {
        if(root==NULL) return "X";
        string LST = serialize(root->left, mp, ans);
        string RST = serialize(root->right, mp, ans);
        string currST = to_string(root->val) + "," + LST + "," + RST;
        mp[currST]++;
        if(mp[currST]==2) ans.push_back(root);
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