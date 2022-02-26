/* Graph problem #23. Maximum Bipartite Matching [Verified]
Given an undirected bipartite graph, find the maximum matching.
Note - G may or may not be connected.

Algo -
1.  Convert the given bipartite undirected graph into a flow network
2.  Use any algo to find the max flow in the flow network (here Ford-Fulkerson Method is used)
3.  The max matching in the given graph is equal to max flow in the flow network

So, basically the given problem is reduced to a max flow in a flow network problem and can be
solved by all the methods that solve a max flow problem.
*/

//  Method 1 - Using Ford-Fulkerson method (using DFS here to find the augmented path)
//  Running time = O(VE) i.e. O(DFS/BFS) = O(E) for finding an augmented path in each iteration
//  and O(min(L, R)) ~ O(V) for the no. of iterations thus, O(V*E) is the total R.T.

#include<iostream>
#include<map>
#include<list>
#include<vector>
#include<queue>
#include<stack>
using namespace std;

template<typename T>
class flowNetwork {                             //  This class is used to represent a flow network of the given undirected graph
    map<T, list<pair<T, int>>> fAdjL;           //  u -> (v1, flow), (v2, flow), etc.
public:
    void addEdge(T u, T v) {
        fAdjL[u].push_back(make_pair(v, 0));    //  The flow in each edge is zero initially
        if(fAdjL.count(v)==0) fAdjL[v];         //  This implies the flow network is a directed graph
    }
    void printAdjL(map<T, list<pair<T, int>>> adjList) {
        for(auto i : adjList) {
            T u = i.first;
            cout<<u<<" -> ";
            for(auto j : adjList[u]) {
                T v = j.first;
                int f = j.second;
                cout<<"("<<v<<", "<<f<<"), ";
            }
            cout<<"\n";
        }
    }
    bool BFS(map<T, list<T>> adjL, vector<T> &L, vector<T> & R) {   //  This BFS function checks whether the given undirected graph G is bipartite
        queue<T> Q;                                                 //  If G is bipartite, then creates disjoint sets L and R
        map<T, int> visited;
        map<T, char> setName;
        typename map<T, list<T>>::iterator it;
        for(it=adjL.begin(); it!=adjL.end(); it++) {                //  IMP - If G is not connected i.e. no. of CC > 1
            T src = it->first;
            if(!visited[src]) {
                Q.push(src);
                visited[src] = 1;
                setName[src] = 'L';
                L.push_back(src);
                while(!Q.empty()) {
                    T u = Q.front();
                    Q.pop();
                    for(auto v : adjL[u]) {
                        if(!visited[v]) {
                            Q.push(v);
                            visited[v] = 1;
                            if(setName[u]=='L') {                   //  This divides V into two sets L and R
                                setName[v] = 'R';
                                R.push_back(v);
                            }
                            else {
                                setName[v] = 'L';
                                L.push_back(v);
                            }
                        }
                        else if(setName[u]==setName[v]) return 0;   //  If a parent and a child are in the same set => that G is not bipartite
                    }
                }
            }
        }
        return 1;
    }
    flowNetwork(map<T, list<T>> adjL, T s, T t) {       //  Creates the flow network G' from the given graph G
        vector<T> L;                                    //  Imp to input s and t as a parameter as we do not know the data type T
        vector<T> R;
        bool isBip = BFS(adjL, L, R);
        if(isBip) {
            for(auto u : L) {                           //  u belongs to L
                addEdge(s, u);                          //  Adds edges from s to u (u belongs to L)
                for(auto v : adjL[u]) addEdge(u, v);    //  Makes the undirected edges, directed as pointing from L to R
            }
            for(auto v : R) {                           //  v belongs to R
                addEdge(v, t);                          //  Adds edges from v (v belongs to R) to t
            }
            cout<<"The given undirected graph is bipartite and the corresponding flow network is: \n";
            printAdjL(fAdjL);
        }
        else cout<<"The given undirected graph is not bipartite hence quitting the program. \n";
    }
    bool ffDFS(T s, T t, T u, map<T, int> &visited, map<T, T> &parent, map<T, list<pair<T, int>>> residualAdjL) {   //  Simple DFS to traverse the residual graph and find a path from s to t
        bool ans = false;
        visited[u] = true;
        if(u==s) parent[u] = u;                         //  IMP - Initialization that the parent of source is the source itself
        for(auto j : residualAdjL[u]) {
            T v = j.first;
            int f = j.second;
            if(!visited[v]) {
                parent[v] = u;
                ans = (ans||ffDFS(s, t, v, visited, parent, residualAdjL));
            }
            if(v==t) return true;
        }
        return ans;
    }
    map<T, list<pair<T, int>>> createResidual() {	    //	This functions helps in creating a residual graph after each iteration
		map<T, list<pair<T, int>>> residualAdjL;
		for(auto i : fAdjL) {
			T u = i.first;
			for(auto j : fAdjL[u]) {
				T v = j.first;
				int f = j.second;                       //  f can be either 0 or 1
				int c = 1;                              //  Each edge has a unit capacity
				int cf = c - f;
				if(cf>0) residualAdjL[u].push_back({v, cf});    //  Forward edges (u, v)
				if(f>0) residualAdjL[v].push_back({u, f});      //  Backward edges (v, u)
			}
		}
		return residualAdjL;
	}
    int maxFlowFordFulkersonAlgo(T s, T t) {                    //  We are using DFS here instead of BFS
        map<T, list<pair<T, int>>> residualAdjL = createResidual();
		map<T, T> parent;
		map<T, int> visited;
		stack<pair<T, T>> augPath;                              //  IMP - augPath is a stack that stores the path from s to t in the residual graph
		int fMax = 0;
		while(ffDFS(s, t, s, visited, parent, residualAdjL)) {  //  While DFS is true i.e. while an augmenting path exists in the residual graph
            T v = t;
            T u = parent[v];
            while(u!=v) {									    //  This adds the path from s to v in a reverse order which is irrelevant here
                augPath.push({u, v});
                v = u;
                u = parent[v];
            }
            int cp = 1;                                         //  If an augmenting path exists => cp = 1 as f is either 0 or 1
            cout<<"The residual capacity of the current augmenting path p = "<<cp<<"\n";
            fMax += cp;
			cout<<"Augmenting path p = ";
			while(!augPath.empty()) {
				T u = augPath.top().first;
				T v = augPath.top().second;
				augPath.pop();
				cout<<"("<<u<<", "<<v<<"), ";
				bool found = 0;								    // 	if an edge(u, v) is on the augmenting path as well as on the graph G => its flow should be increased
				typename list<pair<T, int>>::iterator it;       //  Use iterators instead of auto here
				for(it = fAdjL[u].begin(); it!=fAdjL[u].end(); it++) {
					if(it->first==v) {
                        it->second = it->second + cp;
                        found = 1;
                        break;
					}
				}
				if(found==0) {
					for(it = fAdjL[v].begin(); it!=fAdjL[v].end(); it++) {
						if(it->first==u) it->second = it->second - cp;
					}
				}
			}
            cout<<"\n";
			cout<<"Augmented graph: \n";
            printAdjL(fAdjL);
			residualAdjL = createResidual();
			cout<<"Residual graph: \n";
			printAdjL(residualAdjL);
			visited.clear();
			parent.clear();
		}
		cout<<"The max flow in the given flow network is = "<<fMax<<"\n";
		return fMax;
	}
};

