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

//	Method 1 - Using DFS + map/vector called visitedNodes to help include backedges in O(1) time.
//	There are only two different edges in an undirected graph
//	a.	if(!visited[v]) => tree edges => we'd have to create new nodes for the clone graph and add the tree edges
//	b.	if(visited[v] && parent[u]!=v) => back edges i.e. cycle exists => just add the back edges in the cloned graph 
//		between nodes with val == u and val == v
//	Running time = O(DFS) = O(n+m) ~ O(m)
//	Auxiliary space = O(V) = O(n)

class Solution {
public:
    void DFS(Node* node, map<int, int> &visited, map<int, int> &parent, Node* &cloneNode, map<int, Node*> &visitedNodes) {
        int u = node->val;															//	node => u and nbr => v
        visited[u] = 1;																//	cloneNode => clone u and cloneNbr => clone v
        vector<Node*>::iterator it;	
        for(it = node->neighbors.begin(); it!=node->neighbors.end(); it++) {
            Node* nbr = *it;
            int v = nbr->val;
            if(!visited[v]) {														//	tree edge (u, v)
                Node* newNode = new Node(v);
                cloneNode->neighbors.push_back(newNode);
                newNode->neighbors.push_back(cloneNode);
                parent[v] = u;
                visitedNodes[v] = newNode;
                DFS(nbr, visited, parent, newNode, visitedNodes);
            }
            else if(visited[v] && parent[u]!=v) {									//	back edge (u, v)
                Node* clonedNbr = visitedNodes[v];
                cloneNode->neighbors.push_back(clonedNbr);
                //clonedNbr->neighbors.push_back(cloneNode); 	// This is not required as it creates duplicate edges
            }
        }
    }
    Node* cloneGraph(Node* node) {
        //vector<int> visited(n+1, 0); 							//  We cannot use a vector for visite as n is not defined
        if(node==NULL) return NULL;								//	Base case 1
        else if(node->neighbors.size()==0) {					//	Base case 2
            Node* oneNode = new Node(1);
            return oneNode;
        }
        map<int, int> visited;									//	We can ignore using visited map as we are using visitedNodes here
        map<int, int> parent;									//	which can perform the functions of a visited map too
        map<int, Node*> visitedNodes; 							//	visitedNodes returns the clone Node* pointer for a given value of the node
        parent[1] = 1;											//	Parent of source node is itself
        Node* cloneNode = new Node(1);							//	Source node of the cloned graph
        visitedNodes[1] = cloneNode;
        DFS(node, visited, parent, cloneNode, visitedNodes);		
        /*
        for(auto v : visited) cout<<v.first<<"\t"; cout<<"\n";
        for(auto v : visited) cout<<v.second<<"\t"; cout<<"\n";
        for(auto v : parent) cout<<v.first<<"\t"; cout<<"\n";
        for(auto v : parent) cout<<v.second<<"\t"; cout<<"\n";
        */
        return cloneNode;
    }
};
