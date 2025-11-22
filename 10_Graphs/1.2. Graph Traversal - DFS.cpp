/*	Graph Problem #4 - Depth First Search (DFS)
	DFS works for both directed and undirected graphs.
	The processing order of the nodes in DFS is the exact opposite order as how they were added to the 
	stack, which is Last-in-First-out(LIFO). That's why we use a stack in DFS.
	
	DFS can be implemented using:
a.	a stack (i.e. iterative DFS similar to how BFS uses a queue)
	The advantage of the recursion solution is that it is easier to implement. However, there is a huge 
	disadvantage: if the depth of recursion is too high, you will suffer from stack overflow. 
	In that case, you might want to use BFS instead or implement DFS using an explicit stack.
	
b.	recursion (i.e. recursion stack)
	It seems like we don't have to use any stacks when we implement DFS recursively. But actually, 
	we are using the implicit stack provided by the system, also known as the Call Stack.
	It is easier to implement than using an explicit stack for DFS.

	The first path found in DFS is not always the shortest path, unlike BFS.
*/

//	Running time = O(n+m) = O(V+E) as summation over (v + degree(v))
//	But in a connected graph m >= n-1 hence it becomes O(m) or O(E)
//	Auxiliary space = O(n) or O(V). Since, an extra visited array is needed of size V
//	Note - However the space reqd. for adjacency matrix is O(n+m) (average cases) & O(n^2) (worst case)

#include<iostream>
#include<map>
#include<unordered_map>
#include<list>
#include<stack>
using namespace std;

class graph {
	map<int, list<int>> adjL;				//	Using an ordered map so that it stores the neighbours in a sorted manner
public:
	void addEdge(int x, int y) {            //  It implies it is an undirected graph
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
	void DFS(int src) {                     //  Both DFS iterative and recursive are the same except for the order in which the neighbours are being traversed
		map<int, int> visited;				//	Another (uno/ord as both works) map to check whether a node/vertex was already visited
		stack<int> S;						//	Could have used an array too since the value of node is an integer
		S.push(src);						//	BFS uses a Sueue while DFS uses a stack or recursion
		visited[src] = 1;
		while(!S.empty()) {
			int curr = S.top();
			S.pop();
			cout<<curr<<" ";
			for (auto i : adjL[curr]) {
				if(!visited[i]) {
					S.push(i);
					visited[i] = 1;
				}
			}
		}
		cout<<"\n";
	}
	void DFS1b(int src);                    //  Method declared but defined later

	void recursiveDFS(int src, unordered_map<int, int> &visitedDFS) {            //
		cout<<src<<" ";
		visitedDFS[src] = 1;
		for(auto v : adjL[src]) {
			if(visitedDFS[v]==0) recursiveDFS(v, visitedDFS);
		}
	}

	void DFS2(int src) {                    //  DFS2 calls the recursiveDFS after declaring visitedDFS, can be done without it too
        unordered_map<int, int> visitedDFS; //  visitedDFS needs to be initialized as 0 for all vertex but by default it is initialized as such
        recursiveDFS(src, visitedDFS);
	}

};

void graph::DFS1b(int src) {
		map<int, int> visited;
		stack<int> S;
		S.push(src);
		visited[src] = 1;
		while(!S.empty()) {
			int curr = S.top();
			S.pop();
			cout<<curr<<" ";
			for (list<int>::iterator it = adjL[curr].begin(); it!=adjL[curr].end(); it++) {
				if(!visited[*it]) {
					S.push(*it);
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
	int src = 2;
	cout<<"Iterative DFS traversal with src = "<<src<<"\n";
	G.DFS(src);
	cout<<"Iterative DFS traversal (without using auto) with src = "<<src<<"\n";
	G.DFS1b(src);
	cout<<"Recursive DFS traversal with src = "<<src<<"\n";
	G.DFS2(src);
	cout<<"\n";
	return 0;
}
