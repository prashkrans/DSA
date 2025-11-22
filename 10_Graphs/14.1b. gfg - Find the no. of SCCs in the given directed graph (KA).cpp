/* Graph problem #17.1b. Find the no. of SCCs in the given directed graph (Kosaraju's Algo)
Given a directed graph with V vertices (Numbered from 0 to V-1) and E edges, Find the number of
strongly connected components in the graph.
gfg - https://practice.geeksforgeeks.org/problems/strongly-connected-components-kosarajus-algo/1#

A directed graph is strongly connected if there is a path between all pairs of vertices.
Strongly connected components (SCCs) are maximal strongly connected subgraphs of the given
directed graph.

There are two methods to find the no. of SCCs in the given directed graph:
	1.	Kosaraju's Algo: R.T. = O(m) but 2 DFSs used
	2.	Tarjan's Algo: R.T. = O(m) but a single DFS is used
*/

//	Method 1. Kosaraju's Algo + a stack
//	Steps:
//	1.	Create an empty stack ‘S’ and do DFS1() traversal of a graph. In DFS traversal, after
//		calling recursive DFS for adjacent vertices of a vertex, push the vertex to stack.
//	2.	Reverse directions of all the edges to obtain the transpose/reversed graph.
//	3.	One by one pop a vertex from S while S is not empty. Let the popped vertex be ‘v’. 
//		If v is not visited then take v as a source and do DFS2(v) on the reversed graph. 
//		The DFS starting from v prints a strongly connected component of which v is a part.
//		Hence, no. of times DFS2() is called is the no. of SCCs in the graph
//	Note - 	This can also be used to check if the given graph is strongly connected. 
//			Steps:
//			4. 	After completing the steps 1 to 3 if, visited[v]>1 for any vertex v then 
//				=> G has more than one SCCs thus itself is not a maximal strongly connected subgraph
//				=> G is not strongly connected
//				Else if visited[v]==1 for all the vertices v => G is strongly connected

//	Running time = O(2*DFS + m(reversal) + n(stack & visited)) = O(m+n) ~ O(m) i.e. linear in no. of edges
//	Auxiliary space = O(m+n) if a new adjL is created else O(m) if the given adjL itself is modified but we do need
//	O(m) size vector to store the no. of edges.

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
	//Function to find number of strongly connected components in the graph.

    void DFS1(int src, vector<int> adj[], vector<int> &visited, stack<int> &S) {	//	DFS1 acts on the given graph G and fills the values in the stack S
        visited[src] = 1;
        for(auto v : adj[src]) if(!visited[v]) DFS1(v, adj, visited, S);
        S.push(src);
    }

    void DFS2(int src, vector<int> adj[], vector<int> &visited, int sccNum) {		//	DFS2 acts on the reversed graph G and fills the visited array with sccNum
        visited[src] = sccNum;
        for(auto v : adj[src]) if(!visited[v]) DFS2(v, adj, visited, sccNum);
    }

    vector<int>* reverseEdges(int V, vector<int> adj[]) {							//	It simply reverses the directions of the edges in the graph
        vector<int> *revAdj = new vector<int>[V];									//	Here, it creates a new adjL as a pointer to an array of vectors
        for(int u=0; u<V; u++) {
            for(auto v : adj[u]) revAdj[v].push_back(u);
        }
        return revAdj;
    }

    void printVisited(int V, vector<int> visited) {									//	Both printVisited() and printStack() are not actually required
        cout<<"The visited array is: \n";
        for(int i=0; i<V; i++) cout<<i<<"\t"; cout<<"\n";
        for(int i=0; i<V; i++) cout<<visited[i]<<"\t"; cout<<"\n";
    }

    void printStack(stack<int> S) {
        cout<<"The values of stack are (top = left to bottom = right):\n";
        while(!S.empty()) {
            cout<<S.top()<<" ";
            S.pop();
        }
        cout<<"\n";
    }

    int kosaraju(int V, vector<int> adj[]) {										//	Kosaraju's Algo:
        vector<int> visited(V, 0);													//	1. DFS1(G) => stack S
        stack<int> S;																//	2. reverse(G)
        for(int i=0; i<V; i++) {													//	3. while(!S.empty()) do DFS2(revG)
            if(!visited[i]) DFS1(i, adj, visited, S);       //  DFS1 on G
        }
        printVisited(V, visited);	printStack(S);
        vector<int> *revAdj;
        revAdj = reverseEdges(V, adj);
        for(int i=0; i<V; i++) visited[i] = 0;				// 	Initialising the visited array as visited[v] = 0 for all vertices as we are reusing it
        int sccNum = 0;										//	sccNum simply counts the no. of times DFS2() is called
        while(!S.empty()) {
            int u = S.top();
            S.pop();
            if(!visited[u]) {
                sccNum++;
                DFS2(u, revAdj, visited, sccNum);   		//  DFS2 on rev G
            }
        }
        printVisited(V, visited);
        cout<<"The no. of SCCs in the given directed graph are = ";
        return sccNum;
    }
};

int main() {
    int t;
    cin >> t;
    while(t--) {
    	int V, E;
    	cin >> V >> E;
    	vector<int> adj[V];
    	for(int i = 0; i < E; i++) {
    		int u, v;
    		cin >> u >> v;
    		adj[u].push_back(v);
    	}
    	Solution obj;
    	cout << obj.kosaraju(V, adj) << "\n";
    }
    return 0;
}
