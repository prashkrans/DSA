/*	Graph Problem #10.2. - Topological Sorting
	Topological sorting for Directed Acyclic Graph (DAG) is a linear ordering of vertices
	such that for every directed edge u v, vertex u comes before v in the ordering.
	Topological Sorting for a graph is not possible if the graph is not a DAG.
	There are two methods to obtain the topological sorting of a DAG:
		1. 	DFS + Stack
		2.	BFS + Indegree array (Kahn's Algorithm)
		R.T of both = O(n+m) ~ O(m)
*/

//	Method 2 - Using BFS algo + indegree array (Kahn's algorithm)
//	This algo is based on the property that:
//	"a DAG G has at least one vertex with in-degree 0 and one vertex with out-degree 0"
//	Proof: There’s a simple proof to the above fact is that a DAG does not contain a cycle which means that all
//	paths will be of finite length. Now let S be the longest path from u(source) to v(destination). Since S is the
//	longest path there can be no incoming edge to u and no outgoing edge from v, if this situation had occurred then S
//	would not have been the longest path => indegree(u) = 0 and outdegree(v) = 0
//	Steps:
//	1. 	Compute in-degree (number of incoming edges) for each of the vertex present in the graph and
//		initialize the count of visited nodes as 0.
//	2. 	Pick all the vertices with in-degree as 0 and add them into a queue (Enqueue operation)
//	3.	Remove a vertex from the queue (Dequeue operation) and then.
//		a.	Increment count of visited nodes by 1.
//		b. 	Decrease in-degree by 1 for all its neighboring nodes.
//		c.	If in-degree of a neighboring nodes is reduced to zero, then add it to the queue.
//	4. 	Repeat Step 3 until the queue is empty.
//	5.	Iff count of visited nodes is equal to the number of nodes in the graph then topological sort is possible
//		for the given graph

//	Running time = O(BFS) = O(n+m) = O(V+E) which becomes O(m) or O(E) if m>=n
//	Auxiliary space = O(n) or O(V) due the indegree[] array
//	Running time = O(n+m) ~ O(m) or O(E)
//	Auxiliary space = O(n) or O(V) due to the size of the visted array and the stack

#include<iostream>
#include<map>
#include<list>
#include<queue>
#include<vector>
using namespace std;

template<typename T>
class graph {
	map<T, list<T>> adjL;
public:
	void addEdge(T u, T v) {							//	This implies the given graph is directed
		adjL[u].push_back(v);
		if(adjL.find(v)==adjL.end()) adjL[v];	//	Adds an empty list to a node with no adjacent nodes
	}
	void print() {
		for(auto v : adjL) {
			cout<<v.first<<" -> ";
			for(auto w : adjL[v.first]) cout<<w<<", ";
			cout<<"\n";
		}
	}
	vector<T> topoSortBFS() {
        map<T, int> indegree;
        queue<T> Q;
        int count = 0;
        vector<T> ts;
        for(auto v : adjL) indegree[v.first] = 0;
        for(auto v : adjL) {
            for(auto w : v.second) indegree[w]++;
        }
        for(auto v : adjL) {
            if(indegree[v.first] == 0) {
                Q.push(v.first);
                ts.push_back(v.first);
                count++;
            }
        }
        while(!Q.empty()) {
            T v = Q.front();
            Q.pop();
            for(auto w : adjL[v]) {
                indegree[w]--;
                if(indegree[w] == 0) {
                    Q.push(w);
                    ts.push_back(w);
                    count++;
                }
            }
        }
        if(count!=adjL.size()) {
            cout<<"The given graph is not a DAG therefore cannot have a topological sorting\n";
            return {};
        }
        return ts;
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
	vector<char> topoSort = G.topoSortBFS();
	for(int i=0; i<topoSort.size(); i++) cout<<topoSort[i]<<", ";
	//cout<<"\n";
	return 0;
}



