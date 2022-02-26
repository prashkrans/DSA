/*	Graph Problem #12.2.1b. - Minimum Spanning Tree (MST) using modified Prim's Algorithm
Given a weighted undirected graph. Find the sum of weights of edges of a Minimum Spanning Tree.
hackerearth - https://www.hackerearth.com/practice/algorithms/graphs/minimum-spanning-tree/tutorial/
*/

//	Method 2.1 - Modiefied Prim's algorithm (Greedy Algo) - Better than Prim's Algo
//  Running time = O(mlogn) or O(ElogV)
//  Auxiliary space = O(n) or O(V)

#include<bits/stdc++.h>
using namespace std;

typedef long long int ll;

template<typename T>
class graph {
	map<T, list<pair<T, ll>>> adjList;
public:
	void addEdge(T v, T w, ll wt) {
		adjList[v].push_back(make_pair(w, wt));
		adjList[w].push_back({v, wt});
	}
	void printAdjList() {
		for(auto v : adjList) {
			cout<<v.first<<" -> ";
			for(auto w : v.second) cout<<"("<<w.first<<", "<<w.second<<"), ";
			cout<<"\n";
		}
	}
	int primsAlgoMST() {
		map<T, ll> label;
		set<pair<ll, T>> setPA;
		map<T, bool> inMstSet;
		map<T, T> parent;
		int mstCost = 0;
		for(auto v : adjList) label[v.first] = INT_MAX;
		T src = adjList.begin()->first;
		label[src] = 0; parent[src] = src;
		setPA.insert(make_pair(0, src));
		while(!setPA.empty()) {
			T v = setPA.begin()->second; int edgeWt = setPA.begin()->first;
			inMstSet[v] = 1;
			mstCost += edgeWt;
			setPA.erase(setPA.begin());
			for(auto x : adjList[v]) {
				if(!inMstSet[x.first]) {
                    T w = x.first;
                    ll wt = x.second;
                    if(wt < label[w]) {
                        typename set<pair<ll, T>>::iterator it = setPA.find({label[w], w});
                        if(it!=setPA.end()) setPA.erase(it);
                        label[w] = wt;
                        setPA.insert({label[w], w});
                        parent[w] = v;
                    }
				}
			}
		}
		return mstCost;
	}
};

int main() {
    int n, m;
    cin>>n>>m;
    graph<int> G;
    int u, v;
	ll wt;
    for(int i=0; i<m; i++) {
        cin>>u>>v>>wt;
        G.addEdge(u, v, wt);
    }
    //G.printAdjList();
    auto mstCost = G.primsAlgoMST();
    cout<<mstCost;
    return 0;
}

/* Sample input:
4 5
1 2 7
1 4 6
4 2 9
4 3 8
2 3 6
*/
