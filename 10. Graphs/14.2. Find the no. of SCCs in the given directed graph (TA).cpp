/* Graph problem #17.2. Find the no. of SCCs in the given directed graph (Tarjan's Algo)
Given a directed graph, find the number of strongly connected components in the graph.

A directed graph is strongly connected if there is a path between all pairs of vertices.
Strongly connected components (SCCs) are maximal strongly connected subgraphs of the given
directed graph.

There are two methods to find the no. of SCCs in the given directed graph:
	1.	Kosaraju's Algo: R.T. = O(m) but two DFSs used
	2.	Tarjan's Algo: R.T. = O(m) but a single DFS is used
	
yt - https://www.youtube.com/watch?v=wUgWX0nc4NY&ab_channel=WilliamFiset
*/

//	Method 2. Tarjan's Algo + Stack + inStack
//  The stack used here is quite to similar to stack usage in finding whether a directed
//  graph has a cycle.
//  Working principle:
//  1.  if low[u] == disc[u] => u is the head of an SCC
//  2.  for e(u, v) if v is already visited and v is still in the stack then e(u, v) is a back edge
//      and not a cross edge
//	Steps:

//	Running time = O(DFS) = O(m+n) ~ O(m) i.e. linear in no. of edges
//	Auxiliary space = O(n) or O(V)

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

	void taDFS(T u, map<T, int> &visited, map<T, int> &disc, map<T, int> &low, map<T, int> &inStack, stack<T> &S) {
		static int time = 0;	    //	static keyword allows us to declare a variable only once, even if it is called multiple times in recursion
		static int sccCount = 0;    //  thus it saves us the trouble of using time as a parameter in taDFS()
		visited[u] = 1;
		disc[u] = time++;
		low[u] = disc[u];
		inStack[u] = 1;             //  inStack[u] = 1 or 0 => whether u is currently in the stack or not
		S.push(u);                  //  current vertex u is pushed in the stack
		for(auto v : adjL[u]) {
			if(!visited[v]) {
				taDFS(v, visited, disc, low, inStack, S);	//	recursion gives low[v]
				low[u] = min(low[u], low[v]);
			}
			else if(inStack[v]==1) low[u] = min(low[u], disc[v]);	// 	we consider only back edges here and not cross edges, so a stack is used
		}															//	i.e. and edge(u, v) is a back edge iff v is still present in the stack
		if(low[u] == disc[u]) {                                     //  if (low[u] == disc[u]) => an SCC is found with its root at u
			//u is the root of an SCC                               //  so, remove the nodes including u from the stack
			cout<<"The node(s) in the SCC#"<<++sccCount<<" is/are:\n";
			while(S.top()!=u) {
				cout<<S.top()<<" ";
				inStack[S.top()] = 0;
				S.pop();
			}
			cout<<S.top()<<"\n";
			inStack[S.top()] = 0;
			S.pop();
		}
	}

	void tarjansAlgo() {
		map<T, int> visited;
		map<T, int> disc;
		map<T, int> low;
		map<T, int> inStack;
		stack<T> S;
		int sccCount = 0;
		for(auto i : adjL) {
			T u = i.first;
			if(!visited[u]) {
				sccCount++;
				taDFS(u, visited, disc, low, inStack, S);
			}
		}
		cout<<"The no. of SCCs in the given directed graph is = "<<sccCount<<"\n";
	}
};

int main() {
	graph<int> G;
	G.addEdge(1, 2);    G.addEdge(1, 3);
	G.addEdge(1, 4);    G.addEdge(2, 3);
	G.addEdge(5, 1);    G.addEdge(4, 2);
	//G.addEdge(3, 1);    //  this edge reduces the no. of SCCs
	G.printAdjL();
	G.tarjansAlgo();
	return 0;
}
