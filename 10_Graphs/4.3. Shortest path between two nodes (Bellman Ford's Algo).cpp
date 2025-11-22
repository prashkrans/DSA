/*	Graph Problem #7.3. - Shortest path between two nodes (Bellman Ford Algorithm)
Find the length of the shortest path between two nodes
a. 	Using BFS (only for an unweighted graph): O(V+E)
    This algorithm will work even when negative weight cycles are present in the unweighted graph.
b. 	Using Dijkstra's algorithm (for graphs without negative edges whether directed or undirected): O(ElogV)
c.  Bellman Ford algorithm (for graphs without negative cycles) : O(VE)
*/

//	3. 	Bellman Ford algorithm (for graphs without negative cycles whether directed or undirected) : O(VE)
//		Here, the graph may contain negative edges but those negative edges should not lead to a negative cycle
//		Steps:
//		1.	Let dist[] be an array with INT_MAX for all vertices except the source node which is 0
//		2.	for 1 to n-1 : traverse all the edges of the graph and for an edge (u, v, wt) => d[v] = min(d[v], d[u] + wt)
//		3. 	traverse all the edges one more time and
//			a. 	if(d[u]+wt<d[v]) then there exists a shorter path to v than d[v] thus, a -ve cycle exists and BF algo is
//				not applicable
//			b. 	else if (d[u] + wt == d[v]) then a negative cycle does not exist and BF algo gives the shortest path
//		It is applicable for graphs without negative cycles =>
//			a. 	an directed graph may have negative edges without any negative cycles
//			b. 	an undirected graph without any negative edges (as even a single negative edge in an undirected graph creates
//				a negative cycle)

//	Running time = O(mn) or O(VE). As for 1 to n-1 + traversal of all edges i.e. O((n-1)*(m)) = O(mn)
//	Auxiliary space = O(n) or O(V)

#include<iostream>
#include<map>
#include<list>
#include<vector>
#include<stack>
using namespace std;



template<typename T>
class graph {
	map<T, list<pair<T, int>> > adjL;
public:
	void addEdge(T u, T v, int weight) {
		adjL[u].push_back(make_pair(v, weight));		//	Two different ways to insert a pair value
		//adjL[v].push_back({u, weight});               //  This implies it is an undirected graph
		if(adjL.find(v)==adjL.end()) adjL[v];           //  This implies it is a directed graph
	}
	void printAdjL() {
		typename map<T, list<pair<T, int>>>::iterator it;
		for(it = adjL.begin(); it!=adjL.end(); it++) {
			cout<<it->first<<" -> ";
			typename list<pair<T, int>>::iterator nbr;
			for(nbr = it->second.begin(); nbr != it->second.end(); nbr++) {
				cout<<"("<<nbr->first<<", "<<nbr->second<<"), ";
			}
			cout<<"\n";
		}
	}
	vector<T> printBFA(T src, T dest, map<T, int> dist, map<T, T> parent) {
		if(dist[dest]==INT_MAX) {
            cout<<"No path exists from "<<src<<" to "<<dest<<"\n";
            return {};
		}
		cout<<"The distance of each node v from "<<src<<" is:\n";
		cout<<"node v\tdist[v]\n";
		for(auto i : dist) cout<<i.first<<"\t"<<i.second<<"\n";
		stack<T> S;
		T i = dest;
		while(i!=src) {
			S.push(i);
			i = parent[i];
		}
		S.push(src);
		vector<T> ssspBFA;
		while(!S.empty()) {
			ssspBFA.push_back(S.top());
			S.pop();
		}
		cout<<"The shortest path from "<<src<<" to "<<dest<<" is:\n";
		for(int i=0; i<ssspBFA.size(); i++) cout<<ssspBFA[i]<<" ";
		cout<<"\n";
		cout<<"Thus, the cost of the shortest path = "<<dist[dest]<<"\n";
		return ssspBFA;
	}
	vector<T> bellmanFordAlgo(T src, T dest) {
		map<T, int> dist;
		map<T, T> parent;
		for(auto u : adjL) {
            dist[u.first] = INT_MAX;
            parent[u.first] = u.first;
		}
		dist[src] = 0;
		int V = adjL.size();
		for(int i=1; i<=V-1; i++) { // or for(int i=0; i<V-1; i++) {
			for(auto i : adjL) {
				T u = i.first;
				for(auto j : i.second) {
					T v = j.first;
					int wt = j.second;
					if(dist[u]!=INT_MAX) {  //  if src is not the first node of adjL, then dist[u] = INT_MAX and dist[u] + wt = out of range of int
                        dist[v] = min(dist[v], dist[u] + wt);
                        parent[v] = u;
					}
				}
			}
		}
		vector<T> ssspBFA = printBFA(src, dest, dist, parent);
		return ssspBFA;
	}
};

int main() {
	graph<string> G;
	G.addEdge("A1", "B2", 1); 	G.addEdge("A1", "C3", 2);
	G.addEdge("B2", "E5", 3); 	G.addEdge("C3", "E5", 3);
	G.addEdge("B2", "D4", 1); 	G.addEdge("D4", "E5", 1);
	G.printAdjL();
	string src, dest;
	//src = "A1"; dest = "E5";
	src = "E5"; dest = "A1"; // important case as here we are the src is not the first node of adjL
	vector<string> sssp = G.bellmanFordAlgo(src, dest);
	return 0;
}
