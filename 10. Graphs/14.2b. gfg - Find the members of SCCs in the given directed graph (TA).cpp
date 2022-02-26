/* Graph problem #17.2b. Find the members of SCCs in the given directed graph (Tarjan's Algo)
Given a directed graph with V vertices and E edges, find the members of strongly connected components
in the graph.
Note: A single strongly connected component must be represented in the form of a list if integers sorted
in the ascending order. The resulting list should consist of a list of all SCCs which must be sorted in a
way such that a lexicographically smaller list of integers appears first.

There are two methods to find the members of SCCs in the given directed graph:
	1.	Kosaraju's Algo: R.T. = O(m) but two DFSs used
	2.	Tarjan's Algo: R.T. = O(m) but a single DFS is used

yt - https://www.youtube.com/watch?v=wUgWX0nc4NY&ab_channel=WilliamFiset
*/

//	Method 2. Tarjan's Algo + Stack + inStack
//  The stack used here is quite to similar to stack usage in finding whether a directed
//  graph has a cycle.
//  Working principle:
//  1.  if low[u] == disc[u] => u is the head of an SCC
//  2.  for e(u, v) if v is already visited and v is still in the stack then e(u, v) is a back edge
//      and not a cross edge
//	Steps:

//	Running time = O(DFS + sorting) = O(m+n + nlogn) ~ O(m + nlogn) = O(m) or O(nlogn)
//	Auxiliary space = O(n) or O(V)

#include<bits/stdc++.h>
using namespace std;

class Solution {
	public:
	void taDFS(int u, vector<int> &disc, vector<int> &low, vector<int> &inStack, stack<int> &S, vector<vector<int>> &ans, vector<int> adj[]) {
	    static int time = 0;
	    //static int sccCount = 0;
	    disc[u] = time++;
	    low[u] = disc[u];
	    inStack[u] = 1;
	    S.push(u);
	    for(auto v : adj[u]) {
	        if(disc[v]==-1) {
	            taDFS(v, disc, low, inStack, S, ans, adj);
	            low[u] = min(low[u], low[v]);
	        }
	        else if(inStack[v]==1) low[u] = min(low[u], disc[v]);
	    }
	    if(low[u] == disc[u]) {
	        //sccCount++;
	        //cout<<"SCC#"<<sccCount<<"\n";
	        vector<int> currScc;
	        while(S.top()!=u) {
	            currScc.push_back(S.top());
	            inStack[S.top()] = 0;
	            S.pop();
	        }
	        currScc.push_back(S.top());
	        inStack[S.top()] = 0;
	        S.pop();
	        sort(currScc.begin(), currScc.end());   //  using a sort here to print ans in a sorted manner
	        ans.push_back(currScc);
	    }
	}
    //Function to return a list of lists of integers denoting the members
    //of strongly connected components in the given graph.
    vector<vector<int>> tarjans(int V, vector<int> adj[]) {
        vector<int> disc(V, -1);
        vector<int> low(V, -1);
        vector<int> inStack(V, 0);
        stack<int> S;
        vector<vector<int>> ans;
        for(int i=0; i<V; i++) {
            if(disc[i]==-1) {
                taDFS(i, disc, low, inStack, S, ans, adj);
            }
        }
        sort(ans.begin(), ans.end());               //  using a sort here to print ans in a sorted manner
        return ans;
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
        vector<vector<int>> ptr = obj.tarjans(V, adj);
        for(int i=0; i<ptr.size(); i++) {
            for(int j=0; j<ptr[i].size(); j++) {
                if(j==ptr[i].size()-1)
                    cout<<ptr[i][j];
                else
                    cout<<ptr[i][j]<<" ";
            }
            cout<<',';
        }
        cout<<endl;
	}
    return 0;
}

/*Sample input
1
5 5
1 0
0 2
2 1
0 3
3 4
*/
