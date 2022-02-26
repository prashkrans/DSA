/* Graph problem - #13.2. Transitive Course
Given a directed graph, find out if a vertex j is reachable from another vertex i for all vertex pairs (i, j) in the 
given graph. Here reachable mean that there is a path from vertex i to j. The reach-ability matrix is called transitive 
closure of a graph. The directed graph is represented by adjacency matrix graph where there are N vertices.
The reachability matrix is called transitive closure of a graph
Note - here, graph[i][j] = 1 if there is a direct path from u to v and 0 if no direct path extists from u to v
gfg - https://practice.geeksforgeeks.org/problems/transitive-closure-of-a-graph0930/1
*/

//	Method 1 - Floyd-Warshall Algorithm
//	Running time = O(n^3) i.e. cubic where n = the no. of vertices
//	Auxiliary space = O(1)
//	If dist[u][v] = INT_MAX then no path exists from u to v 
//	else if dist[u][v] != INT_MAX then their exists a path from u to v
//	Refer problem 10.1

//	Method 2 - Modified Floyd-Warshall algo
//	Running time = O(n^3) i.e. cubic but marginally better than Floyd-Warshall algo
//	Auxiliary space = O(n^2) due to a new boolean matrix reach[][]


#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> transitiveClosure(int N, vector<vector<int>> graph) {
        vector<vector<int>> reach = graph;
        for(int k=0; k<N; k++)
            for(int i=0; i<N; i++) 
                for(int j=0; j<N; j++) {	//	modify this if INT_MAX was used to represent that no path extists from u to v
                    reach[i][j] = (reach[i][j] || (reach[i][k] && reach[k][j]));
                }
        for(int i=0; i<N; i++) reach[i][i] = 1;
        return reach;
    }
};

int main() {
    int t;
    cin>>t;
    while(t--){
        int N;
        cin>>N;
        vector<vector<int>> graph(N, vector<int>(N, -1));
        for(int i = 0;i < N;i++)
            for(int j=0;j<N;j++)
            cin>>graph[i][j];
        
        Solution ob;
        vector<vector<int>> ans = ob.transitiveClosure(N, graph);
        for(int i = 0;i < N;i++)
            {for(int j = 0;j < N;j++)
                cout<<ans[i][j]<<" ";
        cout<<"\n";}
    }
    return 0;
}