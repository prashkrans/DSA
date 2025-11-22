/*	Graph Problem #11. - All Topological Sorts of a Directed Acyclic Graph
	Given a DAG, print all topological sorts of the graph.
*/
	
//	Method 1 - Using Kahn's Algo + Recursion (Top-down approach)	
//	In a directed acyclic graph many a times we can have vertices which are unrelated to each other 
//	because of which we can order them in many ways. We can go through all possible ordering via 
//	recursion and backtracking , the algorithm steps are as follows : 
//	Steps:
//	1.	Initialize all vertices as unvisited.
//	2.	Now choose vertex v which is unvisited and has zero indegree and decrease indegree of all 
//		out adjacent vertices w of v by 1
//	3.	Now add this vertex to result and call the recursive function again and backtrack.
//	4.	After returning from function, reset values of visited, result and indegree for enumeration of other possibilities.
//	5. 	The base case of the recursion is that if the size of the result = no. of vertices, which means that all the nodes
//		have been visited in the current branch, i.e. a ts is completed then, print the current result (ts)

//	Running time = O(n!) or O(V!) i.e. factorial. Note - O(n!) > O(2^n) after n = 3;
//	Auxiliary space = O(n) or O(V). Since, the size of visited, result, indegree are all n or V

#include<iostream>
#include<map>
#include<list>
#include<vector>
using namespace std;

template<typename T>
class graph {
	int V;
	map<T, list<T>> adjList;
public:
	void addEdge(T u, T v) {
		adjList[u].push_back(v);
		if(adjList.count(v)==0) adjList[v];
		V = adjList.size();
	}
	void printAdj() {
		typename map<T, list<T>>::iterator it;
		for(it = adjList.begin(); it!=adjList.end(); it++) {
			cout<<it->first<<" -> ";
			typename list<T>::iterator itList;
			for(itList = adjList[it->first].begin(); itList!=adjList[it->first].end(); itList++) {
				cout<<*itList<<", ";
			}
			cout<<"\n";
		}
	}
	void allTopoSortRec(auto &visited, auto &indegree, auto &ts) {
		if(ts.size()==V) {                                  //  this is the base case of recursion that if the ans ts.size() == V (no. of vertices)
			for(int i=0; i<V; i++) cout<<ts[i]<<" ";        //  => all the nodes have been visited in current branch of recursion, then a ts is obtained
			cout<<"\n";                                     //  and thus printed.
		}                                                   //  we have exactly x recursion calls or branch from a state 
		for(auto v : adjList) {                             //	where x = no. of nodes which are not yet visited and have an indegree==0
			if(!visited[v.first] && indegree[v.first]==0) { //  If the curr node v is not visited and has an indegree==0,
				ts.push_back(v.first);                      //  it can be pushed into the ans ts
				visited[v.first] = 1;                       //  then marked as visited
				for(auto w : v.second) {                    //  and finally all the nodes w out adjacent to v have their indegree reduced by 1
                    indegree[w]--;
				}
				allTopoSortRec(visited, indegree, ts);      //  then the recursion is called, with v included in the ans ts
				ts.pop_back();              //  From here, everything related to the current node v is reversed as if it were never picked
				visited[v.first] = 0;       //  1. v is removed from the answer ts
				for(auto w : v.second) {    //  2. v is marked as not visited
                    indegree[w]++;          //  3. all the out adjacent nodes w of v have their indegree increased back by 1
				}                           //  Thus, the above operations revert back to a state where v was not picked
			}
		}
	}
	void allTopoSort() {
		map<T, bool> visited;
		map<T, int> indegree;
		vector<T> ts;
		for(auto v : adjList) {
			for(auto w : v.second) {
				indegree[w]++;
				//	visited[w] = 0;
			}
		}
		cout<<"All the topological sorting of the given DAG are: \n";
		allTopoSortRec(visited, indegree, ts);
	}
};

int main() {
	graph<int> G;   //  make sure that G is a DAG
	G.addEdge(4, 0);	G.addEdge(3, 1);
	G.addEdge(4, 1); 	G.addEdge(5, 0);
	G.addEdge(5, 2); 	G.addEdge(2, 3);
	/*graph<int> G2;	G2.addEdge(1, 2);    
	G2.addEdge(1, 3);	G2.addEdge(4, 2);*/
	G.printAdj();
	G.allTopoSort();
	return 0;
}
