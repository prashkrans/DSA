/* Graph problem #16.2. Strong Connectivity in a directed graph (Tarjan's Algo).
Given a directed graph, find whether it is strongly connected.
Note - This graph has either a single SCC or multiple SCCs.
If the G has a single SCC, return true
else return false


There are three methods to find if a directed graph is strongly connected.
1. 	Naive solution: n*DFS => R.T. = O(nm) or O(n^3) thus, inefficient.
2.	Another naive solution: Using transitive course or Floyd Warshall algorithm => R.T. = O(n^3) again, inefficient.
3.	Kosaraju algorithm: Developed by S. Rao Kosaraju (IITKGP). Here R.T. = O(m) but uses 2 DFS
4.	Tarjan's algorithm: Here R.T. = O(m) but uses a single DFS
*/

//	Method 4. shortest arrival time (sat) + arrival array + one DFS traversal
//  This method is the same as Tarjan's Algo except for variables used (For a single SCC)
//  This works on the principle that the necessary and sufficient condition for a directed graph to be strongly
//  connected is that an edge goes out of every subtree in DFS representation of the graph. The edge could be
//  a back edge or a cross edge(right to left) as directed graphs contain cross edges too.
//  The algo is exactly the same as that for 2-edge/2-vertex connectivity where the variable dbe was used, while
//  here we use sat i.e. the node with the shortest arrival time to which the outgoing edge from a subtree points to.
//  Steps:

//	Running time = O(DFS) = O(n+m) ~ O(m)
//	Auxiliary space = O(n) or O(V)

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
	int taDFS(T u, map<T, int> &visited, map<T, int> &arrival, map<T, T> parent, int &time, T src) {
		visited[u] = 1;
		arrival[u] = time++;
		int sat = arrival[u];
		for(auto v : adjL[u]) {
			if(!visited[v]) {
				parent[v] = u;
				sat = min(sat, taDFS(v, visited, arrival, parent, time, src));
			}
			else if(parent[u]!=v) sat = min(sat, arrival[v]);   //  if (parent[u]!=v) => edge(u, v) is a back edge or a cross edge
		}
		if(u!=src && sat==arrival[u]) return -1;
		return sat;
	}
	bool tarjansAlgo() {
		map<T, int> visited;
		map<T, int> arrival;
		map<T, T> parent;
		int time = 0;
		typename map<T, list<T>>::iterator it = adjL.begin();
		T src = it->first;
		int sat = taDFS(src, visited, arrival, parent, time, src);
		if(sat==0) return true; //  since the arrival time of the source node/root is 0 => sat should be 0 for G to be strongly connected
		else return false;      //  if (sat == -1) => there is atleast one subtree with no edge coming out of it => G is not strongly connected
	}
};

int main () {
	graph<string> G;
	G.addEdge("A1", "B2");	G.addEdge("B2", "C3");
	G.addEdge("C3", "D4"); 	G.addEdge("D4", "E5");
	G.addEdge("E5", "A1"); 	//	this makes the graph strongly connected
	G.printAdjL(G.returnAdjL());
	if(G.tarjansAlgo()) cout<<"The given directed graph is strongly connected\n";
	else cout<<"The given directed graph is not strongly connected\n";
	return 0;
}
