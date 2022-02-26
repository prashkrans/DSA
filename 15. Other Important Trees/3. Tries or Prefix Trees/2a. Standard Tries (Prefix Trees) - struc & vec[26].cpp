/* Trie Problem 1 - LC#208. Implement Trie (Prefix Tree)
A trie (pronounced as "try") or prefix tree is a tree data structure used to efficiently store and reTRIEve keys in a dataset of strings.
There are various applications of this data structure, such as autocomplete and spellchecker.
*/

//  Method 1. Standard trie using a struct node and a vector[26] to store the children.
//  Running time = O(l*m) for insert() and O(l) for search() and startsWith().
//  Auxiliary space = O(l*m) for insert() and O(1) for search() and startsWith().
//  Where, l = average length of the words and m = no. of words

#include<iostream>
#include<vector>
using namespace std;

struct trieNode {				//	Note: There is no need to create a variable char ch to store the value as
	trieNode *children[26];		//  the index itself is sufficient to store the character value of a node.
	bool isCompleteWord;        //  i.e. 0 -> "a", 1 -> "b", ..., 25 -> "z"
	trieNode() {				//	Also, don't forget to have a bool/int variable isCompleteWord or isEndofWord
		for(int i=0; i<26; i++) {	//	to make sure a character marks the end of a word.
			children[i] = NULL;
			isCompleteWord = 0;
		}
	}
};

trieNode *insert(trieNode* root, string s) {
    trieNode *curr = root;
    for(int i=0; i<s.size(); i++) {
        int index = s[i] - 'a';
        if(curr->children[index]==nullptr)
            curr->children[index] = new trieNode;
        curr = curr->children[index];
    }
    curr->isCompleteWord = 1;
    return root;
}

bool search(trieNode* root, string s) {
    trieNode *curr = root;
    for(int i=0; i<s.size(); i++) {
        int index = s[i] - 'a';
        if(curr->children[index]==nullptr) return false;
        curr = curr->children[index];
    }
    if(curr->isCompleteWord==1) return true;       //  The two lines can be condensed as => return (curr->isCompleteWord);
    else return false;
}

void printTrieUtil(trieNode* curr, string s) {          //  Recursive print function (Top-Down approach)
    if(curr==NULL) return;
    else if(curr->isCompleteWord==1) cout<<s<<"\n";
    for(int i=0; i<26; i++) {
        if(curr->children[i]!=nullptr) {
            char ch = i + 'a';                      //  Converts the index of int datatype to its char equivalent
            printTrieUtil(curr->children[i], s+ch);
        }
    }
}

void printTrie(trieNode* root) {
    cout<<"Printing the words of the trie:\n";
    printTrieUtil(root, "");
}

int main() {
	trieNode *root = new trieNode;
	root = insert(root, "see"); root = insert(root, "bear"); root = insert(root, "sell"); root = insert(root, "stock");
	root = insert(root, "see"); root = insert(root, "bull"); root = insert(root, "buy"); root = insert(root, "stock");
	root = insert(root, "bid"); root = insert(root, "stock"); root = insert(root, "bid"); root = insert(root, "stock");
	root = insert(root, "hear"); root = insert(root, "bell"); root = insert(root, "stop");
    trieNode* curr = root; curr = curr->children[1];
	printTrie(root);
	vector<string> key = {"see", "bear", "set", "beam", "stock", "stop", "storm"};
	cout<<"Using the search operation on trie:\n";
	for(int i=0; i<key.size(); i++) {
        if(search(root, key[i])) cout<<key[i]<<" is found in the trie\n";
        else cout<<key[i]<<" is not found in the trie\n";
	}
	return 0;
}