template<typename T>
class graph {
    map<T, list<T>> adjL;
public:
    void addEdge(T u, T v) {
        adjL[u].push_back(v);
        adjL[v].push_back(u);
    }
    void printAdjL() {
        cout<<"The given undirected graph is: \n";
        for(auto i : adjL) {
            T u = i.first;
            cout<<u<<" -> ";
            for(auto v : adjL[u]) cout<<v<<", ";
            cout<<"\n";
        }
    }
    int maxBipartiteMatching(T s, T t) {
        flowNetwork<T> gFN(adjL, s, t);
        int maxCardinalityOfM = gFN.maxFlowFordFulkersonAlgo(s, t);
        cout<<"The cardinality of the maximum bipartite matching is = ";
        return maxCardinalityOfM;
    }
};

int main() {
    //  /*
    graph<string> G;
    G.addEdge("a", "w");    G.addEdge("b", "w");
    G.addEdge("b", "y");    G.addEdge("c", "x");
    G.addEdge("c", "y");    G.addEdge("c", "z");
    G.addEdge("d", "y");    G.addEdge("e", "y");
    //G.addEdge("a", "b");    //  G is not bipartite if this edges is present
    G.printAdjL();
    cout<<G.maxBipartiteMatching("s", "t")<<"\n";   //  */
    graph<int> G1;
    G1.addEdge(1, 8);       G1.addEdge(1, 9);
    G1.addEdge(3, 7);       G1.addEdge(3, 10);
    G1.addEdge(4, 9);       G1.addEdge(5, 9);
    G1.addEdge(5, 10);       G1.addEdge(6, 12);
    G1.printAdjL();
    cout<<G1.maxBipartiteMatching(0 , 100)<<"\n";
    return 0;
}
