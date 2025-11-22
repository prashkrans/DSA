/* Prob. 1a. Huffman Encoding
Given a string S of distinct character of size N and their corresponding frequency f[ ] i.e. character S[i] has f[i] frequency.
Your task is to build the Huffman tree print all the huffman codes in preorder traversal of the tree.
Note: If two elements have same frequency, then the element which occur at first will be taken on the left of Binary Tree and
other one to the right.

gfg - https://practice.geeksforgeeks.org/problems/huffman-encoding3345/1/#
*/

//	Running time = O(nlog2n) where n is the number of distinct characters in the given text
//	Auxiliary space = O(m) = O(n.c) ~ O(n) where c is the max no. of bits for a character and is constant

#include<bits/stdc++.h>
using namespace std;

class Solution {
struct node {
    char ch;
    int freq;
    node *left, *right;
    node() : left(NULL), right(NULL) {}
    node(char ch_, int freq_) : ch(ch_), freq(freq_), left(NULL), right(NULL) {}
};
class cmp {
public:
    bool operator() (node *a, node *b) {
        return a->freq > b->freq;
    }
};
node *hRoot;
map<char, string> HuffmanTable;							//	Private data members are node, cmp, hRoot and HuffmanTable
public:
    void buildHuffmanTable(node *root, string s) {
        if(root->left==NULL && root->right==NULL) {
            HuffmanTable.insert({root->ch, s});
            return;
        }
        buildHuffmanTable(root->left, s+'0');
        buildHuffmanTable(root->right, s+'1');
    }

	vector<string> huffmanCodes(string S, vector<int> f, int N) {
	    vector<string> res;
	    priority_queue<node*, vector<node*>, cmp> minHeap;
	    for(int i=0; i<S.size(); i++) {
	        node *newNode = new node(S[i], f[i]);
	        minHeap.push(newNode);
	    }
	    while(minHeap.size()!=1) {
	        node *left = minHeap.top();
	        minHeap.pop();
	        node *right = minHeap.top();
	        minHeap.pop();
	        node *mergedNode = new node;
	        mergedNode->freq = left->freq + right->freq;
	        mergedNode->left = left;
	        mergedNode->right = right;
	        minHeap.push(mergedNode);
	    }
	    hRoot = minHeap.top();
	    buildHuffmanTable(hRoot, "");
	    for(auto i : HuffmanTable) res.push_back(i.second);
	    sort(res.begin(), res.end());
	    return res;
	}
};

int main(){
    int T;
    cin >> T;
    while(T--) {
	    string S;
	    cin >> S;
	    int N = S.length();
	    vector<int> f(N);
	    for(int i=0;i<N;i++){
	        cin>>f[i];
	    }
	    Solution ob;
	    vector<string> ans = ob.huffmanCodes(S,f,N);
	    for(auto i: ans)
	    	cout << i << " ";
	    cout << "\n";
    }
	return 0;
}

/* Sample input:
1
abc
5 2 1
*/
