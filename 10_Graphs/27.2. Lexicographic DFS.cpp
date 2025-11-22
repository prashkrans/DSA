/* Graph problem - 30.2. Print the lexicographically smallest DFS of the graph starting from 1.
Given a connected graph with N vertices and M edges. The task is to print the lexicographically smallest
DFS traversal of the graph starting any given vertex.
This problem could be solved using two methods:
1.  Using a list to store the adjacent nodes and sorting it later
2.  Using a set instead of a list to insert the adjacent nodes in a sorted order
*/

#include<iostream>
#include<map>
#include<unordered_map>
#include<set>
#include<queue>
#include<list>
using namespace std;

//  Method 1.   Using a list to store the adjacent nodes and sorting it later
//	Running time = O(DFS+Sorting) = O((n+m)+nmlog2(m)) ~ O(nmlog2(m)) or O(VElog2(E))
//	Auxiliary space = O(n) due to the visited array

template<typename T>
class graphUsingList {
	map<T, list<T>> adjL;
public:
	void addEdge(T u, T v) {
		adjL[u].push_back(v);
		adjL[v].push_back(u);
	}
	void printAdjL() {
		typename map<T, list<T>>:: iterator it;
		for(it = adjL.begin(); it!=adjL.end(); it++) {
			T u = it->first;
			cout<<u<<" -> ";
			typename list<T>::iterator jt;
			for(jt = it->second.begin(); jt!=it->second.end(); jt++) cout<<*jt<<" ";
			cout<<"\n";
		}
	}
	void DFS(T src, unordered_map<T, int> &visited) {
		visited[src] = 1;
		cout<<src<<" ";
		for(auto v : adjL[src]) if(!visited[v]) DFS(v, visited);
	}
	void lexDFS() {
	    auto sortGraph = [](auto &adjL) {   					//  Using a lambda function
			for(auto it = adjL.begin(); it!=adjL.end(); it++)   //  Running time = O(deg(v)*log2(deg(v)))
				(it->second).sort();							//	Using the inbuilt sort() function for a list, where it->second is the current list
		};                                                      //  Total running time for sorting = O(nmlog2(m))
		sortGraph(adjL);
		unordered_map<T, int> visited;
		T src = (adjL.begin()->first);
		DFS(src, visited);                                      //  Running time = O(DFS) = O(n+m)
	}
	void usualDFS() {
        unordered_map<T, int> visited;
        T src = (adjL.begin()->first);
        DFS(src, visited);
	}
};

//  Method 2.   Using a set instead of a list to insert the adjacent nodes in a sorted order
//	Running time = O(DFS+Insert n times) = O((n+m)+nlog2(n)) ~ O(m) or O(m) as m <= n^2
//	[#IMP] - Insert n time = log2(1) + log2(2) + log2(3) + ... log2(n) = log(n!) => Using Sterling's approximation we get log2(n!) ~ nlog2(n)
//	Auxiliary space = O(n) due to the visited array

template <typename T>
class graphUsingSet {
    map<T, set<T>> adjL;
public:
    void addEdge(T u, T v) {
		adjL[u].insert(v);  //  Use .insert() instead of .push_back()
		adjL[v].insert(u);	//	Each insert operation here takes log2(x) time where x is the number of current nodes in the adjL
	}
	void printAdjL() {
		typename map<T, set<T>>:: iterator it;
		for(it = adjL.begin(); it!=adjL.end(); it++) {
			T u = it->first;
			cout<<u<<" -> ";
			typename set<T>::iterator jt;
			for(jt = it->second.begin(); jt!=it->second.end(); jt++) cout<<*jt<<" ";
			cout<<"\n";
		}
	}
	void DFSutil() {
        unordered_map<T, int> visited;
        T src = (adjL.begin()->first);
        DFS(src, visited);
	}
	void DFS(T src, unordered_map<T, int> &visited) {
		visited[src] = 1;
		cout<<src<<" ";
		for(auto v : adjL[src]) if(!visited[v]) DFS(v, visited);
	}
};

int main() {
	graphUsingList<char> G;
	G.addEdge('e', 'a');	G.addEdge('b', 'e');
	G.addEdge('b', 'c');	G.addEdge('a', 'b');
	G.addEdge('b', 'd');	G.addEdge('c', 'd');
	cout<<"Printing the adjacency list representation of the graph 1:\n";
	G.printAdjL();
	cout<<"Using Method 1:\n";
	cout<<"Printing the usualDFS:\n";
	G.usualDFS();
	cout<<"\nPrinting the lexDFS by sorting the adjacency list representation:\n";
	G.lexDFS();
	graphUsingSet<int> G2;
	G2.addEdge(2, 4);   G2.addEdge(3, 1);
	G2.addEdge(2, 5);   G2.addEdge(4, 2);
	G2.addEdge(1, 5);
	cout<<"Printing the adjacency list representation of the graph 2:\n";
	G2.printAdjL();
	cout<<"Using Method 2:";
	cout<<"\nPrinting the lexDFS by using a set to store adjacent nodes:\n";
	G2.DFSutil();
	return 0;
}



