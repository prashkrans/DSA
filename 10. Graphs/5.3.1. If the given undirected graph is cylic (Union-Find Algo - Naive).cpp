/*	Graph Problem #8.3.3. - Given an undirected graph, find whether it has a cycle.
    This problem could be solved using three methods
    1.  DFS + parent variable
    2.  BFS + parent array
    3.  Union-find algorithm    (Avoid using find() and union() instead use findSet() and unionOfSets())
        1.  Naive                                   O(n)
        2.  Union by rank/height                    O(log2(n))      modify just unionOfSets() to allow union by rank or height
        3.  Union by rank + Path Compression        O(l)            modify both findSet() to allow path compression and unionOfSets() to allow union by rank or height
*/

//	Method 3.1. Using the union-find algorithm (Naive i.e. find() = O(n) and union() = O(n))
//  Steps:
//  a.  Assume in the beginning that each vertex is in a different set => no. of sets = no. of vertices
//  b.  Pick any edge joining two vertices say vi and vj. Merge the sets containing vi and vj into a single set.
//      Note: If an edge e(u, v) is picked, make sure not to pick the edge e(v, u) since it is an undirected graph.
//      Hence, create an array/map that stores a pair<T, T>. Also, unordered_map and unordered_set don't work with pairs
//  c.  Repeat the step a. until
//      i.  All the edges are picked and each time an edge was picked the number of sets reduced by 1 eventually becoming
//          equal to the no. of connected components in the graph thus implying that the given undirected graph is acyclic.
//      ii. Or, when a particular edge is picked joining two vertices say vi and vj, both of which belong to the same set thus
//          implying that the given undirected graph is cyclic.

//	Running time = O((m*2*Find()) + (Union()*(n-1))) = O(2mF + U(n-1)) ~ O(mF + Un) = O(mn + n^2) ~ O(mn) ~ O(n^3) if m = n^2
//	Auxiliary space = O(n) or O(V) i.e. the max size of the summation of sizes of all the disjoint sets = no. of vertices

#include<iostream>
#include<unordered_map>
#include<vector>
#include<map>
#include<list>
using namespace std;

template<typename T>
class graph {
	map<T, list<T>> adjList;
	vector<pair<int, int>> edges;
public:
	void addEdge(T u, T v) {
		adjList[u].push_back(v);
		adjList[v].push_back(u);                    //  Implies that the graph is undirected
		//edges[{u, v}] = 1;
		edges.push_back({u, v});                    //  [#IMP] We need to store the edges too, else we can't use union-find algo. Here the edges may be a vector, map or set
	}                                               //  So, either get the edges here itself or get it from adjList using a map/set but not a vector as search operation is
                                                    //  required which is O(n) for a vector.
	void printAdjList() {
		for(auto i : adjList) {
			cout<<i.first<<" -> ";
			typename list<T>::iterator it;          //  list<T>::iterator does not work as and it needs to prefixed with typename
			for(it = i.second.begin(); it!=i.second.end(); it++) {
				cout<<(*it)<<", ";
			}
			cout<<"\n";
		}
	}
	T findSet(T u, unordered_map<T, T> parent) {
        while(parent[u]!=u) {
            u = parent[u];
        }
        return u;   //  returns the root of the set in which u was present
	}
	void unionOfSets(T u, T v, unordered_map<T, T> &parent) {
        T uRoot = findSet(u, parent);                       //  uRoot is the root of the set in which u is present
        T vRoot = findSet(v, parent);                       //  vRoot is the root of the set in which v is present
        parent[vRoot] = uRoot; //   vice-versa also works   //  parent of vRoot is now uRoot => all nodes with root = vRoot has now changed to root = uRoot
	}                                                       //  => the set with root = vRoot was merged with the set with root = uRoot and the root of the merged set is now uRoot
	bool isCyclic() {
        unordered_map<T, T> parent;                         //  Using a parent array to identify disjoint sets.
        for(auto i : adjList) parent[i.first] = i.first;    //  Initially a node is a parent of itself. When parent[u] == u => u is the root of a set
        for(auto e : edges) {                               //  Note:   1. If two or more nodes have the same root => they are in the same set.
            T u = e.first;                                  //          2. Two or more nodes in the same set may have different parents but must have a common root
            T v = e.second;
            if(findSet(u, parent)!=findSet(v, parent)) unionOfSets(u, v, parent);
            else return 1;
        }
        cout<<"Vertices\t"; for(auto i : parent) cout<<i.first<<"\t"; cout<<"\n";
        cout<<"Parent\t\t";     for(auto i : parent) cout<<i.second<<"\t"; cout<<"\n";  // No. of distinct roots denote the no. of sets = no. of connected components
        return 0;
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
	if(G.isCyclic()) cout<<"The given undirected graph G is cyclic\n";
	else cout<<"The given undirected graph G is not cyclic\n";
	return 0;
}
