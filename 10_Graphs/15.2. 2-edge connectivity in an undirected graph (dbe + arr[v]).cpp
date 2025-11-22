/* Graph problem #18.2. 2-edge connectivity in an undirected graph
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

//	Method 3. Using deepest backedge + arrival time + one DFS traversal
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
	//	DFS is modified slightly as it uses arr, dbe and treeEdges. 
	int TEdfs(T u, map<T, int> &visited, map<T, int> &arr, map<pair<T, T>, bool> &treeEdges, int &time, T src) {
		arr[u] = time++;
		visited[u] = 1;
		int dbe = arr[u];
		for(auto v : adjL[u]) {
			if(!visited[v]) {
                treeEdges[{u, v}] = 1;  //  Storing tree edges. Since G is undirected we add both
                treeEdges[{v, u}] = 1;  //  ordered pairs (u, v) and (v, u) to map treeEdges
                dbe = min(dbe, TEdfs(v, visited, arr, treeEdges, time, src));
                if(dbe==-1) return -1;
			}
			else {
                if(treeEdges[{u, v}] == 0) // that e(u, v) is not a tree edge
                dbe = min(dbe, arr[v]);
			}
		}
		if(u!=src) {					//	If the node u != src then dbe should point to an ancestor of u
            if(dbe==arr[u]) return -1;	//	If dbe points to u => there in no back edge from the subtree with u as root, 
            else return dbe;			//	thus, G is not 2-edge connected.
		}								//	else, there exists a back edge from that subtree and if every subtree has a back edge => G is 2-edge connected
		return dbe; 					//  => u == src so, we just return dbe which maybe -1 or 0
	}
	bool isTwoEdge() {
		map<T, int> visited;
		map<T, int> arr;                    //  it stores the arrival time of the node
		map<pair<T, T>, bool> treeEdges;    //  it stores all the edges that are tree edges in DFS tree
		int time = 0;                       //  it timestamps the arrival of a node. It is incremented by 1 after a node is timestamped.
		typename map<T, list<T>>::iterator it = adjL.begin();   //  Any node can be used as the source node
		T src = it->first;                                      //  Here, the first node is made the source node
		int dbe = TEdfs(src, visited, arr, treeEdges, time, src);
		cout<<"Deepest backedge points to the node with arrival time = "<<dbe<<"\n";
		if(dbe==0) return 1;    			//  dbe==0 => that the deepest backedge points to the root/source node i.e. G is 2-edge connected
		else return 0;
	}
};

int main() {
	graph<char> G;
	G.addEdge('A', 'B'); 	G.addEdge('A', 'C');
	G.addEdge('B', 'D'); 	G.addEdge('B', 'E');
	G.addEdge('C', 'D'); 	G.addEdge('C', 'F');
	//G.addEdge('E', 'F');    // this edge makes G 2-edge connected
	G.printAdjL();
	if(G.isTwoEdge()) cout<<"The given undirected graph is 2-edge connected\n";
	else cout<<"The given undirected graph is not 2-edge connected\n";
	return 0;
}
