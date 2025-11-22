/* Graph problem #19. Find the articulation points/cut-vertex in an undirected graph. (Verified)
In an undirected disconnected graph, a vertex is called an articulation point/cut-vertex if removing it
and all the edges associated with it results in the increase of the number of connected components in
the graph
In an undirected connected graph, its removal disconnects the graph.

A graph is said to be 2-vertex connected if,
a.	on removing any vertex of the graph, it still remains connected,
 	i.e. it contains no articulation point/cut-vertex.

Biconnected graph: An undirected graph is called biconnected if
a.	the graph is connected
b.	there exists no articulation points/cut-vertices

It can be solve using two methods:
1.	Naive solution: Remove each vertex turn by turn and do a BFS/DFS to see if the graph is still connected.
	R.T. = O(n)*O(BFS/DFS) = O(n*(n+m)) ~ O(mn) i.e. quadratic thus, inefficient
2.	Using deepest back edge + arrival time: (Best solution)
	R.T. = O(DFS) = O(n+m) ~ O(m)
2b. Slight modification of method 2, i.e. arrival time is replaced by discovery time and dbe is replaced by a low[] array
*/

//	Method 2. Using deepest backedge + arrival time + one DFS traversal
//	Note - In a DFS tree representation of an undirected graph, there are only two types of edges
//	a. 	Tree edges
//	b.	Back edges
//	It does not have forward edges or cross edges. So, if all the subtrees have atleast one back edge going out
//	it implies that the undirected graph G is 2-edge connected.
//	It is quite similar to strong connectivity in directed graphs i.e. if all the subtrees have atleast one edge
//	(whether a back edge or a cross edge) going out of them, => G is strongly connected.
//	Steps: Refer notes

//	Running time = O(DFS) or O(m+n) ~ O(m)
//	Auxiliary space = O(n) or O(V)

#include<iostream>
#include<map>
#include<unordered_map>
#include<list>
#include<vector>
using namespace std;

template <typename T>
class graph {
	map<T, list<T>> adjL;
public:
	void addEdge(T u, T v) {
		adjL[u].push_back(v);
		adjL[v].push_back(u);	//	=> G is undirected
	}
	void printAdjL() {
		for(auto i : adjL) {
			cout<<i.first<<" -> ";
			for(auto j : i.second) cout<<j<<", ";
			cout<<"\n";
		}
	}
	//	Either use lines 64 and 65 or lines 71 and 72, both are correct
	int apDFS(T u, map<T, int> &visited, map<T, T> &parent, map<T, int> &disc, map<T, int> &low, int &time, vector<T> &ap, T src) {
		visited[u] = 1;
		disc[u] = time++;
		low[u] = disc[u];
		int DFSchildren = 0;
		for(auto v : adjL[u]) {
			if(!visited[v]) {
				parent[v] = u;
				DFSchildren++;
				low[u] = min(low[u], apDFS(v, visited, parent, disc, low, time, ap, src));
				//if(u!=src && low[v] >= disc[u]) ap.push_back(u);
				//else if(u==src && DFSchildren>1) ap.push_back(u); //  Special case for the source node/root
			}
			else if(parent[u]!=v) {
				low[u] = min(low[u], disc[v]);
			}
		}
		if(u!=src && low[u]>=disc[parent[u]] && parent[u]!=src) ap.push_back(parent[u]);
		if(u==src && DFSchildren>1) ap.push_back(u);                //  Special case for the source node/root
		return low[u];
	}
	void findArticulationPoints() {
		map<T, int> visited;
		map<T, T> parent;
		map<T, int> disc;
		map<T, int> low;
		vector<T> ap;
		int time = 0;
		int ccNum = 0;
		typename map<T, list<T>>:: iterator it;
		for(it = adjL.begin(); it!=adjL.end(); it++) {
			T u = it->first;
			if(!visited[u]) {
				ccNum++;
				int dbe = apDFS(u, visited, parent, disc, low, time, ap, u);
				cout<<"The articulation points/cut-vertices for the CC#"<<ccNum<<" are: \n";
				for(int i=0; i<ap.size(); i++) cout<<ap[i]<<" ";
				cout<<"\n";
				ap.clear();
			}
		}
	}
};

int main() {
	graph<char> G;
	G.addEdge('a', 'b'); 	G.addEdge('b', 'c');
	G.addEdge('c', 'd'); 	G.addEdge('d', 'e');
	G.addEdge('a', 'z');    //  this creates two children for the root/source node*/
	G.addEdge('f', 'g');    G.addEdge('f', 'h');
	G.addEdge('g', 'i');    G.addEdge('h', 'j');
	G.addEdge('j', 'g');
	G.printAdjL();
	G.findArticulationPoints();
	return 0;
}
