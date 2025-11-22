/*	Graph Problem #12.1.2 - Minimum Spanning Tree (MST) using Kruskal's Algorithm & Union by Height & Path Compression [#IMP]

	MST is only defined if the graph is
	a. connected and
	b. undirected
	Given a connected and a undirected graph, find its MST.
	There are two ways to find the MST of a graph. Both are greedy algorithms
	1. Kruskal's Algorithm
		1.	Naive Union-Find Algo
		2.	Union by Rank or Height
		3. 	Union by Rank or Height + Path Compression
	2. Prim's Algorithm
		2a. Prim's Algorithm
		2b.	Modified Prim's Algorithm
*/

//	Method 1.2 - Kruskal's algorithm (Greedy Algo) & Union by Height & Path Compression [#IMP]
//	Steps:
//	1.	Sort all the edges in a non decreasing order of their weights
//	2.	Create an empty tree T
//	3. 	Pick the smallest edge and if it does not make a cycle with the tree T, add it to the tree T,
//		else, discard the edge
//	4. 	Repeat the step 3 until the size of T = V-1 or n-1 i.e. T becomes MST. Hence, return T
//	Hence it comprises of three functions
//	1. 	main kruskalsAlgo()
//	2. 	findSet(T u) - which finds the set in which the node u is present
//	3.	unionOfSets(T u, T v) - which finds the set in which u and v are present and makes a union of those two sets
//	This is how kruskalsAlgo uses "Union-Find algorithm"

//	Running time = O(mlogm + O(union)*n-1 + O(findSet)*2m)
//	a. 	Iff we use a heap to store the disjoint sets (union by rank/height) along with path compression then O(findSet) = O(1) and O(unionOfSets) = O(1)
//		Thus, R.T. = O(mlogm + O(1)*n-1 + O(1)*2m) = O(mlogm)
//	b. 	If we a vector/map to store the disjoint sets then O(findSet) = O(n) and O(unionOfSets) = O(n)
//		Here, the disjoint sets are stored as a map<T, T> setID is maintained where both key is a node v and the value is the parent of node v
//  	So, R.T. = O(mlogm + n*n-1 + n*2m) ~ O(mn) i.e. inefficient.
//	Auxiliary space = O(n) or O(V) as the size of the MST = m = n-1 and the sum of the sizes of all the sets of nodes = n-1

#include<iostream>
#include<map>
#include<unordered_map>
#include<vector>
#include<list>
#include<algorithm>
using namespace std;

template<typename T>
class graph {
	map<T, list<pair<T, int>>> adjL;
	vector<pair<int, pair<T, T>>> edges;    //  It is important to have edges as a data member, so while using addEdge() we can simply add an edge to edges also.
public:										//	Also note that edges is of vector type so sort(vName.begin(), vName.end() is used to sort the edges in terms of its weight
	void addEdge(T u, T v, int wt) {		//	Another way would to represent sorted edges would have been a multimap or multiset which would automatically insert the edges in a sorted manner.
		adjL[u].push_back({v, wt});			//	However, prefer using a vector<pair<int, pair<T, T>>> to store {wt, {u, v}} as explicit sorting is used.
		adjL[v].push_back({u, wt});         //  This implies that it is an undirected graph
		edges.push_back({wt, {u, v}});      //  Add the edge in the vector edges which stores edge info as {weight of the edge, {node first, node second}}
	}
	void printAdjL() {
		for(auto u : adjL) {
			cout<<u.first<<" -> ";
			for(auto v : u.second) {
				cout<<"("<<v.first<<", "<<v.second<<"), ";
			}
		cout<<"\n";
		}
	}
	T findSet(T u, unordered_map<T, pair<T, int>> &subset) {    //  Recurisive findSet() is used here. An iterative solution also works
		T parent = subset[u].first;
		if(parent == u) return u;
		else {
			subset[u].first = findSet(parent, subset);
			return subset[u].first;
		}
	}
	void unionOfSets(T u, T v, unordered_map<T, pair<T, int>> &subset) {
		T r1 = subset[u].first;		T r2 = subset[v].first;
		int h1 = subset[u].second;	int h2 = subset[v].second;
		if(h1 > h2) subset[r1].first = r2;
		else if(h1 < h2) subset[r2].first = r1;
		else {                                                  //  Only when the heights are equal, we increase the height of the merged set
			subset[r1].first = r2;
			subset[r2].second++;
		}
	}
	vector<pair<int, pair<T, T>>> kruskalsAlgoMST() {
        vector<pair<int, pair<T, T>>> mst;						//	Creating an empty mst vector that would store the edges included in MST
		unordered_map<T, pair<T, int>> subset;
		int sum = 0;
		for(auto u : adjL) subset[u.first] = {u.first, 0};		//	Initialization of subset as a node is parent of itself and height = 0 for all the nodes
		sort(edges.begin(), edges.end());						//	Sorting the edges in non decreasing order on the basis of their weights
		cout<<"The edges of the graph are:\n";
		cout<<"Edge e(u, v)\tWeight\n";
		for(auto e : edges) cout<<"("<<e.second.first<<", "<<e.second.second<<")\t\t"<<e.first<<"\n";
		for(auto e : edges) {
			int wt = e.first;
			int u = e.second.first;
			int v = e.second.second;
			if(findSet(u, subset)!=findSet(v, subset)) {		//	This ensures a cycle is not getting formed
				mst.push_back({wt, {u, v}});	//	If the edge does not form a cycle, it is pushed in MST
				sum = sum + wt;					//	This calcultes the current total weight of the MST
				unionOfSets(u, v, subset);				//	This makes the union of two different sets
			}
			if(mst.size()==adjL.size()-1) {		//	If MST is already formed i.e. it has V-1 or n-1 edges, we can break the loop
				cout<<"The edges included in the MST are:\n";
				cout<<"Edge e(u, v)\tWeight\n";
				for(int i=0; i<mst.size(); i++) cout<<"("<<mst[i].second.first<<", "<<mst[i].second.second<<")\t\t"<<mst[i].first<<"\n";
				cout<<"Thus, the total weight of the MST = "<<sum<<"\n";
				return mst;
			}
		}
	}
};

int main() {
    graph<char> G;
    G.addEdge('a', 'b', 2); G.addEdge('a', 'c', 3); //  Note - (a, c, 3) creates a loop hence is not picked in the MST
    G.addEdge('b', 'd', 1); G.addEdge('b', 'e', 5);
    G.addEdge('c', 'd', 2); G.addEdge('d', 'e', 4);
    G.printAdjL();
    auto mst = G.kruskalsAlgoMST();
    return 0;
}
