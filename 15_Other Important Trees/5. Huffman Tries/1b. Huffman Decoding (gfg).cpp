/* Prob. 1b. Huffman Decoding
Given a string S, implement Huffman Encoding and Decoding.
We don't need to read input or print anything but complete the function decode_file(), which takes root of the
tree formed while encoding and the encoded string as the input parameters and returns the decoded string.

Note: Everthing except decod_file was written by gfg.
Here, iterative version of decod_file is used instead of the recursive one as Prob. 1.1.

Example 1:
Input : abc =>10110
Output : abc (from 10110)


gfg - https://practice.geeksforgeeks.org/problems/huffman-decoding-1/1/#
*/

//	Running time = O(m) where m is the no. of bits in the encoded text
//	Auxiliary space = O(n) where n is the no. of leaves/characters in the encoding trie

#include <bits/stdc++.h>
#define MAX_TREE_HT 256
using namespace std;
map<char, string> codes;		//	Used to create the Huffman table
map<char, int> freq;			//	Used to store the frequencies of the characters
struct MinHeapNode {
    char data;
    int freq;
    MinHeapNode *left, *right;
    MinHeapNode(char data, int freq)
    {
        left = right = NULL;
        this->data = data;
        this->freq = freq;
    }
};
struct compare {
    bool operator()(MinHeapNode* l, MinHeapNode* r) {
        return (l->freq > r->freq);		//	To get the node with minimum frequency
    }
};
priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;	//	minHeap using the STL priority_queue

void printCodes(struct MinHeapNode* root, string str) {
    if (!root) return;
    if (root->data != '$')
        cout << root->data << ": " << str << "\n";
    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}

void storeCodes(struct MinHeapNode* root, string str) {	//	Trivial DFS on a binary tree
    if (root==NULL)
        return;
    if (root->data != '$')								//	This implies the node is a leaf node and has a char as value instead of '$'
        codes[root->data]=str;
    storeCodes(root->left, str + "0");
    storeCodes(root->right, str + "1");
}

void HuffmanCodes(int size) {
    struct MinHeapNode *left, *right, *top;
    for (map<char, int>::iterator v=freq.begin(); v!=freq.end(); v++)
        minHeap.push(new MinHeapNode(v->first, v->second));
    while (minHeap.size() != 1) {
        left = minHeap.top();
        minHeap.pop();
        right = minHeap.top();
        minHeap.pop();
        top = new MinHeapNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        minHeap.push(top);
    }
    storeCodes(minHeap.top(), "");						// Finally builds the Huffman trie
}

void calcFreq(string str, int n) {						// Calculates the frequency of characters in the text
    for (int i=0; i<str.size(); i++)
        freq[str[i]]++;
}

string decode_file(struct MinHeapNode* root, string s); // Declaration here, defined later

int main() {
	int t;
	cin>>t;
	while(t--){
		codes.clear();
		freq.clear();
		minHeap=priority_queue <MinHeapNode*, vector<MinHeapNode*>, compare>();
		string str;
		cin>>str;
		string encodedString, decodedString;
		calcFreq(str, str.length());
		HuffmanCodes(str.length());
		/*cout << "Character With there Frequencies:\n";
		for (auto v=codes.begin(); v!=codes.end(); v++)
			cout << v->first <<' ' << v->second << endl;*/
		for (auto i: str)
			encodedString+=codes[i];
		//cout <</* "\nEncoded Huffman data:\n" << */encodedString << endl;
		decodedString = decode_file(minHeap.top(), encodedString);
		cout <</* "\nDecoded Huffman Data:\n" << */decodedString << endl;
	}
    return 0;
}
/*Complete the function below
Which contains 2 arguments
1) root of the tree formed while encoding
2) Encoded String*/
string decode_file(struct MinHeapNode* root, string s) {	//	There could be an iterative as well as a recursive decode_file
    string decS;
    MinHeapNode *curr = root;
    for(int i=0; i<s.size(); i++) {
        if(s[i]=='0') curr = curr->left;
        else if(s[i]=='1') curr = curr->right;
        if((curr->left==NULL && curr->right==NULL)) {
            decS = decS + curr->data;
            curr = root;
        }
    }
    return decS;
}

/* Sample input
1
abcdef
*/
