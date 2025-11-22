/* Binary Tree Prob #. Binary Tree: Huffman Decoding
*/

// 	Running time = O(m) where m is the size of the encoded string
//	Auxiliary space = O(n) where n is the size of the decoded string

void decode_huff(node *root, string s) {
    int n = s.size();
    node *curr = root;
    string ans;
    for(int i=0; i<n; i++) {
        if(s[i]=='0') curr = curr->left;
        else curr = curr->right;
        if(curr->left==NULL && curr->right==NULL) {
            ans = ans + curr->data;
            curr = root;
        }
    }
    cout<<ans;
}