/*	Graph Problem #12.2.1. - Minimum Spanning Tree (MST) using modified Prim's Algorithm
	MST is only defined if the graph is
	a. connected and
	b. undirected
	Given a connected and a undirected graph, find its MST.
	There are two ways to find the MST of a graph. Both are greedy algorithms
	1. Kruskal's Algorithm
	2. Prim's Algorithm
		2a. Prim's Algorithm (Heap of edges)
		2b.	Prim's Algorithm modified (Heap of vertices) (similar to Dijkstra's Algo)
*/

//	Method 2.1 - Modiefied Prim's algorithm (Greedy Algo) - Better than Prim's Algo
//	It is based on the principle that the edge with the minimum length/weight in a cut is included 
//	in the MST.
//	Steps:
//	1.	Create a set mstSet that keeps track of vertices already included in MST and an another set
//		called setPA that include vertices yet to be included in MST
//	2.	Assign a key value/label to all vertices in the input graph. Initialize all key values as INFINITE.
//		Assign key value as 0 for the first vertex or source so that it is picked first. This label stores the length
//		of the edge(v, w)
//	3.	While setPA is not empty or mstSet doesn’t include all vertices
//		a.	Pick a vertex v which is not there in mstSet and has minimum key value.
//		b.	Include v to mstSet.
//		c.	For all adjacent vertices w of v, if the weight of edge(v, w) is less than the label[w] then
//			update the label[w] = weight of edge(v, w)
//	4. 	When setPA is empty => mstSet includes all the vertices i.e. MST is found.
//		So, the path from source to the last vertex included is the MST.

//	Running time = summation over(degree(v))*log(m or n)) = O(mlogm) or O(mlogn)
//	a. 	Prim's Algo: Heap of edges => O(logm) for insert() and delete() => R.T. = O(mlogm)
//	b. 	Modified Prim's Algo: Heap of vertices => O(logn) for decreasePriority() => R.T. = O(mlogn)
//	Auxiliary space = O(n) or O(V) as the size of the MST = m = n-1.

#include<iostream>
#include<map>
#include<list>
#include<vector>
#include<set>
using namespace std;

void print(auto path, int mstCost) {
        cout<<"The "<<path.size()-1<<" edges included in the MST are:\n";   //  Iterate from 1 to size()-1 as path[0] contains edge of length 0, from src to src
		for(int i=1; i<path.size(); i++) cout<<path[i].wt<<"\t("<<path[i].v<<", "<<path[i].w<<")\n";
		cout<<"Thus, the total weight of the MST = "<<mstCost<<"\n";
}

template<typename T>    //  Using a struct to represent an edge instead of STL vector<pair<int, pair<T, T>>> edge
struct edge {           //  Note - templates can be used with structures also
	int wt;             //  Also, we don't even need a DS to store an edge as we can use the parent[] to print the edges included in the MST
	T v;
	T w;
	edge(int wt, T v, T w) : wt(wt), v(v), w(w) {}  //  Constructor to create an object of edge and initialize it
};

template<typename T>
class graph {
	map<T, list<pair<T, int>>> adjList;
public:
	void addEdge(T v, T w, int wt) {
		adjList[v].push_back(make_pair(w, wt));
		adjList[w].push_back({v, wt});
	}
	void printAdjList() {
		for(auto v : adjList) {
			cout<<v.first<<" -> ";
			for(auto w : v.second) cout<<"("<<w.first<<", "<<w.second<<"), ";
			cout<<"\n";
		}
	}
	vector<edge<T>> primsAlgoMST() {        //  Similarities from Dijkstra's Algo (label<=>dist, setPA<=>setDA, inMstSet<=>inSpSet, parent, path, cost)
		map<T, int> label;
		set<pair<int, T>> setPA;
		map<T, bool> inMstSet;
		map<T, T> parent;
		vector<edge<T>> path;
		int mstCost = 0;
		for(auto v : adjList) label[v.first] = INT_MAX;
		T src = adjList.begin()->first;
		label[src] = 0; parent[src] = src;
		setPA.insert(make_pair(0, src));
		while(!setPA.empty()) {
			T v = setPA.begin()->second; int edgeWt = setPA.begin()->first;
			inMstSet[v] = 1;
			mstCost += edgeWt;
			edge<T> e(edgeWt, parent[v], v); path.push_back(e);
			setPA.erase(setPA.begin());

			for(auto x : adjList[v]) {
				if(!inMstSet[x.first]) {
                    T w = x.first;
                    int wt = x.second;
                    if(wt < label[w]) {
                        typename set<pair<int, T>>::iterator it = setPA.find({label[w], w});
                        if(it!=setPA.end()) setPA.erase(it);
                        label[w] = wt;
                        setPA.insert({label[w], w});
                        parent[w] = v;
                    }
				}
			}
		}
		print(path, mstCost);
		return path;
	}
};

int main() {
    graph<char> G;
    G.addEdge('a', 'b', 2); G.addEdge('a', 'c', 3); //  Note - (a, c, 3) creates a loop hence is not picked in the MST
    G.addEdge('b', 'd', 1); G.addEdge('b', 'e', 5);
    G.addEdge('c', 'd', 2); G.addEdge('d', 'e', 4);
    G.printAdjList();
    auto mstPath = G.primsAlgoMST();
    return 0;
}
