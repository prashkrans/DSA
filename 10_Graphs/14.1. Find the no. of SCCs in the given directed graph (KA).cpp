/* Graph problem #17.1. Find the no. of SCCs in the given directed graph (Kosaraju's Algo)
Given a directed graph, find the number of strongly connected components in the graph.

A directed graph is strongly connected if there is a path between all pairs of vertices.
Strongly connected components (SCCs) are maximal strongly connected subgraphs of the given
directed graph.

There are two methods to find the no. of SCCs in the given directed graph:
	1.	Kosaraju's Algo: R.T. = O(m) but 2 DFSs used
	2.	Tarjan's Algo: R.T. = O(m) but a single DFS is used
*/

//	Method 1. Kosaraju's Algo + a stack
//	Steps:
//	1.	Create an empty stack ‘S’ and do DFS1() traversal of a graph. In DFS traversal, after
//		calling recursive DFS for adjacent vertices of a vertex, push the vertex to stack.
//      This is exactly the same use of stack as in finding the topological sort of a DAG
//	2.	Reverse directions of all the edges to obtain the transpose/reversed graph.
//	3.	One by one pop a vertex from S while S is not empty. Let the popped vertex be ‘v’.
//		If v is not visited then take v as a source and do DFS2(v) on the reversed graph.
//		The DFS starting from v prints a strongly connected component of which v is a part.
//		Hence, no. of times DFS2() is called, is the no. of SCCs in the graph
//	Note - 	This can also be used to check if the given graph is strongly connected.
//			Steps:
//			4. 	After completing the steps 1 to 3 if, visited[v]>1 for any vertex v then
//				=> G has more than one SCCs thus G itself is not a maximal strongly connected subgraph
//				=> G is not strongly connected
//				Else if visited[v]==1 for all the vertices v => G is strongly connected

//	Running time = O(2*DFS + m(reversal) + n(stack & visited)) = O(m+n) ~ O(m) i.e. linear in no. of edges
//	Auxiliary space = O(m+n) if a new adjL is created else O(m) if the given adjL itself is modified but we do need
//	O(m) size vector to store the no. of edges.

#include<iostream>
#include<map>
#include<list>
#include<stack>
using namespace std;

template<typename T>
class graph {
	map<T, list<T>> adjL;
public:                                 //  This works completely fine as long as the each node has atleast one in/out edges
	void addEdge(T u, T v) {            //  Since we are adding vertices to the adjacency list only when an edge is being added,
		adjL[u].push_back(v);           //  so, the vertices with zero in/out edges are not added to the adjacency list.
		if(adjL.count(v)==0) adjL[v];   //  Hence, they need to be pushed into the adjacency list by a different means i.e.
	}                                   //  if (n - adjL.size() > 0) we need to add the lone vertices u as adjL[u]; i.e. empty list is to be appended to u.

	void printAdjL() {
		for(auto i : adjL) {
			cout<<i.first<<" -> ";
			for(auto v : i.second) cout<<v<<", ";
			cout<<"\n";
		}
	}

	void printVisited(map<T, int> visited) {
	    cout<<"Printing the visited array: \n";
        for(auto i : visited) cout<<i.first<<"\t"; cout<<"\n";
        for(auto i : visited) cout<<i.second<<"\t"; cout<<"\n";
	}

	void DFS1(int src, map<T, int> &visited, stack<T> &S) {                             //	DFS1 acts on the given graph G and fills the values in the stack S
		visited[src] = 1;                                                               //  DFS1 uses the same algo as in topo sort of DAG to fill the stack S
		for(auto v : adjL[src]) if(!visited[v]) DFS1(v, visited, S);
		S.push(src);
	}

	void DFS2(int src, map<T, list<T>> revAdjL, map<T, int> &visited, int sccNum) {     //	DFS2 acts on the reversed graph G and fills the visited array with sccNum
		visited[src] = sccNum;
		for(auto v : revAdjL[src]) if(!visited[v]) DFS2(v, revAdjL, visited, sccNum);
	}

	map<T, list<T>> reverseEdges() {                                                    //	It simply reverses the directions of the edges in the graph
		map<T, list<T>> revAdjL;                                                        //	Here, it creates a new adjL as a map<T, list<T>>
		for(auto i : adjL) {
			T u = i.first;
			for(auto v : adjL[u]) {
				revAdjL[v].push_back(u);
				if(revAdjL.count(u)==0) revAdjL[u];
			}
		}
		return revAdjL;
	}

	int kosarajuAlgo() {                                            //	Kosaraju's Algo:
		map<T, int> visited;                                        //	1. DFS1(G) => stack S
		stack<T> S;                                                 //	2. reverse(G)
		for(auto i : adjL) {                                        //	3. while(!S.empty()) do DFS2(revG)
			if(!visited[i.first]) DFS1(i.first, visited, S);
		}
		printVisited(visited);
		map<T, list<T>> revAdjL = reverseEdges();
		visited.clear();                                            // 	Initialising the visited array as visited[v] = 0 i.e. visited.clear() used as
		int sccNum = 0;                                             //	visited here is a map whereas sccNum simply counts the no. of times DFS2() is called
		while(!S.empty()) {
			T v = S.top();
			S.pop();
			if(!visited[v]) {
				sccNum++;
				DFS2(v, revAdjL, visited, sccNum);
			}
		}
		printVisited(visited);
		cout<<"The no. of SCCs in are = "<<sccNum<<"\n";
		return sccNum;
	}
};

int main() {
	graph<int> G;
	G.addEdge(1, 2);    G.addEdge(1, 3);
	G.addEdge(1, 4);    G.addEdge(2, 3);
	G.addEdge(5, 1);    G.addEdge(4, 2);
	G.addEdge(3, 1);    //  this edge reduces the no. of SCCs
	G.printAdjL();
	G.kosarajuAlgo();
	return 0;
}
