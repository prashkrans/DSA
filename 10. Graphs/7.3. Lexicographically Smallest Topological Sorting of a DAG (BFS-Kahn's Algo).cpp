/*	Graph Problem #10.3. - Lexicographically Smallest Topological Ordering
	Given a directed graph with N vertices and M edges that may contain cycles, the task is to find the
	lexicographically smallest topological ordering of the graph if it exists otherwise print -1 (if the
	graph has cycles).
	Lexicographically smallest topological ordering means that if two vertices in a graph do not have any
	incoming edge then the vertex with the smaller number should appear first in the ordering.
	For Example, Both 5 2 3 4 0 1, 5 0 2 4 3 1 are correct TS of a graph but the smallest ordering is 4 5 0 2 3 1.
	Note: Here, we assume that all the nodes are inserted in to the DAG using the edges, i.e. there exists no node
	without any edge either coming in or going out. If such is a case we need to insert it into the DAG, separately.

	This problem can only be solved using Kahn's algorithm
*/

//	Method 1 - Using BFS algo + indegree array (Kahn's algorithm)
//	This algo is based on the property that:
//	"a DAG G has at least one vertex with in-degree 0 and one vertex with out-degree 0"
//	Proof: There’s a simple proof to the above fact is that a DAG does not contain a cycle which means that all
//	paths will be of finite length. Now let S be the longest path from u(source) to v(destination). Since S is the
//	longest path there can be no incoming edge to u and no outgoing edge from v, if this situation had occurred then S
//	would not have been the longest path => indegree(u) = 0 and outdegree(v) = 0
//	Steps:
//	1. 	Compute in-degree (number of incoming edges) for each of the vertex present in the graph and
//		initialize the count of visited nodes as 0.
//	2. 	Pick all the vertices with in-degree as 0 and add them into a set instead of a queue (Enqueue operation)
//	3.	Remove a vertex from the set i.e. the smallest would be picked first (Dequeue operation) and then.
//		a.	Increment count of visited nodes by 1.
//		b. 	Decrease in-degree by 1 for all its neighboring nodes.
//		c.	If in-degree of a neighboring nodes is reduced to zero, then add it to the set.
//	4. 	Repeat Step 3 until the set is empty.
//	5.	Iff count of visited nodes is equal to the number of nodes in the graph then topological sort is possible
//		for the given graph

//	Running time = O(BFS + nlog2(n)) = O(n+m + nlog2(n)) ~ O(m) or O(E)
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
public:
	void addEdge(T u, T v) {							//	This implies the given graph is directed
		adjL[u].push_back(v);
		if(adjL.find(v)==adjL.end()) adjL[v];			//	Adds an empty list to a node with no adjacent nodes
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
            if(indeg[u]==0) {
                S.insert(u);
                //lts.push_back(u); //  We cannot use insert a node in the answer as it may not be lexicographically smaller here itself
                //count++;          //  Similarly, increment the count in the while loop
            }
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
	graph<char> G;
	//  Make sure that G is a DAG
	G.addEdge('A', 'B');	G.addEdge('A', 'C');
	G.addEdge('B', 'D');	G.addEdge('D', 'C');
	G.addEdge('F', 'D');    G.addEdge('G', 'E');
	G.addEdge('F', 'G');    G.addEdge('C', 'E');
	//G.addEdge('E', 'A');  //  makes the graph cyclic
	G.print();
	cout<<"The topological sorting is: \n";
	vector<char> topoSort = G.lexTopoSortBFS();
	for(int i=0; i<topoSort.size(); i++) cout<<topoSort[i]<<", ";
	//cout<<"\n";
	return 0;
}



