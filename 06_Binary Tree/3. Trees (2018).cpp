Typical binary tree structure:

struct node{
	int data;
	node* left;
	node* right;
};

node* newNode(int data){    // Helper function newNode() for creating new cell
	node* newptr=new node;  newptr->data=data;  newptr->left=NULL;  newptr->right=NULL;
	return newptr;
}

The insert function as node* insert(node* root, int data)

Things to keep in mind for binary trees:
void or node* or int function_name(node* root){
    if (root==NULL)             // Always take care of base case i.e root==NULL
    return; or [return NULL; or return newNode(val);] or return 0;
    else{
        <block of code> // Preorder
        function_name(root->left); // The end case should be taken care by the base case
        function_name(root->right); // The end case should be taken care by the base case
        //<block of code> Postorder i.e generally preorder or postorder (Depends on the question)
        // No need to return for void
        or
        <block of code>
        root->left = function_name(root->left);    // for node* function_name()
        root->right = function_name(root->right); // for node* function_name()
        return root;    // need to return root
        //block of code
        or
        return (return(size(root->left) + 1 + size(root->right)); // return as int
    }
}



Two methods of traversal :-
1.	BFS (Level order traversal) - Queue
2.	DFS (a. Inorder b. Preorder c. Postorder) – Stack
It is evident from above points that extra space required for Level order traversal is likely to be more when tree is more balanced and
extra space for Depth First Traversal is likely to be more when tree is less balanced.
The most important points is, BFS starts visiting nodes from root while DFS starts visiting nodes from leaves. So if our problem is to
search something that is more likely to closer to root, we would prefer BFS. And if the target node is close to a leaf, we would prefer DFS.

If height = n, then total number of nodes in a binary tree = 2^(n+1)-1

Divided in two parts to improve readability:- Part I - Trees + Few BST functions   Part II – mainly BST

Part I
#include <iostream>
using namespace std;

struct node
    {int data;
    node* left;
    node* right;
    };
////////////////////////////////////////////////////
int count=0;
int size_my(node* root) // Pre-order
    {if (root==NULL)
        {return count;}
     else
         {count++;//cout<<"asdf"<<count;
         count=size_my(root->left);
         count=size_my(root->right);
         }
     return count;
    }
///////////////////////////////////////////////////
int size(node* root)  // In-order
    {if (root==NULL)
        {return 0;}
     else
         {return (size(root->left)+1+size(root->right));
         }
    }

node* newNode(int data) // Helper function to
    {node* ptr=new node;    // new node
    ptr->data=data;
    ptr->left=NULL;
    ptr->right=NULL;
    return ptr;}

int max_depth(node* root) // No. of nodes in the longest branch
    {if (root==NULL)
        {return 0;}
     else
        {int l=max_depth(root->left);
         int r=max_depth(root->right);
         if (l>r)
             {return l+1;}
         else
            {return r+1;}
        }
    }

int maxm=INT_MIN;        // Recursive
int max_val(node* root) // Max val of a binary search tree
    {if (root->right==NULL)
        {maxm=root->data;
         cout<<"The maximum value of tree = ";
        return maxm;}
     else
        {return max_val(root->right);
        }
    }

int min_val(node* root) // Min val of a binary search tree
    {if (root==NULL)    // Iterative
        {cout<<"The tree is empty";
        return (-1);}
     else
        {
        node* curr=root;
        while(curr->left!=NULL)
            {curr=curr->left;}
        cout<<"The minimum value of tree = ";
        return(curr->data);
        }
    }

void print_inorder(node* root) // Recursive inorder printing of
    {if (root==NULL) return;    // tree elements

     else {print_inorder(root->left);
           cout<<root->data<<" ";
           print_inorder(root->right);}
    }

void print_preorder(node* root) // Recursive preorder printing of
    {if (root==NULL)            // tree elements
        {return;}
    else {cout<<root->data<<" ";
         print_preorder(root->left);
         print_preorder(root->right);}
    }

void print_postorder(node* root) // Recursive postorder printing of
    {if (root==NULL) return;    // tree elements

     else {print_postorder(root->left);
           print_postorder(root->right);
           cout<<root->data<<" ";}
    }

void print_onelevel(node* root,int level) // BFS - Level by level
    {if (root==NULL)        // Level 0, 1, 2, and 3 for height = 3
        {return;}
     if (level==0)
         {cout<<root->data<<" ";}
     else if (level>0)
        {print_onelevel(root->left,level-1);
         print_onelevel(root->right,level-1);}
    }

void print_BFS(node* root)
    {int height = max_depth(root)-1; // Height is one less than no. of nodes
    for (int i=0;i<=height;i++)     // in the longest branch
        {print_onelevel(root,i);
        }
    }


int main()
    {
    node* root=new node;
    root=newNode(6);
    root->left=newNode(4);
    root->right=newNode(8);
    root->right->right=newNode(9);
    root->right->left=newNode(7);
    root->left->right=newNode(5);
    root->left->left=newNode(2);
    root->left->left->right=newNode(3);
    root->left->left->left=newNode(1);
    root->left->left->left->left=newNode(0);
    cout<<"The size of the tree is = "<<size(root)<<endl;
    cout<<max_val(root)<<endl;
    cout<<min_val(root)<<endl;
    cout<<"The level by level print (BFS) ";
    print_BFS(root);
    cout<<endl;
    cout<<"Inorder print ";
    print_inorder(root);
    cout<<endl;
    cout<<"Preorder print ";
    print_preorder(root);
    cout<<endl;
    cout<<"Postorder print ";
    print_postorder(root);
    cout<<endl;
    return 0;
}

#####################################################################################################

Part II (Plain and Ordered Binary Trees)
#include <iostream>
using namespace std;

struct node{
	int data;
	node* left;
	node* right;
};

node* newNode(int data){    // Helper function newNode() for creating new cell
	node* newptr=new node;
	newptr->data=data;
	newptr->left=NULL;
	newptr->right=NULL;
	return newptr;
}

node* insert(node* root, int data){ // To insert data in a binary search tree
    if (root==NULL)                 // Note we are not breaking any branch, instead just adding new nodes accordingly
        return newNode(data);
    else {
        if (data > root->data)
            root->right=insert(root->right,data);
        else
            root->left=insert(root->left,data);
        return root;
    }
}

node* build123(){	     // Write code that builds the following little 1-2-3 binary search tree...
	node* root=newNode(2);
	node* left_child=newNode(1);
	node* right_child=newNode(3);
	root->left=left_child;
	root->right=right_child;
	return root;
}

int size(node* root){    // To determine the no. of nodes in a BST. (Same as above)
    if (root==NULL){
        return 0;
    }
    else {
    return(size(root->left)+1+size(root->right));
    }
}

int max_depth(node* root){    //Given a binary tree, compute its "maxDepth" -- the number of nodes
    if (root==NULL)           //along the longest path from the root node down to the farthest leaf node.
        return 0;
    else {
        int left_depth = max_depth(root->left);
        int right_depth = max_depth(root->right);
        if(left_depth>right_depth)
            return (left_depth+1);
        else return (right_depth+1);
    }
}

int count=0; //Usage of global variables
int max=0;
void max_depth(node* root){     // Same as above max_depth function but with the usage of global variables
    if (root==NULL){
        if(::count>::max) ::max=::count;
        return;
    }
    else {
        ::count++;
        max_depth(root->left);
        max_depth(root->right);
        ::count--;
    }
}

int min_val(node* root){  // Find the minimum element in a BST recursively.
    if (root==NULL)
        return -1;
    else if (root->left==NULL)
        return root->data;
    else {
        return min_val(root->left);
    }
}

int max_val(node* root){  // Find the maximum element in a BST iteratively.
    if(root==NULL)
        return -1;
    node* curr=root;
    while(curr->right!=NULL){
        curr=curr->right;
    }
    return curr->data;
}

void print_inorder_BST(node* root){ // Inorder traversal left,node,right
    if (root==NULL){
        return;
    }
    else {
        print_inorder_BST(root->left);
        cout<<root->data<<" ";
        print_inorder_BST(root->right);
    }
}

void print_postorder_BST(node* root){ // Post traversal left,right,node
    if (root==NULL){
        return;
    }
    else {
        print_postorder_BST(root->left);
        print_postorder_BST(root->right);
        cout<<root->data<<" ";
    }
}

//  Given a tree and a sum, return true if there is a path from the root down to a leaf,
//  such that adding up all the values along the path equals the given sum.
//  Strategy: subtract the node value from the sum when recurring down,
//  and check to see if the sum is 0 when you run out of tree.

bool has_path_sum(node* root, int sum){
    if (root==NULL)
        return (sum==0);
    else{
        int sub_sum = sum - root->data;
        return(has_path_sum(root->left, sub_sum)||has_path_sum(root->right, sub_sum));
    }
}


void mirror(node* root){ // Mirror image of a given tree.
    if (root==NULL){
        return;
    }
    else {
        mirror(root->left);
        mirror(root->right);
        node* temp=root->left;
        root->left=root->right;
        root->right=temp;
    }

node* double_tree(node* root){  // For each node in a binary search tree,  create a new duplicate node,
    if (root==NULL)             // and insert  the duplicate as the left child of the original node.
        return NULL;            // The resulting tree should still be a binary search tree.
    else {                      // void type function can also be used here as it was used for mirror()
        root->left=double_tree(root->left);
        root->right=double_tree(root->right);
        node* temp=root->left;
        root->left=newNode(root->data);
        root->left->left=temp;
        return root;
    }
}

bool same_BST_tree(node* a, node* b){   // Given two binary trees, return true if they are structurally identical
    if(a==NULL&&b==NULL)                // i.e. they are made of nodes with the same values arranged in the same way.
        return true;
    else if ((a==NULL&&b!=NULL)||(a!=NULL&&b==NULL))
        return false;
    else {
    return (same_BST_tree(a->left, b->left)&&same_BST_tree(a->right, b->right)&&(a->data==b->data));
    }
}

int main(){
    // node* root=new node;
    // root=newNode(7);
    // root->left=newNode(5);
    // root->right=newNode(9);
    // root->right->right=newNode(10);
    // root->right->left=newNode(8);
    // root->left->right=newNode(6);
    // root->left->left=newNode(3);
    // root->left->left->right=newNode(4);
    // root->left->left->left=newNode(2);
    // root->left->left->left->left=newNode(1);
    // root->right->right->right=newNode(15);
    // root->right->right->right->left=newNode(12);
    // root->right->right->right->left->left=newNode(11);
    // root->right->right->right->left->right=newNode(13);
    // root->right->right->right->left->right->right=newNode(14);
    // OR Using insert function
    node* root=insert(root,7);
    root=insert(root,5);    root=insert(root,9);    root=insert(root,10);    root=insert(root,8);
    root=insert(root,6);    root=insert(root,3);    root=insert(root,4);     root=insert(root,2);
    root=insert(root,1);    root=insert(root,15);   root=insert(root,12);    root=insert(root,11);
    root=insert(root,13);   root=insert(root,14);
    cout<<size(root);
    cout<<endl;
    max_depth2(root);
    cout<<::max<<endl;
    cout<<max_depth(root)<<endl;
    cout<<min_val(root)<<" "<<max_val(root)<<endl;
    print_inorder_BST(root);
    cout<<endl;
    print_postorder_BST(root);
    cout<<endl;
    cout<<"HasPathSum ";
    cout<<(has_path_sum(root,18))?"true":"false"; cout<<" "<<(has_path_sum(root,19))?"true":"false";
    cout<<" "<<(has_path_sum(root,64))?"true":"false"; cout<<" "<<(has_path_sum(root,80))?"true":"false";
    cout<<" "<<(has_path_sum(root,25))?"true":"false"; cout<<" "<<(has_path_sum(root,90))?"true":"false";
    cout<<endl;
    mirror(root);
    cout<<"Mirror image inorder = "<<endl;
    print_inorder_BST(root);
    cout<<endl;
    root=double_tree(root);
    print_inorder_BST(root);
    node* a=insert(a,4);    node* b=insert(b,4);
    a=insert(a,2);          b=insert(b,2);
    a=insert(a,5);          b=insert(b,5);
    a=insert(a,7);          b=insert(b,7);    // b=insert(b,8); for false
    a=insert(a,6);          b=insert(b,6);
    a=insert(a,1);          b=insert(b,1);
    a=insert(a,3);          b=insert(b,3);
    cout<<endl<<"Same BST = "<<same_BST_tree(a,b);

    return 0;
}
