// { Driver Code Starts
//

#include <bits/stdc++.h>
using namespace std;

struct Node
{
	int data, height;
	Node *left, *right;
	Node(int x)
	{
		data = x;
		height = 1;
		left = right = NULL;
	}
};

int setHeights(Node* n)
{
	if(!n) return 0;
	n->height = 1 + max( setHeights(n->left) , setHeights(n->right) );
	return n->height;
}

Node* buildTree(string str)
{   
    // Corner Case
    if(str.length() == 0 || str[0] == 'N')
            return NULL;
    
    // Creating vector of strings from input 
    // string after spliting by space
    vector<string> ip;
    
    istringstream iss(str);
    for(string str; iss >> str; )
        ip.push_back(str);
        
    // Create the root of the tree
    Node* root = new Node(stoi(ip[0]));
        
    // Push the root to the queue
    queue<Node*> queue;
    queue.push(root);
        
    // Starting from the second element
    int i = 1;
    while(!queue.empty() && i < ip.size()) {
            
        // Get and remove the front of the queue
        Node* currNode = queue.front();
        queue.pop();
            
        // Get the current node's value from the string
        string currVal = ip[i];
            
        // If the left child is not null
        if(currVal != "N") {
                
            // Create the left child for the current node
            currNode->left = new Node(stoi(currVal));
                
            // Push it to the queue
            queue.push(currNode->left);
        }
            
        // For the right child
        i++;
        if(i >= ip.size())
            break;
        currVal = ip[i];
            
        // If the right child is not null
        if(currVal != "N") {
                
            // Create the right child for the current node
            currNode->right = new Node(stoi(currVal));
                
            // Push it to the queue
            queue.push(currNode->right);
        }
        i++;
    }
    
    setHeights(root);
    return root;
}

bool isBST(Node *n, int lower, int upper)
{
	if(!n) return 1;
	if( n->data <= lower || n->data >= upper ) return 0;
	return isBST(n->left, lower, n->data) && isBST(n->right, n->data, upper) ;
}

pair<int,bool> isBalanced(Node* n)
{
	if(!n) return pair<int,bool> (0,1);

	pair<int,bool> l = isBalanced(n->left);
	pair<int,bool> r = isBalanced(n->right);

	if( abs(l.first - r.first) > 1 ) return pair<int,bool> (0,0);

	return pair<int,bool> ( 1 + max(l.first , r.first) , l.second && r.second );
}

bool isBalancedBST(Node* root)
{
	if( !isBST(root, INT_MIN, INT_MAX) )
		cout<< "BST voilated, inorder traversal : ";

	else if ( ! isBalanced(root).second )
		cout<< "Unbalanced BST, inorder traversal : ";

	else return 1;
	return 0;
}

void printInorder(Node* n)
{
	if(!n) return;
	printInorder(n->left);
	cout<< n->data << " ";
	printInorder(n->right);
}

struct Node* deleteNode(struct Node* root, int data);

int main()
{
	int t;
	cin>>t;
	getchar();

	while(t--)
	{
		string s;
		getline(cin,s);
		Node* root = buildTree(s);
        
		int n;
		cin>> n;
		int ip[n];
		for(int i=0; i<n; i++)
			cin>> ip[i];
        
		for(int i=0; i<n; i++)
		{
			root = deleteNode(root, ip[i]);
			
			if( !isBalancedBST(root) )
				break;
		}
        
		if(root==NULL)
			cout<<"null";
		else
			printInorder(root);
		cout<< endl;
        
		getline(cin,s); // to deal with newline char
	}
	return 1;
}
// } Driver Code Ends

/* Node is as follows:

struct Node
{
	int data, height;
	Node *left, *right;
	Node(int x)
	{
		data = x;
		height = 1;
		left = right = NULL;
	}
};

*/
int getHeight(Node *root) {
    if(root==NULL) return 0;
    return root->height;
}

bool isNodeBalanced(Node *root) {                   //  Checks whether the current Node is balanced or not.
    if(root==NULL) return true;                 //  If a Node is NULL, return true as empty Node is considered balanced.
    int balanceFactor = getHeight(root->left) - getHeight(root->right);
    if(balanceFactor == -1 || balanceFactor == 0 || balanceFactor == 1) return true;
    else return false;
}

