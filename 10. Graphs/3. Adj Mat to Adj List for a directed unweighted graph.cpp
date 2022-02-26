/*	Graph Problem #6 - Represent the adjacent matrix of a directed unweighted graph using an adjacency list
	Given the adjacent matrix of a directed unweighted graph, represent it using an adjaceny list.
	Now, adjacent matrices are square matrices but here we could have a partial adjacent matrix (m x n) that is not square.
	adjMat[i][j] = '0' if not edge(i, j) doest not exist or '1' otherwise
*/
//	Running time = O(n*n) if n is larger or O(m*m) otherwise
//	Auxiliary space = O(n) or O(V). Since, an extra visited array is needed of size V
//	Note - However the space reqd. for adjacency matrix is O(n+m) (average cases) & O(n^2) (worst case)

#include<iostream>
#include<map>
#include<unordered_map>
#include<list>
#include<queue>
using namespace std;

class graph {
	map<int, list<int>> adjL;				//	Using an ordered map so that it stores the neighbours in a sorted manner
	vector<int> visited;					//	Using a vector instead of a map to store visited[v] and the value of v varies from 1 to n
public:
	graph(int x) {
		visited.resize(x, 0);
	}
	void addEdge(int x, int y) {
            adjL[x].push_back(y);
            //adjL[y].push_back(x);         //  [#IMP] - Here we are converting a adjMat to adjL which already contains both (u, v) and (v, u)
	}                                       //  hence, no need to push x in y as x in y would already be put from the matrix itself
	void printAdjL() {
		for(auto i : adjL) {
			cout<<i.first<<" -> ";
			for(auto j : i.second) cout<<j<<", ";
			cout<<'\n';
		}
	}
	int CC() {
		int ans = 0;
		for(int i=0; i<visited.size(); i++) {
			if(visited[i]==0) BFS(i, ++ans);
		}
		//for(int i=0; i<visited.size(); i++) {
        //    cout<<'Vertex '<<i<<' lies in CC#'<<visited[i]<<'\n';
		//}
		return ans;
	}
	void BFS(int src, int ans) {			//	Use of BFS and CC is optional
		queue<int> Q;						//	Could have used an array too since the value of node is an integer
		Q.push(src);						//	BFS uses a queue while DFS uses a stack or recursion
		visited[src] = ans;					//	ans would vary from 1 to no. of connected components
		while(!Q.empty()) {
			int curr = Q.front();
			Q.pop();
			for (auto i : adjL[curr]) {
				if(!visited[i]) {
					Q.push(i);
					visited[i] = ans;
				}
			}
		}
	}
};

class Solution {
public:
    int adjMatToadjList(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int l = (m>=n) ? m : n;
        graph G(l);
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                if(grid[i][j] == '1') {
                    G.addEdge(i, j);
                }
            }
        }
        G.printAdjL();
        return G.CC();
    }
};

int main() {
	int m, n;
	//cin>>m, n;
	m = 4; n = 5;
	vector<vector<char>> grid(m, vector<char>(n));
	//for(int i=0; i<m; i++) {
	//	for(int j=0; j<n; j++) cin>>grid[i][j];
	//}
	grid = {{'1','1','1','1','0'},
            {'1','1','0','1','0'},
            {'1','1','0','0','0'},
            {'0','0','0','0','0'}};
	Solution s;
	s.adjMatToadjList(grid);
	return 0;
}
