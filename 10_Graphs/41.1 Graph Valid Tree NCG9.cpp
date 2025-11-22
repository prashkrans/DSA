// NCG9 Graph Valid Tree
// Leetcode premium
// Lintcode #178

// Approach: A tree is a graph that is 
// 1. undirected +  2. connected + 3. has no cycles
// 

// Method 1. DFS with parent variable instead of an array. 
// We start with src = 0 check whether all the nodes are visited i.e. is connected
// Better approach as it uses parent variable instead of parent array. 

// the fact m == n-1 could be mean two or more trees that are not connected
// E.g. 
// n = 10
// edges=[[0,1],[5,6],[6,7],[9,0],[3,7],[4,8],[1,8],[5,2],[5,3]]
// There are two trees hence not connected

// Approach: A tree is a graph that is 
// 1. undirected +  2. connected + 3. has no cycles

class Solution {
    public:
        bool isTreeDfs(int u, vector<vector<int>> &adjL, vector<int> &visited, int parent) {
            visited[u] = 1;
            for(auto v: adjL[u]) {
                if(!visited[v]) {
                    if(isTreeDfs(v, adjL, visited, u)==false) return false;
                }
                else {
                    if(v == u) return false;                                // for an edge from u to u (not v)
                    else if(parent != -1 && v != parent) return false;      // if a node v is already visited it should then be a parent of u else a cycle exists
                }
            }
            return true;
        }
    
        bool validTree(int n, vector<vector<int>>& edges) {
            vector<vector<int>> adjL(n, vector<int>());
            vector<int> visited(n, 0);
            int parent = -1;
            
            int m = edges.size();
            // if (m != n-1) return false; This doesn't cover all the cases

            for (int i = 0; i<m; i++) {
                int u = edges[i][0];
                int v = edges[i][1];
                adjL[u].push_back(v);
                if(u!=v) adjL[v].push_back(u);  // Since its an undirected graph
            }
            bool ans = isTreeDfs(0, adjL, visited, parent);
    
            for(int i=0; i<n; i++) // This is required, the fact m == n-1 could be mean two or more trees that are not connected
                if(visited[i]==0) return false; // To check if the graph is connected
            return ans;
        }
    };
    


// Method 1b. DFS with parent array + checking visited array if all the nodes get visited from src == 0 
// Running time: O(V+E) or O(n+m)
// Auxiliary spae: O(V) or O(n) due to the recursion stack, visited and parent

class Solution {
    public:
        bool isTreeDfs(int u, vector<vector<int>> &adjL, vector<int> &visited, vector<int> &parent) {
            visited[u] = 1;
            for(auto v: adjL[u]) {
                if(!visited[v]) {
                    parent[v] = u;
                    if(isTreeDfs(v, adjL, visited, parent)==false) return false;
                }
                else {
                    if(v == u) return false;                                    // for an edge from u to u (not v)
                    else if(parent[u] != -1 && parent[u] != v) return false;    // if a node v is already visited it should then be a parent of u else a cycle exists
                }
            }
            return true;
        }
    
    
        bool validTree(int n, vector<vector<int>>& edges) {
            vector<vector<int>> adjL(n, vector<int>());
            vector<int> visited(n, 0);
            vector<int> parent(n, -1);
            int m = edges.size();
            for (int i = 0; i<m; i++) {
                int u = edges[i][0];
                int v = edges[i][1];
                adjL[u].push_back(v);
                if(u!=v) adjL[v].push_back(u);  // Since its an undirected graph
            }
            bool ans = isTreeDfs(0, adjL, visited, parent);
    
            // int x = 0;
            // for(auto i: adjL) {
            //     cout<<x++<<" -> ";
            //     for(auto v: i) cout<<v<<" ";
            //     cout<<endl;
            // }
            // for (auto i: parent) cout<<i<<" "; 
            // cout<<endl;
            // for (auto i: visited) cout<<i<<" "; 
            // cout<<endl;
    
            for(int i=0; i<n; i++) 
                if(visited[i]==0) return false; // To check if the graph is connected
            return ans;
        }
    };
    

// Method 2. Using BFS and queue<pair<int, int>> q that pushes a pair of {v, parent of v i.e. u} instead of 
// a parent array.
// Running time: O(V+E) or O(n+m)
// Auxiliary spae: O(V) or O(n) due to the queue
class Solution {
    public:    
        bool validTree(int n, vector<vector<int>>& edges) {
            vector<vector<int>> adjL(n, vector<int>());
            vector<int> visited(n, 0);
            
            int m = edges.size();
            // if (m != n-1) return false; This doesn't cover all the cases

            for (int i = 0; i<m; i++) {
                int u = edges[i][0];
                int v = edges[i][1];
                adjL[u].push_back(v);
                if(u!=v) adjL[v].push_back(u);  // Since its an undirected graph
            }

            queue<pair<int, int>> q;
            q.push({0, -1});
            visited[0] = 1;
            while(!q.empty()) {
                auto [u, parent] = q.front();
                q.pop();
                for(auto v: adjL[u]) {
                    if(!visited[v]) {
                        q.push({v, u});
                        visited[v] = 1;
                    }
                    else {
                        if(v != parent) return false;
                    }
                }
            }
    
            for(int i=0; i<n; i++) // This is required, the fact m == n-1 could be mean two or more trees that are not connected
                if(visited[i]==0) return false; // To check if the graph is connected
            return true;
        }
    };

