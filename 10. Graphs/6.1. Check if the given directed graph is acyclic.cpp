/*	Graph Problem #9. - Is the given directed graph acyclic?
	Given a directed graph, check whether the graph contains a cycle or not.
	The function should return true if the given graph contains at least one cycle, else return false.
*/

//	Method 1 - Using DFS and a recursion stack represented with a stack
//	Running time = O(n*(n+m)) or O(nm) or O(VE) and not O(n+m) due to the O(n) search in the stack for each neighbour of the curr node
//	But in a connected graph m >= n-1 hence it becomes O(nm) or O(VE). Here R.T. is quadratic hence not efficient
//	Auxiliary space = O(n) or O(V) i.e. the size of the visited array and the recursion stack
/*
#include<iostream>
#include<map>
#include<unordered_map>
#include<list>
#include<stack>
using namespace std;

template<typename T>
class graph {
	map<T, list<T>> adjL;
	unordered_map<T, bool> visited;
public:
	void addEdge(T u, T v) {
		adjL[u].push_back(v);	//	No need of adjL[v].push_back(v) as it is a directed graph
	}
	void printAdjL() {
		typename map<T, list<T>>::iterator it;
		for(it = adjL.begin(); it!=adjL.end(); it++) {
			cout<<it->first<<" -> ";
			typename list<T>::iterator it2;
			for(it2 = it->second.begin(); it2!=it->second.end(); it2++) cout<<(*it2)<<", ";
			cout<<"\n";
		}
	}
	bool hasCycleDHelper(T v, stack<T> S) {
		S.push(v);
		visited[v] = 1;
		for(auto u : adjL[v]) {
			if(!visited[u]) {
				if(hasCycleDHelper(u, S)) return 1;
			}
			else {
				stack<T> copyS = S;         //  We cannot traverse in a stack without popping hence using a copy stack
				while(!copyS.empty()) {     //  Thus our original stack remains unchanged
					if(u==copyS.top()) return 1;
					copyS.pop();
				}
			}
		}
		S.pop();    //  #IMP - Remove the vertex v which is automatically at the top since DFS(v) is completed
		return 0;
	}
	bool hasCycleD(){
		visited.clear();
		stack<T> S;
		bool ans = 0;
		for(auto v : adjL) {
			if(!visited[v.first]) {
				ans = hasCycleDHelper(v.first, S);	// 	no need to send visited and adjL as they are already data members here
			}
			if(ans==1) break;
		}
		return ans;
	}
};

int main() {
	graph<string> G;
	G.addEdge("AA", "AB");	    G.addEdge("AB", "BB");
	G.addEdge("AB", "BC");	    G.addEdge("BB", "CC");
	//G.addEdge("CC", "AB");      //  makes the graph cyclic
	G.printAdjL();
	if(G.hasCycleD()) cout<<"The given directed graph has a cycle\n";
	else cout<<"The given directed graph does not have a cycle\n";
	return 0;
}
*/
//	Method 1b - Using DFS and an explicit stack represented with a vector<bool> or a map<T, bool>
//	Running time = O(n+m) or O(V+E) as the search operation is O(1) instead of O(n) in the stack (now rep. as a vector/map)
//	But in a connected graph m >= n-1 hence it becomes O(m) or O(E)
//	Auxiliary space = O(n) or O(V) i.e. the size of the visited array and the recursion stack

#include<iostream>
#include<map>
#include<unordered_map>
#include<list>
#include<stack>
using namespace std;

template<typename T>
class graph {
	map<T, list<T>> adjL;
	unordered_map<T, bool> visited;
public:
	void addEdge(T u, T v) {
		adjL[u].push_back(v);	//	No need of adjL[v].push_back(v) as it is a directed graph
	}
	void printAdjL() {
		typename map<T, list<T>>::iterator it;
		for(it = adjL.begin(); it!=adjL.end(); it++) {
			cout<<it->first<<" -> ";
			typename list<T>::iterator it2;
			for(it2 = it->second.begin(); it2!=it->second.end(); it2++) cout<<(*it2)<<", ";
			cout<<"\n";
		}
	}
	bool hasCycleDHelper(T u, map<T, bool> recStack) {
		recStack[u] = 1;
		visited[u] = 1;
		for(auto v : adjL[u]) {
			if(!visited[v]) {
				if(hasCycleDHelper(v, recStack)) return 1;
			}
			else {                              //  else if u is already visited check if it is present in the recursion stack
				if(recStack[v]==1) return 1;    //  if it is present in the recStack then a back edge exists thus a cycle exist
			}
		}
		recStack[u] = 0;    //  #IMP - Remove the vertex u from the recursion stack which is automatically at the top since DFS(v) is completed
		return 0;           //  If the flow reaches here return false as a cycle has not been found
	}
	bool hasCycleD(){
		visited.clear();
		map<T, bool> recStack;
		bool ans = 0;
		for(auto v : adjL) {
			if(!visited[v.first]) {
				ans = hasCycleDHelper(v.first, recStack);	// 	no need to send visited and adjL as they are already data members here
			}
			if(ans==1) break;
		}
		return ans;
	}
};

int main() {
	graph<string> G;
	G.addEdge("AA", "AB");	    G.addEdge("AB", "BB");
	G.addEdge("AB", "BC");	    G.addEdge("BB", "CC");
	//G.addEdge("CC", "AB");      //  makes the graph cyclic
	G.printAdjL();
	if(G.hasCycleD()) cout<<"The given directed graph has a cycle\n";
	else cout<<"The given directed graph does not have a cycle\n";
	return 0;
}



