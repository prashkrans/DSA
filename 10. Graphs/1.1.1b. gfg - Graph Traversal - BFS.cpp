/*	Graph Problem #3.1.1b. - Breadth First Search (BFS) 
	Here we are using the BFS on a directed graph
	Given a directed graph. The task is to do Breadth First Traversal of this graph starting from 0.
	Note: One can move from node u to node v only if there's an edge from u to v and find the BFS traversal of 
	the graph starting from the 0th vertex, from left to right according to the graph. Also, you should only 
	take nodes directly or indirectly connected from Node 0 in consideration.
	gfg - https://practice.geeksforgeeks.org/problems/bfs-traversal-of-graph/1	
*/

//	Running time = O(n+m) = O(V+E) as summation over v + degree(v)
//	But in a connected graph m >= n-1 hence, it becomes O(m) or O(E)
//	Auxiliary space = O(n) or O(V). Since, an extra visited array is needed of size V
//	Note - However the space reqd. for adjacency matrix is O(n+m) (average cases) & O(n^2) (worst case)

#include<bits/stdc++.h>
using namespace std;

class Solution {
    public:
    //Function to return Breadth First Traversal of given graph.
	vector<int>bfsOfGraph(int V, vector<int> adj[]) {
	    vector<bool> visited(V, 0);
	    vector<int> ans;
	    queue<int> Q;
	    Q.push(0);
	    visited[0] = true;
	    ans.push_back(0);
	    while(!Q.empty()) {
	        int v = Q.front();
	        Q.pop();
	        vector<int>::iterator it;
	        for(it = adj[v].begin(); it!=adj[v].end(); it++) {
	            if(!visited[*it]) {
	                Q.push(*it);
	                visited[*it] = true;
	                ans.push_back(*it);
	            }
	        }
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
    	vector<int> adj[V];			//	Adjacency list as an array of vectors
    	for(int i = 0; i < E; i++)    	{
    		int u, v;
    		cin >> u >> v;
    		adj[u].push_back(v);
			//	adj[v].push_back(u);	//	As the graph is a directed graph
    	}
        Solution obj;
        vector<int>ans=obj.bfsOfGraph(V, adj);
        for(int i=0; i<ans.size(); i++) cout<<ans[i]<<" ";
        cout<<endl;
	}
	return 0;
}