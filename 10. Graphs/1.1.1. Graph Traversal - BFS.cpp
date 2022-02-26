/*	Graph Problem #3.1.1 - Breadth First Search (BFS)
	The first path found in BFS is always the shortest path in an unweighted graph whether directed or not, unlike DFS.
	BFS works well with both directed and undirected graphs, however here the graph is undirected.
*/
//	Running time = O(n+m) = O(V+E) as summation over v + degree(v)
//	But in a connected graph m >= n-1 hence, it becomes O(m) or O(E)
//	Auxiliary space = O(n) or O(V). Since, an extra visited array is needed of size V
//	Note - However the space reqd. for adjacency matrix is O(n+m) (average cases) & O(n^2) (worst case)

#include<iostream>
#include<map>
#include<unordered_map>
#include<list>
#include<queue>
using namespace std;

class graph {
	map<int, list<int>> adjL;				//	Using an ordered map so that it stores the neighbours in a sorted manner
public:
	void addEdge(int x, int y) {
		adjL[x].push_back(y);
		adjL[y].push_back(x);				
	}
	void printAdjL() {
		for(auto i : adjL) {
			cout<<i.first<<" -> ";
			for(auto j : i.second) cout<<j<<", ";
			cout<<"\n";
		}
	}
	void BFS(int src) {                     //  Method declared and defined together
		map<int, int> visited;				//	Another map to check whether a node/vertex was already visited
		queue<int> Q;						//	Could have used an array too for visited since the value of node is an integer
		Q.push(src);						//	BFS uses a queue while DFS uses a stack or recursion
		visited[src] = 1;
		while(!Q.empty()) {
			int curr = Q.front();
			Q.pop();
			cout<<curr<<" ";
			for (auto i : adjL[curr]) {
				if(!visited[i]) {
					Q.push(i);
					visited[i] = 1;
				}
			}
		}
		cout<<"\n";
	}
	void BFS1b(int src);                     //  Method declared but defined later
};

void graph::BFS1b(int src) {
		unordered_map<int, int> visited;
		queue<int> Q;
		Q.push(src);
		visited[src] = 1;
		while(!Q.empty()) {
			int curr = Q.front();
			Q.pop();
			cout<<curr<<" ";
			for (list<int>::iterator it = adjL[curr].begin(); it!=adjL[curr].end(); it++) {
				if(visited[*it]==0) {
					Q.push(*it);
					visited[*it] = 1;
				}
			}
		}
		cout<<"\n";
	}

int main() {
	graph G;
	G.addEdge(1, 2);	G.addEdge(1, 3);	G.addEdge(2, 4);	G.addEdge(3, 4);
	G.addEdge(3, 5); 	G.addEdge(4, 5); 	G.addEdge(4, 6); 	G.addEdge(5, 6);
	cout<<"The adjacency list = \n";
	G.printAdjL();
	int src = 5;
	cout<<"BFS traversal with src = "<<src<<"\n";
	G.BFS(src);
	cout<<"BFS traversal (without using auto) with src = "<<src<<"\n";
	G.BFS1b(src);
	return 0;
}
