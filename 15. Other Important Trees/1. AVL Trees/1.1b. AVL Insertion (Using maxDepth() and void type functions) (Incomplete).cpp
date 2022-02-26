/* AVL Tree Problem #1. Insertion in an AVL tree.
AVL tree is a self-balancing Binary Search Tree (BST) where the difference between heights of left and right subtrees cannot
be more than one for all nodes.
*/

//  Method 1.1. Using 5 functions i.e. maxDepth(), isBalanced(), leftRotation(), rightRotation() and rebalance() to implement
//  insert() operation.
//  Note: Prefer making leftRot(), rightRot() and rebalance() as node* return type instead of void.
//  Running time = O(log2(n)) where n is the number of nodes.
//  Auxiliary space = O(n) as n nodes are inserted.

#include<iostream>
using namespace std;

struct node {
	int val;
	node *left;
	node *right;
	node(): val(0), left(nullptr), right(nullptr) {}
	node(int val_): val(val_), left(nullptr), right(nullptr) {}
};

void printPreorder(node *root) {
    if(root==NULL) return;
    cout<<root->val<<" ";
    printPreorder(root->left);
    printPreorder(root->right);
}

int maxDepth(node *root) {                      //  Max depth is used to check the balance of a node
    if(root==NULL) return 0;
    return 1 + max(maxDepth(root->left), maxDepth(root->right));
}

bool isBalanced(node *root) {                   //  Checks whether the current node is balanced or not.
    if(root==NULL) return 0;
    int balanceFactor = maxDepth(root->left) - maxDepth(root->right);
    if(balanceFactor == -1 || balanceFactor == 0 || balanceFactor == 1) return true;
    else return false;
}

node* leftRotation(node *v, node *u) {          //  Only two different rotations are needed hence, define the left and the right rotations.
    node *temp = v->right;
    v->right = u;
    u->left = temp;
    return v;
}

node* rightRotation(node *v, node *u) {
    node *temp = v->left;
    v->left = u;
    u->right = temp;
    return v;
}

node* rebalance(node *root, int data) {         //  We only re-balance once the root which is not balanced is found
    node *z = root;                             //  Four different types of restructuring is possible. Refer notes.
    node *y = NULL;
    node *x = NULL;
    if(z->val >= data) y = z->left;
    else y = z->right;
    if(y->val >= data) x = y->left;
    else x = y->right;
    cout<<"z = "<<z->val<<" y = "<<y->val<<" x = "<<x->val<<" => ";
    if(y==z->left && x==y->left) {
        cout<<"Left left rotation required:\n";
        y = leftRotation(y, z);     z = y->right;   root = y;
    }
    else if(y==z->right && x==y->right) {
        cout<<"Right right rotation required:\n";
        y = rightRotation(y, z);    z = y->left;    root = y;
    }
    else if(y==z->left && x==y->right) {
        cout<<"Left right rotation required:\n";
        x = rightRotation(x, y);    y = x->left;
        x = leftRotation(x, z);     z = x->right;   root = x;
    }
    else if(y==z->right && x==y->left) {
        cout<<"Right left rotation required:\n";
        x = leftRotation(x, y);     y = x->right;
        x = rightRotation(x, z);    z = x->left;   root = x;
    }
    cout<<"After restructuring: z = "<<z->val<<" y = "<<y->val<<" x = "<<x->val<<" => ";
    printPreorder(root); cout<<"\n";
    return root;
}

void insert(node *&root, int data) {
    if(root==NULL) root = new node(data);
    else {
        if(root->val >= data) insert(root->left, data);
        else insert(root->right, data);
        if(!isBalanced(root)) {                         //  Add the below 4 lines to the insert function of a BST to make it the insert function of an AVL tree.
            cout<<root->val<<" is not balanced\n";
            root = rebalance(root, data);
        }
    }
}

int main() {
	node *root = nullptr;
	insert(root, 5);    insert(root, 4);    insert(root, 3);    insert(root, 9);
	insert(root, 7);    insert(root, 8);	insert(root, 10);   insert(root, 6);
	insert(root, 11);   insert(root, 1);    insert(root, 2);    insert(root, 12);
	cout<<"The AVL tree after all the insertions is:\n";
	printPreorder(root); cout<<"\n";
	cout<<"The max depth and height of the AVL tree are: "<<maxDepth(root)<<", "<<maxDepth(root)-1<<"\n";
	return 0;
}
