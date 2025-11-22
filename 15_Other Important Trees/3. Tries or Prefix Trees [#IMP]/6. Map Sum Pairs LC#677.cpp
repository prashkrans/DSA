/**
LC#677. Map Sum Pairs

Time complexity: 
1. Insert: O(l*m) 
2. Search: O(l)
3. GetSum: O(l*26) ~ O(l)

Space complexity: O(l*m)

where l: average length of words and m: no. of words

**/

class MapSum {
    struct TrieNode {
        int val;      // this replaces bool isCompleteWord;
        TrieNode* children[26];
        TrieNode() {
            val = 0;
            for(int i=0; i<26; i++) children[i] = nullptr;
        }  
    };
    TrieNode* root;
    
    TrieNode* search(string prefix) {
        TrieNode* curr = root;
        for(int i=0; i<prefix.size(); i++) {
            int index = prefix[i] - 'a';
            if(curr->children[index]==nullptr) return nullptr;
            else curr = curr->children[index];
        }
        return curr;
    }
    
    int getSum(TrieNode* curr) {
        if(curr == nullptr) return 0;
        int ans = curr->val;
        for(int i=0; i<26; i++) ans += getSum(curr->children[i]); // For incomplete word val = 0
        return ans;
        
    }
public:
    MapSum() {
        root = new TrieNode();
    }
    
    void insert(string key, int val) {
        TrieNode* curr = root;
        for(int i=0; i<key.size(); i++) {
            int index = key[i] - 'a';
            if(curr->children[index]==nullptr) curr->children[index] = new TrieNode;
            curr = curr->children[index];
        }
        curr->val = val;    // Standard trie insert except curr->isCompleteWord = true; we use curr->val = val;
    }
    
    int sum(string prefix) {
        TrieNode* commonNode = search(prefix);
        return getSum(commonNode);
    }
};

/**
 * Your MapSum object will be instantiated and called as such:
 * MapSum* obj = new MapSum();
 * obj->insert(key,val);
 * int param_2 = obj->sum(prefix);
 */