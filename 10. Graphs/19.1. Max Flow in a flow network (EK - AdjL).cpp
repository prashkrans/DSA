/* Graph problem #22.1. Max flow in a flow network [Verified]
Given a flow network G = (V, E), find the maximum flow.
Note - a flow network G is a directed graph with flow and capacity for each edges
instead of weight/length.
Also, here adjacency list is used but it is easier to be implemented in adjacency matrix representation
Given,
a. 	if e(u, v) exists in G then e(v, u) does not exist
b.	there is a single source s and a single sink t
c. 	the edges have a non-negative capacity

It can be solved by using various methods
1.	Ford - Fulkerson method - R.T. = O(fmax*E) or O(fmax*m)
	a. Using DFS to find the augmenting paths
	b. Using BFS to find the augmenting paths which is known as Edmonds Karp algorithm - R.T. = O(V*E^2)
2.	Dinic's algorithm - R.T. = O(V^2*E)
3.	Push Relabel methods - R.T. = O(V^2*E)
*/

//	Method 1 - Edmonds Karp algorithm to find the max flow in a given flow network
//	Ford - Fulkerson method:
//	Steps:
//	1. 	initialize the flow value f in all the edges to 0
//	2.	create a residual graph of the given directed graph G
//	3.	while an augmenting path p exists from s to t in the residual graph (using BFS here)
//		a.	augment the flow of the edges included in p by cp = min(cf of all (u, v) in p)
//		b. 	update the residual network graph
//	4.	if no augmenting exists in the residual graph G return the flow obtained from the above steps as
//		is the max flow
//	Note - Edmonds Karp is a Ford-Fulkerson method where BFS is used to find the augmenting paths.
//	Running time = O(V*E^2) or O(nm^2)
//	Auxiliary space = O(n+m) ~ O(m)

#include<iostream>
#include<map>
#include<list>
#include<vector>
#include<queue>
#include<stack>
using namespace std;

template <typename T>				//	this can be discarded if we are using a map using two pairs
struct adjNode {					//	e.g. map<pair<T, T>, pair<int, int>> adjList
    T v;
    int f;
    int c;
    adjNode<T>(T v, int f, int c) : v(v), f(f), c(c) {}
};

template <typename T>
class graph {
	map<T, list<adjNode<T>>> adjList;
public:
    map<T, list<adjNode<T>>> returnAdjList() {
        return adjList;
    }
	void addEdge(T u, T v, int c) {  //  f is 0 as the initial condition
		adjNode<T> a(v, 0, c);
		adjList[u].push_back(a);
		if(adjList.count(v)==0) adjList[v];
	}
	void printAdjList(map<T, list<adjNode<T>>> adjL) {
		for(auto i : adjL) {
			T u = i.first;
			cout<<u<<" -> ";
			for(auto j : adjL[u]) {
				T v = j.v;
				int f = j.f;
				int c = j.c;
				cout<<"("<<v<<", "<<f<<", "<<c<<"), ";
			}
			cout<<"\n";
		}
	}
	map<T, list<adjNode<T>>> createResidual() {				//	this functions helps in creating a residual graph after each iteration
		map<T, list<adjNode<T>>> residualAdjL;
		for(auto i : adjList) {
			T u = i.first;
			for(auto j : adjList[u]) {
				T v = j.v;
				int f = j.f;
				int c = j.c;
				int cf = c - f;
				if(cf>0) {
                    adjNode<T> a(v, cf, -1);
                    residualAdjL[u].push_back(a);
				}
				if(f>0) {
                    adjNode<T> a(u, f, -1);
                    residualAdjL[v].push_back(a);
				}
			}
		}
		return residualAdjL;
	}
	bool ekBFS(T s, T t, map<T, int> &visited, map<T, T> &parent, map<T, list<adjNode<T>>> residualAdjL) {
		queue<T> Q;             //  It is just a simple BFS on the residual graph with a parent array
		Q.push(s);
		visited[s] = 1;
		parent[s] = s;
		bool found = 0;
		while(!Q.empty()) {
			T u = Q.front();
			Q.pop();
			for(auto j : residualAdjL[u]) {
				T v = j.v;
				if(!visited[v]) {
					Q.push(v);
					visited[v] = 1;
					parent[v] = u;
				}
				if(v==t) return true;   //  => that there exists a path from s to v in the residual graph
			}
		}
		return false;                   //  => that there does not exist a path from s to v in the residual graph
	}
	int maxFlowEdmondsKarpAlgo(T s, T t) {
		map<T, list<adjNode<T>>> residualAdjL = createResidual();
		map<T, T> parent;
		map<T, int> visited;
		stack<pair<pair<T, T>, int>> augPath;               //  IMP - augPath is a stack that stores the path from s to t in the residual graph
		int fMax = 0;
		while(ekBFS(s, t, visited, parent, residualAdjL)) { //  While BFS is true i.e. while an augmenting path exists in the residual graph
            T v = t;
            T u = parent[v];
            int cp = INT_MAX;
            while(u!=v) {									//  This adds the path from s to v in a reverse order which is irrelevant here
                int cf;
                for(auto i : residualAdjL[u]) {
                    if(i.v==v) {
                        cf = i.f;
                        break;
                    }
                }
                augPath.push({{u, v}, cf});
                if(cf<cp) cp = cf;      					//  cp = minimum cf of all (u, v) in the augmenting path p
                v = u;
                u = parent[v];
            }
            cout<<"The residual capacity of the current augmenting path p = "<<cp<<"\n";
            fMax += cp;
			cout<<"Augmenting path p = ";
			while(!augPath.empty()) {
				T u = augPath.top().first.first;
				T v = augPath.top().first.second;
				int cf = augPath.top().second;
				augPath.pop();
				cout<<"(("<<u<<", "<<v<<"), "<<cf<<"), ";
				bool found = 0;								// 	if an edge(u, v) is on the augmenting path as well as on the graph G => its flow should be increased
				typename list<adjNode<T>>::iterator it;     //  Use iterators instead of auto here
				for(it = adjList[u].begin(); it!=adjList[u].end(); it++) {
					if(it->v==v) {
                        it->f = it->f + cp;
                        found = 1;
                        break;
					}
				}
				if(found==0) {
					for(it = adjList[v].begin(); it!=adjList[v].end(); it++) {
						if(it->v==u) it->f = it->f - cp;
					}
				}
				/*for(auto i : adjList[u]) {                //  auto keyword does not update the values here
                    if(i.v == v) i.f = i.f + cp;            //  figure out the reason
                    found == 1;
                    break;
                }
                if(found==0) {
                    for(auto j : adjList[v]) {
                        if(j.v == u) j.f = j.f - cp;
                    }
                }*/
            }
			cout<<"\n";
			cout<<"Augmented graph: \n";
            printAdjList(adjList);
			residualAdjL = createResidual();
			cout<<"Residual graph: \n";
			printAdjList(residualAdjL);
			visited.clear();
			parent.clear();
			//  augPath is already empty
		}
		cout<<"The max flow in the given flow network = ";
		return fMax;
	}
};

