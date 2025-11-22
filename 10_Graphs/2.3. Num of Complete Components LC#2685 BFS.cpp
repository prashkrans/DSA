// LC# 2685. Count the Number of Complete Components
/**
Hint 1 Find the connected components of an undirected graph using depth-first search (DFS) or breadth-first search (BFS).
Hint 2 For each connected component, count the number of nodes and edges in the component.
Hint 3 A connected component is complete if and only if the number of edges in the component is equal to m*(m-1)/2, 
where m is the number of nodes in the component.
**/
class Solution {
    public:
        pair<int, int> bfs(int src, vector<vector<int>> &adjL, vector<int> &visited) {
            int countNodes = 0;
            vector<pair<int, int>> edges;
            queue<int> q;
            q.push(src);
            visited[src] = 1;
            countNodes++;
            while(!q.empty()) {
                int u = q.front();
                q.pop();
                for(auto v: adjL[u]) {
                    edges.push_back({u, v});
                    if(!visited[v]) {
                        q.push(v);
                        visited[v] = 1;
                        countNodes++;
                    }
                }
            }
            // cout<<"countNodes: "<<countNodes<<"\n";
            // cout<<"edges size: "<<edges.size()<<"\n";
            // for(auto i: edges) cout<<i.first<<"->"<<i.second<<" | ";
            // cout<<endl;
            return {countNodes, edges.size()/2};
        }
    
        int countCompleteComponents(int n, vector<vector<int>>& edges) {
            int m = edges.size();
            int numOfCompleteComp = 0;
            vector<vector<int>> adjL(n, vector<int>());
            vector<int> visited(n, 0);
            for(int i=0; i<m; i++) {
                int u = edges[i][0];
                int v = edges[i][1];
                adjL[u].push_back(v);
                if(u!=v) adjL[v].push_back(u);
            }
            for(int i=0; i<n; i++) {
                if(!visited[i]) {
                    auto [currNodes, currEdges] = bfs(i, adjL, visited);
                    if(currEdges == (currNodes*(currNodes-1))/2) numOfCompleteComp++;
                }
            }
            return numOfCompleteComp;        
        }
    };