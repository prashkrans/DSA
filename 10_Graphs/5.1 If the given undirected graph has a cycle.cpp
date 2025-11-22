/*	Graph Problem #8.1. - Given an undirected graph, find whether it has a cycle.
    This problem could be solved using three methods
    1.  DFS + parent variable
    2.  BFS + parent array
    3.  Union-find algorithm    (Avoid using find() and union() instead use findSet() and unionOfSets())
*/
//	Method 1. DFS + Parent Variable
//	Running time = O(DFS) = O(n+m) = O(m) = O(E)
//	Auxiliary space = O(n) = O(V) to store the visited array

//#include<bits/stdc++.h>
#include<iostream>
#include<map>
#include<list>
using namespace std;

template<typename T>
class graph {
	map<T, list<T>> adjList;
	map<T, bool> visited;
public:
	void addEdge(T u, T v) {
		adjList[u].push_back(v);
		adjList[v].push_back(u);
	}
	void printAdjList() {
		for(auto i : adjList) {
			cout<<i.first<<" -> ";
			typename list<T>::iterator it;          //  It does not work as list<T>::iterator it and it needs to prefixed as typename
			for(it = i.second.begin(); it!=i.second.end(); it++) {
				cout<<(*it)<<", ";
			}
			cout<<"\n";
		}
	}                                               //  It is a recursive function i.e. DFS
	bool hasCycleHelper(T src, char parent) {       //  Two parameters reqd. 1. src node 2. parent node (parent of a src node is '0' or anything apart from any other node
        visited[src] = true;                        //  as the parent of a source node does not exist
        for(auto v : adjList[src]) {
            if(!visited[v]) {                       //  If the node v is not visited then mark it as visited and make the source node as the parent and call the func on v
                parent = src;
                if(hasCycleHelper(v, parent)==true) //  If the recursive call returns true then it means the graph has a cycle and thus return true
                    return true;                    //  We could have also used return hasCycleHelper(v, parent); but needs a different base case that all the nodes have been visited
            }
            else {                                  //  If the node v is already visited and if v is not equal to parent of current src then it is an ancestor hence a back edge exits
                if(parent != v)                     //  thus a cycle exists
                    return true;
            }
        }
        return false;                               //  If all the nodes have been visited and no true has been returned, only then the false is returned implying no cycle exists
	}

	bool hasCycle() {
		bool ans = false;
        visited.clear();
        typename map<T, list<T>>::iterator it;
		for(it = adjList.begin(); it!=adjList.end(); it++) {
			if(!visited[it->first])
				ans = hasCycleHelper(it->first, '0');
			if(ans==true) break;
		}
		return ans;
	}
};


int main() {
	graph<char> G;
	G.addEdge('A', 'B');	G.addEdge('A', 'C');
	G.addEdge('C', 'D');	G.addEdge('C', 'E');
	//G.addEdge('D', 'E');  //  makes G cyclic
	//G.addEdge('B', 'D');  //  makes G cyclic
	G.addEdge('F', 'G');    //  makes the no. of cc = 2
	G.printAdjList();
	if(G.hasCycle()) cout<<"The given undirected graph G has a cycle\n";
	else cout<<"The given undirected graph G has no cycle\n";
	return 0;
}
