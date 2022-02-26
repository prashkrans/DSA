/* Red-black tree Problem #1.1. Insertion in a red-black tree. [Verified]
A red-black tree is a kind of self-balancing binary search tree where each node has an extra bit, and that bit is often
interpreted as the colour (red or black). These colours are used to ensure that the tree remains balanced during
insertions and deletions. Although the balance of the tree is not perfect, it is good enough to reduce the searching time
and maintain it around O(log n) time, where n is the total number of elements in the tree. This tree was invented in 1972
by Rudolf Bayer.
It must be noted that as each node requires only 1 bit of space to store the colour information, these types of trees show
identical memory footprint to the classic (uncoloured) binary search tree.
However since C++ does not have a datatype of size 1 bit, we may use bool or int or char to represent the colour red and black.

*/

//	Method 1.1. Without using parent variable.
//	Running time = O(log2(n))
//	Auxiliary space = O(n) to store n keys as nodes in the RBT.

#include<iostream>
using namespace std;

struct node {
	int val;
	char clr;               //  Need to include the variable clr to store the colour of the node i.e. whether black or red.
	node *left, *right;     //  Also no need to include parent pointer as we are using recursive insertion however we can include it too.
	node(): val(0), clr('R'), left(nullptr), right(nullptr) {}
	node(int val_): val(val_), clr('R'), left(nullptr), right(nullptr) {}
};

void printInorder(node *root) {
    if(root==NULL) return;
    printInorder(root->left);
    cout<<"("<<root->val<<", "<<root->clr<<") ";
    printInorder(root->right);
}

bool isDoubleRed(node *root) {
	if(root->clr == 'B') {
		if(root->left!=NULL && root->left->clr == 'R') {
			if((root->left->left!=NULL && root->left->left->clr == 'R') || (root->left->right!=NULL && root->left->right->clr == 'R')) return true;
		}
		if(root->right!=NULL && root->right->clr == 'R') {
			if((root->right->left!=NULL && root->right->left->clr == 'R') || (root->right->right!=NULL && root->right->right->clr == 'R')) return true;
		}
	}
	return false;
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

void recolor(node *&root) {
    if(root->clr == 'R') root->clr = 'B';
    else root->clr = 'R';
}

node* rebalanceInsertion(node *root, int data) {//  We only re-balance once the root which is not balanced is found
    node *b = root;                            	//  Four different types of restructuring is possible. Refer notes.
    node *a = NULL;								//	rebalance() re-balances the tree after each insertion
	node *c = NULL;
    node *k = NULL;
	if(root->val >= data) a = b->left;          //  Here, b is the grandparent of k, a is the parent of k and c is the uncle of k.
	else a = b->right;                          //  And, k is the node being inserted.
	if(b->left==a) c = b->right;
	else c = b->left;
    if(a->val >= data) k = a->left;
    else k = a->right;
    cout<<"b = "<<b->val<<" a = "<<a->val<<" k = "<<k->val;
    if(c!=NULL) cout<<" c = "<<c->val<<"\n";
    else cout<<" and c is NULL\n";
	if(c==NULL || c->clr == 'B') {
		cout<<"Case 1 of double red problem\n";
		if(a==b->left && k==a->left) {
			cout<<"Left left rotation required:\n";
			a = leftRotation(a, b);     b = a->right;   root = a;
            recolor(a);                 recolor(b);                 //  Rotations are the same as in AVL trees except the addition of recoloring here.
		}
		else if(a==b->right && k==a->right) {
			cout<<"Right right rotation required:\n";
			a = rightRotation(a, b);    b = a->left;    root = a;
			recolor(a);                 recolor(b);
		}
		else if(a==b->left && k==a->right) {
			cout<<"Left right rotation required:\n";
			k = rightRotation(k, a);    a = k->left;
			k = leftRotation(k, b);     b = k->right;   root = k;
			recolor(k);                 recolor(b);
		}
		else if(a==b->right && k==a->left) {
			cout<<"Right left rotation required:\n";
			k = leftRotation(k, a);     a = k->right;
			k = rightRotation(k, b);    b = k->left;   root = k;
			recolor(k);                 recolor(b);
		}
	}
	else if(c!=NULL && c->clr == 'R') {
        cout<<"Case 2 of double red problem\n";         //  No need to continue this further up here as it would automatically be checked in the
        recolor(b);                                     //  recursive insert function and corrected there itself since we are not using a parent pointer.
        recolor(c);
        recolor(a);
	}
    cout<<"After restructuring: b = "<<b->val<<" a = "<<a->val<<" k = "<<k->val<<" => ";
    printInorder(root); cout<<"\n";
    return root;
}

node *insertUtil(node* root, int data) {
    if(root==NULL) return new node(data);
    else {
        if(root->val >= data) root->left = insertUtil(root->left, data);    //  It allows duplicate elements in the RBT.
		else root->right = insertUtil(root->right, data);
        if(isDoubleRed(root)) {                                             //  Add the below 4 lines to the insert function of a BST to make it the insert function of a RBT.
            cout<<"Double red problem at "<<root->val<<" => ";
            root = rebalanceInsertion(root, data);
        }
        return root;
    }
}

node* insert(node *root, int data) {                    //  Need to use an insert utility as we need to add one line i.e. root->clr = 'B' after each insert.
    root = insertUtil(root, data);                      //  insertUtil(node* root, int data) is a simple recursive insert function of a BST along with rebalanceInsertion() function.
    root->clr = 'B';
}

int main() {
	node *root = nullptr;
	root = insert(root, 7);     root = insert(root, 4);     root = insert(root, 3);    root = insert(root, 9);
	root = insert(root, 15);    root = insert(root, 8);	    root = insert(root, 10);   root = insert(root, 6);
	//root = insert(root, 11);   root = insert(root, 1);      root = insert(root, 2);    root = insert(root, 12);
	cout<<"The AVL tree after all the insertions is:\n";
	printInorder(root); cout<<"\n";                //  Preorder print
	//cout<<"The max depth and height of the AVL tree are: "<<maxDepth(root)<<", "<<maxDepth(root)-1<<"\n";
	//root = deleteNode(root, 6);
	return 0;
}
