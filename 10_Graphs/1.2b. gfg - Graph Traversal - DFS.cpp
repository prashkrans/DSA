/*	Graph Problem #4b - Depth First Search (DFS)
	DFS works for both directed and undirected graphs
	Given a connected undirected graph. Perform a Depth First Traversal of the graph.
	Note: Use recursive approach to find the DFS traversal of the graph starting from the 
	0th vertex from left to right according to the graph.
	gfg - https://practice.geeksforgeeks.org/problems/depth-first-traversal-for-a-graph/1
*/
//	Running time = O(n+m) = O(V+E) as summation over (v + degree(v))
//	But in a connected graph m >= n-1 hence it becomes O(m) or O(E)
//	Auxiliary space = O(n) or O(V). Since, an extra visited array is needed of size V
//	Note - However the space reqd. for adjacency matrix is O(n+m) (average cases) & O(n^2) (worst case)

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    void DFS(int v, vector<int> adj[], vector<int> &visited, vector<int> &ans) {
        visited[v] = true;
        ans.push_back(v);
        vector<int>::iterator it;
        for(it = adj[v].begin(); it!=adj[v].end(); it++) {
            if(!visited[*it]){
                DFS(*it, adj, visited, ans);
            }
        }
    }
    
	//Function to return a list containing the DFS traversal of the graph.
	vector<int>dfsOfGraph(int V, vector<int> adj[]) {
	    vector<int> visited(V, 0);
	    vector<int> ans;
	    DFS(0, adj, visited, ans);
	    return ans;
	}
};

int main(){
	int tc;
	cin >> tc;
	while(tc--){
		int V, E;
    	cin >> V >> E;

    	vector<int> adj[V];

    	for(int i = 0; i < E; i++)
    	{
    		int u, v;
    		cin >> u >> v;
    		adj[u].push_back(v);
    		adj[v].push_back(u);
    	}
        // string s1;
        // cin>>s1;
        Solution obj;
        vector<int>ans=obj.dfsOfGraph(V, adj);
        for(int i=0;i<ans.size();i++){
        	cout<<ans[i]<<" ";
        }
        cout<<endl;
	}
	return 0;
}