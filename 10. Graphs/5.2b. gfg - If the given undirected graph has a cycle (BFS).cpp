/*	Graph Problem #8.2b. - Given an undirected graph, find whether it has a cycle.
	gfg - https://practice.geeksforgeeks.org/problems/detect-cycle-in-an-undirected-graph/1#
	Here the graph is not a class and uses an array of vectors<int> to store the adjacency list.
	The concept remains the same except for the variation in traversal of the adjacency list.
*/

//	Method 2. BFS + Parent Array (instead of parent variable in DFS)
//	Steps
//	1.	Do a BFS traversal of the given graph.
//	2.	For every visited vertex ‘v’, if there is an adjacent ‘u’ such that u is already visited
//		and u is not a parent of v, then there is a cycle in the graph.
//	3.	If we don’t find such an adjacent for any vertex, we say that there is no cycle.

//	Running time = O(BFS) = O(n+m) = O(m) = O(E)
//	Auxiliary space = O(n) = O(V) to store the visited and the parent arrays

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    //Function to detect cycle in an undirected graph.
	bool isCyclicBFS(int src, vector<int> adj[], vector<int> &visited, vector<int> &parent) {
	    queue<int> Q;
	    Q.push(src);
	    visited[src] = 1;
	    while(!Q.empty()) {
	        int v = Q.front();
	        Q.pop();
	        vector<int>::iterator it;
	        for(it = adj[v].begin(); it!=adj[v].end(); it++) {
	            if(!visited[*it]) {
	                Q.push(*it);
	                visited[*it] = 1;
	                parent[*it] = v;
	            }
	            else {
	                if(parent[v] != *it) return 1;
	            }
	        }
	    }
	    return 0;
	}
	
	
	bool isCycle(int V, vector<int>adj[]) {
	    vector<int> visited(V, 0);
	    vector<int> parent(V, -1);
	    bool ans = 0;
	    for(int i=0; i<V; i++) {
	        if(!visited[i]) {
	            ans = isCyclicBFS(i, adj, visited, parent);
	        }
	        if(ans==1) break;
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
			adj[v].push_back(u);
		}
		Solution obj;
		bool ans = obj.isCycle(V, adj);
		if(ans)
			cout << "1\n";
		else cout << "0\n";
	}
	return 0;
}