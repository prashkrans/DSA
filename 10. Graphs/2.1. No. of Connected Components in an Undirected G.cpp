/*	Graph Problem #5.1. - LC#323. No. of connected components (Premium)
	Find the no. of connected components in the given undirected graph.
	It should even take care of a vertex not connected to any other vertices.
	#IMP - The given graph should be undirected as there is a different notion for directed graphs
	There are three methods to solve this problem:
	1. BFS: #Algo. - No. of time BFS is called = No. of connected components
	2. DFS
	3. Disjoint Set (Union-Find Algo)
	
*/
//	Method 1: BFS
//	Running time = O(n+m) = O(V+E) as summation over (v + degree(v))
//	But in a connected graph m >= n-1 hence it becomes O(m) or O(E)
//	Auxiliary space = O(n) or O(V). Since, an extra visited array is needed of size V


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
		if(y==-1) adjL[x].push_back(-1);    //  If a vertex has no edges to any other vertex
		else {
            adjL[x].push_back(y);
            adjL[y].push_back(x);
		}
	}
	void printAdjL() {
		for(auto i : adjL) {
			cout<<i.first<<" -> ";
			for(auto j : i.second) if(j!=-1) cout<<j<<", ";
			cout<<"\n";
		}
	}
	int CC() {
		map<int, int> visitedCC;
		for(auto i : adjL)
			visitedCC[i.first] = 0;
		int ans = 0;
		for(auto i : visitedCC) {
			if(i.second==0) BFS(i.first, ++ans, visitedCC);
		}
		for(auto i : visitedCC) {
            if(i.first!=-1) cout<<"Vertex "<<i.first<<" lies in CC#"<<i.second<<"\n";
		}
		return ans;
	}

	void BFS(int src, int ans, map<int, int> &visitedCC) {
		queue<int> Q;						//	Could have used an array too since the value of node is an integer
		Q.push(src);						//	BFS uses a queue while DFS uses a stack or recursion
		visitedCC[src] = ans;				//	ans would vary from 1 to no. of connected components
		while(!Q.empty()) {
			int curr = Q.front();
			Q.pop();
			cout<<curr<<" ";
			for (auto i : adjL[curr]) {
				if(!visitedCC[i] && i!=-1) {
					Q.push(i);
					visitedCC[i] = ans;
				}
			}
		}
		cout<<"\n";
	}
};

int main() {
	graph G;
	G.addEdge(1, 2);	G.addEdge(1, 3);	G.addEdge(2, 4);	G.addEdge(3, 4);
	G.addEdge(3, 5); 	G.addEdge(4, 5); 	G.addEdge(4, 6); 	G.addEdge(5, 6);
	G.addEdge(7, -1);   G.addEdge(8, 9);    G.addEdge(10, 11);  G.addEdge(12, 1);
	cout<<"The adjacency list = \n";
	G.printAdjL();
	cout<<"The connected components = \n";
	int cc = G.CC();
	cout<<"The no. of connected components are = "<<cc<<"\n";
	return 0;
}
