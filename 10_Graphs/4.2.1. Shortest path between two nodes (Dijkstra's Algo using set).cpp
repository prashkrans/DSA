/*	Graph Problem #7.2. - Shortest path between two nodes (Dijkstra's Algo using the STL set)
Find the length of the shortest path between two nodes
a. 	Using BFS (only for an unweighted graph): O(V+E)
    This algorithm will work even when negative weight cycles are present in the unweighted graph.
b. 	Using Dijkstra's algorithm (for graphs without negative edges whether directed or undirected): O(ElogV)
c.  Bellman Ford algorithm (for graphs without negative cycles) : O(VE)
*/

//	2. 	Dijkstra's Algorithm (for weighted graphs without negative edges whether directed or undirected)
//	Steps:
//	a.	Initialize distances of all vertices as infinite i.e. dist[v] = INT_MAX for all vertices
//	b.	Create an empty set.  Every item of set is a pair (weight, vertex). Weight (or distance) is used
//		as the first item of pair as the first item by default is used to compare two pairs.
//	c. 	Create a parent array that stores the parent of the node and initialize it as the node itself is its parent
//	d.	i. Insert source vertex into the set and make its distance as 0.
//		or ii. insert all the nodes into the set with dist = INT_MAX except for the source node which has dist = 0
//		cii. requires an extra case for while loop to break hence it is better to use the ci.
//	e. 	While Set doesn't become empty, do following:
//		i.	Extract minimum distance vertex from Set. Let the extracted vertex be v
//		ii.	Loop through all adjacent node w of v and do the following for each w
//			if(dist[v] + weight(v, w) > dist[w]) then
//				1. 	if the node w is already in the set, delete it using s.erase(s.find(make_pair(dist[w], [w])
//				2.	update distance of w as dist[w] = dist[v] + wt;
//				3. 	insert the updated distance of w as s.insert({dist[w], w});
//				4.	make v the parent of w i.e. parent[w] = v;
//	f.	The dist[dest] stores the length of the shortest distance from src to dest
//	g. 	Use a stack to store information of the path from dest to its parent and so on until source is reached
//	h.	Use a vector to store the reverse order of the path stored in the stack. Thus, it stores the shortestpath from src to dest

//	Running time = O(mlogn) = O(mlogn) or O(ElogV) as O(m) (for for loop) * O(logn) (for decreaseKey and deleteMin())
//	Auxiliary space = O(n) or O(V). Since, the size of the set or priority queue is of O(n)
//	Note - However the space reqd. for adjacency matrix is O(n+m) (average cases) & O(n^2) (worst case)

#include<iostream>
#include<map>
#include<list>
#include<set>
#include<vector>
#include<stack>
using namespace std;

template<typename T>
class graph {
	map<T, list<pair<T, int>> > adjL;
public:
	void addEdge(T u, T v, int weight) {
		adjL[u].push_back(make_pair(v, weight));		//	Two different ways to insert a pair value
		//adjL[v].push_back({u, weight});                 //  This implies it is an undirected graph
		if(adjL.find(v)==adjL.end()) adjL[v];           //  This implies it is a directed graph
	}
	void printAdjL() {
		typename map<T, list<pair<T, int>>>::iterator it;
		for(it = adjL.begin(); it!=adjL.end(); it++) {
			cout<<it->first<<" -> ";
			typename list<pair<T, int>>::iterator nbr;
			for(nbr = it->second.begin(); nbr != it->second.end(); nbr++) {
				cout<<"("<<nbr->first<<", "<<nbr->second<<"), ";
			}
			cout<<"\n";
		}
	}
	vector<T> dijkstrasAlgo(T src, T dest) {
		set<pair<int, T>> setDA;				//	It is really important to order the pair as <int, T> as the key here is the weight and not the other way round
		map<T, int> dist;
		map<T, T> parent;						//	parent, sp ans sssp are reqd. only when we need to print the shortest path
		stack<T> sp;
		vector<T> sssp;							//	Also, use of vector<T> sssp is optional
		for(auto v : adjL) {					//	Initialization
			if(v.first==src) {					//	Exception for the source node
				setDA.insert(make_pair(0, src));//  Note - enter the value as <int, T> and not <T, int>
				dist[src] = 0;
				parent[src] = src;
			}
			else {
				setDA.insert({INT_MAX, v.first});       //  If the set only contains src then line 62 is not needed as there will be no node with dist = INT_MAX
				dist[v.first] = INT_MAX;                //  else we if the set contains all the nodes in initialization then line 62 is needed
				parent[v.first] = v.first;              //  so, it is better to initialize the set with only {0, src}
			}
		}
		while(!setDA.empty()) {
            if(setDA.begin()->first==INT_MAX) break;    //  i.e. if the smallest distance == INT_MAX, then there exists no path from s to those nodes, thus break.
			T v = setDA.begin()->second;
			setDA.erase(setDA.begin());
            for(auto x : adjL[v]) {
                T w = x.first;
                int weight_vTow = x.second;
                if(dist[v] + weight_vTow < dist[w]) {
                    typename set<pair<int, T>>::iterator it = setDA.find({dist[w], w});   	//  use this to delete {dist[w], w} before updating dist[w] if the set is initialized for all the nodes
                    if(it!=setDA.end()) setDA.erase(it);
					//if(dist[w]!=INT_MAX) setDA.erase(setDA.find(make_pair(dist[w], w))); 	//	use this to delete {dist[w], w} if the set is initialized for only the src node
                    dist[w] = dist[v] + weight_vTow;
                    setDA.insert({dist[w], w});
                    parent[w] = v;
                }
            }
        }
		cout<<"Node v	dist[v]\n";
		for(auto i : dist) cout<<i.first<<"	"<<i.second<<"\n";
		if(dist[dest] == INT_MAX) {
            cout<<"There does not exist any path from "<<src<<" to "<<dest<<"\n";
            return sssp;
		}
		cout<<"The distance between "<<src<<" and "<<dest<<" is = "<<dist[dest]<<"\n";
		T x = dest;
		while(x!=src) {
			sp.push(x);
			x = parent[x];
		}
		sp.push(src);
		while(!sp.empty()) { // Basically reversing the stack push
			sssp.push_back(sp.top());
			sp.pop();
		}
		cout<<"The shortest path between "<<src<<" and "<<dest<<" is: \n";
		for(int i=0; i<sssp.size(); i++) {
            cout<<sssp[i];
            if(i!=sssp.size()-1) cout<<" -> ";
        }
        cout<<"\n";
		return sssp;
	}
};

int main() {
	graph<string> G;
	G.addEdge("A1", "B2", 1); 	G.addEdge("A1", "C3", 2);
	G.addEdge("B2", "E5", 3); 	G.addEdge("C3", "E5", 3);
	G.addEdge("B2", "D4", 1); 	G.addEdge("D4", "E5", 1);
	G.printAdjL();
	cout<<"\n";
	string src, dest;
	src = "A1"; dest = "E5";
	//src = "E5"; dest = "A1";
	vector<string> ans = G.dijkstrasAlgo(src, dest);
	return 0;
}






