/* Graph problem #14.1. - LC#785. Is Graph Bipartite?
There is an undirected graph with n nodes, where each node is numbered between 0 and n - 1.
The graph is given as an adjacency list as vector of vectors.
Return true if and only if it is bipartite.
Constraints:
1. 	no self edges
2.	no parallel edges
3. 	graph may not be connected

A graph is bipartite if the nodes can be partitioned into two independent sets A and B such that 
every edge in the graph connects a node in set A and a node in set B.
A bipartite graph cannot have an odd cycle i.e a cycle with odd no. of edges.
Maximum no. edges in an undirected bipartite graph = floor(n*n/4)
Generally, we are given an undirected graph to check whether it is bipartite.
*/
//	Method 1. BFS + level array
//	Working principle: In the BFS if we find an edge, both of whose endpoints are in the same level
//	then G is not bipartite.

//	Method 1a. - BFS + level check inside the BFS itself
//	Running time = O(BFS) = O(n+m) ~ O(m)
//	Auxiliary space = O(n) or O(V)

class Solution {
public:
    bool BFS(int src, vector<int> &visited, vector<int> &level, vector<vector<int>> graph) {
        queue<int> Q;
        Q.push(src);
        visited[src] = 1;
        level[src] = 0;
        while(!Q.empty()) {
            int u = Q.front();
            Q.pop();
            vector<int>::iterator it;
            for(it=graph[u].begin(); it!=graph[u].end(); it++) {
                int v = *it;
                if(!visited[v]) {			//	If v is not visited => level v would be level u + 1 hence, not equal
                    Q.push(v);
                    visited[v] = 1;
                    level[v] = level[u]+1;
                }
                else if(visited[v]) {		//	If v is visited => if level u == level v then G has edges in the same levels i.e. G is not bipartite
                    if(level[u]==level[v]) return 0;
                }
            }
        }
        return 1;							//	If program reaches here => that no edges were in the same level, hence G is bipartite
    }
    
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();  
        vector<int> visited(n, 0);
        vector<int> level(n, -1);
        bool ans = 1;
        for(int u=0; u<n; u++) {
            if(!visited[u]) ans = BFS(u, visited, level, graph);
            if(ans==0) return ans;
        }
        return ans;        
    }
};

//	Method 1b. - BFS + level check after BFS is completed
//	Running time = O(BFS + m) = O(n + 2m) ~ O(m)
//	Auxiliary space = O(n) or O(V)

class Solution {
public:
    void BFS(int src, vector<int> &visited, vector<int> &level, vector<vector<int>> graph) {
        queue<int> Q;
        Q.push(src);
        visited[src] = 1;
        level[src] = 0;
        while(!Q.empty()) {
            int u = Q.front();
            Q.pop();
            vector<int>::iterator it;
            for(it=graph[u].begin(); it!=graph[u].end(); it++) {
                int v = *it;
                if(!visited[v]) {
                    Q.push(v);
                    visited[v] = 1;
                    level[v] = level[u]+1;
                }
            }
        }
    }
    
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();  
        vector<int> visited(n, 0);
        vector<int> level(n, -1);
        bool ans = 1;
        for(int u=0; u<n; u++) {
            if(!visited[u]) BFS(u, visited, level, graph);
        }
        for(int u = 0; u<n; u++) {
            vector<int>::iterator it;
            for(it=graph[u].begin(); it!=graph[u].end(); it++) {
                int v = *it;
                if(level[u]==level[v]) {
                    ans = 0; 
                    return ans;
                }
            }
        }
        for(auto i : level) cout<<i<<" ";   cout<<"\n";
        for(auto i : visited) cout<<i<<" "; cout<<"\n";
        return ans;        
    }
};