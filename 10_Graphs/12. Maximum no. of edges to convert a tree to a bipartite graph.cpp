/* Graph problem #15. - Maximum number of edges to be added to a tree so that it stays a Bipartite graph
Given a undirected tree, compute the maximum no. of edges that can be added to the tree so that it
remains a bipartite graph. Note - A tree by definition is connected.
*/

//	Method 1 - BFS + 2 Colours (say red-1 and blue-0)
//	Steps:
//	1.	Do a simple BFS traversal of graph and color it with two colors.
//	2.	While coloring also keep track of counts of nodes colored with the two colors. Let the two counts be
//		count_blue0 and count_red1.
//	3.	Now we know maximum edges a bipartite graph can have are count_blue0 x count_red1.
//	4.	We also know a tree with n nodes has n-1 edges. So, the answer is (count_blue0 x count_red1 – (n-1)).
//	4b.	If a graph was given instead of a tree, then count the no. of edges in the graph say noOfEdges.
//		So, the answer would be (count_blue0 x count_red1 - noOfEdges)

//  Running time = O(BFS) or O(n+m) ~ O(m)
//  Auxiliary space = O(n) or O(V)

#include<iostream>
#include<map>
#include<list>
#include<queue>
using namespace std;

void addEdge(int u, int v, auto &adjL) {
	adjL[u].push_back(v);
	adjL[v].push_back(u);
}

void printAdjL(auto adjL) {
	for(auto i : adjL) {
		cout<<i.first<<" -> ";
		for(auto j : i.second) cout<<j<<", ";
		cout<<"\n";
	}
}

int BFSbipartite(auto adjL) {
	int n = adjL.size();
	map<int, int> visited;
	map<int, int> color;
	int redCount = 0; int blueCount = 0;
	queue<int> Q;
	map<int, list<int>>::iterator it = adjL.begin();
	int src = it->first;
	Q.push(src);
	visited[src] = 1;
	color[src] = 1;	//	The src node is colored red
	redCount++;     //  Count the src node as colored red
	while(!Q.empty()) {
		int u = Q.front();
		Q.pop();
		for(auto v : adjL[u]) {
			if(!visited[v]) {
				Q.push(v);
				visited[v] = 1;
				color[v] = !color[u];
				if(color[v] == 1) redCount++;
				else blueCount++;
			}
		}
	}
	int edgesPresent = n-1;
	int maxEdgesPossible = redCount * blueCount;
	cout<<"No. of red nodes = "<<redCount<<"\n";
	cout<<"No. of blue nodes = "<<blueCount<<"\n";
	cout<<"No. of edges already present = "<<edgesPresent<<"\n";
	cout<<"Max no. of edges possible for the graph to remain bipartite = "<<maxEdgesPossible<<"\n";
	cout<<"The max no. of edges that can be added to the given tree is = ";
	return (maxEdgesPossible - edgesPresent);
}


int main() {
	map<int, list<int>> adjL;
	addEdge(1, 2, adjL);	addEdge(1, 3, adjL);
	addEdge(1, 4, adjL);	addEdge(2, 5, adjL);
	addEdge(2, 6, adjL);	addEdge(3, 7, adjL);
	addEdge(3, 8, adjL);	addEdge(3, 9, adjL);
	//  The given tree contains 8 edges
	printAdjL(adjL);
	cout<<BFSbipartite(adjL)<<"\n";
	return 0;
}


