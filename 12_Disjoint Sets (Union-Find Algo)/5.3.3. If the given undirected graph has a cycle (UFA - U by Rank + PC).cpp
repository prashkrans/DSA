/*	Graph Problem #8.3.3. - Given an undirected graph, find whether it has a cycle.
    This problem could be solved using three methods
    1.  DFS + parent variable
    2.  BFS + parent array
    3.  Union-find algorithm    (Avoid using find() and union() instead use findSet() and unionOfSets())
        1.  Naive                                   O(n)
        2.  Union by rank/height                    O(log2(n))      modify just unionOfSets() to allow union by rank or height
        3.  Union by rank + Path Compression        O(l)            modify both findSet() to allow path compression and unionOfSets() to allow union by rank or height
*/

//	Method 3.3. Using the union-find algorithm + Path Compression (Union by rank or height i.e. find() = O(1) and union() = O(1))
//  Here, we are using union by rank along with path compression to use the union-find algorithm
//  Steps: The process remains the same as for a naive union-find algo except that we optimize the find() and union() operations.
//  a.  Assume in the beginning that each vertex is in a different set => no. of sets = no. of vertices
//  b.  Pick any edge joining two vertices say vi and vj. Merge the sets containing vi and vj into a single set.
//      Note: If an edge e(u, v) is picked, make sure not to pick the edge e(v, u) since it is an undirected graph.
//      Hence, create an array/map that stores a pair<T, T>. Also, unordered_map and unordered_set don't work with pairs
//  c.  Repeat the step a. until
//      i.  All the edges are picked and each time an edge was picked the number of sets reduced by 1 eventually becoming
//          equal to the no. of connected components in the graph thus implying that the given undirected graph is acyclic.
//      ii. Or, when a particular edge is picked joining two vertices say vi and vj, both of which belong to the same set thus
//          implying that the given undirected graph is cyclic.

//	Running time = O((m*2*Find()) + (Union()*(n-1))) = O(2mF + U(n-1)) ~ O(mF + Un) = O(m.1 + 1.n) ~ O(n+m) ~ O(m) if m > n
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
	vector<pair<T, T>> edges;
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
	void printEdges() {
        for(int i=0; i<edges.size(); i++) cout<<"Edge #"<<i+1<<": ("<<edges[i].first<<", "<<edges[i].second<<")\n";
	}
	pair<T, int> findSet(T u, unordered_map<T, pair<T, int>> &subset) { //  It is a recursive function that first finds the root of the set and makes it the parent
		T parent = subset[u].first;
		int rank = subset[u].second;
		if(parent == u) return {u, rank};       //  returns the root of the set in which u was present
		else {
            pair<T, int> rootSet = findSet(parent, subset);
            subset[u].first = rootSet.first;    //  Path compression i.e. makes root the parent of all the nodes in the current path
            subset[u].second = rootSet.second;
		}
		return subset[u];	                    //  returns the root and rank after the path compression
	}
	void unionOfSets(T u, T v, unordered_map<T, pair<T, int>> &subset) {
		pair<T, int> uSet = findSet(u, subset);
		pair<T, int> vSet = findSet(v, subset);
		T uRoot = uSet.first;   int uRank = uSet.second;
        T vRoot = vSet.first;   int vRank = vSet.second;
        int mergedRank = uRank + vRank;
		if(vRank <= uRank) {
            subset[vRoot] = {uRoot, mergedRank};
            subset[uRoot].second = mergedRank;
		}
		else {
            subset[uRoot] = {vRoot, mergedRank};
            subset[vRoot].second = mergedRank;
		}
	}
	bool isCyclic() {
        unordered_map<T, pair<T, int>> subset;              	//  Using a subset map to identify disjoint sets that maps a node u to its parent and the rank of the set in which u is present
        for(auto i : adjList) subset[i.first] = {i.first, 1}; 	//  Initially a node is a parent of itself and the rank is 1. When parent[u] == u => u is the root of a set
		for(auto e : edges) {                               	//  Note:   1. If two or more nodes have the same root => they are in the same set.
            T u = e.first;                                  	//          2. Two or more nodes in the same set may have different parents but must have a common root
            T v = e.second;
            if(findSet(u, subset)!=findSet(v, subset)) unionOfSets(u, v, subset);
            else return 1;
        }
        cout<<"Vertices\t"; for(auto i : subset) cout<<i.first<<"\t"; cout<<"\n";
        cout<<"Parent\t\t";     for(auto i : subset) cout<<i.second.first<<"\t"; cout<<"\n";  	// 	No. of distinct roots (not parents) denote the no. of sets = no. of connected components
		cout<<"Rank\t\t"; for(auto i : subset) cout<<i.second.second<<"\t"; cout<<"\n";			//	i.e. if a parent[u] == u => u is a root
        return 0;
	}
};

int main() {
	graph<char> G;
	G.addEdge('A', 'B');	G.addEdge('A', 'C');
	G.addEdge('C', 'D');	G.addEdge('C', 'E');
	G.addEdge('F', 'G');	G.addEdge('G', 'H');
	G.addEdge('E', 'F');	G.addEdge('G', 'I');            //  Except H, all nodes would have A as their parent due to path compression
	//G.addEdge('B', 'H');      //  makes the graph cyclic
	//G.addEdge('I', 'F');      //  makes the graph cyclic

	//G.printAdjList();
	G.printEdges();
	if(G.isCyclic()) cout<<"The given undirected graph G is cyclic\n";
	else cout<<"The given undirected graph G is not cyclic\n";
	return 0;
}
