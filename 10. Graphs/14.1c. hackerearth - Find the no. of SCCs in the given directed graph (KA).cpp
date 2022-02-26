/* Graph problem #17.1c. Find the no. of SCCs in the given directed graph (Kosaraju's Algo)
Given a directed graph with N nodes and M directed edges. Find C-D where,
C Sum of number of nodes in all Strongly Connected Components with odd number of nodes.
D Sum of number of nodes in all Strongly Connected Components with even number of nodes.
Constraints:
The nodes vary from 1 to N. 
There can be nodes with zero in/out edges.

hackerearth - https://www.hackerearth.com/practice/algorithms/graphs/strongly-connected-components/tutorial/
*/

//	Method 1. Using Kosaraju's algo + a stack
//	Running time = O(2*DFS) ~ O(m)
//	Auxiliary space = O(n+m) ~ O(m)

#include<iostream>
#include<map>
#include<list>
#include<stack>
using namespace std;

class graph {
	map<int, list<int>> adjL;
public:                                 
	graph(int n) {
		for(int i=1; i<=n; i++) adjL[i];
	}
//  This works completely fine as long as the each node has atleast one in/out edges
	void addEdge(int u, int v) {        //  Since we are adding vertices to the adjacency list only when an edge is being added,
		adjL[u].push_back(v);           //  so, the vertices with zero in/out edges are not added to the adjacency list.
		if(adjL.count(v)==0) adjL[v];   //  Hence, they need to be pushed into the adjacency list by a different means i.e.
	}                                  	//  if (n - adjL.size() > 0) we need to add the lone vertices u as adjL[u]; i.e. empty list is to be appended to u.

	void printAdjL() {
		for(auto i : adjL) {
			cout<<i.first<<" -> ";
			for(auto v : i.second) cout<<v<<", ";
			cout<<"\n";
		}
	}

	void printVisited(map<int, int> visited) {
	    cout<<"Printing the visited array: \n";
        for(auto i : visited) cout<<i.first<<"\t"; cout<<"\n";
        for(auto i : visited) cout<<i.second<<"\t"; cout<<"\n";
	}

	void DFS1(int src, map<int, int> &visited, stack<int> &S) {                             //	DFS1 acts on the given graph G and fills the values in the stack S
		visited[src] = 1;
		for(auto v : adjL[src]) if(!visited[v]) DFS1(v, visited, S);
		S.push(src);
	}

	void DFS2(int src, map<int, list<int>> revAdjL, map<int, int> &visited, int sccNum) {     //	DFS2 acts on the reversed graph G and fills the visited array with sccNum
		visited[src] = sccNum;
		for(auto v : revAdjL[src]) if(!visited[v]) DFS2(v, revAdjL, visited, sccNum);
	}

	map<int, list<int>> reverseEdges() {                                                    //	It simply reverses the directions of the edges in the graph
		map<int, list<int>> revAdjL;                                                        //	Here, it creates a new adjL as a map<int, list<int>>
		for(auto i : adjL) {
			int u = i.first;
			for(auto v : adjL[u]) {
				revAdjL[v].push_back(u);
				if(revAdjL.count(u)==0) revAdjL[u];
			}
		}
		return revAdjL;
	}

	int kosarajuAlgo() {                                            //	Kosaraju's Algo:
		map<int, int> visited;                                        //	1. DFS1(G) => stack S
		stack<int> S;                                                 //	2. reverse(G)
		for(auto i : adjL) {                                        //	3. while(!S.empty()) do DFS2(revG)
			if(!visited[i.first]) DFS1(i.first, visited, S);
		}
		//printVisited(visited);
		map<int, list<int>> revAdjL = reverseEdges();
		visited.clear();                                            // 	Initialising the visited array as visited[v] = 0 i.e. visited.clear() used as
		int sccNum = 0;                                             //	visited here is a map whereas sccNum simply counts the no. of times DFS2() is called
		while(!S.empty()) {
			int v = S.top();
			S.pop();
			if(!visited[v]) {
				sccNum++;
				DFS2(v, revAdjL, visited, sccNum);
			}
		}
		//printVisited(visited);
		//cout<<"The no. of SCCs in are = "<<sccNum<<"\n";
		int C = 0;
		int D = 0;
		for(int i=1; i<=sccNum; i++) {
			int noOfNodes = 0;
			for(auto j : visited) {
				if(j.second==i) noOfNodes++;
			}
			if(noOfNodes%2==1) C += noOfNodes;
			else D += noOfNodes;
		}
		return C-D;
	}
};

int main() {
	int n, m;
	cin>>n>>m;
	graph G(n);
	int u, v;
	for(int i=0; i<m; i++) {
		cin>>u>>v;
		G.addEdge(u, v);
	}
	//G.printAdjL();
	cout<<G.kosarajuAlgo();
	return 0;
}

/* Sample input:
15 15
3 1
12 11
10 9
8 5
1 12
10 2
1 14
7 9
10 13
11 1
6 5
1 15
2 11
2 6
9 11
*/
//	Output = 15
//	Note - Here node 4 is a lone node 
