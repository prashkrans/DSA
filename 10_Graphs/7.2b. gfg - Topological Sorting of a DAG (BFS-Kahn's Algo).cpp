/*	Graph Problem #10.2b. - Topological Sorting
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

//	Method 2 - Using BFS algo + indegree array (Kahn's algorithm)
//	This algo is based on the property that:
//	"a DAG G has at least one vertex with in-degree 0 and one vertex with out-degree 0"

//	Running time = O(BFS) = O(n+m) = O(V+E) which becomes O(m) or O(E) if m>=n
//	Auxiliary space = O(n) or O(V) due the indegree[] array
//	Running time = O(n+m) ~ O(m) or O(E)
//	Auxiliary space = O(n) or O(V) due to the size of the visted array and the stack

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
	//Function to return list containing vertices in Topological order.
	vector<int> topoSort(int V, vector<int> adj[]) {
        vector<int> indegree(V, 0);
        vector<int> ans;
        queue<int> Q;
        for(int v=0; v<V; v++) {
            for(auto w : adj[v]) {
                indegree[w]++;
            }
        }
        for(int v=0; v<V; v++) {
            if(indegree[v]==0) {    //  This automatically takes care of all the connected components
                Q.push(v);          //  As each acyclic connected component would have atleast a node with indegree = 0
                ans.push_back(v);
            }
        }
        while(!Q.empty()) {
            int v = Q.front();
            Q.pop();
            for(auto w : adj[v]) {
                indegree[w]--;
                if(indegree[w]==0) {
                    Q.push(w);
                    ans.push_back(w);
                }
            }
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
        int V, E;
        cin >> V >> E;
        int u, v;
        vector<int> adj[V];
        for (int i = 0; i < E; i++) {
            cin >> u >> v;
            adj[u].push_back(v);        //  This implies it is a directed graph
        }
        Solution obj;
        vector <int> res = obj.topoSort(V, adj);
        cout << check(V, res, adj) << endl;
    }
    return 0;
}

/* Sample input:
1
5 6
0 1
0 2
3 1
4 0
2 3
4 2
*/