Node* leftRotation(Node *v, Node *u) {          //  Only two different rotations are needed hence, define the left and the right rotations.
    Node *temp = v->right;
    v->right = u;
    u->left = temp;
    u->height = 1 + max(getHeight(u->left), getHeight(u->right));
    v->height = 1 + max(getHeight(v->left), getHeight(v->right));
    return v;
}

Node* rightRotation(Node *v, Node *u) {
    Node *temp = v->left;
    v->left = u;
    u->right = temp;
    u->height = 1 + max(getHeight(u->left), getHeight(u->right));
    v->height = 1 + max(getHeight(v->left), getHeight(v->right));
    return v;
}

Node* rebalanceDeletion(Node *root) {
    Node *z = root;
    Node *y = NULL;
    Node *x = NULL;
    if(getHeight(z->left) > getHeight(z->right)) y = z->left;
    else y = z->right;
    if(getHeight(y->left) >= getHeight(y->right)) x = y->left;
    else x = y->right;
    //cout<<"z = "<<z->val<<" y = "<<y->val<<" x = "<<x->val<<" => ";
    if(y==z->left && x==y->left) {
        //cout<<"Left left rotation required:\n";
        y = leftRotation(y, z);     z = y->right;   root = y;
    }
    else if(y==z->right && x==y->right) {
        //cout<<"Right right rotation required:\n";
        y = rightRotation(y, z);    z = y->left;    root = y;
    }
    else if(y==z->left && x==y->right) {
        //cout<<"Left right rotation required:\n";
        x = rightRotation(x, y);    y = x->left;
        x = leftRotation(x, z);     z = x->right;   root = x;
    }
    else if(y==z->right && x==y->left) {
        //cout<<"Right left rotation required:\n";
        x = leftRotation(x, y);     y = x->right;
        x = rightRotation(x, z);    z = x->left;   root = x;
    }
    //cout<<"After restructuring: z = "<<z->val<<" y = "<<y->val<<" x = "<<x->val<<" => ";
    //printPreorder(root); cout<<"\n";
    return root;
}

Node* deleteNode(Node* root, int data) {
    if(root==NULL) return root;
    if(root->data > data) root->left = deleteNode(root->left, data);
    else if(root->data < data) root->right = deleteNode(root->right, data);            //  Recursion finds if a Node x with value == data exists
    else {                                                              //  i.e. if(root->data==val)
        //cout<<"Deleting the Node with value = "<<data<<"\n";
        if(root->left==NULL && root->right == NULL) {                   //  Case 1. x has no children
            delete root;                                                //  delete keyword destroys the value or memory block pointed by pointer and not the pointer itself.
            root = NULL;                                                //  After deleting the contents of root, it is made NULL
        }
        else if(root->left==NULL || root->right==NULL) {                //  Case 2. x has a single child
            Node *child = NULL;                                         //  Here, root is modified and made a copy of its child
            if(root->left==NULL) child = root->right;                   //  Also, we don't delete root here but delete its child
            else child = root->left;
            root->data = child->data;                                     //  Don't use root = child; as we are deleting the child. Had we not used delete we could have used root = child.
            root->left = child->left;
            root->right = child->right;
            delete child;
        }
        else {                                                          //  Case 3. x has two children => both root->left and root->right exist.
            Node* successor = root->right;                              //  Here, root is modified s.t. it stores the value of its successor, its left child is unchanged and right child is
            while(successor->left!=NULL) successor = successor->left;   //  made the right subtree minus the successor Node. So, we don't delete root here but delete the successor.
            root->data = successor->data;
            root->right = deleteNode(root->right, successor->data);
        }
    }
    if(root!=NULL) root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    if(!isNodeBalanced(root)) {                                             //  Add the below 4 lines to the delete function of a BST to make it the delete function of an AVL tree.
        //cout<<root->val<<" is not balanced\n";
        root = rebalanceDeletion(root);
    }
    
    return root;                                                        //
}