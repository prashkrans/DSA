// LC# 1584. NCAG3. Min Cost to Connect All Points

// Approach: Convert the math problem to edges so, that Kruskal's algo can be used to find MST from the graph. 
// No need to create adjacency list
// Two methods to find Minimum Spanning Tree for an undirected graph. a. Kruskal's Algo     b. Modified Prim's Algo

// Method 1. Kruskal's Algo
// Running time: O(mlogm + m*(find()+union())) where m * (find() + union()) → O(m * α(n)) ≈ O(m) Thus, R.T. becomes O(mlogm) where 
// m = (n(n-1))/2 thus R.T. = O(n^2log(n^2)) = O(2(n^2logn)) ~ O(n^2logn)
// Auxiliary space: O(m) ~ O(n^2) due to the edges array

// Note: Where α(n) is the inverse Ackermann function, which grows extremely slowly. 
// For all practical values of n (even up to the size of the universe), α(n) ≤ 5


// Note: cmp class is not required if we declare edges vector as vector<pair<int, pair<int, int>> edges; 
// where edges[i].first = wt, edges[i].second.first = u and edges[i].second.second = v
class cmp {
    public:
        bool operator()(vector<int> &a, vector<int> &b) const {
            return a[2] < b[2];
        }
    };
    
    class Solution {
    public:
        int find(int u, vector<pair<int, int>> &subset) {
            int parent = subset[u].first;
            if(u==parent) return u;
            else return subset[parent].first = find(parent, subset);
        }
    
        void unionOfSets(int u, int v, vector<pair<int, int>> &subset) {
            int uRoot = find(u, subset);        int vRoot = find(v, subset);
            int uRank = subset[uRoot].second;   int vRank = subset[vRoot].second;
            int mergedRank = uRank + vRank;
            int newRoot = (uRank <= vRank) ? vRoot : uRoot;
            subset[uRoot] = {newRoot, mergedRank};
            subset[vRoot] = {newRoot, mergedRank};
        }
    
        int minCostConnectPoints(vector<vector<int>>& points) {
            int minCostMST = 0;
            int n = points.size();  // Each point represents a node say 0 to n-1
            int m = (n*(n-1))/2;       // There would be an edge between each pair of points i.e. nC2
            vector<vector<int>> edges; // 2D array where each row is u, v, wt
            for(int i=0; i<n; i++) {
                for(int j=i+1; j<n; j++) {
                    int x1 = points[i][0];  int x2 = points[j][0];
                    int y1 = points[i][1];  int y2 = points[j][1];
                    int manhattanDist = abs(x1-x2) + abs(y1-y2);
                    edges.push_back({i, j, manhattanDist});
                }
            }
            // for(auto i: edges) cout<<i[0]<<", "<<i[1]<<" | "<<i[2]<<endl;
            sort(edges.begin(), edges.end(), cmp());
            // for(auto i: edges) cout<<i[0]<<", "<<i[1]<<" | "<<i[2]<<endl;
    
            vector<pair<int, int>> subset(n, pair<int, int>());
            for(int i=0; i<n; i++) subset[i] = {i, 1};
    
            for(int i=0; i<edges.size(); i++) {
                int u = edges[i][0];
                int v = edges[i][1];
                int wt = edges[i][2];
                if(find(u, subset) != find(v, subset)) {
                    minCostMST += wt;
                    unionOfSets(u, v, subset);
                }
            }
            return minCostMST;
        }
    };