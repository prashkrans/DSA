/* Graph problem #22.1b. Max flow in a flow network
Given a flow network G = (V, E), find the maximum flow.
Note - a flow network G is a directed graph with flow and capacity for each edges
instead of weight/length.
Also, here adjacency list is used but it is easier to be implemented in adjacency matrix representation
Given,
a. 	if e(u, v) exists in G then e(v, u) does not exist
b.	there is a single source s and a single sink t
c. 	the edges have a non-negative capacity

It can be solved by using various methods
1.	Ford - Fulkerson method - R.T. = O(fmax*E) or O(fmax*m)
	a. Using DFS to find the augmenting paths
	b. Using BFS to find the augmenting paths which is known as Edmonds Karp algorithm - R.T. = O(V*E^2)
2.	Dinic's algorithm - R.T. = O(V^2*E)
3.	Push Relabel methods - R.T. = O(V^2*E)
*/

//	Method 1 - Edmonds Karp algorithm to find the max flow ina given flow network
//	Ford - Fulkerson method:
//	Steps:
//	1. 	initialize the flow value f in all the edges to 0
//	2.	create a residual graph of the given directed graph G
//	3.	while an augmenting path p exists from s to t in the residual graph (using BFS here)
//		a.	augment the flow of the edges included in p by cp = min(cf of all (u, v) in p)
//		b. 	update the residual network graph
//	4.	if no augmenting exists in the residual graph G return the flow obtained from the above steps as
//		is the max flow
//	Note - Edmonds Karp is a Ford-Fulkerson method where BFS is used to find the augmenting paths.
//	Running time = O(V*E^2) or O(nm^2)
//	Auxiliary space = O(n+m) ~ O(m)


#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    void printMat(vector<vector<int>> mat, int N) {
        for(int i=1; i<N+1; i++) {
            for(int j=1; j<N+1; j++) cout<<mat[i][j]<<" ";
            cout<<"\n";
        }
    }
    bool BFS(int s, int t, vector<int> &parent, vector<vector<int>> &resM, int N) {
        queue<int> Q;
        Q.push(s);
        parent[s] = s;
        while(!Q.empty()) {
            int u = Q.front();
            Q.pop();
            for(int v=1; v<N+1; v++) {
                if(resM[u][v]!=0 && parent[v]==-1) {
                    Q.push(v);
                    parent[v] = u;
                    if(v==t) return true;
                }
            }
        }
        cout<<"returning false\n";
        return false;
    }
    int edmondsKarpAlgo(int s, int t, vector<vector<int>> adjM, vector<vector<int>> e, int N) {
        vector<vector<int>> augM(N+1, vector<int>(N+1, 0));
        vector<vector<int>> resM = adjM;
        vector<int> parent(N+1, -1); // itself acts a visited array too
        vector<pair<int, int>> augPath;
        int fMax = 0;
        while(BFS(s, t, parent, resM, N)) {
            int cp = INT_MAX;
            int v = t;
            while(parent[v] != v) {
                cp = min(cp, resM[parent[v]][v]);
                augPath.push_back({parent[v], v});
                v = parent[v];
            }
            cout<<"The residual capacity of the current augmentation path is = "<<cp<<"\n";
            cout<<"The edges in the current augmentation path are: \n";
            for(int i=0; i<augPath.size(); i++) {
                int u = augPath[i].first;
                int v = augPath[i].second;
                cout<<"("<<u<<", "<<v<<") ";
                if(adjM[u][v]!=0) augM[u][v] += cp;
                else augM[v][u] -= cp;
            }
            cout<<"\nThe augmentated matrix is: \n";
            printMat(augM, N);
			for(int u=1; u<N+1; u++) {
				for(int v=1; v<N+1; v++) {
					if(augM[u][v]>0) {
						resM[u][v] = adjM[u][v] - augM[u][v];
						resM[v][u] = augM[u][v];
					}
				}
			}
			cout<<"The corresponding residual matrix is: \n";
			printMat(resM, N);
			parent.clear();             //  It is really important to initialize parent and augPath each time BFS is called
			parent.resize(N+1, -1);
			augPath.clear();
        }
        for(int i=1; i<N+1; i++) {
            if(augM[s][i]!=0) fMax += augM[s][i];
        }
        return fMax;
    }

    int solve(int N, int M, vector<vector<int>> e) {
        vector<vector<int>> adjM(N+1, vector<int>(N+1, 0));
        for(int i=0; i<M; i++) adjM[e[i][0]][e[i][1]] = e[i][2];
        cout<<"The adjacency matrix representation of the given flow network is: \n";
        printMat(adjM, N);
        int s = 1;
        int t = N;
        return edmondsKarpAlgo(s, t, adjM, e, N);
        return edmondsKarpAlgo(s, 6, adjM, e, N);
    }
};

int main() {
    int t;
    cin>>t;
    while(t--) {
        int i,j,N,M,u,v,w;
        int res;
        cin>>N>>M;
        vector<vector<int>> Edges;
        for(i=0;i<M;i++)
        {
            cin>>u>>v>>w;
        	Edges.push_back({u,v,w});
    	}
        Solution obj;
        res = obj.solve(N, M, Edges);
        cout<<res<<endl;
    }
    return 0;
}

/* Sample input: CLRS Figure 26.6
1
6 9
1 2 16 1 3 13 2 4 12 3 2 4 3 5 14 4 3 9 4 6 20 5 4 7 5 6 4
Output: 23
*/
