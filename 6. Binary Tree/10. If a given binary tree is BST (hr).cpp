/* Binary Tree Prob. # . Is the given binary tree a BST?
*/

//	Running time = O(nlog2n) [Verify once]
//	Auxiliary space = O(1)

int maxVal(Node *root) {
    if(root->right==NULL) return root->data;
    else return maxVal(root->right);
}

int minVal(Node *root) {
    if(root->left==NULL) return root->data;
    else return minVal(root->left);
}

bool checkBST(Node* root) {
    if(root==NULL) return 1;
    if(root->left!=NULL && root->data <= maxVal(root->left)) return 0;				//	Note: It is important to use <= & >= as here, a BST is defined to have unique values only
    if(root->right!=NULL && root->data >= minVal(root->right)) return 0;
    return (checkBST(root->left) && checkBST(root->right));
}