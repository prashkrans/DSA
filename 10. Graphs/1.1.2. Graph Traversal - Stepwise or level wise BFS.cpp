/*	Graph Problem #3.1.2. - Stepwise or level wise Breadth First Search (BFS)
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

template <typename T>
class graph {
	map<T, list<T>> adjL;				    //	Using an ordered map so that it stores the neighbours in a sorted manner
public:
	void addEdge(T x, T y) {
		adjL[x].push_back(y);
		adjL[y].push_back(x);               //  Implies that G is an undirected graph
	}
	void printAdjL() {
		for(auto i : adjL) {
			cout<<i.first<<" -> ";
			for(auto j : i.second) cout<<j<<", ";
			cout<<"\n";
		}
	}
	void BFS(T src) {                     	//  Method declared and defined together
		unordered_map<T, T> visited;		//	Another map to check whether a node/vertex was already visited
		queue<T> Q;							//	Could have used an array too for visited since the value of node is an integer
		int l = 0;                          //  Level begins from 0.
		Q.push(src);						//	BFS uses a queue while DFS uses a stack or recursion
		visited[src] = 1;
		while(!Q.empty()) {
			cout<<"Level "<<l<<": ";
			int qSize = Q.size();			//	Current size of the queue represents nodes in the current level L.
			for(int i=0; i<qSize; i++) {
				int curr = Q.front();
				Q.pop();
				cout<<curr<<" ";
				for (auto i : adjL[curr]) {
					if(!visited[i]) {
						Q.push(i);			//	Nodes getting pushed here would represent the next level L+1.
						visited[i] = 1;
					}
				}
			}
			l++; cout<<"\n"; 				//	Increasing the level when the for loop gets finised.
		}
	}
};

int main() {
	graph<int> G;
	G.addEdge(1, 2);	G.addEdge(1, 3);	G.addEdge(2, 4);	G.addEdge(3, 4);
	G.addEdge(3, 5); 	G.addEdge(4, 5); 	G.addEdge(4, 6); 	G.addEdge(5, 6);
	cout<<"The adjacency list = \n";
	G.printAdjL();
	int src = 5;
	cout<<"BFS traversal with src = "<<src<<"\n";
	G.BFS(src);
	src = 1;
	cout<<"BFS traversal with src = "<<src<<"\n";
	G.BFS(src);
	return 0;
}
