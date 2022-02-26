/* Graph Problem: 10.6 Topological Sorting using DFS along with cycle check [#IMP]
Given a directed graph whether connected, or strongly connected or not connected, print its any topological sort,
after checking whether its a DAG.

This problem could be solved using two methods i.e. Kahn's Algo or using DFS and a stack.
*/

//  Method 1. DFS + 2 Stacks (1. To find out if the graph is cyclic & 2. To store the topological sort)
//  Running time = O(DFS) = O(n+m) ~ O(m)
//  Auxiliary space = O(n) due to the two stacks used here.

#include<iostream>
#include<unordered_map>
#include<map>
#include<list>
#include<stack>
#include<vector>
using namespace std;

template <typename T>
class graph {
    map<T, list<T>> adjL;  //  We are not using a list instead using an set as nodes cannot be duplicates
public:
	/*void addNode(char v) {                        //  There is no need to add nodes separately
        if(adjL.count(v)==0) adjL[v];               //  Another way to add a node is adjL[v] = list<T>(); where list<T>() is an empty list
	}*/
	void addEdge(T u, T v) {
		adjL[u].push_back(v);
		if(adjL.count(v)==0) adjL[v] = list<T>();
		//addNode(v);
	}
	void printAdjL() {
		for(auto i : adjL) {
			cout<<i.first<<" -> ";
			for(auto j : i.second) cout<<j<<", ";
			cout<<"\n";
		}
	}
	bool DFS(T u, unordered_map<T, int> &visited, stack<T> &TSstack, unordered_map<T, int> &cycleStack) {
        visited[u] = 1;
        cycleStack[u] = 1;
        for(auto v : adjL[u]) {
            if(!visited[v]) {
                if(DFS(v, visited, TSstack, cycleStack)==0) return 0;
            }
            else if(cycleStack[v]==1) return 0;     //  If a node v is already visited and is still present in the recursion stack => a cycle exists
        }
        cycleStack[u] = 0;                          //  Remove the node u from the recursion stack once DFS(u) is completed
        TSstack.push(u);                            //  Add the node u to the topological order once DFS(u) is completed
        return 1;
	}
	vector<T> topoSortDFS() {
        unordered_map<T, int> visited;
        unordered_map<T, int> cycleStack;   //  The two stacks are the important here, a. cycleStack is used to find out whether the graph is cyclic or not
        stack<T> TSstack;                   //  b.  TSstack is used to store the topological sort
        vector<T> ts;                       //  So, it uses two concepts 1. find a cycle in a directed graph and 2. get the topological sort, both using the same DFS [#IMP]
        bool isDAG;
        for(auto i : adjL) {                //  Using a for loop since the graph so obtained may not be a strongly connected graph or even a connected graph.
            T src = i.first;
            if(!visited[src]) {
				isDAG = DFS(src, visited, TSstack, cycleStack);
				if(!isDAG) break;                   //  If even a part of a graph is cyclic, we stop.
			}              //  If even a part of a graph is cyclic, we stop.
        }
        if(isDAG) {
            while(!TSstack.empty()) {
                ts.push_back(TSstack.top());
                TSstack.pop();
            }
            cout<<"The given directed graph is a DAG so, atleast one topological sort exists:\n";
            for(auto i : ts) cout<<i<<" "; cout<<"\n";
        }
        else cout<<"The given directed graph is cyclic hence, no topological sort exists.\n";
        return ts;
	}
};

int main() {
	graph<string> G;
	G.addEdge("E5", "C3");  G.addEdge("F6", "A1");
	G.addEdge("A1", "B2");  G.addEdge("A1", "C3");
	G.addEdge("A1", "D4");  G.addEdge("B2", "C3");
	G.addEdge("D4", "C3");  G.addEdge("D4", "E5");
	G.addEdge("G7", "B2");  G.addEdge("E5", "G7");
	//G.addEdge("B2", "F6");  //  makes the graph cyclic
	G.printAdjL();
	G.topoSortDFS();
	return 0;
}
