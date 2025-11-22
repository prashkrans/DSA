/* AVL Tree Problem #1.2. Insertion in an AVL tree. (Without using the maxDepth function)
Given a AVL tree and N values to be inserted in the tree. Write a function to insert a given value into the tree.
gfg - https://practice.geeksforgeeks.org/problems/avl-tree-insertion/1
*/

//  Method 1.2. Without using the maxDepth function instead using a variable height to store the maxDepth within the node itself.
//  Note: Prefer making leftRot(), rightRot() and rebalance() as node* return type instead of void.
//  Running time = O(log2(n)) or O(height of the tree) where n is the number of nodes.
//  Auxiliary space = O(n) as n nodes are inserted.
#include <bits/stdc++.h>
#define MAXN 2000
using namespace std;

struct Node {
    int data, height;
    Node *left, *right;
    Node(int x) {
        data=x;
        left=right=NULL;
        height=1;
    }
};

bool isBST(Node *n, int lower, int upper) {
	if(!n) return 1;
	if( n->data <= lower || n->data >= upper ) return 0;
	return isBST(n->left, lower, n->data) && isBST(n->right, n->data, upper) ;
}

pair<int,bool> isBalanced(Node* n) {
	if(!n) return pair<int,bool> (0,1);
	pair<int,bool> l = isBalanced(n->left);
	pair<int,bool> r = isBalanced(n->right);
	if( abs(l.first - r.first) > 1 ) return pair<int,bool> (0,0);
	return pair<int,bool> ( 1 + max(l.first , r.first) , l.second && r.second );
}

bool isBalancedBST(Node* root) {
	if( !isBST(root, INT_MIN, INT_MAX) )
        cout<< "BST voilated, inorder traversal : ";
    else if ( ! isBalanced(root).second )
		cout<< "Unbalanced BST, inorder traversal : ";
    else return 1;
	return 0;
}

void printInorder(Node* n) {
	if(!n) return;
	printInorder(n->left);
	cout<<"("<<n->data<<", "<<n->height<<") ";
	printInorder(n->right);
}

class Solution {                            //  Main function begins in the class Solution, and rest could be ignored.
  public:
    int getHeight(Node* node) {
        if(node==NULL) return 0;
        else return node->height;
    }

    bool isBalanced(Node* node) {
        if(node==NULL) return 0;
        int balanceFactor = getHeight(node->left) - getHeight(node->right);
        if(balanceFactor == -1 || balanceFactor == 0 || balanceFactor == 1) return true;
        else return false;
    }

    Node* leftRotate(Node* v, Node* u) {
        Node* temp = v->right;
        v->right = u;
        u->left = temp;
        u->height = 1 + max(getHeight(u->left), getHeight(u->right));   //  First update the height of u then update the height of v. [#IMP]
        v->height = 1 + max(getHeight(v->left), getHeight(v->right));
        return v;
    }

    Node* rightRotate(Node* v, Node* u) {
        Node* temp = v->left;
        v->left = u;
        u->right = temp;
        u->height = 1 + max(getHeight(u->left), getHeight(u->right));   //  First update the height of u then update the height of v. [#IMP]
        v->height = 1 + max(getHeight(v->left), getHeight(v->right));
        return v;
    }

    Node* rebalance(Node* node, int data) {
        Node* z = node;
        Node* y = NULL;
        Node* x = NULL;
        if(data > z->data) y = z->right;
        else y = z->left;
        if(data > y->data) x = y->right;
        else x = y->left;
        if(y==z->left && x==y->left) {
            //cout<<"LL\n";
            y = leftRotate(y, z);   z = y->right;
            node = y;
        }
        else if(y==z->right && x==y->right) {
            //cout<<"RR\n";
            y = rightRotate(y, z);  z = y->left;
            node = y;
        }
        else if(y==z->left && x==y->right) {
            //cout<<"LR\n";
            x = rightRotate(x, y);  y = x->left;
            x = leftRotate(x, z);   z = x->right;
            node = x;
        }
        else if(y==z->right && x==y->left) {
            //cout<<"RL\n";
            x = leftRotate(x, y);   y = x->right;
            x = rightRotate(x, z);  z = x->left;
            node = x;
        }
        return node;
    }

    Node* insertToAVL(Node* node, int data) {
        if(node==NULL) return new Node(data);
        if(data > node->data) node->right = insertToAVL(node->right, data);
        else if(data < node->data)node->left = insertToAVL(node->left, data);
        else return node;
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));      //  After insertion of any node, the height of all its ancestors should be updated here.
        if(!isBalanced(node)) node = rebalance(node, data);
        return node;
    }
};

int main() {
	int ip[MAXN];
    int t;
    cin>>t;
    while(t--) {
        int n;
        cin>>n;
        for(int i=0; i<n; i++) cin>> ip[i];
        Node* root = NULL;
        Solution obj;
        for(int i=0; i<n; i++) {
            root = obj.insertToAVL( root, ip[i] );
            if (!isBalancedBST(root)) break;
        }
        printInorder(root);
        cout<< endl;
    }
    return 0;
}
