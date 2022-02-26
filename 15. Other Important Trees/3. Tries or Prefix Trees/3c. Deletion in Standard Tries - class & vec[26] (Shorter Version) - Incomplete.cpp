/* Trie Problem 2 - Deletion in Standard Tries (Prefix Trees)
A trie (pronounced as "try") or prefix tree is a tree data structure used to efficiently store and reTRIEve keys in a dataset of strings.
There are various applications of this data structure, such as autocomplete and spellchecker.
*/

//  Method 1. Standard trie using a class trie, a struct node and a vector[26] to store the children.
//  Running time = O(l*m) for deletion.
//  Auxiliary space = O(1) for deletion.
//  Where, l = average length of the words and m = no. of words

#include<iostream>
#include<vector>
using namespace std;

struct trieNode {
	trieNode *children[26];		//  Note, here index itself is used to store the character value of a node.
	bool isCompleteWord;        //  i.e. 0 -> "a", 1 -> "b", ..., 25 -> "z"
	trieNode() {
		for(int i=0; i<26; i++) {
			children[i] = NULL;
			isCompleteWord = 0;
		}
	}
};

class trie {
    trieNode *root;
public:
    trie() {
        root = new trieNode();
    }
    void *insert(string s) {
        trieNode *curr = root;
        for(int i=0; i<s.size(); i++) {
            int index = s[i] - 'a';
            if(curr->children[index]==NULL) curr->children[index] = new trieNode;
            curr = curr->children[index];
        }
        curr->isCompleteWord = 1;
    }
    bool search(string s) {
        trieNode *curr = root;
        for(int i=0; i<s.size(); i++) {
            int index = s[i] - 'a';
            if(curr->children[index]==NULL) return 0;
            curr = curr->children[index];
        }
        return (curr->isCompleteWord);
    }
    void printTrieUtil(trieNode* curr, string s) {          //  Recursive print function (Top-Down approach)
        if(curr==NULL) return;
        if(curr->isCompleteWord==1) cout<<s<<"\n";
        for(int i=0; i<26; i++) {
            if(curr->children[i]!=nullptr) {
                char ch = i + 'a';                          //  Converts the index of int datatype to its char equivalent
                printTrieUtil(curr->children[i], s+ch);
            }
        }
    }
    void printTrie() {
        cout<<"Printing the words of the trie:\n";
        printTrieUtil(root, "");
    }
    trieNode *deleteUtil(trieNode *curr, string s, int k) {
        if(k==s.size()) {                   //  This implies that the word is found either as a leaf node or an internal node
            bool hasChild = 0;
            for(int i=0; i<25; i++) {
                if(curr->children[i]!=NULL) {
                    hasChild = 1;
                    break;
                }
            }
            if(hasChild==0) {               //  If the hasChild == 0 the last character is a leaf node
                delete curr;                //  So, we can simply delete the leaf node and then return NULL;
                curr = NULL;
            }
            else if(hasChild) {
                //  cout<<"Unmarking\n";    //  If the hasChild == 1 the last character is not a leaf node
                curr->isCompleteWord = 0;   //  In this case only unmarking is sufficient to delete that word
            }
            return curr;
        }
        int index = s[k] - 'a';
        curr->children[index] = deleteUtil(curr->children[index], s, k+1);
        else return curr;
        bool hasChild = 0;
        for(int i=0; i<25; i++) {           //  The same process is used here as we need to continue deleting nodes if it becomes
            if(curr->children[i]!=NULL) {   //  a leaf node and is not the last character of any other word
                hasChild = 1;
                break;
            }
        }
        if(hasChild==0 && curr==0) {
            delete curr;
            curr = NULL;
        }
        return curr;
    }
    void deleteKey(string s) {
        cout<<"Deleting the string: "<<s<<"\n";
        string::iterator it = s.begin();
        deleteUtil(root, s, 0);
    }

};

int main() {
    trie *t = new trie();
	t->insert("hear"); t->insert("bid"); t->insert("big"); t->insert("been");
	t->insert("stopped"); t->insert("stop"); t->insert("storm"); t->insert("stock");
	t->insert("beam"); t->insert("bear"); t->insert("bee"); t->insert("be");
	t->printTrie();
	vector<string> key = {"see", "bear", "set", "beam", "stock", "stop", "storm"};
	cout<<"Using the search operation on trie:\n";
	for(int i=0; i<key.size(); i++) {
        if(t->search(key[i])) cout<<key[i]<<" is found in the trie\n";
        else cout<<key[i]<<" is not found in the trie\n";
	}
	t->deleteKey("hear");
	t->deleteKey("be");
	t->deleteKey("been");
	t->printTrie();
	return 0;
}