int main() {
	/*graph<string> G;
	G.addEdge("s", "v1", 10);	G.addEdge("s", "v2", 8);
	G.addEdge("v1", "v2", 2);	G.addEdge("v1", "t", 7);
	G.addEdge("v2", "t", 6);
	G.printAdjList(G.returnAdjList());
	cout<<G.maxFlowEdmondsKarpAlgo("s", "t")<<"\n"; //*/
	graph<string> G2;   //  CLRS Figure 26.6
	G2.addEdge("s", "v1", 16);   G2.addEdge("s", "v2", 13);
	G2.addEdge("v1", "v3", 12);  G2.addEdge("v2", "v1", 4);
	G2.addEdge("v2", "v4", 14);  G2.addEdge("v4", "v3", 7);
	G2.addEdge("v3", "v2", 9);   G2.addEdge("v3", "t", 20);
	G2.addEdge("v4", "t", 4);
	cout<<"The given network flow is: \n";
    G2.printAdjList(G2.returnAdjList());
	cout<<G2.maxFlowEdmondsKarpAlgo("s", "t")<<"\n";
	/*graph<int> G3;
	G3.addEdge(1, 3, 5);    G3.addEdge(1, 2, 4);
	G3.addEdge(2, 3, 7);    G3.addEdge(3, 4, 1);
	cout<<"The given network flow is: \n";
    G3.printAdjList(G3.returnAdjList());
	cout<<G3.maxFlowEdmondsKarpAlgo(1, 5)<<"\n";*/
	return 0;
}

