#include<iostream>
using namespace std;

struct node{
    int val;
    node* leftChild;
    node* rightChild;
    node(int x) : val(x), leftChild(NULL), rightChild(NULL) {}          // Constructor function to create a new node and initialize it
};

// Or including a pointer to its parent
struct node2{
    int val;
    node2* leftChild;
    node2* rightChild;
    node2* parent;                                                                  // Makes life easier but uses more space
    node2() : val(0), leftChild(NULL), rightChild(NULL), parent(NULL) {}            // Line 16 and 17 represents constructors
    node2(int x) : val(x), leftChild(NULL), rightChild(NULL), parent(NULL) {}       // Line 17 and 18 are synonymous
    // or node2(int x) {val = x; leftChild = NULL; rightChild = NULL; parentC = NULL;}
    node2 (int x, node2* leftChild, node2* rightChild, node2* parent) :             // Since its a constructor use only the variables defined in the struct
            val(x), leftChild(leftChild), rightChild(leftChild), parent(leftChild) {}     // Methods should end with {}
    // Initialises as   a. Pointer => node2* newNode = new node2(); or node2* newNode = new node2();    // in this way of declaration
    //                  b. Object => node2 newNodeObj(); node2 newNodeObj(x); // Verify
};

class binaryTree{           // This binaryTree is in the form of a linked list. Could have defined the tree as a structure too
    int size = 0;           // Stores the current size of the binary tree. Important to initialize size=0 and root = NULL when creating an object
    node* root = NULL;      // Pointer to the root node. Both size and root are private
public :                    // Methods declared here but defined outside the class
    void insert(int val);                           // Note - we are not breaking any branch, instead just adding new nodes accordingly
    node* findNodeBST(node* root, int nodeVal);     // Given the index works in preorder way of traversal
    void insertLeft(int nodeVal, int val);          // Given the left of the given node at that index is empty
    void insertRight(int nodeVal, int val);         // Given the right of the given node at that index is empty
    void preOrder(node* root);
    void inOrder(node* root);
    void postOrder(node* root);
    int sizeOfTree();
    node* returnRoot();
    int numOfSiblingPairs(node* root);
};

// 1.   insert() function - Inserts a given value at its appropriate position.
void binaryTree :: insert(int val){
    //node* newNode = new node; newNode->val = val;             // Lengthier option
    //newNode->leftChild = NULL; newNode->rightChild = NULL;
    node* newNode = new node(val);                              // Creating a new node dynamically + calling the constructor
    if(size==0) {                                               // Important to set size = 0 when an object is created
        root = newNode;
        size++;
    }
    else {
        node* curr = root;
        while(1){
            if(val<=curr->val){
                if(curr->leftChild!=NULL) curr = curr->leftChild;
                else{
                    curr->leftChild = newNode;
                    size++;
                    break;
                }
            }
            else if (val>curr->val){
                if(curr->rightChild!=NULL) curr = curr->rightChild;
                else {
                    curr->rightChild = newNode;
                    size++;
                    break;
                }
            }
        }
    }
}

// 2.   findNodeBST() - Returns the node at which the given data is found else returns null.
node* binaryTree :: findNodeBST(node* root, int nodeVal){
    if(root==NULL) return NULL;
    if(nodeVal<root->val) return findNodeBST(root->leftChild, nodeVal);
    else if (nodeVal>root->val) return findNodeBST(root->rightChild, nodeVal);
    if(nodeVal == root->val) return root;
}

// 3.   insertLeft() - Given a value inside the tree find the node and insert another value as the left child of that node.
void binaryTree :: insertLeft(int nodeVal, int val){
    node* curr = findNodeBST(root, nodeVal);
    if (curr == NULL){
        cout<<"There does not exist any node with value = "<<nodeVal<<" in the binary tree\n";
        return;
    }
    if(curr->leftChild!=NULL){
        cout<<"The left child of the node with value = "<<nodeVal<<" is not empty\n";
        return;
    }
    else {
        node* newNode = new node(val);
        curr->leftChild = newNode;
        size++;
    }
}

// 4.   insertRight() - Given a value inside the tree find the node and insert another value as the right child of that node.
void binaryTree :: insertRight(int nodeVal, int val){
    node* curr = findNodeBST(root, nodeVal);
    if (curr == NULL){
        cout<<"There does not exist any node with value = "<<nodeVal<<" in the binary tree\n";
        return;
    }
    if(curr->rightChild!=NULL){
        cout<<"The left child of the node with value = "<<nodeVal<<" is not empty\n";
        return;
    }
    else {
        node* newNode = new node(val);
        curr->rightChild = newNode;
        size++;
    }
}
// 5.   preOrder print.
void binaryTree :: preOrder(node* root){
    if(root==NULL) return;
    cout<<root->val<<" ";
    preOrder(root->leftChild);
    preOrder(root->rightChild);
}
// 6.   inOrder print.
void binaryTree :: inOrder(node* root){         //  The most important traversal
    if(root==NULL) return;                      // 1.   An inorder traversal on a binary search tree will order the nodes
    inOrder(root->leftChild);                   //      of the tree in increasing order of their values.
    cout<<root->val<<" ";                       // 2.   An inorder traversal gives the true form of arithmetic expressions
    inOrder(root->rightChild);
}

// 7. postOrder print.
void binaryTree :: postOrder(node* root){
    if(root==NULL) return;
    postOrder(root->leftChild);
    postOrder(root->rightChild);
    cout<<root->val<<" ";
}

