/*	Graph Problem #7.2c. - Shortest path between two nodes (Dijkstra's Algo using the STL set)
	Given a weighted, undirected and connected graph of V vertices and E edges, Find the shortest
	distance of all the vertex's from the source vertex S.
	Note: The Graph doesn't contain any negative edge.
	gfg - https://practice.geeksforgeeks.org/problems/implementing-dijkstra-set-1-adjacency-matrix/1#
*/

//	2. 	Dijkstra's Algorithm (for weighted graphs without negative edges whether directed or undirected)

//	Running time = O(mlogn) = O(mlogn) or O(ElogV) as O(m) (for for loop) * O(logn) (for decreaseKey and deleteMin())
//	Auxiliary space = O(n) or O(V). Since, the size of the set or priority queue is of O(n)
//	Note - However the space reqd. for adjacency matrix is O(n+m) (average cases) & O(n^2) (worst case)

#include<bits/stdc++.h>
using namespace std;

class Solution {
	public:
	//Function to find the shortest distance of all the vertices
    //from the source vertex S.
    vector <int> dijkstra(int V, vector<vector<int>> adj[], int S) {
        vector<int> dist(V, INT_MAX);
        set<pair<int, int>> setD;
        dist[S] = 0;
        setD.insert({0, S});
        while(!setD.empty()) {
            int v = setD.begin()->second;
            setD.erase(setD.begin());
            for(int j=0; j<adj[v].size(); j++) {
                int w = adj[v][j][0];
                int wt = adj[v][j][1];
                if(dist[v] + wt < dist[w]) {
                    if(dist[w]!=INT_MAX)
                        setD.erase(setD.find(make_pair(dist[w], w)));
                    dist[w] = dist[v] + wt;
                    setD.insert(make_pair(dist[w], w));
                }
            }
        }
        //for(int i = 0; i<V; i++) cout<<i<<" -> "<<dist[i]<<"\n";
        return dist;
    }
};

int main()
{
    int t;
    cin >> t;
    while (t--) {
        int V, E;
        cin >> V >> E;
        vector<vector<int>> adj[V];		//	Here adjList is represent by an array of vector<vector<int>>(V, vector<int>(2));
        int i=0;						//	So, there are 0 to V-1 nodes and adj[v] -> (w1, wt1), (w2, wt2), ...
        while (i++<E) {
            int u, v, w;
            cin >> u >> v >> w;
            vector<int> t1,t2;
            t1.push_back(v);
            t1.push_back(w);
            adj[u].push_back(t1);
            t2.push_back(u);
            t2.push_back(w);
            adj[v].push_back(t2);
        }
        int S;
        cin>>S;

        Solution obj;
    	vector<int> res = obj.dijkstra(V, adj, S);

    	for(int i=0; i<V; i++)
    	    cout<<res[i]<<" ";
    	cout<<endl;
    }
    return 0;
}

/* Sample input:
1
4 3
0 1 2
0 2 4
2 3 1
0
*/
