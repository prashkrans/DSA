/*	Graph Problem #9.2. - Is the given directed graph acyclic?
	Given a directed graph, check whether the graph contains a cycle or not.
	The function should return true if the given graph contains at least one cycle, else return false.
*/
//	Method 2. - Using BFS (Kahn's Algorithm for Topological Sorting) + Count Variable
//	Steps :
//	1. 	Compute in-degree (number of incoming edges) for each of the vertex present in the graph and initialize the count of visited nodes as 0.
//	2. 	Pick all the vertices with in-degree as 0 and add them into a queue (Enqueue operation)
//	3.	Remove a vertex from the queue (Dequeue operation) and then. \
//		a.	Increment count of visited nodes by 1.
//		b. 	Decrease in-degree by 1 for all its neighboring nodes.
//		c.	If in-degree of a neighboring nodes is reduced to zero, then add it to the queue.
//	4. 	Repeat Step 3 until the queue is empty.
//	5.	If count of visited nodes is not equal to the number of nodes in the graph has cycle, otherwise not.

// 	Note: 
// 1. There's no need of visited array
// 2. Increase count or add nodes to toposort at two places a. when inserting u and b. inserting v
// 

//	Running time = O(BFS) = O(n+m) = O(V+E) which becomes O(m) or O(E) if m>=n
//	Auxiliary space = O(n) or O(V) due the indegree[] array

#include<iostream>
#include<map>
#include<unordered_map>
#include<queue>
#include<list>
#include<vector>
using namespace std;

template<typename T>
class graph {
	map<T, list<T>> adjL;
public:
	vector<T> topoSort;

	void addEdge(T u, T v) {
		adjL[u].push_back(v);
		if(adjL.count(v)==0) {
		    list<T> emptyList;
            adjL[v] = emptyList;    //  To make sure that a vertex pointing to no other vertex is also included in the adjL
		}                           //  i.e. we just create an empty list for that vertex
	}                               //  or just directly use adj[v]; as follows:    //  void addEdge(T u, T v) {
                                                                                    // 	    adjL[u].push_back(v);
                                                                                    // 	    if(adjL.count(v)==0) adj[v]; // this also creates an empty list
	void printAdjL() {                                                              //  }
		for(auto u : adjL) {
			cout<<u.first<<" -> ";
			for(auto v : adjL[u.first]) cout<<v<<", ";
			cout<<"\n";
		}
	}
	bool isCyclicBFS() {
		map<T, int> inDegree;		//  It is important to initialize inDegree[v] = 0 for all vertices
        for(auto v : adjL) inDegree[v.first] = 0;
		queue<T> Q;
		int count = 0;
		for(auto u : adjL) {
			for(auto v : u.second) if(v!=-1) inDegree[v]++;
		}
		//for(auto i : inDegree) cout<<i.first<<" = "<<i.second<<"\n";
		for(auto u : inDegree) {
			if(u.second==0) {
				Q.push(u.first);
				count++;
				topoSort.push_back(u.first);
			}
		}
		while(!Q.empty()) {
			T u = Q.front();
			Q.pop();
			for(auto v : adjL[u]) {
				inDegree[v]--;
				if(inDegree[v]==0) {
					Q.push(v);
					count++;
					topoSort.push_back(v);
				}
			}
		}
		if(count!=adjL.size()) return true;
		else return false;
	}
};

int main() {
	graph<double> G;
	G.addEdge(1.0, 2.0);	    G.addEdge(3.0, 1.0);
	G.addEdge(2.0, 3.5);	    G.addEdge(3.0, 4.2);
	//G.addEdge(3.5, 3.0);      //  makes the graph cyclic
	G.printAdjL();
	if(G.isCyclicBFS()) cout<<"The given directed graph has a cycle\n";
	else cout<<"The given directed graph does not have a cycle\n";
	return 0;
}



