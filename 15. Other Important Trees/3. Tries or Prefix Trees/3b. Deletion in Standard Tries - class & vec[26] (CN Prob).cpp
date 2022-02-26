/* Trie Problem 2 - Deletion in Standard Tries (Prefix Trees)
A trie (pronounced as "try") or prefix tree is a tree data structure used to efficiently store and reTRIEve keys in a dataset of strings.
There are various applications of this data structure, such as autocomplete and spellchecker.

Example 1:
Query A - 1 coding
This query will add the string “coding” in the trie.

Query B - 2 coding
This query will delete the string “coding” from the Trie. After deleting the string, it will produce “TRUE” as it’s output.


coding ninjas - https://www.codingninjas.com/codestudio/problems/trie-delete-operation_1062663?leftPanelTab=0
*/

//  Method 1. Standard trie using a class trie, a struct node and a vector[26] to store the children.
//  Running time = O(len) for deletion.
//  Auxiliary space = O(1) for deletion.
//  Where, len = average length of the words and m = no. of words

/*class TrieNode {                      //  Definition of TrieNode class
public:
    TrieNode * children[26];
    bool isEnd;
    TrieNode()
    {
        isEnd=false;
        for(int i=0;i<26;i++)
            children[i]=NULL;
    }

};*/

TrieNode *deleteUtil(TrieNode *curr, string s, int depth) {
	if(curr==NULL) return curr;         //  Takes care of an empty trie
	if(depth==s.size()) {               //  This implies that the word is found either as a leaf node or an internal node
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
			curr->isEnd = 0;   //  In this case only unmarking is sufficient to delete that word
		}
		return curr;
	}
	int index = s[depth] - 'a';
	if(curr->children[index]!=NULL) curr->children[index] = deleteUtil(curr->children[index], s, depth+1);
	else return curr;
	bool hasChild = 0;
	for(int i=0; i<25; i++) {           //  The same process is used here as we need to continue deleting nodes if it becomes
		if(curr->children[i]!=NULL) {   //  a leaf node and is not the last character of any other word
			hasChild = 1;
			break;
		}
	}
	if(hasChild==0 && curr->isEnd==0) {        //  If root does not have any child (its only child got deleted), and it is not end of another word.
        delete curr;
        curr = NULL;
    }
	return curr;
}

TrieNode* solution::deleteWord(TrieNode* root, string word) {
  // Write your code here
    root = deleteUtil(root, word, 0);
    return root;
}

