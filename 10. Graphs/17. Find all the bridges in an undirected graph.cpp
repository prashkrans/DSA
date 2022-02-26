/* Graph problem #20. Find all the bridges in an undirected graph. (Verified)
Bridge: Such an edge whose removal disconnects a graph is called a bridge.

It can be solve using two methods:
1.	Naive solution: Remove each edge turn by turn and do a BFS/DFS to see if the graph is still connected.
	If the graph gets disconnected add the edge in the list of bridges.
	R.T. = O(m)*O(BFS/DFS) = O(m*(n+m)) ~ O(m^2) i.e. quadratic in no. of edges thus, inefficient.
2.	Using deepest backedge + arrival time: (Best solution)
	R.T. = O(DFS) = O(n+m) ~ O(m)
*/

//	Method 2. Using deepest backedge + arrival time + one DFS traversal
//	Note - In a DFS tree representation of an undirected graph, there are only two types of edges
//	a. 	Tree edges
//	b.	Back edges
//	It does not have forward edges or cross edges. So, if all the subtrees have atleast one back edge going out
//	it implies that the edge(parent[u], u) is not a bridge, otherwise it is a bridge
//	It is quite similar to strong connectivity in directed graphs i.e. if all the subtrees have atleast one edge
//	(whether a back edge or a cross edge) going out of them, => G is strongly connected.
//	Steps: Refer notes

//	Running time = O(DFS) or O(m+n) ~ O(m)
//	Auxiliary space = O(n) or O(V)

#include<iostream>
#include<map>
#include<list>
#include<vector>
using namespace std;
//  Here we have used two methods to store the bridge edges
//  a.  Using a map of pair, bool i.e. map<pair<T, T>, bool> bridges;
//  b.  Using a vector of structure edge that stores two nodes connected by an edge i.e. vector<edge> bridges;
template <typename T>   //  Here we use vector of struct edge to store edges
struct edge {           //  Note - map<edge<T>, int> bridges; fails to work
    T u, v;             //  i.e. map cannot be used to store structures as a structure fails a map's compare function
    edge(T u, T v) : u(u), v(v) {}
};

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
	//int bridgeDFS(T u, map<T, int> &visited, map<T, int> &arr, map<T, T> &parent, map<pair<T, T>, int> &bridges, int &time, T src) {
	int bridgeDFS(T u, map<T, int> &visited, map<T, int> &arr, map<T, T> &parent, vector<edge<T>> &bridges, int &time, T src) {
		visited[u] = 1 ;
		arr[u] = time++;
		int dbe = arr[u];                   //  dbe initialized for the current vertex u
		for(auto v : adjL[u]) {
			if(!visited[v]) {
				parent[v] = u;              //  this records that the edge(u, v) is a tree edge
				dbe = min(dbe, bridgeDFS(v, visited, arr, parent, bridges, time, src));
			}
			else {
                if(parent[u]!=v) {			//	=> edges e(u, v) that are only back edges are considered here
					dbe = min(dbe, arr[v]);	// 	because if (parent[u] == v) => e(u, v) is a tree edge
                }
			}
		}
		if(u!=src && dbe>=arr[u]) {         //  Note - dbe cannot be greater than arr[u], it can only be less than or equal to arr[u]
            //bridges[{parent[u], u}] = 1;  //  if dbe is < arr[u] => edge(p[u], u) is not a bridge
            edge<T> e(parent[u], u);        //  if dbe is == arr[u] => edge(p[u], u) is a bridge
            bridges.push_back(e);           //  so, add this edge to bridges
		}
		return dbe;                         //  this is really important as it returns dbe of a child to its parent
	}
	void findBridges() {
		map<T, int> visited;
		int time = 0;
		map<T, int> arr;
		map<T, T> parent;           //  parent array/map is used for a. checking if an edge is a back edge & b. printing the bridges as an edge from parent[u] to u.
		//map<pair<T, T>, int> bridges;
		vector<edge<T>> bridges;    //  this simply stores the bridge edges
		typename map<T, list<T>>:: iterator it;
		int ccNum = 0;              //  if G is disconnected, ccNum labels different connected components
		for(it = adjL.begin(); it!=adjL.end(); it++) {
			T u = it->first;
			if(!visited[u]) {
				ccNum++;
				int dbe = bridgeDFS(u, visited, arr, parent, bridges, time, u); //  this fills the bridges vector/map with all the bridge edges in the current CC
				cout<<"The bridges in CC#"<<ccNum<<" are: \n";
				//for(auto j : bridges) cout<<"edge("<<j.first.first<<", "<<j.first.second<<")\n";  //  j.f.f and j.f.s as it is map of pairs
				for(auto j : bridges) cout<<"edge("<<j.u<<", "<<j.v<<")\n";
				bridges.clear();                                                //  clearing the bridges to use it for a different CC
			}
		}
	}
};

int main() {
	graph<char> G;
	G.addEdge('a', 'b'); 	G.addEdge('a', 'e');
	G.addEdge('b', 'c'); 	G.addEdge('b', 'd');
	G.addEdge('f', 'g'); 	G.addEdge('f', 'h');
	G.addEdge('f', 'i');    G.addEdge('g', 'j');
	G.addEdge('d', 'a');    G.addEdge('h', 'i');    //  the last two edges create a cycle, hence reduces bridges
	G.printAdjL();
	G.findBridges();
	return 0;
}
