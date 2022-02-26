/*	Graph Problem #10.1b. - Topological Sorting
	Given a Directed Graph with V vertices and E edges, Find #any# topological sorting of that graph
	gfg - https://practice.geeksforgeeks.org/problems/topological-sort/1
	Topological sorting for Directed Acyclic Graph (DAG) is a linear ordering of vertices
	such that for every directed edge u v, vertex u comes before v in the ordering.
	Topological Sorting for a graph is not possible if the graph is not a DAG.
	There are two methods to obtain the topological sorting of a DAG:
		1. 	DFS + Stack
		2.	BFS + Indegree array (Kahn's Algorithm)
		R.T of both = O(n+m) ~ O(m)
*/

//	Method 1 - Using DFS algo and a stack in which a node is pushed only when all the adjacent nodes
//	of that node have been visited.
//	Running time = O(n+m) ~ O(m) or O(E)
//	Auxiliary space = O(n) or O(V) due to the size of the visted array and the stack


#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
	void topoSortUtil(int v, vector<int> &visited, stack<int> &tsStack, vector<int> adj[]) {
	    visited[v] = 1;
	    vector<int>::iterator it;
	    for(it = adj[v].begin(); it!=adj[v].end(); it++) {
	        if(!visited[*it]) topoSortUtil(*it, visited, tsStack, adj);
	    }
	    tsStack.push(v);
	}	
	//Function to return list containing vertices in Topological order. 
	vector<int> topoSort(int V, vector<int> adj[]) {
	    vector<int> visited(V, 0);
	    stack<int> tsStack;
	    vector<int> ans;
	    for(int v=0; v<V; v++) {
	        if(!visited[v]) {
	            topoSortUtil(v, visited, tsStack, adj);
	        }
	    }
	    while(!tsStack.empty()) {
	        ans.push_back(tsStack.top());
	        tsStack.pop();
	    }
	    return ans;
	}
};

/*  Function to check if elements returned by user
*   contains the elements in topological sorted form
*   V: number of vertices
*   *res: array containing elements in topological sorted form
*   adj[]: graph input
*/
int check(int V, vector <int> &res, vector<int> adj[]) {
    vector<int> map(V, -1);
    for (int i = 0; i < V; i++) {
        map[res[i]] = i;
    }
    for (int i = 0; i < V; i++) {
        for (int v : adj[i]) {
            if (map[i] > map[v]) return 0;
        }
    }
    return 1;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N, E;
        cin >> E >> N;
        int u, v;

        vector<int> adj[N];

        for (int i = 0; i < E; i++) {
            cin >> u >> v;
            adj[u].push_back(v);
        }
        
        Solution obj;
        vector <int> res = obj.topoSort(N, adj);

        cout << check(N, res, adj) << endl;
    }
    
    return 0;
}