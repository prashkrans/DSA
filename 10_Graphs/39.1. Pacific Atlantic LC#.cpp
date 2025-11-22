// LC#417. NCG5. Pacific Atlantic Water Flow

// Method 1. DFS + Two Sets Pacific and Atlantic
// Method 2. BFS + Two sets/vectors Pacific and Atlantic (TODO)

// Running time: O(m*n) 
// Auxiliary time: O(m*n) due to pacific and atlantic sets

// Note: unordered_set doesn't work with pair<int, int> so use set<pair<int, int>> st;


class Solution {
    public:
    
        void dfs (int ui, int uj, int &m, int &n, vector<vector<int>> &heights, set<pair<int, int>> &st) {
            st.insert({ui, uj});
            vector<pair<int, int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
            for(auto dir: dirs) {
                int vi = ui + dir.first;
                int vj = uj + dir.second;
                if((vi>=0 && vi<m && vj>=0 && vj<n) && heights[ui][uj] <= heights[vi][vj] && st.find({vi, vj})==st.end())
                    dfs(vi, vj, m, n, heights, st);
            }
            
        }
    
        vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
            vector<vector<int>> ans;
    
            int m = heights.size(); // Leetcode uses m x n instead of n x m
            int n = heights[0].size();
            set<pair<int, int>> pacific;  // top left 
            set<pair<int, int>> atlantic; // bottom right
    
            for(int j=0; j<n; j++) dfs(0, j, m, n, heights, pacific);   // top
            for(int i=0; i<m; i++) dfs(i, 0, m, n, heights, pacific);   // left
    
            for(int j=0; j<n; j++) dfs(m-1, j, m, n, heights, atlantic);    // bottom
            for(int i=0; i<m; i++) dfs(i, n-1, m, n, heights, atlantic);    // right
    
            for(auto p: pacific) {  // find the common pair of i, j in both pacific and atlantic
                if(atlantic.find(p)!=atlantic.end()) 
                    ans.push_back({p.first, p.second});
            }
    
            return ans;
        }
    };


// Method 2. BFS + Two sets/vectors Pacific and Atlantic (TODO)