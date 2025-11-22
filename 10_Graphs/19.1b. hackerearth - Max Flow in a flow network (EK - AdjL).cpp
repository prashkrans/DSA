/* Graph problem #22.1. Max flow in a flow network [Verified]
Given a directed flow network where each edge has a capacity of flow it could allow, find the maximum flow over the network from source(S) to sink(T).
Network will follow these rules:
1.  Only one source(S) and only one sink(T).
2.  Other than source and sink, nodes are represented with alphabets .
3.  There are no self loops.
4.  There will be no initial dead ends other than T.
5.  For any pair of nodes, direction of edges between them will be in single direction.
hackerearth - https://www.hackerearth.com/practice/algorithms/graphs/maximum-flow/practice-problems/algorithm/find-the-flow/
*/
//	Method 1 - Edmonds Karp algorithm to find the max flow in a given flow network
//	Running time = O(V*E^2) or O(nm^2)
//	Auxiliary space = O(n+m) ~ O(m)

#include<bits/stdc++.h>
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
				if(v==t) return true;   //  that there exists a path from s to v in the residual graph
			}
		}
		return false;                   //  that there does not exist a path from s to v in the residual graph
	}
	int maxFlowEdmondsKarpAlgo(T s, T t) {
		map<T, list<adjNode<T>>> residualAdjL = createResidual();
		map<T, T> parent;
		map<T, int> visited;
		map<pair<T, T>, int> augPath;   //  Note - Here, augPath is not a stack, which may give an incorrect order while printing the augmenting path
		int fMax = 0;                   //  but since augmenting path order is irrelevant here this is allowed here
		while(ekBFS(s, t, visited, parent, residualAdjL)) { //  while BFS is true i.e. while an augmenting path exists in the residual graph
            T v = t;
            T u = parent[v];
            int cp = INT_MAX;
            while(u!=v) {									// this adds the path from s to v in a reverse order which is irrelevant here
                int cf;
                for(auto i : residualAdjL[u]) {
                    if(i.v==v) {
                        cf = i.f;
                        break;
                    }
                }
                augPath[{u, v}] = cf;
                if(cf<cp) cp = cf;      					//  cp = minimum cf of all (u, v) in the augmenting path p
                v = u;
                u = parent[v];
            }
            //cout<<"The residual capacity of the current augmenting path p = "<<cp<<"\n";
            fMax += cp;
			//cout<<"Augmenting path p = ";
			for(auto e : augPath) {
				T u = e.first.first;
				T v = e.first.second;
				//cout<<"("<<u<<", "<<v<<"), ";
				bool found = 0;								// 	if an edge(u, v) is on the augemeting path as well as on the graph G => its flow should be increased
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
			//cout<<"\n";
			//cout<<"Augmented graph: \n";
            //printAdjList(adjList);
			residualAdjL = createResidual();
			//cout<<"Residual graph: \n";
			//printAdjList(residualAdjL);
			visited.clear();
			parent.clear();
			augPath.clear();
		}
		//cout<<"The max flow in the given flow network = ";
		return fMax;
	}
};

int main() {
	graph<char> G;
	int m;
	cin>>m;
	for(int i=0; i<m; i++) {
		char u, v;
		int c;
		cin>>u>>v>>c;
		G.addEdge(u, v, c);
    }
    //G.printAdjList(G.returnAdjList());
    cout<<G.maxFlowEdmondsKarpAlgo('S', 'T');
	return 0;
}

/* Sample input
10
S A 8
S B 10
A B 4
A C 8
A D 5
B D 2
B C 5
C T 4
C D 3
D T 12
Output = 14
*/
