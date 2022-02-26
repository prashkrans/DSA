/*	Graph Problem #5.1b. - LC#323. No. of connected components (Premium)
	Given n, i.e. total number of nodes in an undirected graph numbered from 1 to n and an integer e, i.e. 
	total number of edges in the graph. Calculate the total number of connected components in the graph. 
	A connected component is a set of vertices in a graph that are linked to each other by paths.
	https://www.hackerearth.com/problem/algorithm/connected-components-in-a-graph/
*/
//	Running time = O(n+m) = O(V+E) as summation over (v + degree(v))
//	But in a connected graph m >= n-1 hence it becomes O(m) or O(E)
//	Auxiliary space = O(n) or O(V). Since, an extra visited array is needed of size V


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
	graph(int n) {
		visited.resize(n+1, 0);
	}
	void addEdge(int x, int y) {
		if(y==-1) adjL[x].push_back(-1);    //  If a vertex has no edges to any other vertex
		else {
            adjL[x].push_back(y);
            adjL[y].push_back(x);
		}
	}
	void printAdjL() {
		for(auto i : adjL) {
			cout<<i.first<<" -> ";
			for(auto j : i.second) if(j!=-1) cout<<j<<", ";
			cout<<"\n";
		}
	}
	int CC() {
		int ans = 0;
		for(int i=1; i<visited.size(); i++) {
			if(visited[i]==0) BFS(i, ++ans);
		}
		//for(int i=1; i<visited.size(); i++) {
        //    cout<<"Vertex "<<i<<" lies in CC#"<<visited[i]<<"\n";
		//}
		return ans;
	}
	void BFS(int src, int ans) {
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

int main() {
	int n, m;
	cin>>n>>m;
	int u, v;
	graph G(n);
	for(int i=0; i<m; i++) {
		cin>>u>>v;
		G.addEdge(u, v);
	}
	//G.printAdjL();
	cout<<G.CC();
	return 0;
}
