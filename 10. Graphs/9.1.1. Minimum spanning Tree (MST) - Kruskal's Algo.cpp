/*	Graph Problem #12.1.1 - Minimum Spanning Tree (MST) using Kruskal's Algorithm & Naive Union-Find Algorithm
	
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

//	Method 1.1 - Kruskal's algorithm (Greedy Algo) & findSet() ~ O(n)
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
//	a. 	Iff we use a heap to store the disjoint sets (union by rank/height) then O(findSet) = O(logn) and O(unionOfSets) = O(1)
//		Thus, R.T. = O(mlogm + O(1)*n-1 + O(logn)*2m) = O(mlogm) as mlogm>mlogn
//	b. 	If we a vector/map to store the disjoint sets then O(findSet) = O(n) and O(unionOfSets) = O(n)
//		Here, the disjoint sets are stored as a map<T, T> setID is maintained where both key is a node v and the value is the parent of node v
//  	So, R.T. = O(mlogm + n*n-1 + n*2m) ~ O(mn) i.e. inefficient.
//	Auxiliary space = O(n) or O(V) as the size of the MST = m = n-1 and the sum of the sizes of all the sets of nodes = n-1

#include<iostream>
#include<map>
#include<vector>
#include<list>
#include<algorithm>
using namespace std;

void printEdges(auto edges) {
	cout<<"Edge e(u, v)\tWeight\n";
	for(auto e : edges) {
		cout<<"("<<e.second.first<<", "<<e.second.second<<")\t\t";
        cout<<e.first<<"\n";
	}
}

template<typename T>
class graph {
	map<T, list<pair<T, int>>> adjL;
	vector<pair<int, pair<T, T>>> edges;    //  It is important to have edges as a data member, so while using addEdge() we can simply add an edge to edges also
	map<T, T> setID;                    	//	A set is represented by the first node u or root present in it, for which setID[u] = u
public:
	void addEdge(T u, T v, int wt) {
		adjL[u].push_back({v, wt});
		adjL[v].push_back({u, wt});         //  This implies that it is an undirected graph
		edges.push_back({wt, {u, v}});      //  Add the edge in the vector edges which stores edge info as {weight of the edge, {node first, node second}}
	}
	void printAdj() {
		for(auto u : adjL) {
			cout<<u.first<<" -> ";
			for(auto v : u.second) {
				cout<<"("<<v.first<<", "<<v.second<<"), ";
			}
		cout<<"\n";
		}
	}
	T findSet(T u) {
		if(setID[u] == u) return u;		//	A set is represented by a root u i.e. if the setID[u] == u => u is the root of the setID[u]
		else return findSet(setID[u]);	//	If u is not the root, then go back to findSet(setID[u]) until the root is found
	}
	void unionOfSets(T u, T v) {		//	Note that if setID were to be sent here as a parameter, remember to use &setID as the function is a void type
		T uRoot = findSet(u);			//	Find the root representing the set in which u is present
		T vRoot = findSet(v);			//	Find the root representing the set in which v is present
		setID[uRoot] = setID[vRoot];	//	Make the root of set in which v is present as the root of the set in which u is present
		// or setID[vRoot] = setID[uRoot]; //	It works both ways
	}									//	Hence, merging the setID[u] into setID[v]
	vector<pair<int, pair<T, T>>> kruskalsAlgoMST() {
        vector<pair<int, pair<T, T>>> mst;		//	Creating an empty mst vector that would store the edges included in MST
		setID.clear();
		int sum = 0;
		for(auto u : adjL) {
			setID[u.first] = u.first;			//	Initialization of setID i.e. a node itself is the parent
		}
		sort(edges.begin(), edges.end());		//	Sorting the edges in non decreasing order on the basis of their weights
		cout<<"The edges of the graph are:\n"; printEdges(edges);
		for(auto i : edges) {
			int wt = i.first;
			int u = i.second.first;
			int v = i.second.second;
			if(findSet(u)!=findSet(v)) {		//	This ensures a cycle is not getting formed
				mst.push_back({wt, {u, v}});	//	If the edge does not form a cycle, it is pushed in MST
				sum = sum + wt;					//	This calcultes the current total weight of the MST
				unionOfSets(u, v);				//	This makes the union of two different sets
			}
			if(mst.size()==adjL.size()-1) {		//	If MST is already formed i.e. it has V-1 or n-1 edges, we can break the loop
				cout<<"The edges included in the MST are:\n"; printEdges(mst);				
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
    G.printAdj();
    auto mst = G.kruskalsAlgoMST();
    return 0;
}