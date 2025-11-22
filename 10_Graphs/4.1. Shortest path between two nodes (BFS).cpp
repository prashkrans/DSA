/*	Graph Problem #7.1. - Shortest path between two nodes (BFS)
Find the length of the shortest path between two nodes
a. 	Using BFS (only for an unweighted graph): O(V+E)
	This uses the principle that BFS from the starting node u to all v in V-{u} gives the shortest distance from u to v,
	given that the graph is undirected and unweighted.
    #IMP - This algorithm will work even when negative weight cycles are present in the unweighted graph.
b. 	Using Djikstra's algorithm (for graphs without a negative edges whether directed or undirected): O(ElogV)
c.  Bellman Ford algorithm (for graphs without negative cycles) : O(VE)
*/

//	1a. BFS (for an unweighted graph) using the concept of predecessor/parent
//	Running time = O(BFS) = O(n+m) = O(m) = O(E)
//	Auxiliary space = O(n) or O(V). Since, two extra arrays i.e. visited and level are needed of size V
//	Note - However the space reqd. for adjacency matrix is O(n+m) (average cases) & O(n^2) (worst case)

#include<iostream>
#include<map>
#include<unordered_map>
#include<list>
#include<queue>
using namespace std;

template<typename T>                    //  template<typename anyName>
class graph {                           //  class className{...}; int main() {... className<dataType> objectName; ...}
	map<T, list<T>> adjL;				//	Using an ordered map so that it stores the neighbours in a sorted manner
	map<T, int> visited;				//	Another map to check whether a node/vertex was already visited
	map<T, int> level;                  //  Another map to store the level of the ndoe
public:
	void addEdge(T x, T y) {            //  This implies it is an undirected graph
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
	void BFS(T src) {                       //  Method declared and defined together
		queue<T> Q;						    //	Could have used an array too since the value of node is an integer
		Q.push(src);						//	BFS uses a queue while DFS uses a stack or recursion
		visited[src] = 1;
		level[src] = 0;                     //  level of the source node == 0
		while(!Q.empty()) {
			T curr = Q.front();
			Q.pop();
			//cout<<curr<<" ";
			for(auto it = adjL[curr].begin(); it!=adjL[curr].end(); it++) {
				if(!visited[*it]) {
					Q.push(*it);
					visited[*it] = 1;
					level[*it] = level[curr]+1; //  concept of predecessor used
				}                               //  i.e. level of adjacent vertices = level of predecessor + 1
			}
		}
		cout<<"Vertex:\t";    for(auto i : level) cout<<i.first<<"\t";
		cout<<"\nLevel:\t";		for(auto i : level) cout<<i.second<<"\t";
		cout<<"\n";
	}
	int bfsWithoutDistArray(T src, T dest);
	int lenOfSP(T src, T dest) {
        BFS(src);
        cout<<"The distance between src ("<<src<<") and dest ("<<dest<<") = ";
        return level[dest];

	}
};

//	1b. BFS (for an unweighted graph) using the concept of levels
//	Running time = O(BFS) = O(n+m) = O(m) = O(E)
//	Auxiliary space = O(n) or O(V). Since, two extra arrays i.e. visited and level are needed of size V
//	Note - However the space reqd. for adjacency matrix is O(n+m) (average cases) & O(n^2) (worst case)

template <typename T>
int graph<T>::bfsWithoutDistArray(T src, T dest) {
	visited.clear();
	queue<T> q;
	int dist = 0;
	q.push(src);
	visited[src] = 1;
	while(!q.empty()) {
		int qSize = q.size();				// Get the queue size upfront
		for(int i=0; i<qSize; i++) {		// Use a for loop and the rest remains the same
			T u = q.front();
			q.pop();
			for(auto v: adjL[u]) {
				if(!visited[v]) {
					q.push(v);
					visited[v] = 1;
					if(v==dest) return dist+1;
				}
			}
		}
		dist++;								// Increase dist by one when the loop ends
	}
	return -1;	// No path exists between src and dest
}


int main() {
	graph<int> G;   //  Just change the typename here for different datatypes
	G.addEdge(1, 2);	G.addEdge(1, 3);	G.addEdge(2, 4);	G.addEdge(3, 4);
	G.addEdge(3, 5); 	G.addEdge(4, 5); 	G.addEdge(4, 6); 	G.addEdge(5, 6);
	cout<<"The adjacency list = \n";
	G.printAdjL();
	int src = 1; int dest = 6;
	//cin>>src>>dest;
	cout<<G.lenOfSP(src, dest)<<"\n";
	dest = 5;
	cout<<"The distance between src: "<<src<<" and the dest: "<<dest<<" is: ";
	cout<<G.bfsWithoutDistArray(src, dest)<<"\n";
	return 0;
}