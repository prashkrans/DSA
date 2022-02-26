/* Graph problem #19c. Given a graph with n vertices, e edges and an array arr[] denoting the edges 
connected to each other, check whether it is Biconnected or not.
Note: The given graph is Undirected.
n = no. of vertices (vertices are indexed from 0 to n-1)
e = no. of edges
size of arr[] = 2*e

gfg - https://practice.geeksforgeeks.org/problems/biconnected-graph2528/1
*/

//	Method 2. Using deepest backedge + arrival time + one DFS traversal + special case for root
//	Running time = O(DFS) or O(m+n) ~ O(m)
//	Auxiliary space = O(n) or O(V)

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int biDFS(int u, vector<int> &visited, vector<int> &arrival, vector<int> &parent, int time, vector<int> &ap, map<int, list<int>> adjL, int src) {
        visited[u] = 1;
        arrival[u] = time++;
        int dbe = arrival[u];
        int DFSchildren = 0;
        for(auto v : adjL[u]) {
            if(!visited[v]) {
                parent[v] = u;
                DFSchildren++;
                int dbe_v = biDFS(v, visited, arrival, parent, time, ap, adjL, src);
                if(u!=src && dbe_v>=arrival[u]) {
                    ap.push_back(u);
                    return -1;
                }
                else if(u==src && DFSchildren>1) {
                    ap.push_back(u);
                    return -1;
                }
                dbe = min(dbe, dbe_v);
            }
            else if(parent[u]!=v) {
                dbe = min(dbe, arrival[v]);
            }
        }
        return dbe;
    }
    bool biGraph(int arr[], int n, int e) {
        map<int, list<int>> adjL;
        for(int i=0; i<n; i++) adjL[i];
        int m = 2*e;
        for(int i=0; i<m-1; i=i+2) {
            int u = arr[i];
            int v = arr[i+1];
            adjL[u].push_back(v);
            adjL[v].push_back(u);
        }
        /*for(auto i : adjL) {
            cout<<i.first<<" -> ";
            for(auto j : i.second) cout<<j<<", ";
            cout<<"\n";
        }*/
        vector<int> visited(n, 0);
        vector<int> arrival(n);
        vector<int> parent(n);
        vector<int> ap;
        int time = 0;
        int dbe = biDFS(0, visited, arrival, parent, time, ap, adjL, 0);
        if(dbe==-1) return 0;
        for(int i=0; i<n; i++) if(visited[i]==0) return 0;
        if(ap.size()>0) return 0;
        return 1;
    }
};

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n,e;
        cin>>n>>e;
        int arr[2*e];
        for(int i=0; i<2*e; i++) cin>>arr[i];
        Solution ob;
        cout << ob.biGraph(arr,n,e) << endl;
    }
    return 0;
}

/* Sample input
1
5 6
1 0 0 2 2 1 0 3 3 4 2 4
*/
