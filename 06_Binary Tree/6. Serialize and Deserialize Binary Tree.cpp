/*	Binary tree problem - LC#297. Serialize and Deserialize Binary Tree
Serialization is the process of converting a data structure or object into a sequence of bits so that it 
can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed 
later in the same or another computer environment.
Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your 
serialization/deserialization algorithm should work. You just need to ensure that a binary tree can be serialized 
to a string and this string can be deserialized to the original tree structure.
Clarification: The input/output format is the same as how LeetCode serializes a binary tree. You do not necessarily 
need to follow this format, so please be creative and come up with different approaches yourself.

Constraints:
The number of nodes in the tree is in the range [0, 104].
-1000 <= Node.val <= 1000

Example 1:
Input: root = [1,2,3,null,null,4,5]
Output: [1,2,3,null,null,4,5]


*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
//	Method 1 - We use DFS to solve this problem
//	Running time = O(DFS)
//	Auxiliar space = O(n)

class Codec {
public:
    int strToInt(string s) {            //  Converts a string to integer
        if(s=="X") return 10000;        //  it also takes care of negative integers stored in the string
        string str;
        if(s[0]=='-') str = s.substr(1);
        else str = s;
        int n = str.size(); 
        int ans = 0;
        for(int i=0; i<n; i++) ans = ans*10 + (str[i] - '0');
        if(s[0]=='-') return -ans;
        return ans;
    }
    
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if(root==NULL) return "X";              //  NULL is represented by X
        string LST = serialize(root->left);
        string RST = serialize(root->right);
        string currST = to_string(root->val) + "," + LST + "," + RST;   //  Values are separated by ','
        return currST;
    }
    
    TreeNode* deserializeHelper(queue<int> &intQ) { 
        if(intQ.size()==0) return NULL;
        if(intQ.front()==10000) {                   //  Since the values in nodes <1000 using 10000 to represent NULL
            intQ.pop();
            return NULL;
        }
        TreeNode* root = new TreeNode(intQ.front());        
        intQ.pop();
        root->left = deserializeHelper(intQ);
        root->right = deserializeHelper(intQ);
        return root;       
    }
    
    // Decodes your encoded data to tree.			//  Trickier than serialize() as we dont know where the left subtree ends hence we first 
    TreeNode* deserialize(string s) {               //  convert the string to a queue as it helps keep the info where the left subtree ends 
        queue<string> Q;                            //  The string is split at the ',' using a queue of strings
        queue<int> intQ;                            //  The resulting queue of string is then converted back to a queue of integers (+ or -)
        int prev = 0;
        for(int i=0; i<s.size(); i++){
            if(s[i]==',') {
                Q.push(s.substr(prev, i-prev));     //  As integers with 2 or more digits are stored as strings of size = no. of digits
                prev = i+1;
            }
        }
        Q.push(s.substr(prev));                     //  Adding the last substring to the queue of strings
        while(!Q.empty()) {
            int val = strToInt(Q.front());          //  Converting the string to its integer counterpart
            intQ.push(val);          
            Q.pop();
        }        
        return deserializeHelper(intQ);             //  It is the main deserializer function
    }        
};

// Your Codec object will be instantiated and called as such:
// Codec* ser = new Codec();
// Codec* deser = new Codec();
// string tree = ser->serialize(root);
// TreeNode* ans = deser->deserialize(tree);
// return ans;