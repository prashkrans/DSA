/* BST Problem 1. Basics of BST [Verified]
1.  insert():   O(log2(n)) in average cases O(n) in the worst case
2.  maxVal():   O(log2(n)) in average cases O(n) in the worst case
3.  minVal():   O(log2(n)) in average cases O(n) in the worst case
4.  print() - Pre, In, Post: O(n) in all the cases
5.  search():   O(log2(n)) in average cases O(n) in the worst case
6.  deleteNode(): O(log2(n)) in average cases O(n) in the worst case
Note:
a.  h = O(log2(n))
b.  Insert(), search() and deleteNode() reduces to O(log2(n)) = O(h) for AVL trees even in worst cases.
c.  deleteNode() can be implemented using either a successor or a predecessor.
*/

//  deleteNode() using succesors
#include<iostream>
using namespace std;

struct node {
	int val;
	node *left;
	node *right;
	node(): val(0), left(nullptr), right(nullptr) {}
	node(int val_): val(val_), left(nullptr), right(nullptr) {}
};

void insertVoidType(node *&root, int data) {        //  Since the insert is of void type, need to use node *&root instead of node *root.
    if(root==NULL) root = new node(data);
    else {
        if(root->val >= data) insertVoidType(root->left, data);
        else insertVoidType(root->right, data);
    }
}

node* insert(node *root, int data) {                //  Since the insert is of node* type, no need to use node *&root instead of node *root.
    if(root==NULL) return new node(data);
    else {
        if(root->val >= data) root->left = insert(root->left, data);
        else root->right = insert(root->right, data);
    }
}

int maxVal(node *root) {
    if(root==NULL) return INT_MIN;
    else if(root->right==NULL) return root->val;
    else maxVal(root->right);
}

int minVal(node *root) {
    if(root==NULL) return INT_MAX;
    else if(root->left==NULL) return root->val;
    else maxVal(root->left);
}

void printInorder(node *root) {
    if(root==NULL) return;
    printInorder(root->left);
    cout<<root->val<<" ";
    printInorder(root->right);
}

bool search(node *root, int data) {
    if(root==NULL) return 0;
    if(root->val==data) return 1;
    else if(root->val > data) search(root->left, data);
    else search(root->right, data);
}

node* deleteNode(node *root, int data) {
    if(root==NULL) return root;
    if(root->val > data) root->left = deleteNode(root->left, data);
    else if(root->val < data) root->right = deleteNode(root->right, data);            //  Recursion finds if a node x with value == data exists
    else {                                                              //  i.e. if(root->data==val)
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
    return root;                                                        //  We return root for five out of six cases.
}

int main() {
	node *root = nullptr;
	insertVoidType(root, 1);    insertVoidType(root, 2);    insertVoidType(root, 3);
	root = insert(root, 4);     root = insert(root, 5);     root = insert(root, 6);
	printInorder(root); cout<<"\n";
	cout<<"Maxval = "<<maxVal(root)<<"\n";
	cout<<"Minval = "<<minVal(root)<<"\n";
	int val = 3;
	val = 7;
	if(search(root, val)) cout<<val<<" is found in the given BST\n";
	else cout<<val<<" is not found in the given BST\n";
	node* root2 = NULL;
	root2 = insert(root2, 10000);
	printInorder(root2); cout<<"\n";
	root2 = deleteNode(root2, 10000);
	printInorder(root2); cout<<"\n";
	root = deleteNode(root, 2);     root = deleteNode(root, 5);
	printInorder(root); cout<<"\n";
	return 0;
}
