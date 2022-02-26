/* Graph problem #18.1. 2-edge connectivity in an undirected graph
Given an undirected graph G, with V vertices and E edges, check whether the graph is 2-edge connected or not.

A graph is said to be 2-edge connected if,
a.	on removing any edge of the graph, it still remains connected,
b. 	or it contains no bridges.

Bridge: Such an edge whose removal disconnects a graph is called a bridge.

It can be solve using three methods:
1.	Naive solution: Remove each edge turn by turn and do a BFS/DFS to see if the graph is still connected.
	R.T. = O(m)*O(BFS/DFS) = O(m*(n+m)) ~ O(m^2) i.e. quadratic in no. of edges thus, inefficient
2.	Number of edges connected to each node: (Easiest solution)
	R.T. = O(n+m) ~ O(m) i.e. traversal of all the edges
3.	Using deepest backedge + arrival time: (Best solution)
	R.T. = O(DFS) = O(n+m) ~ O(m)
*/

//	Method 2. Using number of edges connected to each node.
//	Since the given graph is undirected, the problem can be solved only by counting the number of edges
//	connected to the nodes. If for any of the nodes, the number of edges connected to it is 1 it means on
//	removing this edge the node becomes disconnected and it can’t be reached from any other node therefore
//	the graph is not 2-edge connected.
//	Steps:
//		1.	Create an array noOfEdges[] of size V which will store the number of edges connected to a node.
//		2.	For every ordered pair edge (u, v) increment the number of edges for node u only.
//		3.	Now iterate over the array noOfEdges[] and check if any node has only 1 edge connected to it.
//			a.	If yes then the graph is not 2-edge connected.
//			b.	Otherwise, the graph is 2-edge connected.

#include<iostream>
#include<map>
#include<list>
using namespace std;

template<typename T>
class graph {
	map<T, list<T>> adjL;
public:
	void addEdge(T u, T v) {
		adjL[u].push_back(v);
		adjL[v].push_back(u);
	}
	void printAdjL() {
		for(auto i : adjL) {
			cout<<i.first<<" -> ";
			for(auto v : i.second) cout<<v<<", ";
			cout<<"\n";
		}
	}
	bool isTwoEdge() {
		map<T, int> noOfEdges;
		for(auto i : adjL) {
			T u = i.first;
			noOfEdges[u] = adjL[u].size();
		}
		typename map<T, int>::iterator it;
		for(it = noOfEdges.begin(); it!=noOfEdges.end(); it++) {
			if(it->second<2) return 0;  		//	equivalent to if(noOfEdges[v]<2) return false;
		}
		return 1;								//	if program reaches here => there were no nodes with less than 2
	}											//	edges connected to it => G is 2-edge connected
};

int main() {
	graph<string> G;
	G.addEdge("A1", "B2");	G.addEdge("A1", "C3");
	G.addEdge("B2", "D4");	G.addEdge("B2", "E5");
	G.addEdge("B2", "F6");	G.addEdge("E5", "F6");
	//G.addEdge("C3", "D4"); // it makes the graph 2-edge connected
	G.printAdjL();
	if(G.isTwoEdge()) cout<<"The given undirected graph is 2-edge connected\n";
	else cout<<"The given undirected graph is not 2-edge connected\n";
	return 0;
}

