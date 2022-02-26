/* 	Graph Problem - #12.1.1b. LC#684. Redundant Connection
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

class Solution {
public:
    int findSet(int u, vector<int> setID) {
        if(setID[u] == u) return u;
        else return findSet(setID[u], setID);
    }
    void unionOfSets(int u, int v, vector<int> &setID) {
        int r1 = findSet(u, setID);
        int r2 = findSet(v, setID);
        setID[r1] = setID[r2];
    }
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {	// edges.size() == n and edges[0].size() == 2 
        int V = edges.size();
        vector<int> setID(V+1);
        vector<int> ans;
        for(int i = 1; i<=V; i++) setID[i] = i;
        for(int i=0; i<edges.size(); i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            if(findSet(u, setID)==findSet(v, setID)) {					//	using the union-find algo to detect that if an edge is include it creates a cycle or not
                ans = {u, v};
                break;
            }
            else unionOfSets(u, v, setID);
        }
        return ans;
    }
};