//	Method 1 - Here the given adjacency list is not represented as u -> (v, f, c) but as u -> (v, c)
//	So, we just have to create another ajdacency list to store the flow as the given adjacency list
//	already stores the capacities of the edges
/*
#include<iostream>
#include<map>
#include<list>
#include<vector>
#include<queue>
using namespace std;

template <typename T>
class graph {
	map<T, list<pair<T, int>>> adjL;
public:
    map<T, list<pair<T, int>>> returnAdjL() {
        return adjL;
    }
	void addEdge(T u, T v, int c) {
		adjL[u].push_back({v, c});
		if(adjL.count(v)==0) adjL[v];
	}
	void printAdjL(map<T, list<pair<T, int>>> adjList) {
		for(auto i : adjList) {
			T u = i.first;
			cout<<u<<" -> ";
			for(auto j : adjList[u]) {
				T v = j.first;
				int c = j.second;
				cout<<"("<<v<<", "<<c<<"), ";
			}
			cout<<"\n";
		}
	}
	map<T, list<pair<T, int>>> createResidual(map<T, list<pair<T, int>>> augAdjL) {
		map<T, list<pair<T, int>>> residualAdjL;
		for(auto i : augAdjL) {
			T u = i.first;
			for(auto j : augAdjL[u]) {
				T v = j.first;
				int f = j.second;
				int c;
				for(auto k : adjL[u]) if(k.first==v) c = k.second;
				int cf = c - f;
				if(cf>0) residualAdjL[u].push_back({v, cf});
			}
		}
		for(auto i : augAdjL) {
			T u = i.first;
			for(auto j : augAdjL[u]) {
				T v = j.first;
				int f = j.second;
				if(f>0) residualAdjL[v].push_back({u, f});
			}
		}
		return residualAdjL;
	}

	bool ekBFS(T s, T t, map<T, int> &visited, map<T, T> &parent, map<T, list<pair<T,int>>> residualAdjL) {
		queue<T> Q;
		Q.push(s);
		visited[s] = 1;
		parent[s] = s;
		int cp = INT_MAX;
		bool found = 0;
		while(!Q.empty()) {
			T u = Q.front();
			Q.pop();
			for(auto j : residualAdjL[u]) {
				T v = j.first;
				int cf = j.second;
				if(!visited[v]) {
					Q.push(v);
					visited[v] = 1;
					parent[v] = u;
				}
				if(v==t) return true;
			}
		}
		return false;
	}
	int maxFlowEdmondsKarpAlgo(T s, T t) {
		map<T, list<pair<T,int>>> residualAdjL = adjL;  //  the residual graph = capacity graph as flow is 0 in the beginning
		map<T, list<pair<T,int>>> augAdjL;
		for(auto i : adjL) {
            T u = i.first;
            for(auto j : adjL[u]) {
                T v = j.first;
                augAdjL[u].push_back({v, 0});
            }
		}
		map<T, T> parent;
		map<T, int> visited;
		map<pair<T, T>, int> augPath;
		while(ekBFS(s, t, visited, parent, residualAdjL)) {
            T v = t;
            T u = parent[v];
            int cp = INT_MAX;
            while(u!=v) {
                int cf;
                for(auto i : residualAdjL[u]) {
                    if(i.first==v) {
                        cf = i.second;
                        break;
                    }
                }
                augPath[{u, v}] = cf;
                if(cf<cp) cp = cf;
                v = u;
                u = parent[v];
            }
            cout<<"The residual capacity of the current augmenting path p = "<<cp<<"\n";
			cout<<"Augmenting path p = ";
			for(auto e : augPath) {
				T u = e.first.first;
				T v = e.first.second;
				cout<<"("<<u<<", "<<v<<"), ";
				bool found = 0;
				typename list<pair<T, int>>::iterator it;
				for(it = augAdjL[u].begin(); it!=augAdjL[u].end(); it++) {
					if(it->first==v) {
                        it->second = it->second + cp;
                        found = 1;
                        break;
					}
				}
				if(found==0) {
					for(it = augAdjL[v].begin(); it!=augAdjL[v].end(); it++) {
						if(it->first==u) it->second = it->second - cp;
					}
				}
			}
			cout<<"\n";
			cout<<"Augmented graph = \n";
            printAdjL(augAdjL);
			residualAdjL = createResidual(augAdjL);
			cout<<"Residual graph = \n";
			printAdjL(residualAdjL);
			visited.clear();
			parent.clear();
			augPath.clear();
		}
		int fMax = 0;
		for(auto i : augAdjL[s]) {
			T v = i.first;
			int f = i.second;
			fMax += f;
		}
		cout<<"The max flow in the given flow network = ";
		return fMax;
	}
};

int main() {
	/*graph<string> G;
	G.addEdge("s", "v1", 10);	G.addEdge("s", "v2", 8);
	G.addEdge("v1", "v2", 2);	G.addEdge("v1", "t", 7);
	G.addEdge("v2", "t", 6);
	G.printAdjL(G.returnAdjL());
	cout<<G.maxFlowEdmondsKarpAlgo("s", "t")<<"\n"; //
	graph<string> G2;
	G2.addEdge("s", "v1", 16);   G2.addEdge("s", "v2", 13);
	G2.addEdge("v1", "v3", 12);  G2.addEdge("v2", "v1", 4);
	G2.addEdge("v2", "v4", 14);  G2.addEdge("v4", "v3", 7);
	G2.addEdge("v3", "v2", 9);   G2.addEdge("v3", "t", 20);
	G2.addEdge("v4", "t", 4);
    G2.printAdjL(G2.returnAdjL());
	cout<<G2.maxFlowEdmondsKarpAlgo("s", "t")<<"\n";
	return 0;
}
*/
