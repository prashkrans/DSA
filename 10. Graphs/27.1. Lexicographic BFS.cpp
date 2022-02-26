/* Graph problem - 30.1. Print the lexicographically smallest BFS of the graph starting from 1.
Given a connected undirected graph with N vertices and M edges. The task is to print the lexicographically
smallest BFS traversal of the graph starting from any given vertex.
*/

//	Running time = O(BFS) = O(n+m) ~ O(m) or O(E)
//	Auxiliary space = O(n) due to the visited and the priority_queue
#include<iostream>
#include<map>
#include<queue>
#include<list>
using namespace std;

template<typename T>
class graph {
	map<T, list<T>> adjL;
public:
	void addEdge(T u, T v) {
		adjL[u].push_back(v);
		adjL[v].push_back(u);
	}
	void printAdjL() {
		typename map<T, list<T>>:: iterator it;
		for(it = adjL.begin(); it!=adjL.end(); it++) {
			T u = it->first;
			cout<<u<<" -> ";
			typename list<T>::iterator jt;
			for(jt = it->second.begin(); jt!=it->second.end(); jt++) cout<<*jt<<" ";
			cout<<"\n";
		}
	}
	void lexBFS() {
		map<T, int> visited;
		priority_queue<T> PQ;
		T src = adjL.begin()->first;
		PQ.push(src);
		visited[src] = 1;
		cout<<src<<" ";
		while(!PQ.empty()) {
			T u = PQ.top();
			PQ.pop();
			typename list<T>:: iterator it;
			for(it = adjL[u].begin(); it!=adjL[u].end(); it++) {
				T v = *it;
				if(!visited[v]) {
					PQ.push(v);
					visited[v] = 1;
					cout<<v<<" ";
				}
			}
		}
	}
};

int main() {
	graph<char> G;
	G.addEdge('b', 'c');	G.addEdge('a', 'b');
	G.addEdge('b', 'd');	G.addEdge('c', 'd');
	G.addEdge('e', 'a');	G.addEdge('b', 'e');
	G.printAdjL();
	G.lexBFS();
	return 0;
}