// 8.   sizeOfTree() - Since size is a private member so, need a member function to access it.
int binaryTree :: sizeOfTree(){
    return size;
}

// 9.   returnRoot() - Since root is a private member so, need a member function to access it.
node* binaryTree :: returnRoot(){
    return root;
}

// 10.  Write a function numOfSiblingPairs() to count the number of pairs of siblings in a binary tree. Two nodes in a binary tree are
//      said to be siblings if they have the same parent.
int binaryTree :: numOfSiblingPairs(node* root){
    if(root==NULL) return 0;
    else if(root->leftChild==NULL) return numOfSiblingPairs(root->rightChild);
    else if(root->rightChild==NULL) return numOfSiblingPairs(root->leftChild);
    else if (root->leftChild!=NULL&&root->rightChild!=NULL) {
        int left = numOfSiblingPairs(root->leftChild);
        int right = numOfSiblingPairs(root->rightChild);
        return 1 + left + right;
    }
}

//#########################################################################################################################################
int main(){
binaryTree bt;
cout<<"Creating a binary tree with values from 1 to 10\n";
for(int i=1; i<=10; i++) bt.insert(i);
cout<<"Preorder print = ";
bt.preOrder(bt.returnRoot()); cout<<"\n";
cout<<"Inorder print = ";
bt.inOrder(bt.returnRoot()); cout<<"\n";                        // or node* root = bt.returnRoot(); then bt.inOrder(root);
cout<<"Postorder print = ";
bt.postOrder(bt.returnRoot()); cout<<"\n";

binaryTree bt2;
cout<<"Creating binary tree (2)\n";
bt2.insert(6); bt2.insert(3); bt2.insert(1); bt2.insert(4); bt2.insert(10);
bt2.insert(14); bt2.insert(11); bt2.insert(20);
node* root2 = bt2.returnRoot();
cout<<"Preorder print = ";
bt.preOrder(root2); cout<<"\n";
cout<<"Inorder print = ";
bt.inOrder(root2); cout<<"\n";
cout<<"Postorder print = ";
bt.postOrder(root2); cout<<"\n";
cout<<"####################################################################################\n";
cout<<"Here are the list of functions = \n";
cout<<"1.   - insert() function\n";
cout<<"2.   - findNodeBST() function\n";
cout<<"3.   - insertLeft() function\n";
cout<<"4.   - insertRight() function\n";
cout<<"5.   - \n";
cout<<"6.   - \n";
cout<<"7.   - \n";
cout<<"8.   - \n";
cout<<"9.   - \n";
cout<<"10.  - numOfSiblingPairs() function\n";
cout<<"####################################################################################\n";
int funcNum;
char input = 'y'; char input2 = 'y';
int value; int sib;
node* nodeBST = NULL;
while(input=='y'){
    cout<<"Enter the number of the function to be used = ";
    cin>>funcNum;
    switch(funcNum){                                // Donot declare variables inside the switch case
        case 1 :
            input2 = 'y';
            while(input2=='y'){
                cout<<"Enter the value to be inserted in the binary tree (2) = ";
                cin>>value;
                bt2.insert(value);
                cout<<"Wanna continue? => insert() (y/n) = ";
                cin>>input2;
            }
            cout<<"Printing the updated binary tree (InOrder) = ";
            bt2.inOrder(bt2.returnRoot());
            cout<<"\n";
            break;
        case 2 :
            cout<<"Enter the value to be found in the binary tree (2) = ";
            cin>>value;
            nodeBST = bt2.findNodeBST(bt2.returnRoot(), value);
            if(nodeBST == NULL) cout<<"The element is not present in the binary tree (2)\n";
            else cout<<"The element "<<nodeBST->val<<" is present in the binary tree (2)\n";
            break;
        case 3 :
            input2 = 'y';
            while(input2=='y'){
                cout<<"Enter the value of a node already present and the value to be inserted as left child of that node in the binary tree (2) = ";
                int nodeVal; cin>>nodeVal; cin>>value;
                bt2.insertLeft(nodeVal, value);
                cout<<"Wanna continue? => insertLeft() (y/n) = ";
                cin>>input2;
            }
            cout<<"Printing the updated binary tree (InOrder) = ";
            bt2.inOrder(bt2.returnRoot());
            cout<<"\n";
            break;
        case 4 :
            input2 = 'y';
            while(input2=='y'){
                cout<<"Enter the value of a node already present and the value to be inserted as right child of that node in the binary tree (2) = ";
                int nodeVal; cin>>nodeVal; cin>>value;
                bt2.insertRight(nodeVal, value);
                cout<<"Wanna continue? => insertRight() (y/n) = ";
                cin>>input2;
            }
            cout<<"Printing the updated binary tree (InOrder) = ";
            bt2.inOrder(bt2.returnRoot());
            cout<<"\n";
            break;
        case 5 :
        case 6 :
        case 7 :
        case 8 :
        case 9 :
        case 10 :
            cout<<"The number of sibling pairs in the binary tree (2) is/are = ";
            sib = bt2.numOfSiblingPairs(bt2.returnRoot());
            cout<<sib<<"\n";
            break;
        default :
            cout<<"Not a valid number\n";
            break;
    }
    cout<<"Wanna use another function? (y/n) = ";
    cin>>input;
}

cout<<"End of program";
return 0;
}
