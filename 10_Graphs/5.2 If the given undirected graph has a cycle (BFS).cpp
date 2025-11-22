/*	Graph Problem #8.2. - Given an undirected graph, find whether it has a cycle.
    This problem could be solved using three methods
    1.  DFS + parent variable
    2.  BFS + parent array
    3.  Union-find algorithm    (Avoid using find() and union() instead use findSet() and unionOfSets())
*/

//	Method 2. BFS + Parent Array (instead of parent variable in DFS)
//	Steps
//	1.	Do a BFS traversal of the given graph.
//	2.	For every visited vertex ‘v’, if there is an adjacent ‘u’ such that u is already visited
//		and u is not a parent of v, then there is a cycle in the graph.
//	3.	If we don’t find such an adjacent for any vertex, we say that there is no cycle.

//	Running time = O(BFS) = O(n+m) = O(m) = O(E)
//	Auxiliary space = O(n) = O(V) to store the visited and the parent arrays

#include<iostream>
#include<map>
#include<list>
#include<queue>
using namespace std;

template<typename dataType>             //  Generally use as template<typename T>
class graph {
	map<dataType, list<dataType>> adjList;
public:
	void addEdge(dataType u, dataType v) {
		adjList[u].push_back(v);
		adjList[v].push_back(u);
	}
	void printAdjList() {
		for(auto v : adjList) {
			cout<<v.first<<" -> ";
			for(auto w : v.second) cout<<w<<" ";
			cout<<"\n";
		}
	}
	bool hasCycleBFSHelper(dataType v, map<dataType, bool> visited, map<dataType, dataType> parent) {
		queue<dataType> Q;
		Q.push(v);
		visited[v] = 1;
		while(!Q.empty()) {
			dataType curr = Q.front();
			Q.pop();
			for(auto u : adjList[curr]) {
				if(!visited[u]) {
					Q.push(u);
					visited[u] = 1;
					parent[u] = curr;
				}
				else {                  //  i.e. if u is already visited and if u is not the parent of curr then a cycle exists
					if(parent[curr]!=u) return true;
				}
			}
		}
		return false;
	}
	bool hasCycleBFS() {
		map<dataType, bool> visited;
		map<dataType, dataType> parent;
		bool ans = 0;
		for(auto v : adjList) {
			if(!visited[v.first]) ans = hasCycleBFSHelper(v.first, visited, parent);
			if(ans==1) break;
		}
		return ans;
	}
};

int main() {
	graph<char> G;
	G.addEdge('A', 'B');	G.addEdge('A', 'C');
	G.addEdge('C', 'D');	G.addEdge('C', 'E');
	//G.addEdge('D', 'E');  //  makes G cyclic
	//G.addEdge('B', 'D');  //  makes G cyclic
	G.addEdge('F', 'G');    //  makes the no. of cc = 2
	G.printAdjList();
	if(G.hasCycleBFS()) cout<<"The given undirected graph G has a cycle\n";
	else cout<<"The given undirected graph G has no cycle\n";
	return 0;
}
