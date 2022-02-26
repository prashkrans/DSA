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

//  deleteNode() using predecessors
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

void printInorder(node *root) {
    if(root==NULL) return;
    printInorder(root->left);
    cout<<root->val<<" ";
    printInorder(root->right);
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
            node* pred = root->left;                                    //  Here, root is modified s.t. it stores the value of its predecessor, its right child is unchanged and right child is
            while(pred->right!=NULL) pred = pred->right;                //  made the right subtree minus the predecessor node. So, we don't delete root here but delete the successor.
            root->val = pred->val;
            root->left = deleteNode(root->left, pred->val);
        }
    }
    return root;                                                        //  We return root for five out of six cases.
}


int main() {
	node *root = nullptr;
	insertVoidType(root, 1);    insertVoidType(root, 2);    insertVoidType(root, 3);
	insertVoidType(root, 4);    insertVoidType(root, 5);    insertVoidType(root, 6);
	printInorder(root); cout<<"\n";
	root = deleteNode(root, 2);     root = deleteNode(root, 5);     root = deleteNode(root, 7);
	printInorder(root); cout<<"\n";
	node* root2 = NULL;
	insertVoidType(root2, 10000);
	printInorder(root2); cout<<"\n";
	root2 = deleteNode(root2, 10000);
	printInorder(root2); cout<<"\n";
	return 0;
}
