// LC# 1584. NCAG3. Min Cost to Connect All Points

// Approach: Convert the math problem to edges so, that Kruskal's algo can be used to find MST from the graph. 
// No need to create adjacency list
// Two methods to find Minimum Spanning Tree for an undirected graph. a. Kruskal's Algo     b. Modified Prim's Algo

// Method 2. Modified Prims Algo
// Running time: O(mlogn) ~ O(n^2logn) as m = n(n-1)/2
// Auxiliary space: Adjacency list: O(m) ~ O(n²) - storing edges between all pairs of points


class Solution {
    public:
        int minCostConnectPoints(vector<vector<int>>& points) {
            int minCostMST = 0;
            int n = points.size();          // Each point represents a node say 0 to n-1
            // int m = (n*(n-1))/2;         // There would be an edge between each pair of points i.e. nC2
            vector<vector<pair<int, int>>> adjL(n, vector<pair<int, int>>());    // Need adjList instead of edges here
            for(int i=0; i<n; i++) {
                for(int j=i+1; j<n; j++) {
                    int x1 = points[i][0];  int x2 = points[j][0];
                    int y1 = points[i][1];  int y2 = points[j][1];
                    int manhattanDist = abs(x1-x2) + abs(y1-y2);
                    adjL[i].push_back({j, manhattanDist});
                    adjL[j].push_back({i, manhattanDist});  // Note: MST exists for an undirected graph
                }
            }
            set<pair<int, int>> setPq;
            vector<int> inMstSet(n, 0);
            vector<int> cost(n, INT_MAX);
            for(int i=1; i<n; i++) setPq.insert({INT_MAX, i});
            setPq.insert({0, 0}); // Taking root node as 0
            inMstSet[0] = 1;
            cost[0] = 0;
            while(!setPq.empty()) {
                int u = setPq.begin()->second;
                int wt = setPq.begin()->first;
                inMstSet[u] = 1;
                minCostMST += wt;
                setPq.erase(setPq.begin());
                for(auto i: adjL[u]) {
                    int v = i.first;
                    int wt_uTov = i.second;
                    if(!inMstSet[v]) {
                        if(wt_uTov < cost[v]) {
                            auto it = setPq.find({cost[v], v});
                            if(it!=setPq.end()) setPq.erase(it);
                            cost[v] = wt_uTov;
                            setPq.insert({cost[v], v});
                        }
                    }
                }
            }
            return minCostMST;
        }
    };