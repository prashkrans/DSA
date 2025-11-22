/* Graph problem #19b. and #20b. Find all the bridges and articulation points in the given undirected graph
hackerearth - https://www.hackerearth.com/practice/algorithms/graphs/articulation-points-and-bridges/tutorial/
*/

// 	Method 2 - Uses dbe + arr or disc + one DFS traversal
//	Running time = O(DFS) = O(n+m) ~ O(m)
//	Auxiliary space = O(n) or O(V)
//	Here, separate methods are used to find brides and aps, but the two methods can be merged easily.
//	Do it later.

#include<bits/stdc++.h>
using namespace std;

template <typename T>
class graph {
	map<T, list<T>> adjL;
public:
	graph(int n) {
		for(int i=0; i<n; i++) adjL[i];
	}
	void addEdge(T u, T v) {
		adjL[u].push_back(v);
		adjL[v].push_back(u);	//	=> G is undirected
	}
	void printAdjL() {
		for(auto i : adjL) {
			cout<<i.first<<" -> ";
			for(auto j : i.second) cout<<j<<", ";
			cout<<"\n";
		}
	}
	//	Either use lines 64 and 65 or lines 71 and 72, both are correct
	int apDFS(T u, map<T, int> &visited, map<T, T> &parent, map<T, int> &disc, map<T, int> &low, int &time, set<T> &ap, T src) {
		visited[u] = 1;
		disc[u] = time++;
		low[u] = disc[u];
		int DFSchildren = 0;
		for(auto v : adjL[u]) {
			if(!visited[v]) {
				parent[v] = u;
				DFSchildren++;
				low[u] = min(low[u], apDFS(v, visited, parent, disc, low, time, ap, src));
				//if(u!=src && low[v] >= disc[u]) ap.push_back(u);
				//else if(u==src && DFSchildren>1) ap.push_back(u); //  Special case for the source node/root
			}
			else if(parent[u]!=v) {
				low[u] = min(low[u], disc[v]);
			}
		}
		if(u!=src && low[u]>=disc[parent[u]] && parent[u]!=src) ap.insert(parent[u]);
		if(u==src && DFSchildren>1) ap.insert(u);                //  Special case for the source node/root
		return low[u];
	}
	void findArticulationPoints() {
		map<T, int> visited;
		map<T, T> parent;
		map<T, int> disc;
		map<T, int> low;
		//vector<T> ap;
		set<T> ap;
		int time = 0;
		int ccNum = 0;
		typename map<T, list<T>>:: iterator it;
		for(it = adjL.begin(); it!=adjL.end(); it++) {
			T u = it->first;
			if(!visited[u]) {
				ccNum++;
				int dbe = apDFS(u, visited, parent, disc, low, time, ap, u);
				//cout<<"The articulation points/cut-vertices for the CC#"<<ccNum<<" are: \n";
				cout<<ap.size()<<"\n";
				for(auto i : ap) cout<<i<<" ";
				cout<<"\n";
				//ap.clear();
			}
		}
	}
	int bridgeDFS(T u, map<T, int> &visited, map<T, int> &arr, map<T, T> &parent, map<pair<T, T>, int> &bridges, int &time, T src) {
		visited[u] = 1 ;
		arr[u] = time++;
		int dbe = arr[u];                   //  dbe initialized for the current vertex u
		for(auto v : adjL[u]) {
			if(!visited[v]) {
				parent[v] = u;              //  this records that the edge(u, v) is a tree edge
				dbe = min(dbe, bridgeDFS(v, visited, arr, parent, bridges, time, src));
			}
			else {
                if(parent[u]!=v) {			//	=> edges e(u, v) that are only back edges are considered here
					dbe = min(dbe, arr[v]);	// 	because if (parent[u] == v) => e(u, v) is a tree edge
                }
			}
		}
		if(u!=src && dbe>=arr[u]) {         //  Note - dbe cannot be greater than arr[u], it can only be less than or equal to arr[u]
            bridges[{parent[u], u}] = 1;  //  if dbe is < arr[u] => edge(p[u], u) is not a bridge
            //edge<T> e(parent[u], u);        //  if dbe is == arr[u] => edge(p[u], u) is a bridge
            //bridges.push_back(e);           //  so, add this edge to bridges
		}
		return dbe;                         //  this is really important as it returns dbe of a child to its parent
	}
	void findBridges() {
		map<T, int> visited;
		int time = 0;
		map<T, int> arr;
		map<T, T> parent;           //  parent array/map is used for a. checking if an edge is a back edge & b. printing the bridges as an edge from parent[u] to u.
		map<pair<T, T>, int> bridges;
		//vector<edge<T>> bridges;    //  this simply stores the bridge edges
		typename map<T, list<T>>:: iterator it;
		int ccNum = 0;              //  if G is disconnected, ccNum labels different connected components
		for(it = adjL.begin(); it!=adjL.end(); it++) {
			T u = it->first;
			if(!visited[u]) {
				ccNum++;
				int dbe = bridgeDFS(u, visited, arr, parent, bridges, time, u); //  this fills the bridges vector/map with all the bridge edges in the current CC
				//cout<<"The bridges in CC#"<<ccNum<<" are: \n";
				cout<<bridges.size()<<"\n";
				for(auto j : bridges) {
					T u = j.first.first;
					T v = j.first.second;
					if(u<=v) cout<<u<<" "<<v<<"\n";
					else cout<<v<<" "<<u<<"\n";
					//cout<<"edge("<<j.first.first<<", "<<j.first.second<<")\n";  //  j.f.f and j.f.s as it is map of pairs
                    //for(auto j : bridges) cout<<"edge("<<j.u<<", "<<j.v<<")\n";
				}
				bridges.clear();                                                //  clearing the bridges to use it for a different CC
			}
		}
	}
};

int main() {
	int n,m;
	cin>>n>>m;
	graph<int> G(n);
	int u, v;
	for(int i=0; i<m; i++) {
		cin>>u>>v;
		G.addEdge(u, v);
	}
	//G.printAdjL();
	G.findArticulationPoints();
	G.findBridges();
	return 0;
}

/* Sample input 
6 7
0 5
0 1
1 3
3 4
4 2
2 3
2 1
*/
