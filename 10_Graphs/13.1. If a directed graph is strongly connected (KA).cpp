/* Graph problem #16.1. Strong Connectivity in a directed graph (Kosaraju's Algo).
Given a directed graph, find whether it is strongly connected.
Note - This graph has either a single SCC or multiple SCCs. 
If the G has a single SCC, return true
else return false.

There are three methods to find if a directed graph is strongly connected:
	1. 	Naive solution: n*DFS => R.T. = O(nm) or O(n^3) thus, inefficient.
	2.	Another naive solution: Using transitive course or Floyd Warshall algorithm => R.T. = O(n^3) again, inefficient.
	3.	Kosaraju's algorithm: Developed by S. Rao Kosaraju (IITKGP). Here R.T. = O(m) but uses 2 DFS
	4.	Tarjan's algorithm: Here R.T. = O(m) but uses a single DFS
*/

//	Method 3. Kosaraju's Algorithm (For a single SCC)
//	Steps:
//	1. 	Pick any arbitrary vertex v and do DFS(v). If all the vertices are not visited then return false.
//	2.	Reverse the directions of all the edges in the graph G or a copy of the graph G.
//	3.	Do a DFS(v) again using the same source vertex v. If all the vertices are not visited then return false.
//		Only if all the vertices are visited in both the DFSs, G is strongly connected.
//	Running time = 2*O(DFS) + O(m) i.e. 2 DFSs used and m edges reversed
//				 = O(2*(n+m) + m) ~ O(n+m) ~ O(m) i.e. O(E)
//	Auxiliary space = O(m) if G itself is reverse or O(n+m) if a copy of G is created and then reversed
//	To reverse G itself we would first have to store edges i.e. O(m), then clear G and use the vector of edges to create 
//	the reversed G in G itself.

#include<iostream>
#include<map>
#include<list>
using namespace std;

template<typename T>
class graph {
	map<T, list<T>> adjL;
public:
    map<T, list<T>> returnAdjL() {
        return adjL;
    }
    void printVisited(map<T, int> visited) {
        cout<<"The visited array after the DFS is: \n";
        for(auto i : visited) cout<<i.first<<"\t"; cout<<"\n";
        for(auto i : visited) cout<<i.second<<"\t"; cout<<"\n";
    }
	void addEdge(T u, T v) {
		adjL[u].push_back(v);
		if(adjL.count(v)==0) adjL[v];	//	This implies it is a directed graph
	}
	void printAdjL(map<T, list<T>> adjList) {
		for(auto i : adjList) {
			T u = i.first;
			cout<<u<<" -> ";
			for(auto v : i.second) cout<<v<<", ";
			cout<<"\n";
		}
	}
	void DFS(T src, map<T, int> &visited, map<T, list<T>> adjList) {
		visited[src] = 1;
		for(auto v : adjList[src]) {
			if(!visited[v]) DFS(v, visited, adjList);
		}
	}

	map<T, list<T>> reverseEdges(map<T, list<T>> adjList) {
		map<T, list<T>> revAdjL;
		for(auto i : adjList) {
			int u = i.first;
			for(auto v : i.second) revAdjL[v].push_back(u);    //  Reversing (u, v) to (v, u)
		}
		cout<<"The reversed graph is: \n";
		printAdjL(revAdjL);
		return revAdjL;
	}

	bool kosarajuAlgo() {
		int n = adjL.size();
		map<T, int> visited;
		typename map<T, list<T>>::iterator it = adjL.begin();	//	We can take any node as the source node. Here, the first node is taken as the source node
		T src = it->first;
		DFS(src, visited, adjL);								//	DFS(src) on the graph G
		printVisited(visited);
		if(visited.size()!=n) return 0;							//	If a node v is not visited then v is not added to the map visited => size of visited < n
		map<T, list<T>> revAdjL = reverseEdges(adjL);			//	Creating a new adjacency list which is the reverse of the given graph G
		visited.clear();										//	Clearing the visited map as it was already used in DFS1
		DFS(src, visited, revAdjL);								//	DFS(src) on the reversed graph G
		printVisited(visited);
		if(visited.size()!=n) return 0;
		else return 1;											//	If size of visited == n => G is strongly connected
	}
};

int main () {
	graph<char> G;
	G.addEdge('A', 'B');	G.addEdge('B', 'C');
	G.addEdge('C', 'D'); 	G.addEdge('D', 'E');
	//G.addEdge('E', 'A'); 	//	this makes the graph strongly connected
	G.printAdjL(G.returnAdjL());
	if(G.kosarajuAlgo()) cout<<"The given directed graph is strongly connected\n";
	else cout<<"The given directed graph is not strongly connected\n";
	return 0;
}
