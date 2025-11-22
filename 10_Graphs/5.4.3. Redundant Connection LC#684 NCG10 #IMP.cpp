// LC#684. NCG10. Redundant Connection
// Refer topics 5.3 union by rank and 5.4 union by height

// Approach: Using Union-Find algorithm (or Disjoint Set Union) with union by rank/height and path compression
// Time Complexity: O(find()*edges + union()*vertices)
//      Since O(find()) = O(1) due to path compression and O(union()) = O(find()) = O(1) hence
//      Time complexity becomes O(1*m + 1*n) i.e. O(n+m) or O(V+E)

// Method 1a. Union by Rank and path compression
// Running time: O(find()*edges + union()*vertices) ~ O(n+m) Since n == m here => O(2n) ~ O(n)
// Auxiliary space: O(V) i.e. O(n) due to the unordered_map subset with max size == no. of vertices


class Solution {
    public:
        pair<int, int> findSet(int u, unordered_map<int, pair<int, int>> &subset) {
            int parent = subset[u].first;
            if(u == parent) return subset[u];
            else {
                subset[u] = findSet(parent, subset); // Path compression i.e. making the parents of all the nodes in a set as the set's root
                return subset[u];
            }
        }
    
        void unionOfSets(int u, int v, unordered_map<int, pair<int, int>> &subset) {
            pair<int, int> uSet = findSet(u, subset);
            pair<int, int> vSet = findSet(v, subset);
            int uRoot = uSet.first;     int uRank = uSet.second;
            int vRoot = vSet.first;     int vRank = vSet.second;
    
            int mergedRank = uRank + vRank;
            int newRoot = (uRank <= vRank) ? vRoot : uRoot;
            subset[uRoot] = {newRoot, mergedRank};
            subset[vRoot] = {newRoot, mergedRank};
    
            // Using auto keyword C++17 onwards
            // auto [uRoot, uRank] = findSet(u, subset);unorderd_map
            // if(vRank <= uRank) {
            //     subset[vRank] = {uRoot, mergedRank};
            //     subset[uRank].second = mergedRank;
            // } else {
            //     subset[uRank] = {vRoot, mergedRank};
            //     subset[vRank].second = mergedRank;
            // }
    
            // debug
            // cout<<uRoot<<", "<<uRank<<" | ";
            // cout<<vRoot<<", "<<vRank<<" | ";
            // cout<<newRoot<<", "<<mergedRank<<endl;
        }
    
        vector<int> findRedundantConnection(vector<vector<int>>& edges) {
            // Using Union-Find algorithm (or Disjoint Set Union) with union by rank and path compression
            unordered_map<int, pair<int, int>> subset;
            int n = edges.size(); // Given m = n-1+1 i.e. m = n
            vector<int> ans;
            for(int i=1; i<=n; i++)
                subset[i] = make_pair(i, 1);
            for(int i=0; i<n; i++) {
                int u = edges[i][0];
                int v = edges[i][1];
                if(findSet(u, subset) != findSet(v, subset)) unionOfSets(u, v, subset);
                else ans = {u, v};
            }
            return ans;   
        }
    };
    

// Method 1b. Union by Height and path compression
// Running time: O(find()*edges + union()*vertices) ~ O(n+m) Since n == m here => O(2n) ~ O(n) (0ms beats 100%)
// Auxiliary space: O(V) i.e. O(n) due to the vector<pair<int, int>> subset with max size == no. of vertices

class Solution {
    public:
        // Path compression i.e. making the parents of all the nodes in a set as the set's root 
        int findSet(int u, vector<pair<int, int>> &subset) {
            int parent = subset[u].first;
            if(u == parent) return subset[u].first;
            else
                return subset[u].first = findSet(parent, subset);
        }
    
        // Union by Height (initial height = 0 and has three cases unlike union by rank which has initial rank = 1 and only two cases)
        void unionOfSets(int u, int v, vector<pair<int, int>> &subset) {
            int uRoot = findSet(u, subset);     int uHeight = subset[uRoot].second;
            int vRoot = findSet(v, subset);     int vHeight = subset[vRoot].second;
    
            if(uHeight <= vHeight) {
                subset[uRoot].first = vRoot;
                if(uHeight == vHeight) subset[vRoot].second++;
            }
            else if(uHeight > vHeight) subset[vRoot].first = uRoot;
        }
    
        // Using Union-Find algorithm (or Disjoint Set Union) with union by rank and path compression
        vector<int> findRedundantConnection(vector<vector<int>>& edges) {
            int n = edges.size(); // Given m = n-1+1 i.e. m = n
            vector<pair<int, int>> subset(n+1, pair<int, int>()); // Since nodes vary from 1 to n
            for(int i=1; i<n+1; i++) subset[i] = {i, 0}; // Init: parent of a node is node itself with initial height = 0
            vector<int> ans;
            for(int i=0; i<n; i++) {
                int u = edges[i][0];
                int v = edges[i][1];
                if(findSet(u, subset) == findSet(v, subset)) return {u, v};
                else unionOfSets(u, v, subset);
            }
            return vector<int>();
        }
    };