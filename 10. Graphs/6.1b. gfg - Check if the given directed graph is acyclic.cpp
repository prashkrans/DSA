/*	Graph Problem #9.1b - Is the given directed graph acyclic?
	Given a Directed Graph with V vertices (Numbered from 0 to V-1) and E edges, 
	check whether it contains any cycle or not.
	gfg - https://practice.geeksforgeeks.org/problems/detect-cycle-in-a-directed-graph/1
*/
//	Method 1b - Using DFS and a recursion stack represented with a vector<bool> or a map<T, bool>
//	Running time = O(n+m) or O(V+E) as the search operation is O(1) instead of O(n) in the stack (now rep. as a vector/map)
//	But in a connected graph m >= n-1 hence it becomes O(m) or O(E)
//	Auxiliary space = O(n) or O(V) i.e. the size of the visited array and the recursion stack

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isCyclicUtil(int v, vector<int> &visited, vector<int> &recStack, vector<int> adj[]) {
        visited[v] = 1;
        recStack[v]= 1;
        vector<int>::iterator it;
        for(it = adj[v].begin(); it!=adj[v].end(); it++) {
            if(!visited[*it]) {
                if(isCyclicUtil(*it, visited, recStack, adj)) return 1;
            }
            else {
                if(recStack[*it]==1) return 1;
            }
        }
        recStack[v] = 0;
        return 0;
    }

	//Function to detect cycle in a directed graph.
	bool isCyclic(int V, vector<int> adj[]) {
	    bool ans = 0;
	    vector<int> visited(V, 0);
	    vector<int> recStack(V, 0);
	    for(int i=0; i<V; i++) {
	        if(!visited[i]) ans = isCyclicUtil(i, visited, recStack, adj);
	        if(ans==1) break;
	    }
	    return ans;
	}
};

int main()
{
    
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
    	cout << obj.isCyclic(V, adj) << "\n";
    }
    return 0;
}