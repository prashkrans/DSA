#include<iostream>
#include<map>       //  Note: Avoid using an unordered_map in adjacency list representation
#include<list>
#include<set>       //  For a sorted order of the adjacent nodes in the adjacency list representation
#include<utility>	//	Optional
using namespace std;

class graph {
	map<string, list<pair<string, int>>> adjL;
public:
	void addEdge(string v, string w, int weight, bool bidir) {
		adjL[v].push_back(make_pair(w, weight));
		if(bidir) adjL[w].push_back(make_pair(v, weight));
		if(adjL.count(w)==0) adjL[w];           //  This adds an empty list<pair> to a node from which there is no path. Here, Ranchi.
	}
	void printAdjL() {
		for(auto i : adjL) {
			cout<<i.first<<" -> ";
			for(auto j : i.second)
				cout<<"("<<j.first<<", "<<j.second<<") ";
			cout<<"\n";
		}
	}
};

template <typename T>
class sortedGraph {
	map<T, set<pair<T, int>>> adjL;         //  map sorts the order of the first element and set sorts the order of the second element
public:
	void addEdge(T u, T v, int wt) {
		//adjL[u].push_back({v, wt});       //  .push_back() will not work here as instead of a list, a set is used to store the adjacent nodes
		adjL[u].insert({v, wt});            //  There is no need to use a multiset instead of a set, as duplicate nodes do not exist
		if(adjL.find(v)==adjL.end()) adjL[v];
	}
	void printAdjL() {
		for(auto i : adjL) {
			T u = i.first;
			cout<<u<<" -> ";
			for(auto j : adjL[u]) {
				T v = j.first;
				int wt = j.second;
				cout<<"("<<v<<", "<<wt<<"), ";
			}
			cout<<"\n";
		}
	}
};

template <typename T>
class unSortedGraph {
	map<T, list<pair<T, int>>> adjL;         //  map sorts the order of the first element and set sorts the order of the second element
public:
	void addEdge(T u, T v, int wt) {
		adjL[u].push_back({v, wt});
		if(adjL.find(v)==adjL.end()) adjL[v];
	}
	void printAdjL() {
		for(auto i : adjL) {
			T u = i.first;
			cout<<u<<" -> ";
			for(auto j : adjL[u]) {
				T v = j.first;
				int wt = j.second;
				cout<<"("<<v<<", "<<wt<<"), ";
			}
			cout<<"\n";
		}
	}
};


int main() {
	graph G;
	G.addEdge("Mumbai", "Bangalore", 100, true);
	G.addEdge("Bangalore", "Delhi", 150, true);
	G.addEdge("Delhi", "Ranchi", 90, false);    //  Note - There is no path from Ranchi to any other city here
	G.addEdge("Kota", "Mumbai", 120, false);
    cout<<"Printing the graph G:\n";
	G.printAdjL();
	sortedGraph<char> sG;
	sG.addEdge('b', 'd', 6); 	sG.addEdge('c', 'e', 2);
	sG.addEdge('e', 'b', 3); 	sG.addEdge('e', 'a', 1);
	sG.addEdge('a', 'd', 4); 	sG.addEdge('a', 'c', 2);
	sG.addEdge('a', 'b', 5); 	sG.addEdge('b', 'c', 1);
	cout<<"Showing the difference between a sorted graph and an unSortedGraph:\n";
	cout<<"Printing the sortedGraph sG:\n";
	sG.printAdjL();
	unSortedGraph<char> nSG;
	nSG.addEdge('b', 'd', 6); 	nSG.addEdge('c', 'e', 2);
	nSG.addEdge('e', 'b', 3); 	nSG.addEdge('e', 'a', 1);
	nSG.addEdge('a', 'd', 4); 	nSG.addEdge('a', 'c', 2);
	nSG.addEdge('a', 'b', 5); 	nSG.addEdge('b', 'c', 1);
	cout<<"Printing the unSortedGraph sG:\n";
	nSG.printAdjL();
	return 0;
}
