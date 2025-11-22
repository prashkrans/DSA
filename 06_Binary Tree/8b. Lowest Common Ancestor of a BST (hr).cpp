#include <bits/stdc++.h>
using namespace std;

class Node {
    public:
        int data;
        Node *left;
        Node *right;
        Node(int d) {
            data = d;
            left = NULL;
            right = NULL;
        }
};

class Solution {
    public:
  		Node* insert(Node* root, int data) {
            if(root == NULL) {
                return new Node(data);
            } 
			else {
                Node* cur;
                if(data <= root->data) {
                    cur = insert(root->left, data);
                    root->left = cur;
                } 
				else {
                    cur = insert(root->right, data);
                    root->right = cur;
				}

               return root;
			}
		}

    Node *lca(Node *root, int v1, int v2) {
		int temp = v1;
        if(v1 > v2) {
            v1 = v2;
            v2 = temp;
        }
        if(root==NULL) return root;
        if(root->data > v1 && root->data > v2) 
            return lca(root->left, v1, v2);
        else if(root->data < v1 && root->data < v2)
            return lca(root->right, v1, v2);
        else 
            return root;
    }

}; //End of Solution

int main() {  
    Solution myTree;
    Node* root = NULL;    
    int t;
    int data;
    cin >> t;
    while(t-- > 0) {
        cin >> data;
        root = myTree.insert(root, data);
    }  	
  	int v1, v2;
  	cin >> v1 >> v2;  
    Node *ans = myTree.lca(root, v1, v2);
    cout << ans->data;
    return 0;
}
