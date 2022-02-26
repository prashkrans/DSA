/*	Graph Problem #10.3b. - Lexicographically Smallest Topological Ordering
	Given a directed graph with N vertices and M edges that may contain cycles, the task is to find the
	lexicographically smallest topological ordering of the graph if it exists otherwise print -1 (if the
	graph has cycles).
	Lexicographically smallest topological ordering means that if two vertices in a graph do not have any
	incoming edge then the vertex with the smaller number should appear first in the ordering.
	For Example, Both 5 2 3 4 0 1, 5 0 2 4 3 1 are correct TS of a graph but the smallest ordering is 4 5 0 2 3 1.
	Note: Here, the graph may be connected or not, so, create an empty list for each node 1 to n
	This problem can only be solved using Kahn's algorithm
    hackerearth - https://www.hackerearth.com/practice/algorithms/graphs/topological-sort/practice-problems/algorithm/topological-sorttutorial/
*/
//	Running time = O(BFS + nlog2(n)) = O(n+m + nlog2(n)) ~ O(m) or O(E) since m <= n^2
//	Auxiliary space = O(n) or O(V) due the indegree[] array

#include<iostream>
#include<map>
#include<unordered_map>
#include<set>
#include<list>
#include<vector>
using namespace std;

template<typename T>
class graph {
	map<T, list<T>> adjL;
	int n;
public:
    graph(int x) {
        n = x;
        for(int i=1; i<=n; i++) adjL[i];                //  Creating an empty list for all the vertices 1 to n
    }
	void addEdge(T u, T v) {							//	This implies the given graph is directed
		adjL[u].push_back(v);
	}
	void print() {
		for(auto v : adjL) {
			cout<<v.first<<" -> ";
			for(auto w : adjL[v.first]) cout<<w<<", ";
			cout<<"\n";
		}
	}
	vector<T> lexTopoSortBFS() {
        unordered_map<T, int> indeg;
        set<T> S;
        int count = 0;
        vector<T> lts;
        for(auto i : adjL) indeg[i.first]=0;
        for(auto i : adjL) {
            for(auto v : i.second) indeg[v]++;
        }
        for(auto i : adjL) {
            T u = i.first;
            if(indeg[u]==0) S.insert(u);
        }
        while(!S.empty()) {
            T u = (*S.begin());
            lts.push_back(u);
            count++;
            S.erase(S.begin());
            for(auto v : adjL[u]) {
                indeg[v]--;
                if(indeg[v]==0) S.insert(v);    //  Each insert operation takes O(log2(x)) time where x is the number of nodes in the set currently
            }
        }
        if(count!=adjL.size()) {
            cout<<"The given graph is cyclic hence, no TS exists\n";
			vector<T> newLTS;
            return newLTS;
        }
        return lts;
    }
};


int main() {
	//  Make sure that G is a DAG
	int n, m, u, v;
	cin>>n>>m;
	graph<int> G(n);
	for(int i=0; i<m; i++) {
		cin>>u>>v;
		G.addEdge(u, v);
	}
	//G.print();
	//cout<<"The topological sorting is: \n";
	vector<int> topoSort = G.lexTopoSortBFS();
	for(int i=0; i<topoSort.size(); i++) cout<<topoSort[i]<<" ";
	//cout<<"\n";
	return 0;
}
