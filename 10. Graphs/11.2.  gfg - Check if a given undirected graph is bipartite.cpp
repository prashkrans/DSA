/* Graph problem #14.2. - LC#785. Is Graph Bipartite?
There is an undirected graph with n nodes, where each node is numbered between 0 and n - 1.
The graph is given as an adjacency list as vector of vectors.
Return true if and only if it is bipartite.
Constraints:
1. 	no self edges
2.	no parallel edges
3. 	graph may not be connected
gfg - https://practice.geeksforgeeks.org/problems/bipartite-graph/1#

A graph is bipartite if the nodes can be partitioned into two independent sets A and B such that 
every edge in the graph connects a node in set A and a node in set B.
A bipartite graph cannot have an odd cycle i.e a cycle with odd no. of edges.
Maximum no. edges in an undirected bipartite graph = floor(n*n/4)
*/
//	Method 2. BFS + Graph colouring (2 colours say red and blue where they are opposites of each other)
//	Graph coloring: If we color a bipartite graph with two colors then the alternate levels have the same color.
//	Working principle: In the BFS if we find an edge, both of whose endpoints are in vertices of the
//	same colour then G is not bipartite.
//	Running time = O(BFS) = O(n+m) ~ O(n)
//	Auxiliary space = O(n) or O(V)

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
	bool BFS(int src, vector<int>adj[], vector<int> &visited, vector<int> &colour) {
	    queue<int> Q;		//	note the use of & for visited and colour as they are getting modified by BFS
	    Q.push(src);
	    visited[src] = 1;
	    colour[src] = 0;
	    while(!Q.empty()) {
	        int u = Q.front();
	        Q.pop();
	        vector<int>::iterator it;
	        for(it = adj[u].begin(); it!=adj[u].end(); it++) {
	            int v = *it;
	            if(!visited[v]) {							//	If v is not visited => colour of v would be the opposite of colour of u hence
	                Q.push(v);
	                visited[v] = 1;
	                colour[v] = !colour[u];
	            }
	            else if(colour[u]==colour[v]) return 0;		//	If v is visited then => if colour[u] == colour[v] then G is not bipartite
	        }
	    }
	    return 1;
	}
	
	bool isBipartite(int V, vector<int>adj[]) {
	    vector<int> visited(V, 0);
	    vector<int> colour(V, -1);  //  Say 0 denotes red and 1 denotes blues and -1 denotes not visited yet
	    bool ans = 1;
	    for(int u=0; u<V; u++) {
	        if(!visited[u]) ans = BFS(u, adj, visited, colour);
	        if(ans==0) return ans;
	    }
	    return ans;
	}

};

int main(){
	int tc;
	cin >> tc;
	while(tc--){
		int V, E;
		cin >> V >> E;
		vector<int>adj[V];
		for(int i = 0; i < E; i++){
			int u, v;
			cin >> u >> v;
			adj[u].push_back(v);
			adj[v].push_back(u);	//	this implies G is a directed graph
		}
		Solution obj;
		bool ans = obj.isBipartite(V, adj);    
		if(ans)cout << "1\n";
		else cout << "0\n";  
	}
	return 0;
}}