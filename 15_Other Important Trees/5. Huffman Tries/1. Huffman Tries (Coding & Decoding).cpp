/* Prob. 1. Huffman Encoding and Decoding. (My method)
Huffman Encoding:
1. Create a priority queue PQ consisting of each unique character and its frequency.
2. Create a new node
3. Extract 2 minimum values from PQ
4. Calculate the sum of frequency of these two minimum values and assign it to the frequency of new node
5. Assign 1st minimum node as left child and, 2nd minimum node as right child of the newly created node
6. Insert this new node back into PQ
7. Repeat {2. to 6.} till there is only one node left in PQ
8. Remaining last node in PQ is our Huffman tree's root node [#Imp]

Running time = O(nlog2n) where n is the number of characters in the given text
Auxiliary space = O(m)

Huffman Decoding
1. Start from root node and move to left child for '0' and right child for '1'
2. As soon as leaf node is encountered, append its character to our output string.
3. Repeat {1. to 2.} till we reach end of the shortUrl string.

Running time = O(m) where m is the number of bits in the given encoded text.
Auxiliary space = O(n)
*/

//	Method 1. Using a class to represent HuffmanCodec.
//	Method 2. Without using a class but making variables such as hRoot, origText, HuffmanTable global so that
//	they could be used in mulitple functions without passing them as parameters.

#include<iostream>
#include<queue>
#include<map>
using namespace std;

struct node {
	char ch;
	int freq;
	node *left;
	node *right;
	node() : left(NULL), right(NULL) {}
};

class cmp {
public:
    bool operator()(node *a, node *b) const {
        return a->freq > b->freq;
    }
};

class HuffManCodec {
    string origText;
    node *hRoot;
public:
    HuffManCodec(string s) : origText(s), hRoot(NULL) {}

    void printInorder(node *root) {
        if(root==NULL) return;
        printInorder(root->left);
        cout<<root->freq<<" ";
        printInorder(root->right);
    }

    void buildHuffmanTable(node *root, string s, map<char, string> &HuffManTable) {
        if(root->left==NULL&&root->right==NULL) {
            cout<<"("<<root->ch<<", "<<root->freq<<") = "<<s<<"\n";
            HuffManTable[root->ch] = s;
            return;
        }
        if(root->left!=NULL) buildHuffmanTable(root->left, s+'0', HuffManTable);
        if(root->right!=NULL) buildHuffmanTable(root->right, s+'1', HuffManTable);
    }

    node *buildHuffmanTrie(string s) {
        priority_queue<node*, vector<node*>, cmp> minHeap;
        map<char, int> freqMp;
        for(int i=0; i<s.size(); i++) freqMp[s[i]]++;
        for(auto m : freqMp) {
            node *newNode = new node;
            newNode->ch = m.first;
            newNode->freq = m.second;
            minHeap.push(newNode);
        }
        node *root = NULL;
        while(minHeap.size()>1) {
            root = new node;
            node *left = minHeap.top(); minHeap.pop();
            node *right = minHeap.top(); minHeap.pop();
            root->freq = left->freq + right->freq;
            root->left = left;
            root->right = right;
            minHeap.push(root);
        }
        return root;
    }

    string HuffmanEncoding(string s) {
        hRoot = buildHuffmanTrie(s);
        map<char, string> HuffManTable;
        string code;
        printInorder(hRoot); cout<<"\n";
        buildHuffmanTable(hRoot, "", HuffManTable);             //  We can use "" or {} to denote an empty string
        for(auto mp : HuffManTable) cout<<mp.first<<" "<<mp.second<<"\n";
        for(int i=0; i<s.size(); i++)
            code = code + HuffManTable[s[i]];
        return code;
    }

    void HuffManDecUtil(string s, node *root, string &decText) {        //  Recursive Huffman Decoding
        if(root->left==NULL && root->right==NULL) {
            decText = decText + root->ch;
            HuffManDecUtil(s, hRoot, decText);      //  Remember to not advance s when leaf node is found.
            return;
        }
        if(s[0]=='0') HuffManDecUtil(s.substr(1), root->left, decText);
        else if(s[0]=='1') HuffManDecUtil(s.substr(1), root->right, decText);
    }

    string HuffmanDecoding(string s) {
        string decText;
        HuffManDecUtil(s, hRoot, decText);
        return decText;
    }
};


int main() {
	string s;
	s = "ABRACADABRA";
	HuffManCodec h1(s);
	string code = h1.HuffmanEncoding(s);
	cout<<"Encoded text = "<<code<<"\n";
	string decodedText = h1.HuffmanDecoding(code);
	cout<<"Decoded text = "<<decodedText<<"\n";
	return 0;
}


