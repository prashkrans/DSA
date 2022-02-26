/* AVL Tree Problem #2.1. Deletion in an AVL tree. (Using maxDepth function)
AVL tree is a self-balancing Binary Search Tree (BST) where the difference between heights of left and right subtrees cannot
be more than one for all nodes.
*/

//  Method 2.1. Using 5 functions i.e. maxDepth(), isBalanced(), leftRotation(), rightRotation() and rebalance() to implement
//  insert() operation.
//  Note: Prefer making leftRot(), rightRot() and rebalance() as node* return type instead of void.
//  Running time = O(log2(n)) or O(height of the tree) where n is the number of nodes.
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

void printInorder(node *root) {
    if(root==NULL) return;
    printInorder(root->left);
    cout<<root->val<<" ";
    printInorder(root->right);
}

int maxDepth(node *root) {                      //  Max depth is used to check the balance of a node
    if(root==NULL) return 0;
    return 1 + max(maxDepth(root->left), maxDepth(root->right));
}

bool isBalanced(node *root) {                   //  Checks whether the current node is balanced or not.
    if(root==NULL) return true;                 //  If a node is NULL, return true as empty node is considered balanced.
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
    node *y = NULL;								//	rebalance() re-balances the tree after each insertion
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

node* rebalanceDeletion(node *root) {			//	rebalanceDeletion() re-balances the tree after each deletion
    node *z = root;
    node *y = NULL;
    node *x = NULL;
    if(maxDepth(z->left) > maxDepth(z->right)) y = z->left;
    else y = z->right;
    if(maxDepth(y->left) >= maxDepth(y->right)) x = y->left;
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

node* insert(node *root, int data) {                    //  Since the insert is of void type, need to use node *&root instead of node *root.
    if(root==NULL) return new node(data);
    else {
        if(root->val >= data) root->left = insert(root->left, data);    //  It allows duplicate elements in the AVL tree.
        else root->right = insert(root->right, data);
        if(!isBalanced(root)) {                         //  Add the below 4 lines to the insert function of a BST to make it the insert function of an AVL tree.
            cout<<root->val<<" is not balanced\n";
            root = rebalance(root, data);
        }
        return root;
    }
}

node* deleteNode(node *root, int data) {
    if(root==NULL) return root;
    if(root->val > data) root->left = deleteNode(root->left, data);
    else if(root->val < data) root->right = deleteNode(root->right, data);            //  Recursion finds if a node x with value == data exists
    else {                                                              //  i.e. if(root->data==val)
        cout<<"Deleting the node with value = "<<data<<"\n";
        if(root->left==NULL && root->right == NULL) {                   //  Case 1. x has no children
            delete root;                                                //  delete keyword destroys the value or memory block pointed by pointer and not the pointer itself.
            root = NULL;                                                //  After deleting the contents of root, it is made NULL
        }
        else if(root->left==NULL || root->right==NULL) {                //  Case 2. x has a single child
            node *child = NULL;                                         //  Here, root is modified and made a copy of its child
            if(root->left==NULL) child = root->right;                   //  Also, we don't delete root here but delete its child
            else child = root->left;
            root->val = child->val;                                     //  Don't use root = child; as we are deleting the child. Had we not used delete we could have used root = child.
            root->left = child->left;
            root->right = child->right;
            delete child;
        }
        else {                                                          //  Case 3. x has two children => both root->left and root->right exist.
            node* successor = root->right;                              //  Here, root is modified s.t. it stores the value of its successor, its left child is unchanged and right child is
            while(successor->left!=NULL) successor = successor->left;   //  made the right subtree minus the successor node. So, we don't delete root here but delete the successor.
            root->val = successor->val;
            root->right = deleteNode(root->right, successor->val);
        }
    }
    if(!isBalanced(root)) {                                             //  Add the below 4 lines to the delete function of a BST to make it the delete function of an AVL tree.
        cout<<root->val<<" is not balanced\n";
        root = rebalanceDeletion(root);
    }
    return root;                                                        //  We return root for five out of six cases.
}

int main() {
	node *root = nullptr;
	root = insert(root, 5);    root = insert(root, 4);      root = insert(root, 3);    root = insert(root, 9);
	root = insert(root, 7);    root = insert(root, 8);	    root = insert(root, 10);   root = insert(root, 6);
	root = insert(root, 11);   root = insert(root, 1);      root = insert(root, 2);    root = insert(root, 12);
	cout<<"The AVL tree after all the insertions is:\n";
	printPreorder(root); cout<<"\n";                //  Preorder print
	cout<<"The max depth and height of the AVL tree are: "<<maxDepth(root)<<", "<<maxDepth(root)-1<<"\n";
	//root = deleteNode(root, 6);
	root = deleteNode(root, 10);    root = deleteNode(root, 8);                                                                     //  RR Rotation with z = 9
	root = deleteNode(root, 3);     root = deleteNode(root, 5);     root = deleteNode(root, 6);                                     //  LL Rotation with z = 4
	root = deleteNode(root, 9);     root = deleteNode(root, 12);    root = deleteNode(root, 1);     root = deleteNode(root, 11);    //  LR Rotation with z = 7
	root = deleteNode(root, 4);     root = deleteNode(root, 7);     root = deleteNode(root, 2);
	cout<<"The AVL tree after all the deletions is:\n";
	printPreorder(root); cout<<"\n";                //  Preorder print
	cout<<"The max depth and height of the AVL tree are: "<<maxDepth(root)<<", "<<maxDepth(root)-1<<"\n";
	root = insert(root, 5);    root = insert(root, 4);      root = insert(root, 3);    root = insert(root, 9);                      //  Re-populating
	root = insert(root, 7);    root = insert(root, 8);	    root = insert(root, 10);   root = insert(root, 6);
	root = insert(root, 11);   root = insert(root, 1);      root = insert(root, 2);    root = insert(root, 12);
	root = deleteNode(root, 8);                                                                                                     //  RL Rotation with z = 9
	cout<<"Want custom input? (y/n)\n";
	char ch;
	//ch = 'n';
	cin>>ch;
	if(ch=='y') {
        int n, val;
        cin>>n;
        node* root2 = NULL;
        for(int i=0; i<n; i++) {
            cin>>val;
            root2 = insert(root2, val);
        }
        cout<<"The AVL tree after all the insertions is:\n";
        printInorder(root2); cout<<"\n";            //  Inorder print
        cout<<"The max depth and height of the AVL tree are: "<<maxDepth(root2)<<", "<<maxDepth(root2)-1<<"\n";
	}
	return 0;
}

/* Sample input
y
6
366 359 344 496 270 213
Output: 213 270 344 359 366 496 (Inorder)
*/
