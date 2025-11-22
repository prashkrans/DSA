/* Graph problem #24b. LC#133. Clone a connected undirected graph
Given a reference of a node in a connected undirected graph. Return a deep copy (clone) of the graph.
Each node in the graph contains a value (int) and a list (List[Node]) of its neighbors.
Here, map<T, list<T>> is not used to represent an adjacency list.
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

So, the adjacency list representation is given as Node* node.
Since, the graph is connected, a single pointer to any node can be used to traverse the whole graph.

The given node will always be the first node with val = 1. You must return the copy of the given node as a reference to the cloned graph.

Example 1:
Input: adjList = [[2,4],[1,3],[2,4],[1,3]]
Output: [[2,4],[1,3],[2,4],[1,3]]

Example 2:
Input: adjList = [[]]
Output: [[]]
Here, a node with value == 1 exists with no neighbors.

Example 3:
Input: adjList = []
Output: []
Here, no node exists.
*/

//	Method 1 - Uses the concept of a parent and backedges in case of a cycle
//  Using DFS + map/vector called visitedNodes to help include backedges in O(1) time.
//	There are only two different edges in an undirected graph
//	a.	if(!visited[v]) => tree edges => we'd have to create new nodes for the clone graph and add the tree edges
//	b.	if(visited[v] && parent[u]!=v) => back edges i.e. cycle exists => just add the back edges in the cloned graph 
//		between nodes with val == u and val == v
//	Running time = O(DFS) = O(n+m) ~ O(m)
//	Auxiliary space = O(V) = O(n)


//  Using a adjList and parent, has the same Running Time as method 2 tho takes more space but is the easiest to understand.
//	Running time = O(DFS) = O(n+m) ~ O(m)
//	Auxiliary space = O(V) = O(n) (multiple times n)

class Solution {
    public:
        void dfs(Node* u, map<int, set<int>> &adjList, map<int, int> &visited, map<int, int> &parent) {
            if(u==nullptr) return;      
            visited[u->val] = 1;
            adjList[u->val].insert({}); // Basics of a Graph that we initiate a node with {} i.e. empty neighbors
            for(auto v: u->neighbors) {
                if(visited.count(v->val)==0){
                    adjList[u->val].insert(v->val);
                    adjList[v->val].insert(u->val);
                    parent[v->val] = u->val;
                    dfs(v, adjList, visited, parent);
                }
                else if(visited.count(v->val) && parent[v->val] != u->val) {
                    adjList[u->val].insert(v->val);
                    adjList[v->val].insert(u->val);
                }
            }        
        }
    
        Node* cloneGraph(Node* node) {
            //vector<int> visited(n+1, 0); 	    //  We cannot use a vector for visited we don't know the value of n beforehand
            map<int, set<int>> adjList;
            map<int, int> visited;              //  Hence, use map instead
            map<int, int> parent;
            dfs(node, adjList, visited, parent);
    
            map<int, Node*> nodes;
            for(auto i: adjList) nodes[i.first] = new Node(i.first);
    
            cout<<"adjList size: "<<adjList.size()<<"\n";
            for(auto i:adjList) {
                Node *u = nodes[i.first];
                vector<Node *> neighbors = {};
                cout<<i.first<<"-> ";
                for(auto j: i.second) {
                    Node *v = nodes[j];
                    neighbors.push_back(v);
                    cout<<j<<", ";
                }
                u->neighbors = neighbors;
                cout<<"\n";
            }
    
            for (auto i: visited) cout<<i.first<<" "<<i.second<<endl;
            return nodes[1];
            
        }
    };


// Method 2: Best solution: Simple Recursion similar to DFS but tricky to form the solution
//	Running time = O(DFS) = O(n+m) ~ O(m)
//	Auxiliary space = O(V) = O(n)

class Solution {
    public:
        unordered_map<Node*,Node*> nodeMap;     // One to one mapping
        Node* cloneGraph(Node* node) {  
            if(!node) return nullptr;           // Base Case#1     
            if(nodeMap.find(node)!=nodeMap.end()) return nodeMap[node]; // #IMP Base Case#2 current node is already mapped out or visited earlier is returned
            Node* clonednode=new Node(node->val);   // The copy of current node is made                        
            nodeMap[node]=clonednode;               // The copy of current node is added to nodeMap with 0 neigbours
            for(Node* neighbor:node->neighbors){    // Update the neighbours of the copy of the current node
                clonednode->neighbors.push_back(cloneGraph(neighbor));
            }
            return clonednode;
        }
    };