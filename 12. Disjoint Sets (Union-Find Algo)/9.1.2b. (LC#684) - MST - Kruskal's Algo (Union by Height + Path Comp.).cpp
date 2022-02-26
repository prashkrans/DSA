/* 	Graph Problem - #12.1.2b. LC#684. Redundant Connection (Union by Height + Path Compression)
	In this problem, a tree is an undirected graph that is connected and has no cycles.
	You are given a graph that started as a tree with n nodes labeled from 1 to n, with 
	one additional edge added. The added edge has two different vertices chosen from 1 to n, 
	and was not an edge that already existed. The graph is represented as an array edges of 
	length n where edges[i] = [ai, bi] indicates that there is an edge between nodes ai & bi
	in the graph. Return an edge that can be removed so that the resulting graph is a tree 
	of n nodes. If there are multiple answers, return the answer that occurs last in the input.
	
	Constraints:
	a.	There are no repeated edges.
	b.	The given graph is connected.
	
	Example 1:
	Input: edges = [[1,2],[1,3],[2,3]]
	Output: [2,3]
*/

//	Running time = O(Sorting m edges + U(n-1) + 2F(m)) ~ O(0 + Un + Fm) ~ O(n + m) as O(U) = O(F) ~ O(1)
//	Auxiliary space = O(n) or O(V) due to the subset vector
//	Note: Using union by height + PC reduced the R.T. from 36ms to 4ms 

class Solution {
public:
    int findSet(int u, vector<pair<int, int>> &subset) {
		int parent = subset[u].first;
        if(parent == u) return u;
		else {
			subset[u].first = findSet(parent, subset);					//	Path compression
			return subset[u].first;
		}        
    }
    void unionOfSets(int u, int v, vector<pair<int, int>> &subset) {
        int r1 = subset[u].first;	int r2 = subset[v].first;
		int h1 = subset[u].second;	int h2 = subset[v].second;
		if(h1 < h2) subset[r1].first =  r2;
		else if(h1 > h2) subset[r2].first = r1;
		else {
			subset[r1].first = r2;
			subset[r2].second++;
		}
    }
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {	// edges.size() == n and edges[0].size() == 2 
        //	Since the graph is unweighted, all edge lengths can be considered to be the same hence sorting is not required.
		int V = edges.size();
        vector<pair<int, int>> subset(V+1);
        vector<int> ans;
        for(int i = 1; i<=V; i++) subset[i] = {i, 0};					//	Union by height
        for(int i=0; i<edges.size(); i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            if(findSet(u, subset)==findSet(v, subset)) {				//	using the union-find algo to detect that if an edge is included, it creates a cycle or not
                ans = {u, v};
                break;
            }
            else unionOfSets(u, v, subset);
        }
        return ans;
    }
};