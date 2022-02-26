/*	Graph Problem #7.2b. - Shortest path between two nodes (Dijkstra's Algo using the STL priority_queue)
Find the length of the shortest path between two nodes
a. 	Using BFS (only for an unweighted graph): O(V+E)
    This algorithm will work even when negative weight cycles are present in the unweighted graph.
b. 	Using Dijkstra's algorithm (for graphs without negative edges whether directed or undirected): O(ElogV)
c.  Bellman Ford algorithm (for graphs without negative cycles) : O(VE)
*/

//	2b.	Dijkstra's Algorithm (for weighted graphs without negative edges whether directed or undirected)
//		Refer 4.2. for steps:
//		#IMP - The problem is, STL priority_queue doesn’t support decrease key. To resolve this problem, we do not
//	    update a key, but insert one more copy of it. So we allow multiple instances of same vertex in priority queue.
//	    This approach doesn’t require decrease key operation and has below important properties.
//	    ->  Whenever distance of a vertex is reduced, we add one more instance of vertex in priority_queue. Even if there are multiple
//	        instances, we only consider the instance with minimum distance and ignore other instances.
//	    ->  The time complexity remains O(ELogV)) as there will be at most O(E) vertices in priority queue and O(Log E) is same as O(Log V)
//	    Note - The duplicates v may come out multiple times however all the w adjacent nodes to v will get the correct distance allocated to
//	    them because of the duplicate with the least distance itself

//	Running time = slightly larger than O(mlogn) = O(mlogn) or O(ElogV) as O(m) (for for loop) * O(logn) (for decreaseKey and deleteMin())
//	But since we are not using the deleteMin() function this may lead to R.T. > O(mlogn) but only slightly and can be neglected
//	Auxiliary space = O(n) or O(V). Since, the size of the set or priority queue is of O(n)
//	Note - However the space reqd. for adjacency matrix is O(n+m) (average cases) & O(n^2) (worst case)

#include<iostream>
#include<map>
#include<list>
#include<queue>
#include<stack>
#include<vector>
using namespace std;

template<typename T>
class graph {
	map<T, list<pair<T, int>>> adjL;
public:
	void addEdge(T u, T v, int weight) {
		adjL[u].push_back(make_pair(v, weight));
		//adjL[v].push_back(make_pair(u, weight));    	//  This implies an undirected graph
		if(adjL.count(v)==0) adjL[v];             		//	This implies a directed graph
	}
	void printAdjL() {
		for(auto u : adjL) {
			cout<<u.first<<" -> ";
			for(auto v : adjL[u.first]) {
				cout<<"("<<v.first<<", "<<v.second<<"), ";
			}
			cout<<"\n";
		}
	}
	vector<T> dijkstrasAlgoPQ(T s, T t) {
		priority_queue<pair<int, T>, vector<pair<int, T>>, greater<pair<int, T>> > pq;	// 	pq is a minHeap
		map<T, int> dist;
		map<T, T> parent;
		stack<T> S;
		vector<T> sssp;
		for(auto v : adjL) {
			if(v.first == s) {
				pq.push(make_pair(0, s));
				dist[s] = 0;
				parent[s] = s;
			}
			else {
				dist[v.first] = INT_MAX;
				parent[v.first] = v.first;
			}
		}
		while(!pq.empty()) {        //  When the loop begins, pq has only one value i.e. {0, s}
			T v = pq.top().second;
			pq.pop();
			for(auto x : adjL[v]) {
				T w = x.first;
				int wt = x.second;
				if(dist[v] + wt < dist[w]) {
					dist[w] = dist[v] + wt;
					pq.push({dist[w], w});  //  As we traverse, we keep on adding the vertices
					parent[w] = v;
				}
			}
		}
		cout<<"Node v	dist[v]\n";
		for(auto i : dist) cout<<i.first<<"	"<<i.second<<"\n";
		if(dist[t] == INT_MAX) {
            cout<<"There does not exist any path from "<<s<<" to "<<t<<"\n";
            return sssp;
		}
		cout<<"The distance between "<<s<<" and "<<t<<" is = "<<dist[t]<<"\n";
		T x = t;
		while(x!=s) {
			S.push(x);
			x = parent[x];
		}
		S.push(s);
		while(!S.empty()) {
			sssp.push_back(S.top());
			S.pop();
		}
		cout<<"The shortest path between "<<s<<" and "<<t<<" is: \n";
		for(int i=0; i<sssp.size(); i++) {
            cout<<sssp[i];
            if(i!=sssp.size()-1) cout<<" -> ";
        }
		return sssp;
	}
};

int main() {
	graph<int> G;
	G.addEdge(1, 2, 3);	G.addEdge(1, 3, 5);
	G.addEdge(3, 4, 5);	G.addEdge(2, 5, 4);
	G.addEdge(2, 3, 1);	G.addEdge(4, 2, 2);
	G.printAdjL();
	int src, dest;
	src = 3; dest = 5;
	//src = 5; dest = 1;    // no path exists
	vector<int> ans = G.dijkstrasAlgoPQ(src, dest);
	return 0;
}




