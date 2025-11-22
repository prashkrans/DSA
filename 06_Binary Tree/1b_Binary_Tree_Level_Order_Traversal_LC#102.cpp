
// Method 1: Without using a queue:
class Solution {
    public:
        void binaryTreeLevelOrderTraversal(TreeNode* root, vector<vector<int>> &ans, int currLevel) {
            if(root==NULL) return;
            else {
                if (ans.size() <= currLevel) ans.push_back({}); // Ensure the ans vector has enough space
                ans[currLevel].push_back(root->val);
                binaryTreeLevelOrderTraversal(root->left, ans, currLevel+1);
                binaryTreeLevelOrderTraversal(root->right, ans, currLevel+1);
            }
        }
    
        vector<vector<int>> levelOrder(TreeNode* root) {
            vector<vector<int>> ans;
            binaryTreeLevelOrderTraversal(root, ans, 0);
            return ans;
        }
    };


// Method 2: Using a queue: TODO
// Running time: O(n) 
// Auxiliary space: O(n) due to the vector<vector<int>> ans

class Solution {
    public:
        vector<vector<int>> levelOrder(TreeNode* root) {
            vector<vector<int>> ans;
            if(root==NULL) return ans;
            queue<TreeNode*> q;
            q.push(root);
            while(!q.empty()) {
                int currLevelSize = q.size();  // Number of nodes at the current level
                vector<int> currLevelNodes;
                // This for loop makes sure nodes at a particular level are separated from nodes at other levels
                for(int i=0; i<currLevelSize; i++) { 
                    TreeNode* curr = q.front();
                    q.pop();
                    currLevelNodes.push_back(curr->val);
                    
                    if(curr->left!=nullptr) q.push(curr->left);
                    if(curr->right!=nullptr) q.push(curr->right);
                }
                ans.push_back(currLevelNodes);
            }
            return ans;
        }
    };