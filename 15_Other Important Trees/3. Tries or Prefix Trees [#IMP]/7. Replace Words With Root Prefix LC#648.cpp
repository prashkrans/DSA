/** LC#648. Replace Words:
# Approach

1. Create a Trie data structure where each node has:
   - A boolean flag `isRoot` to mark if a path forms a complete root word
   - An array of 26 pointers to child nodes (one for each lowercase letter)

2. Insert all dictionary words (not sentence words) into the Trie, marking the end of each word as a root.

3. Split the input sentence into individual words.

4. For each word in the sentence:
   - Traverse the Trie character by character
   - If character doesn't exist in the Trie, return the original word
   - If we reach a node marked as root, return the prefix up to that point
   - If we finish the word without finding a root marker, return the original word

5. Join the processed words back with spaces to form the result.

# Time Complexity
- Building the Trie: O(L), where L is the total length of all dictionary words
- Processing the sentence: O(N), where N is the length of the sentence
- Overall: O(L + N)

# Space Complexity
- Trie storage: O(L), where L is the total length of all dictionary words
- Word storage: O(N), where N is the length of the sentence
- Overall: O(L + N)

**/

class Solution {
    struct TrieNode {
        bool isRoot;
        vector<TrieNode*> children;
        
        TrieNode(): isRoot(false), children(26, nullptr) {}
        // or TrieNode(): isRoot(false), children(vector<TrieNode*>(26, nullptr)) {} // both are correct
        
        void insert(string word) {
            // replaces TrieNode* curr = root; since insert is a method inside the struct
            TrieNode* curr = this; 
            for(int i=0; i<word.size(); i++) {
                int index = word[i] - 'a';
                if(curr->children[index] == nullptr) curr->children[index] = new TrieNode();
                curr = curr->children[index];
            }
            curr->isRoot = true;
        }
        
        string replaceWithPrefixRoot(string word) {
            TrieNode* curr = this;
            for(int i=0; i<word.size(); i++) {
                int index = word[i] - 'a';
                if(curr->children[index] == nullptr) return word; // Don't return with " " here instead return the word itself
                else if(curr->children[index]->isRoot) return word.substr(0, i+1);
                curr = curr->children[index];
            }
            return word;
        }
    };
    
    TrieNode* root;
    
    vector<string> splitBySpace(string sentence) { // Note its important to split the sentences by space
        vector<string> words;
        int startIndex = 0;
        for(int i=0; i<sentence.size(); i++) {
            if(sentence[i]==' ') {
                words.push_back(sentence.substr(startIndex, i-startIndex));
                startIndex=i+1;
            }
        }
        words.push_back(sentence.substr(startIndex)); // Pushing the last word
        return words;
    }
public:
    Solution (): root(new TrieNode) {}  // [#IMP] to initialize root = new TrieNode
        
    string replaceWords(vector<string>& dictionary, string sentence) {
        vector<string> words = splitBySpace(sentence);
        for(auto &word: dictionary) root->insert(word);
        // for(int i=0; i<words.size(); i++) words[i] = root->replaceWithPrefixRoot(words[i]); or using the auto & as below
        // if & is not used then word is not passed by reference which gives incorrect results
        for(auto &word: words) word = root->replaceWithPrefixRoot(word); 
        string ans;
        for(auto &word: words) ans += " " + word;
        return ans.substr(1);
    }
};