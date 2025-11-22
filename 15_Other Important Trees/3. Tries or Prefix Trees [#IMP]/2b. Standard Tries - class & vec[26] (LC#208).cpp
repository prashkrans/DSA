/*Trie Problem 1 - LC#208. Implement Trie (Prefix Tree)
A trie (pronounced as "try") or prefix tree is a tree data structure used to efficiently store and reTRIEve keys in a dataset of strings.
There are various applications of this data structure, such as autocomplete and spellchecker.

Implement the Trie class:
Trie(): Initializes the trie object.
void insert(String word): Inserts the string word into the trie.
boolean search(String word): Returns true if the string word is in the trie (i.e., was inserted before), and false otherwise.
boolean startsWith(String prefix): Returns true if there is a previously inserted string word that has the prefix prefix, and false otherwise.

Constraints:
1 <= word.length, prefix.length <= 2000
word and prefix consist only of lowercase English letters => could use an array of size 26 to denote 'a' to 'z'.
At most 3 * 10^4 calls in total will be made to insert, search, and startsWith.

Example 1:
Input
["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
[[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
Output
[null, null, true, false, true, null, true]

Explanation
Trie trie = new Trie();
trie.insert("apple");
trie.search("apple");   // return True
trie.search("app");     // return False
trie.startsWith("app"); // return True
trie.insert("app");
trie.search("app");     // return True
*/

//  Method 1. Standard trie using a struct node and a vector[26] to store the children.
//  Running time = O(l*m) for insert() and O(l) for search() and startsWith().
//  Auxiliary space = O(l*m) for insert() and O(1) for search() and startsWith().
//  Where, l = average length of the words and m = no. of words

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */

struct node {
    node *children[26];
    bool isWord;
    node() {
        for(int i=0; i<26; i++) children[i] = nullptr;
        isWord = 0;
    }
};

class Trie {
    node *root;
public:
    Trie() {
        root = new node;
    }

    void insert(string word) {
        node *curr = root;
        for(int i=0; i<word.size(); i++) {
            int index = word[i] - 'a';
            if(curr->children[index]==nullptr) curr->children[index] = new node();
            curr = curr->children[index];
        }
        curr->isWord = 1;
    }

    bool search(string word) {
        node *curr = root;
        for(int i=0; i<word.size(); i++) {
            int index = word[i] - 'a';
            if(curr->children[index]==nullptr) return false;
            curr = curr->children[index];
        }
        return curr->isWord;        //  Note: The difference between search and startsWith is the return value.
    }

    bool startsWith(string prefix) {
        node *curr = root;
        for(int i=0; i<prefix.size(); i++) {
            int index = prefix[i] - 'a';
            if(curr->children[index]==nullptr) return false;
            curr = curr->children[index];
        }
        return true;
    }
};
