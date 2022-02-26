/*	Graph Problem #8.1b. - Given an undirected graph, find whether it has a cycle.
	gfg - https://practice.geeksforgeeks.org/problems/detect-cycle-in-an-undirected-graph/1#
	Here the graph is not a class and uses an array of vectors<int> to store the adjacency list.
	The concept remains the same except for the variation in traversal of the adjacency list.
*/

//	Method 1. DFS + Parent Variable
//	Running time = O(DFS) = O(n+m) = O(m) = O(E)
//	Auxiliary space = O(n) = O(V) to store the visited array


#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isCycleUtil(int s, int parent, vector<bool> visited, vector<int>adj[]) {
        visited[s] = true;
        vector<int>::iterator it;
        for(it = adj[s].begin(); it!=adj[s].end(); it++) {		//	We need an iterator of vector<int> data type to traverse this adjacency list
            int v = *it;
            if(!visited[v]) {
                if(isCycleUtil(v, s, visited, adj)) return true;
            }
            else if(visited[v]) {
                if(parent!=v) return true;
            }
        }
        return false;
    }

    bool isCycle(int V, vector<int> adj[]) {
        vector<bool> visited(V, 0);
        bool ans = 0;
        for(int v=0; v<V; v++) {            //  Using a for loop here as the graph have > 1 connected components
            if(!visited[v]) {               //  So, if a node is not visited => it lies in a different connected component
                ans = isCycleUtil(v, -1, visited, adj);
                if(ans == 1) break;
            }
        }
        return ans;
    }

	void print(int V, vector<int> adj[]) {  //  This is how we iterate over an array of vectors
		for(int i=0; i<V; i++) {
            cout<<i<<" -> ";
            vector<int>::iterator it;
            for(it = adj[i].begin(); it!=adj[i].end(); it++) cout<<*it<<", ";
            cout<<"\n";
		}
	}
};

int main(){
	int tc;
	cin >> tc;
	while(tc--){
		int V, E;
		cin >> V >> E;
		vector<int>adj[V];          //  This is an array of vectors with fixed no. of rows where each row is a vector of variable length
		for(int i = 0; i < E; i++){ //  Thus no. of rows is always fixed and known here V while each row size can be obtained from adj[i].size();
			int u, v;
			cin >> u >> v;
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
		Solution obj;
		obj.print(V, adj);
		bool ans = 0;
		ans = obj.isCycle(V, adj);
		if(ans)
			cout << "1\n";
		else cout << "0\n";
	}
	return 0;
}
