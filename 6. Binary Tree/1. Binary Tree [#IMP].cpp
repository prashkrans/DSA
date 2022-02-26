#include<iostream>
#include<queue>
using namespace std;

struct node{
    int data;
    node* left;
    node* right;
    node(int data): data(data), left(NULL), right(NULL) {}  // If constructors are not to be used then need a helper function to save redundancy
    node(int val, node* l, node* r) {                       // node* newNode(int data){
        data = val;                                         //      node* new newN = new node; newN->data = data;
        left = l;                                           //      newN->left = NULL; newN->right = NULL;
        right = r;                                          //      return newN;
    }                                                       // }
    // or node(int data, node* left, node* right) : data(data), left(left), right(right) {}
    // Lines 9 to 13 do the same thing as the line 14
    // node* parent; // Makes life easier but takes one space extra
};

// 1.   Write a function insert() (Recursive) such that given a binary search tree and a number, insert a new node with the given number into the tree in the
//      correct place. The insert() code is similar to lookup(), but with the complication that it modifies the tree structure.
//      The standard trick to avoid using reference parameters i.e. avoid using void type functions.
node* insert(node* root, int data){
    //node* newNode = new node(data);
    node* newNode = new node(data, NULL, NULL);
    if(root==NULL) return newNode; // or root = newNode; return root;
    else{
        if(root->data>data) root->left =  insert(root->left, data);
        else if(root->data<=data) root->right = insert(root->right, data);
    }
    return root;
}

// 2.   Write a function lookup() such that given a binary search tree (BST) and a "target" value, search the tree to see if it contains the target.
// 2a.  Recursive lookup() - (Best)
bool lookup(node* root, int val){
    if(root==NULL) return 0;                // The tree is empty, it does not contain any element
    if(root->data==val) return 1;
    else if (root->data>val) return lookup(root->left, val);
    else if (root->data<val) return lookup(root->right, val);
}

// 2b. Iterative lookup()
bool lookupIter(node* root, int val){
    node* curr = root;                      // Not actually needed though
    while(curr!=NULL){
        if(curr->data==val) return true;
        else if(curr->data>val) curr = curr->left;
        else curr = curr->right;
    }
    return false;                           // Covers the base case too
}

// 3.   Write a function to print the elements of the given binary tree by any of the three methods of traversal
//      i.e. 1. preOrder, 2. inOrder, 3. postOrder.
void traversePrint(node* root, int value){
    if(root==NULL) return;
    if(value==1) cout<<root->data<<" ";
    traversePrint(root->left, value);
    if(value==2) cout<<root->data<<" ";
    traversePrint(root->right, value);
    if(value==3) cout<<root->data<<" ";
}

// 4.   Write a function size() such that given a binary tree, it counts the number of nodes in the tree.
//      size() function can only be implemented recursively.
int size(node* root){
    if(root==NULL) return 0;
    int leftSize = size(root->left);
    int rightSize = size(root->right);
    return 1 + leftSize + rightSize;
}

// 5.   Write a function maxDepth() such that given a binary tree, it computes its "maxDepth" -- the number
//      of nodes along the longest path from the root node down to the farthest leaf node.
//      The maxDepth of the empty tree is 0.
//      #IMPORTANT - Visualize that recursion takes care of the left and right subtree and now we have to take care of the root node
//      i.e. if say left has more no. of nodes than the right, we just have add one to left and vice versa
int maxDepth(node* root){
    if(root==NULL) return 0;
    int leftDepth = maxDepth(root->left);                   // Compute the depth of each subtree
    int rightDepth = maxDepth(root->right);
    if(leftDepth>=rightDepth) return 1 + leftDepth;         // Use the larger one either left or right
    else return 1 + rightDepth;                             // Can also use the max fucntion as in return max(leftD, rightD) + 1
}

//	5b. Shorter version of the above function:
int maxDepth2(node *root) {		//	Verify Once
	if(root==NULL) return 0;
	return 1 + max(maxDepth2(root->left), maxDepth2(root->right));
}

// #IMPORTANT - In a BST or OBT, the leftmost element is the minimum and the rightmost item is the maximum.
// 6.   Write a function minValue() such that given a non-empty binary search tree (BST) (an ordered binary tree),
//      it returns the minimum data value found in that tree. Note that it is not necessary to search the entire tree.
// 6a.  Recursive minValue() function.
int minValue(node* root){
    if(root->left==NULL) return root->data;         // No need of base case as the given BST in non-empty
    return minValue(root->left);
}

// 6b.  Iterative minValue() function.              // Note - Iterative solutions generally work for BST only
int minValueIter(node* root){                       // when we have to work with just one subtree i.e. either left or right
    node* curr = root;
    while(curr->left!=NULL) curr = curr->left;
    return curr->data;
}

// 7.   Write a function maxValue() such that given a non-empty binary search tree (BST) (an ordered binary tree),
//      it returns the maximum data value found in that tree. Note that it is not necessary to search the entire tree.
// 7a.  Recursive maxValue() function.
int maxValue(node* root){
    if(root->right==NULL) return root->data;         // No need of base case as the given BST in non-empty
    return maxValue(root->right);
}

// 7b.  Iterative maxValue() function.
int maxValueIter(node* root){
    node* curr = root;
    while(curr->right!=NULL) curr = curr->right;
    return curr->data;
}

// 8.   Write a function hasPathSum() such that given a binary tree and a sum, returns true if the tree has a root-to-leaf path
//      such that adding up all the values along the path equals the given sum. Return false if no such path can be found.
/*
bool hasPathSum(node* root, int sum){   // My Code
    if(root==NULL){
        if(sum==0) return true;     // Strategy: subtract the node value from the sum when recurring down,
        else return false;          // and check to see if the sum is 0 when you run out of tree i.e. if(root==NULL&sum==0) true
    }
    sum = sum - root->data;
    bool leftPath = hasPathSum(root->left, sum);
    if(leftPath == true) return true;
    else{
        bool rightPath = hasPathSum(root->right, sum);
        if (rightPath == true) return true;
    }
    return false;
}*/
// Same code as above but concise.
bool hasPathSum(node* root, int sum){
    if (root==NULL) return (sum==0);
    sum-=root->data;                                                        // Same principle as in maxDepth()
    return (hasPathSum(root->left, sum)||hasPathSum(root->right, sum));     // The root node has two options either go left or right
}

// 9.   Given a binary tree, print out all of its root-to-leaf paths, one per line. Hint: In C, C++, and Java,
//      probably the best solution is to create a recursive helper function printPathsRecur(node, int path[], int pathLen),
//      where the path array communicates the sequence of nodes that led up to the current call. Alternately, the problem
//      may be solved bottom-up, with each node returning its list of paths.
void printPaths(node* root, int a[], int size){
    if(root==NULL) return;
    a[size++] = root->data;                             // append this node to the path array and increase the size of the array
    if(root->left==NULL&&root->right==NULL){            // it's a leaf, so print the path that led to here
        for(int i=0; i<size; i++) cout<<a[i]<<" ";
        cout<<"\n";
    }
    printPaths(root->left, a, size);                    // otherwise try both subtrees
    printPaths(root->right, a, size);
}

// 10.  Write a function mirror() to change a tree so that the roles of the left and right pointers are swapped at every node.
//      #IMP - This is also known as inverting a binary tree.
//      The solution is short, but very recursive. As it happens, this can be accomplished without changing the root node
//      pointer, so the return-the-new-root construct is not necessary.
//      The function is void type but we are not changing the root pointer hence no need of node*& root
void mirror(node* root){        // Postorder implementation
    if(root==NULL) return;      // Inorder print gives the sorted order of elements of a BST
    mirror(root->left);         // Mirror image in inorder gives the reversed sorted order (Eg. asc. -> desc.)
    mirror(root->right);
    node* temp = root->left;    // Just swap the left child with the right child for a given node
    root->left = root->right;
    root->right = temp;
}

// 10b. Write a function that swaps the left and right children at every node i.e. gives the mirror image of the
//      binary tree. (Same as the above program but returnable)
/*node* swapChildren(node* root){
    if(root==NULL) return root;
    root->left = swapChildren(root->left);
    root->right = swapChildren(root->right);
    node* temp = root->left;
    root->left = root->right;
    root->right = temp;
    return root;
}*/

// 11.  Write a function doubleTree() that for each node in a binary search tree, creates a new duplicate node,
//      and inserts the duplicate as the left child of the original node. The resulting tree should still be a
//      binary search tree. As with the previous problem, this can be accomplished without changing the root node
//      pointer i.e. no need of node*& root.
void doubleTree(node* root){
    if(root==NULL) return;
    doubleTree(root->left);
    doubleTree(root->right);
    node* newNode = new node(root->data);
    newNode->left = root->left;
    root->left = newNode;
}
// 12.  Write a function sameTree() such that given two binary trees, return true if they are structurally identical
//      i.e. they are made of nodes with the same values arranged in the same way.
bool sameTree(node* root1, node* root2){
    if(root1==NULL&&root2==NULL) return 1;                      // Three cases
    if(root1==NULL&&root2!=NULL) return 0;                      // 1. both empty -> true
    if(root1!=NULL&&root2==NULL) return 0;                      // 2. only one empty -> false (Structurally different)
    if(root1->data==root2->data){                               // 3. both non-empty -> compare their data
        bool leftST = sameTree(root1->left, root2->left);       //      if equal -> true else false
        bool rightST = sameTree(root2->right, root2->right);
        if(leftST==1&&rightST==1) return 1;
        else return 0;
    }
    else return 0;      // Returns false if data are not equal
}
// 13.  Write a recursive function countTrees() that, given a value, computes the number of structurally
//      unique binary search trees that store those values. For example countTrees(4) should return 14, since there
//      are 14 structurally unique binary search trees that store 1, 2, 3, and 4. The base case is easy, and the
//      recursion is short but dense. Your code should not construct any actual trees; it's just a counting problem.
//      This is not a binary tree programming problem in the ordinary sense -- it's more of a math/combinatorics recursion
//      problem that happens to use binary trees. #IMP - Learn it
int countTrees(int n){
    if(n==0||n==1) return 1;                // If (n==0) then the subtree is empty & if n==1 then the subtree is just a node (Either way both cases return only 1 combination)
    int sum = 0;                            // Iterate through all the values that could be the root i.e. 1 to n
    for(int root=1; root<=n; root++){       // There will be one value at the root, with whatever remains
        int leftCT = countTrees(root-1);    // on the left and right each forming their own subtrees.
        int rightCT = countTrees(n-root);   // i.e. leftSubtree = root-1; & rightSubtree = n-root;
        sum += leftCT*rightCT;              // # IMP - Number of possible trees with this root => leftCT*rightCT
    }
    return sum;
}
// 14.  Write a function isBST() to check whether the given plain binary tree is a binary search tree (BST).
// 14a. Inefficient - Uses two helper functions minValue() and maxValue() and the fact that at every node
//      maxValue(LeftSubtree) <= Node->Data <= minValue(RightSubtree)
bool isBST(node* root){
    if(root==NULL) return 1;
    bool leftBST = isBST(root->left);
    bool rightBST = isBST(root->right);
    bool rootLeft = 1;
    bool rootRight = 1;
    if(root->left!=NULL){
        int leftMax = maxValue(root->left);
        if(leftMax>root->data) rootLeft = 0;        // If maxValue(L) > node->data => not a BST
    }
    if(root->right!=NULL){
        int rightMin = minValue(root->right);
        if(rightMin<root->data) rootRight = 0;      // If minValue(L) < node->data => not a BST
    }
    return (leftBST&&rightBST&&rootLeft&&rootRight); // Only if all the four conditions are true it returns true;
}
// 14b. Efficient isBST() that keeps track of the narrowing min and max, looking at each node only once. The initial values
//      of min = INT_MAX; and max = INT_MIN.
bool isBST2rec(node* root, int min, int max){               // Efficient but tricky
    if(root==NULL) return 1;
    if(root->data<min||root->data>max) return false;        // false if this node violates the min/max constraint
    // otherwise check the subtrees recursively, tightening the min or max constraint
    return((root->left, min, root->data)&&(root->right, root->data+1, max));
}

bool isBST2(node* root){
    return isBST2rec(root, INT_MIN, INT_MAX);
}

// 15.  Binary Tree Level Order Traversal - There are two methods of level order traversal or breadth first search approach.
//      (Both are important)
// 15a. Without using a queue. But using two functions 1. maxDepth() and 2. printOneLevel(). # Really IMPORTANT (Learn It)
//      This is useful when we need to keep a track of all nodes at a particular level
// I.   maxDepth-1 gives the height of the given binary tree i.e. levels 0, 1, 2, 3, ..., n for tree of height n.
// II.  printOneLevel() function prints all the nodes in that level.
void printOneLevel(node* root, int level){      // The root and the level at which all the nodes are to be printed are passed
    if(root==NULL) return;
    if(level==0) cout<<root->data<<" ";         // Print only the nodes of a given level
    else if(level>0){                           // If the level > 0 => not reached the required level yet
        printOneLevel(root->left, level-1);     // Prints both the left and right nodes in a given level
        printOneLevel(root->right, level-1);
    }
}

void printBFSorLOT(node* root){
    if(root==NULL) cout<<"The given binary tree is empty\n";
    else {                                      // We cannot write a function for maxHeight directly but use the fact h = mD - 1
        int height = maxDepth(root)-1;          // As max depth calculates the max number of nodes in a path
        for(int i=0; i<=height; i++){           // while height is the max number of connections in a path i.e. maxDepth - 1
            cout<<"[ ";
            printOneLevel(root, i);             // Prints all the nodes for the given level i which itself varies from 0 to height
            cout<<"]";                          // thus prints all the nodes in BFS or LOT.
        }
    }
}

// 15b. Using a queue(STL) to print all the nodes in BFS/LOT. Not useful in tracking all the nodes in a particular level.
void printBFSusingQ(node* root){                // # Really IMPORTANT (Learn It)
    if(root==NULL){
        cout<<"The given binary tree is empty \n";
        return;
    }
    queue<node*> Q;     // Need #include<queue> or can create our own class for queue using three functions push(), front() & pop()
    Q.push(root);
    while(!Q.empty()){
        node* curr = Q.front();
        Q.pop();
        cout<<curr->data<<" ";
        if(curr->left!=NULL) Q.push(curr->left);
        if(curr->right!=NULL) Q.push(curr->right);
    }
}
// 15c. A leetcode problem which is a variation of 15a. Given a binary tree, return the level order traversal of its nodes'
//      values. (ie, from left to right, level by level). Here we return the values instead of printing them.
//      {Correct soln as passed all the test cases but not the best)
/*
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}        // 3 Constructors
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 *
vector<int> nodesAtOneLevel(TreeNode* root, int level){
    vector<int> a;
    if(root==NULL) return a;
    if(level==0){
        a.push_back(root->val);
    }
    else if(level>0){
        vector<int> leftArr = nodesAtOneLevel(root->left, level-1);
        vector<int> rightArr = nodesAtOneLevel(root->right, level-1);
        for(int i=0; i<leftArr.size(); i++) a.push_back(leftArr[i]);
        for(int i=0; i<rightArr.size(); i++) a.push_back(rightArr[i]);
    }
    return a;
}

int maxDepth(TreeNode* root){
    if(root==NULL) return 0;
    else return max(maxDepth(root->left), maxDepth(root->right))+1;
}

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> bfsArr;
        if(root==NULL) return bfsArr;
        int height = maxDepth(root) - 1;
        for(int i=0; i<=height; i++){
            vector<int> a = nodesAtOneLevel(root, i);
            bfsArr.push_back(a);
        }
    return bfsArr;
    }
};
*/

// 16.  Write a funtion makeACopy() recursively to create a copy of a given binary tree.
node* makeACopy(node* root){
    if(root==NULL) return root;
    node* copyRoot = new node(root->data);       // Creates a new node every time when visits an unvisited node
    copyRoot->left = makeACopy(root->left);
    copyRoot->right = makeACopy(root->right);
    return copyRoot;
}

// 17.  Write a function areEqual() recusively to compare two binary trees and check whether they are equal.
bool areEqual(node* root1, node* root2){
    if(root1==NULL&&root2==NULL) return true;
    else if((root1!=NULL&&root2==NULL)||(root1==NULL&&root2!=NULL)) return false;
    bool nodeAns=true;
    if(root1->data!=root2->data) nodeAns = false;             // Compares the values at the nodes
    bool leftAns = areEqual(root1->left, root2->left);      // Compares the left subtrees
    bool rightAns = areEqual(root1->right, root2->right);   // Compares the right subtrees
    return (nodeAns&&leftAns&&rightAns);                    // L, the node, R should all be equal
}

// 18.  Write a function isSymmetric() to check whether the given binary tree is symmetric around its center i.e. the left
//      and the right subtrees are mirror images. (leetcode)
//      Therefore, the question is: when are two trees a mirror reflection of each other?
//      Two trees are a mirror reflection of each other if:
//      a.  Their two roots have the same value.
//      b.  The right subtree of each tree is a mirror reflection of the left subtree of the other tree.
// 18a. Recursive -
bool isMirror(node* root1, node* root2){
    if(root1==NULL&&root2==NULL) return true;
    else if((root1==NULL&&root2!=NULL)||(root2!=NULL&&root2==NULL)) return false; // Structurally different, hence not symmetrical
    bool nodeAns = true;
    if(root1->data!=root2->data) nodeAns = false;       // 1. Comparing the node values of both the trees
    bool lfRi = isMirror(root1->left, root2->right);    // 2. Comparing the left subtree of tree (1) with the right subtree of tree (2)
    bool riLf = isMirror(root1->right, root2->left);    // 3. Comparing the right subtree of tree (1) with the left subtree of tree (2)
    return (nodeAns&&lfRi&&riLf);                       // All the above 3 conditions should be met for both the trees to be mirror images
}

bool isSymmetricRec(node* root){
    if(root==NULL) return true;
    else return isMirror(root->left, root->right);           // Just need to check whether the left & right subtrees are mirror images
}
// 18b. Iterative using a queue. Each two consecutive nodes in the queue should be equal, and their subtrees
//      a mirror of each other. Initially, the queue contains root and root. Then the algorithm works similarly
//      to BFS, with some key differences. Each time, two nodes are extracted and their values compared. Then, the
//      right and left children of the two nodes are inserted in the queue in opposite order. The algorithm is done
//      when either the queue is empty, or we detect that the tree is not symmetric (i.e. we pull out two consecutive
//      nodes from the queue that are unequal).
bool isSymmetricIter(node* root) {                      // leetcode soln
        if(root==NULL) return true;
        queue<node*> Q;
        Q.push(root);
        Q.push(root);
        while(!Q.empty()){
            node* root1 = Q.front(); Q.pop();
            node* root2 = Q.front(); Q.pop();
            if(root1==NULL&&root2==NULL) continue;      // Donot return true instead use continue for complete traversal
            if(root1==NULL||root2==NULL) return false;
            if(root1->data!=root2->data) return false;
            Q.push(root1->left);
            Q.push(root2->right);
            Q.push(root1->right);
            Q.push(root2->left);
        }
        return true;
}

// 19.  Write a function buildTreePreIn() that creates a binary tree from the given preOrder and inOrder vectors/arrays.
//      For example, given preorder = [3,9,20,15,7] inorder = [9,3,15,20,7] (leetcode)
//      Return the following binary tree:
//    3
//   / \
//  9  20
//    /  \
//   15   7
node* buildTreePreIn(vector<int>& preorder, vector<int>& inorder) {
        if(inorder.size()==0) return NULL;      // Base case 1. when the size of the pre = in arrays is zero, it appends null
        if(inorder.size()==1){
            node* root = new node(inorder[0]);  // Base case 2. when the size of the pre = in arrays is one, it appends the single node
            return root;
        }
        int rootVal = preorder[0]; int rootPos = 0;     // Gets the rootnode i.e. the first element of the inorder array
        while(rootVal!=inorder[rootPos]) rootPos++;     // Gets the rootnode position in the inorder array
        vector<int> leftPRE, rightPRE;
        for(int i=1; i<=rootPos; i++) leftPRE.push_back(preorder[i]);   // Creates the left subtree in preOrder
        for(int i=rootPos+1; i<preorder.size(); i++) rightPRE.push_back(preorder[i]);   // Creates the right subtree in preOrder
        vector<int> leftIN, rightIN;
        for(int i=0; i<rootPos; i++) leftIN.push_back(inorder[i]);      // Creates the left subtree in inOrder
        for(int i=rootPos+1; i<inorder.size(); i++) rightIN.push_back(inorder[i]);  // Creates the right subtree in inOrder
        node* root = new node(rootVal);
        root->left = buildTreePreIn(leftPRE, leftIN);
        root->right = buildTreePreIn(rightPRE, rightIN);
        return root;
    }

// 20.  Write a function buildTreeInPost() that creates a binary tree from the given inOrder and postOrder vectors/arrays. (leetcode)
node* buildTreeInPost(vector<int>& inorder, vector<int>& postorder) {
        if(inorder.size()==0&&postorder.size()==0) return NULL;
        if(inorder.size()==1&&postorder.size()==1){
            node* root = new node(inorder[0]);
            return root;
        }
        int rootVal = postorder.back(); int rootPos = 0;
        while(rootVal!=inorder[rootPos]) rootPos++;
        vector<int> leftIN, rightIN;
        for(int i=0; i<rootPos; i++) leftIN.push_back(inorder[i]);
        for(int i = rootPos+1; i<inorder.size(); i++) rightIN.push_back(inorder[i]);
        vector<int> leftPOST, rightPOST;
        for(int i=0; i<rootPos; i++) leftPOST.push_back(postorder[i]);
        for(int i=rootPos; i<postorder.size()-1; i++) rightPOST.push_back(postorder[i]);
        /*
        cout<<"Left Inorder = "; for(int i=0; i<rootPos; i++) cout<<leftIN[i]<<" "; cout<<"\n";
        cout<<"Left Postorder = "; for(int i=0; i<rootPos; i++) cout<<leftPOST[i]<<" "; cout<<"\n";
        cout<<"Right Inorder = "; for(int i=0; i<rightIN.size(); i++) cout<<rightIN[i]<<" "; cout<<"\n";
        cout<<"Right Postorder = "; for(int i=0; i<rightPOST.size(); i++) cout<<rightPOST[i]<<" "; cout<<"\n";
        */
        node* root = new node(rootVal);
        root->right = buildTreeInPost(rightIN, rightPOST);
        root->left = buildTreeInPost(leftIN, leftPOST);
        return root;
}

// 21.  Write a function connectAllNodesLeftToRight() such that given a perfect binary tree where all leaves are on the same
//      level, and every parent has two children, it connects all the nodes at a given level from left to right. (leetcode)
//      Note - This function only works if the given binary is a perfect binary tree.
//The binary tree has the following definition:
struct cnctdNode {
  int val;
  cnctdNode *left;
  cnctdNode *right;
  cnctdNode *next;
  cnctdNode(int val) : val(val), left(NULL), right(NULL), next(NULL) {}
};
//      Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set
//      to NULL. Initially, all next pointers are set to NULL
//      Uses BFS traversal, hence using a queue.
cnctdNode* makeRightChildNextNULL(cnctdNode* root){    // Helper function to make the rightmost nodes at all levels point to NULL
        if(root==NULL) return root;
        root->next = NULL;                              // Makes the rightmost node->next = NULL
        root->right = makeRightChildNextNULL(root->right);
        return root;
    }

cnctdNode* connectAllNodesLeftToRightOnlyPBT(cnctdNode* root) {
        if(root==NULL) return root;
        queue<cnctdNode*> Q;                            // A queue of type cnctdNode defined
        Q.push(root);
        while(!Q.empty()){
            cnctdNode* curr = Q.front();
            if(curr->left!=NULL) Q.push(curr->left);    // Enqueues the left and right child of the root node
            if(curr->right!=NULL) Q.push(curr->right);
            Q.pop();                                    // Dequeues the front node of the queue
            if(!Q.empty()) curr->next = Q.front();      // Checks whether there exists a node right to the current node
            else curr->next = NULL;                     // If a right node to the current node doesn't exist make curr->next = NULL
        }
    root = makeRightChildNextNULL(root);                // Before the helper function the rightmost nodes at all levels point to
    return root;                                        // the leftmost node at their corresponding next level
    }


// 22.  Write a function connectAllNodesLeftToRightAnyBTree() such that given a binary tree (any BT = full, complete, perfect, degen, etc)
//      it connects all the nodes at a given level from left to right. (leetcode)
//      Note - This function only works for any given binary tree.
//      This uses three functions -
//      1. maxDepth() - to calculate the height of the given binary tree
//      2. fillQueue() - to create a queue containing all the nodes at a given level
//      3. connectALevel() - to connect all the nodes at a given level i.e. connect all the nodes of the queue obtained from fillQueue()
/*The binary tree has the following definition:
struct cnctdNode {
  int val;
  cnctdNode *left;
  cnctdNode *right;
  cnctdNode *next;
  cnctdNode(int val) : val(val), left(NULL), right(NULL), next(NULL) {}
}*/
int maxDepthCnctd(cnctdNode* root){   // maxDepth() is defined again for cnctdNode
        if(root==NULL) return 0;
        else return (max(maxDepthCnctd(root->left), maxDepthCnctd(root->right)) + 1);
    }
void fillQueue(cnctdNode* root, int level, queue<cnctdNode*>& Q){   // Note the use of & i.e. the queue is passed as reference
    if(root==NULL) return;                                          // as the function is void type
    if(level==0) Q.push(root);
    if(level>0){
        fillQueue(root->left, level-1, Q);
        fillQueue(root->right, level-1, Q);
    }
}
cnctdNode* connectALevel(cnctdNode* root, int level){
    if(root==NULL) return root;
    queue<cnctdNode*> Q;
    fillQueue(root, level, Q);                  // Calls the helper function
    while(!Q.empty()){
        cnctdNode* curr = Q.front(); Q.pop();
        if(!Q.empty()) curr->next = Q.front();  // Connects the nodes left to right at a given level
        else curr->next = NULL;                 // Makes the righmost node to point to NULL
    }
    return root;
}
cnctdNode* connectAllNodesLeftToRight(cnctdNode* root) {
    if(root==NULL) return root;
    int height = maxDepthCnctd(root) - 1;            // Calculates the height using the maxDepth function
    for(int i=0; i<=height; i++){               // Connects the nodes in all the levels as levels varies from 0 to height
        root = connectALevel(root, i);
    }
    return root;
}

// 21.&22.  Write a function printBFScnctd() to print the elements of a given binary tree in a BFS/LOT manner using the extra
//          next pointer provided the nodes at all the levels are connected from left to right.
void inOrderPrintCnctd(cnctdNode* root){
    if(root==NULL) return;
    inOrderPrintCnctd(root->left);
    cout<<root->val<<" ";
    inOrderPrintCnctd(root->right);
}

cnctdNode* insertCnctd(cnctdNode* root, int val){   // Inserts data in the connected binary tree following BST rules
    cnctdNode* newNode = new cnctdNode(val);
    if(root==NULL) return newNode; // or root = newNode; return root;
    else{
        if(root->val>val) root->left =  insertCnctd(root->left, val);
        else if(root->val<=val) root->right = insertCnctd(root->right, val);
    }
    return root;
}

cnctdNode* returnLeftMostNodeAtAlevel(cnctdNode* root, int level){
    if(root==NULL) return root;
    if(level==0) return root;
    cnctdNode* left = NULL;
    cnctdNode* right = NULL;
    if(level>0){
        left = returnLeftMostNodeAtAlevel(root->left, level-1);
        right = returnLeftMostNodeAtAlevel(root->right, level-1);
    }
    if(left!=NULL) return left;
    else return right;
}

void printBFScnctd(cnctdNode* root){
        if(root==NULL) return;
        int height = maxDepthCnctd(root) - 1;
        for(int i=0; i<=height; i++){
            cnctdNode* curr = returnLeftMostNodeAtAlevel(root, i);
            while(curr!=NULL){
            cout<<curr->val<<" ";
            curr = curr->next;
            }
            cout<<"\n";
        }
    }


//#############################################################################################################################################################

int main(){
node* root = NULL;
cout<<"Creating binary tree (1) (Inorder print) = \n";
root = insert(root, 12); root = insert(root, 15); root = insert(root, 14); root = insert(root, 8); root = insert(root, 4);
//root->right->data = 1;    // for an unordered binary tree
root = insert(root, 18); root = insert(root, 25); root = insert(root, 1); root = insert(root, 5); root = insert(root, 22);
traversePrint(root, 2); if(root!=NULL) cout<<" with the root at "<<root->data<<"\n";
cout<<"Creating binary tree (2) (Inorder print) = \n";
node* root2 = NULL;
root2 = insert(root2, 12); root2 = insert(root2, 15); root2 = insert(root2, 14); root2 = insert(root2, 8); root2 = insert(root2, 4);
root2 = insert(root2, 18); root2 = insert(root2, 25); root2 = insert(root2, 1); root2 = insert(root2, 5); root2 = insert(root2, 22);
traversePrint(root2, 2); if(root2!=NULL) cout<<" with the root at "<<root2->data<<"\n";
cout<<"Creating binary tree (3) (Inorder print) = \n";
node* root3 = NULL;
root3 = insert(root3, 5); root3 = insert(root3, 8); root3 = insert(root3, 6); root3 = insert(root3, 10);
node* newNode = new node(8); root3->left = newNode;             // Cannot use insert() as it follows BST rule
node* newNode2 = new node(6); root3->left->right = newNode2;
node* newNode3 = new node(10); root3->left->left = newNode3;
traversePrint(root3, 2); if(root3!=NULL) cout<<" with the root at "<<root3->data<<"\n";
cout<<"Creating a connected perfect binary tree (cnctdPerfect) \n";
cnctdNode* cPBTr = NULL;
cPBTr = insertCnctd(cPBTr, 15); cPBTr = insertCnctd(cPBTr, 7); cPBTr = insertCnctd(cPBTr, 10); cPBTr = insertCnctd(cPBTr, 20);
cPBTr = insertCnctd(cPBTr, 18); cPBTr = insertCnctd(cPBTr, 25); cPBTr = insertCnctd(cPBTr, 21); cPBTr = insertCnctd(cPBTr, 19);
cPBTr = insertCnctd(cPBTr, 17); cPBTr = insertCnctd(cPBTr, 12); cPBTr = insertCnctd(cPBTr, 8); cPBTr = insertCnctd(cPBTr, 3);
cPBTr = insertCnctd(cPBTr, 5); cPBTr = insertCnctd(cPBTr, 1); cPBTr = insertCnctd(cPBTr, 27);
inOrderPrintCnctd(cPBTr); if(cPBTr!=NULL) cout<<" with the root at "<<cPBTr->val<<"\n";
cout<<"Creating a connected binary tree (cnctdAnyBT) \n";
cnctdNode* cAnyBTr = NULL;
cAnyBTr = insertCnctd(cAnyBTr, 25); cAnyBTr = insertCnctd(cAnyBTr, 18); cAnyBTr = insertCnctd(cAnyBTr, 35);
cAnyBTr = insertCnctd(cAnyBTr, 12); cAnyBTr = insertCnctd(cAnyBTr, 11); cAnyBTr = insertCnctd(cAnyBTr, 30);
cAnyBTr = insertCnctd(cAnyBTr, 6); cAnyBTr = insertCnctd(cAnyBTr, 9); cAnyBTr = insertCnctd(cAnyBTr, 15);
cAnyBTr = insertCnctd(cAnyBTr, 40); cAnyBTr = insertCnctd(cAnyBTr, 22); cAnyBTr = insertCnctd(cAnyBTr, 20);
inOrderPrintCnctd(cAnyBTr); if(cPBTr!=NULL) cout<<" with the root at "<<cAnyBTr->val<<"\n";
cout<<"################################################################################################\n";
cout<<"Function list = \n";
cout<<"1. insert() function \n";
cout<<"2. lookup() function => a. Recursive b. Iterative \n";
cout<<"3. traversePrint() function => 1. preOrder, 2. inOrder, 3. postOrder \n";
cout<<"4. size() function \n";
cout<<"5. maxDepth() function \n";
cout<<"6. minValue() function \n";
cout<<"7. maxValue() function \n";
cout<<"8. hasPathSum() function \n";
cout<<"9. printPaths() function \n";
cout<<"10. mirror() function \n";
cout<<"11. doubleTree() function \n";
cout<<"12. sameTree() function \n";
cout<<"13. countTrees() function \n";
cout<<"14. isBST() function \n";
cout<<"15. printBFSorLOT() function \n";
cout<<"16. makeACopy() fucntion \n";
cout<<"17. areEqual() function \n";
cout<<"18. isSymmetric() function \n";
cout<<"19. buildTreePreIn() function \n";
cout<<"20. buildTreeInPost() function \n";
cout<<"21. connectAllNodesLeftToRightOnlyPBT() function \n";
cout<<"22. connectAllNodesLeftToRight() function \n";
cout<<"################################################################################################\n";
char input = 'y';
char input2 = 'y';
char method = 'a';
int funcNum, value, count, sizeofArr;
bool ans;
int a[10000];
int arrSize = 0;
node* copyRoot = NULL;
vector<int> preA, inA, postA;
node* rootPreIn = NULL;
node* rootInPost = NULL;
while(input=='y'){
    cout<<"Enter the number of the function to be used = ";
    cin>>funcNum;
    switch(funcNum){
        case 1 :
            input2='y';
            while(input2=='y'){
                cout<<"Enter the value that needs to inserted into the binary tree (1) = ";
                cin>>value;
                root = insert(root, value);
                cout<<"Wanna continue? => insert() function (y/n) = ";
                cin>>input2;
            }
            cout<<"The updated binary tree (1) is (Inorder print) = \n";
            traversePrint(root, 2); cout<<"\n";
            break;
        case 2 :
            input2='y';
            while(input2=='y'){
                cout<<"Enter the value that needs to looked up in the binary tree (1) = ";
                cin>>value;
                cout<<"Which lookup() function is to be used? Input (a) for recursive and (b) for iterative \n";
                cin>>method;
                if (method == 'a'){
                    cout<<"Recursive lookup() selected\n";
                    ans = lookup(root, value);
                }
                else if (method == 'b'){
                    cout<<"Iterative lookup() selected\n";
                    ans = lookupIter(root, value);
                }
                else cout<<"Not a valid input\n";
                if (ans==true) cout<<"The given element is present in the binary tree (1)\n";
                else cout<<"The given element is not present in the binary tree (1)\n";
                cout<<"Wanna continue? => lookup() function (y/n) = ";
                cin>>input2;
            }
            break;
        case 3 :
            input2='y';
            while(input2=='y'){
                cout<<"Enter the method of printing binary tree (1)";
                cout<<" i.e. (1) = preOrder, (2) = inOrder, (3) = postOrder\n";
                cin>>value;
                if(value!=1&&value!=2&&value!=3) cout<<"Not a valid input\n";
                else traversePrint(root, value);
                cout<<"\n";
                cout<<"Wanna continue? => traversePrint() function (y/n) = ";
                cin>>input2;
            }
            break;
        case 4 :
            cout<<"The total no. of nodes i.e. size of the binary tree (1) = "<<size(root)<<"\n";
            break;
        case 5 :
            cout<<"The maxDepth of the binary tree (1) = "<<maxDepth(root)<<"\n";
            break;
        case 6 :
            cout<<"Which minValue() function is to be used? Input (a) for recursive and (b) for iterative \n";
            cin>>method;
            cout<<"The minimum value of the given binary tree (1) = ";
            if(method=='a') cout<<minValue(root)<<"\n";
            else if(method=='b') cout<<minValueIter(root)<<"\n";
            break;
        case 7 :
            cout<<"Which maxValue() function is to be used? Input (a) for recursive and (b) for iterative \n";
            cin>>method;
            cout<<"The maximum value of the given binary tree (1) = ";
            if(method=='a') cout<<maxValue(root)<<"\n";
            else if(method=='b') cout<<maxValueIter(root)<<"\n";
            break;
        case 8 :
            input2='y';
            while(input2=='y'){
                cout<<"Enter the value of sum of the path = ";
                cin>>value;
                ans = hasPathSum(root, value);
                if(ans) cout<<"The binary tree (1) has a path of sum = "<<value<<"\n";
                else cout<<"There is no such path in binary tree (1)\n";
                cout<<"Wanna continue? => hasPathSum() function (y/n) = ";
                cin>>input2;
            }
            break;
        case 9 :
            cout<<"Printing all the paths of the binary tree (1) = \n";
            arrSize = 0;
            printPaths(root, a, arrSize);
            break;
        case 10 :
            cout<<"The original binary tree (1) (Inorder Print) = \n";
            traversePrint(root, 2); cout<<"\n";
            cout<<"The mirror image of the binary tree (1) (Inorder Print) = \n";
            mirror(root);
            traversePrint(root, 2); cout<<"\n";
            break;
        case 11 :
            cout<<"The original binary tree (1) (Inorder Print) = \n";
            traversePrint(root, 2); cout<<"\n";
            cout<<"The updated tree after using the doubleTree() on binary tree (1) (Inorder Print) = \n";
            doubleTree(root);
            traversePrint(root, 2); cout<<"\n";
            break;
        case 12 :
            cout<<"Comparing whether the binary trees (1) & (2) are same \n";
            ans = sameTree(root, root2);
            if(ans) cout<<"They are the same\n";
            else cout<<"They are not the same\n";
            break;
        case 13 :
            cout<<"Enter the value of n = ";
            cin>>value;
            cout<<"The number of distinct binary search trees for n = "<<value<<" are = ";
            cout<<countTrees(value)<<"\n";
            break;
        case 14 :
            cout<<"Which isBST() function is to be used on the binary tree (1)? \n";
            cout<<"Input (a) for the inefficient one and (b) for the efficient one \n";
                cin>>method;
                if (method == 'a'){
                    cout<<"Inefficient isBST() selected \n";
                    ans = isBST(root);
                }
                else if (method == 'b'){
                    cout<<"Efficient isBST2() selected \n";
                    ans = isBST2(root);
                }
                else cout<<"Not a valid input\n";
                if (ans==true) cout<<"The given binary tree is a BST \n";
                else cout<<"The given binary tree is not a BST \n";
                break;
        case 15 :
            cout<<"Which printBSTorLOT() function is to be used on the binary tree (1)? \n";
            cout<<"Input (a) for the one without queue (b) for the one with queue & (c) to just printOneLevel()\n";
            cin>>method;
            if(method == 'a'){
                cout<<"Without using a queue, the BST/LOT print is = \n";
                printBFSorLOT(root);
                cout<<"\n";
            }
            else if(method == 'b'){
                cout<<"Using a queue, the BST/LOT print is = \n";
                printBFSusingQ(root);
                cout<<"\n";
            }
            else if(method == 'c'){
                input2 = 'y';
                while(input2=='y'){
                    cout<<"For which level should all the nodes be printed? (Level should <= height) \n";
                    cin>>value;
                    cout<<"Printing all the nodes at level = "<<value<<"\n";
                    printOneLevel(root, value);
                    cout<<"\n";
                    cout<<"Wanna continue? => printOneLevel() function (y/n) = ";
                    cin>>input2;
                }
            }
            else cout<<"Invalid input for the type of the method to be used \n";
            break;
        case 16 :
            cout<<"Making another copy of the binary tree (1) = \n";
            copyRoot = makeACopy(root);
            cout<<"Printing the original binary tree (1) = \n";
            traversePrint(root, 2); cout<<"\n";
            cout<<"Printing the copied binary tree \n";
            traversePrint(copyRoot, 2); cout<<"\n";
            break;
        case 17 :
            cout<<"Comparing the binary trees (1) and (2) \n";
            ans = areEqual(root, root2);
            if(ans) cout<<"The binary trees (1) and (2) are equal \n";
            else cout<<"The binary trees (1) and (2) are not equal \n";
            break;
        case 18 :
            cout<<"Which type of isSymmetric function is to be used on binary tree (1)? \n";
            cout<<"Input (a) for recursive and (b) for iterative versions = \n";
            cin>>method;
            if(method=='a'){
                cout<<"Checking whether binary tree (3) is symmetrical or not using recursive version \n";
                ans = isSymmetricRec(root3);
                if(ans) cout<<"Binary tree (3) is symmetrical \n";
                else cout<<"Binary tree (3) is not symmetrical \n";
            }
            else if(method=='b'){
                cout<<"Checking whether binary tree (3) is symmetrical or not using iterative version \n";
                ans = isSymmetricIter(root3);
                if(ans) cout<<"Binary tree (3) is symmetrical \n";
                else cout<<"Binary tree (3) is not symmetrical \n";
            }
            else cout<<"Invalid input for the type of method to be used \n";
            break;
        case 19 :
            cout<<"Calling the function to create a binary tree from the given preOrder and inOrder vectors/arrays \n";
            cout<<"Enter the size followed by elements of the preOrder and inOrder arrays = \n";
            cin>>sizeofArr;
            for(int i=0; i<sizeofArr; i++){
                cin>>value;
                preA.push_back(value);
            }
            for(int i=0; i<sizeofArr; i++){
                cin>>value;
                inA.push_back(value);
            }
            rootPreIn = buildTreePreIn(preA, inA);
            cout<<"Printing the binary tree created from the given preOrder and inOrder arrays (Inorder) = \n";
            traversePrint(rootPreIn, 2); cout<<"\n";
            break;
        case 20 :
            cout<<"Calling the function to create a binary tree from the given inOrder and postOrder vectors/arrays \n";
            cout<<"Enter the size followed by elements of the inOrder and postOrder arrays = \n";
            cin>>sizeofArr;
            for(int i=0; i<sizeofArr; i++){
                cin>>value;
                inA.push_back(value);
            }
            for(int i=0; i<sizeofArr; i++){
                cin>>value;
                postA.push_back(value);
            }
            rootInPost = buildTreeInPost(inA, postA);
            cout<<"Printing the binary tree created from the given inOrder and postOrder arrays (Inorder) = \n";
            traversePrint(rootInPost, 2); cout<<"\n";
            break;
        case 21 :
            cout<<"Connecting the nodes from left to right at all levels for the perfect binary tree (cnctdPerfect) \n";
            cPBTr = connectAllNodesLeftToRightOnlyPBT(cPBTr);
            cout<<"Printing the connected perfect binary tree(cnctdPerfect) = \n";
            printBFScnctd(cPBTr);
            break;
        case 22 :
            cout<<"Connecting the nodes from left to right at all levels for the binary tree (cnctdAnyBT) \n";
            cAnyBTr = connectAllNodesLeftToRight(cAnyBTr);
            cout<<"Printing the connected binary tree(cnctdAnyBT) = \n";
            printBFScnctd(cAnyBTr);
            break;
        default :
            cout<<"Not a valid number\n";
            break;

    }
    cout<<"Wanna use another function? (y/n) = ";
    cin>>input;
}

cout<<"Ending the program";
return 0;
}


