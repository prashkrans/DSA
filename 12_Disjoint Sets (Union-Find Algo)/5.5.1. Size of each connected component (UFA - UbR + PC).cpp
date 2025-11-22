/* Graph Problem #8.5.1. Size of each connected component
You are given number of nodes, N, and number of edges, M, of a undirected connected graph. After adding each edge, print 
the size of all the connected components (in increasing order).

Input:
First line contains two integers, N and M, number of nodes and number of edges.
Next M lines contains two integers each, X and Y, denoting that there is an edge between X and Y.

Output:
For each edge, print the size of all the connected components (in increasing order) after adding that edge.

Constraints:
1<=N<=10^3
1<=M<=N-1 i.e. the graph is not cyclic
1<=X,Y<=N

hackerearth - https://www.hackerearth.com/practice/data-structures/disjoint-data-strutures/basics-of-disjoint-data-structures/tutorial/
*/

//	Method 1.1. Using union-find algo (Union by rank + path compression)
//	Running time = O(m*(2*Find() + Union()) = O(m*(2*1 + 1)) ~ O(m). Since, for each of the m edges we run two find() and one union() operations
//	Auxiliary space = O(n) or O(V) i.e. the max size of the summation of sizes of all the disjoint sets = no. of vertices
 
#include<bits/stdc++.h>
using namespace std;

typedef int T;

pair<T, int> findSet(T u, unordered_map<T, pair<T, int>> &subset) { //  It is a recursive function that first finds the root of the set and makes it the parent
		T parent = subset[u].first;
		int rank = subset[u].second;
		if(parent == u) return {u, rank};       //  returns the root of the set in which u was present
		else {
            pair<T, int> rootSet = findSet(parent, subset);
            subset[u].first = rootSet.first;    //  Path compression i.e. makes root the parent of all the nodes in the current path
            subset[u].second = rootSet.second;
		}
		return subset[u];	                    //  returns the root and rank after the path compression
	}
void unionOfSets(T u, T v, unordered_map<T, pair<T, int>> &subset) {
		pair<T, int> uSet = findSet(u, subset);
		pair<T, int> vSet = findSet(v, subset);
		T uRoot = uSet.first;   int uRank = uSet.second;
        T vRoot = vSet.first;   int vRank = vSet.second;
        int mergedRank = uRank + vRank;
		if(vRank <= uRank) {
            subset[vRoot] = {uRoot, mergedRank};
            subset[uRoot].second = mergedRank;
		}
		else {
            subset[uRoot] = {vRoot, mergedRank};
            subset[vRoot].second = mergedRank;
		}
}
void numOfCC(int n, auto edges) {
        unordered_map<T, pair<T, int>> subset;              //  Using a subset map to identify disjoint sets that maps a node u to its parent and the rank of the set in which u is present
		multiset<T> mSet;
        for(int i=1; i<=n; i++) subset[i] = {i, 1};    //  Initially a node is a parent of itself and the rank is 1. When parent[u] == u => u is the root of a set
		for(auto e : edges) {                               //  Note:   1. If two or more nodes have the same root => they are in the same set.
            T u = e.first;                                  //          2. Two or more nodes in the same set may have different parents but must have a common root
            T v = e.second;                                 //  Important to mark both u and v visited, so that an edge e(u, v) is only counted once
            if(findSet(u, subset)!=findSet(v, subset)) {
				unionOfSets(u, v, subset);
				for(auto i : subset) {
					if(i.first==i.second.first) mSet.insert(i.second.second);
				}
				for(auto i : mSet) cout<<i<<" "; cout<<"\n";
				mSet.clear();
			}

        }
        //cout<<"Vertices\t"; for(auto i : subset) cout<<i.first<<"\t"; cout<<"\n";
        //cout<<"Parent\t\t";     for(auto i : subset) cout<<i.second.first<<"\t"; cout<<"\n";  // No. of distinct roots denote the no. of sets = no. of connected components
		//cout<<"Rank\t\t"; for(auto i : subset) cout<<i.second.second<<"\t"; cout<<"\n";
        
	}

int main() {
	int n, m, u, v;
	cin>>n>>m;
	vector<pair<int, int>> edges(m);
	for(int i=0; i<m; i++) {
		cin>>u>>v;
		edges[i] = {u, v};
	}
	numOfCC(n, edges);
	return 0;
}