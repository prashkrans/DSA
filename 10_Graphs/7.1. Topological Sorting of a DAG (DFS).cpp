/*	Graph Problem #10.1. - Topological Sorting
	Topological sorting for Directed Acyclic Graph (DAG) is a linear ordering of vertices
	such that for every directed edge u v, vertex u comes before v in the ordering.
	Topological Sorting for a graph is not possible if the graph is not a DAG.
	There are two methods to obtain the topological sorting of a DAG:
		1. 	DFS + Stack
		2.	BFS + Indegree array (Kahn's Algorithm)
		R.T of both = O(n+m) ~ O(m)
*/

//	Method 1 - Using DFS algo and a stack in which a node is pushed only when all the adjacent nodes
//	of that node have been visited.
//	Running time = O(n+m) ~ O(m) or O(E)
//	Auxiliary space = O(n) or O(V) due to the size of the visted array and the stack

#include<iostream>
#include<map>
#include<list>
#include<stack>
using namespace std;

template<typename T>
class graph {
	map<T, list<T>> adjL;
public:
	addEdge(T u, T v) {							//	This implies the given graph is directed
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
	void tsDFS(int src, map<T, bool> &visited, stack<T> &tsStack) {	//	Note the use of & before vistited and tsStack
		visited[src] = 1;
		for(auto v : adjL[src]) {
			if(!visited[v]) tsDFS(v, visited, tsStack);
		}
		tsStack.push(src);
	}
	void printTopologicalSort() {
		map<T, bool> visited;
		stack<T> tsStack;
		for(auto v : adjL) {
			if(!visited[v.first]) {
				tsDFS(v.first, visited, tsStack);
			}
		}
		cout<<"The topological sorting is: \n";
		while(!tsStack.empty()) {
			cout<<tsStack.top()<<" ";
			tsStack.pop();
		}
		cout<<"\n";
	}
};

int main() {
	graph<char> G;
	//  Make sure that G is a DAG
	G.addEdge('a', 'b');	G.addEdge('a', 'c');
	G.addEdge('b', 'c');	G.addEdge('c', 'd');
	G.addEdge('e', 'd');    G.addEdge('f', 'c');
	G.addEdge('e', 'f');    G.addEdge('g', 'b');
	G.print();
	G.printTopologicalSort();
	return 0;
}



