/* Graph problem #34.1. Roads and Libraries
*/

//	Running time = O(BFS/DFS) ~ O(V+E) i.e. O(n+m)
//	Auxiliary space = O(1) 

#include <bits/stdc++.h>
using namespace std;

class graph {
    int n;
    map<int, list<int>> adjL;
public:
    graph(int n_) {
        adjL.clear();
        n = n_;
        for(int i=1; i<=n; i++) adjL[i] = list<int>();
    }
    void addEdges(int u, int v) {
        adjL[u].push_back(v);
        adjL[v].push_back(u);
    }
    void printAdjL() {
        for(auto u : adjL) {
            cout<<u.first<<" -> ";
            for(auto v : u.second)
                cout<<v<<", ";
            cout<<"\n";
        }
    }
    int bfs(int src, map<int, int> &visited) {          			//  Can also use DFS instead of BFS here
        int numOfV = 0;
        queue<int> Q;
        Q.push(src);
        visited[src] = 1;
        numOfV++;
        while(!Q.empty()) {
            int u = Q.front();
            Q.pop();
            for(auto v : adjL[u]) {
                if(!visited[v]) {
                    Q.push(v);
                    visited[v] = 1;
                    numOfV++;
                }
            }
        }
        return numOfV;
    }
    long minCost(int cL, int cR) {
        map<int, int> visited;
        vector<int> ccS;
        int count = 0, numOfV;
        for(int i=1; i<=n; i++) {
            if(!visited[i]) {
                numOfV = bfs(i, visited);
                count++;
                ccS.push_back(numOfV);
            }
        }
        for(int i=0; i<ccS.size(); i++) cout<<i+1<<" "<<ccS[i]<<"\n";
        long cost = 0;
        for(int i=0; i<count; i++)
            cost += min(((ccS[i]-1)*cR)+cL, ccS[i]*cL) ;        	//  This is important as it helps finds the min cost for each connected component
        return cost;
    }
};

long roadsAndLibraries(int n, int c_lib, int c_road, vector<vector<int>> cities) {
    graph G(n);                                     				//  if(c_lib < c_road) return n*c_lib; Don't use it as it is incorrect.
    for(int i=0; i<cities.size(); i++)
        G.addEdges(cities[i][0], cities[i][1]);
    //G.printAdjL();
    return G.minCost(c_lib, c_road);
}

int main() {
    int t;
    cin>>t;
    while(t--) {
        int n, m, cL, cR, u, v;
        cin>>n>>m>>cL>>cR;
        vector<vector<int>> cities(m, vector<int>(2));
        for(int i=0; i<m; i++) {
            cin>>u>>v;
            cities.push_back({u, v});
        }
        cout<<"The minimum cost = \n"<<roadsAndLibraries(n, cL, cR, cities)<<"\n";
    }
    return 0;
}

/* Sample Input
5
9 2 91 84
8 2
2 9
5 9 92 23
2 1
5 3
5 1
3 4
3 1
5 4
4 1
5 2
4 2
8 3 10 55
6 4
3 2
7 1
1 0 5 3
2 0 102 1
*/
