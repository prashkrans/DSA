/* Graph problem - #13. All Pairs Shortest Path using Floyd-Warshall Algorithm
Find the shortest distances between every pair of vertices in a given edge weighted graph.
*/

//	Method 1 - Floyd-Warshall Algorithm
//	It works for both directed and undirected graphs but fails if the graph contains a negative cycle.
//	It is easier if the graph is already in adjacency matrix, else we need to convert an adjacency list
//	to an adjacency matrix.

//	Running time = O(n^3) i.e. cubic where n = the no. of vertices
//	Auxiliary space = O(1) if the adjMat itself is modified or O(n^2) if a copy of adjMat is used

#include<iostream>
#include<map>
#include<list>
#include<vector>
using namespace std;

void printSquareMat(vector<vector<int>> mat) {
    int n = mat.size();
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            if(mat[i][j] == INT_MAX) cout<<"INF\t";
            else cout<<mat[i][j]<<"\t";
        }
        cout<<"\n";
    }
}

template<typename T>
class graph {
	map<T, list<pair<T, int>>> adjList;
	vector<vector<int>> adjMat;	        //	declared an empty adjacency matrix here but resized later and of type int as we are storing wt
public:
	void addEdge(T u, T v, int wt) {
		adjList[u].push_back({v, wt});
		//adjList[v].push_back({u, wt});        //  this implies an undirected graph
		if(adjList.count(v)==0) adjList[v];     //  this implies a directed graph
	}
	void printAdjList() {
		cout<<"The adjacency list representation is: \n";
		for(auto i : adjList) {
			cout<<i.first<<" -> ";
			for(auto j : i.second) cout<<"("<<j.first<<", "<<j.second<<"), ";
			cout<<"\n";
		}
	}
	void printAdjMat() {
        cout<<"The adjacency matrix representation is: \n";
        int n = adjMat.size();
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                if(adjMat[i][j]==INT_MAX) cout<<"INF\t";
                else cout<<adjMat[i][j]<<"\t";
            }
            cout<<"\n";
        }
	}
	vector<vector<int>> floydWarshallAlgo() {
		int n = adjList.size();
		//vector<vector<int>> adjMat(n, vector<int>(n, INT_MAX));	//	of type int as we are storing wt
		adjMat.resize(n, vector<int>(n, INT_MAX));                  //  resizes the adjMat as it was declared as an empty matrix
		map<T, int> index;                                          //  this maps the vertices to indices as v0 -> 0, v1 -> 1, ... vn-1 -> n-1.
		int idx = 0;
		for(auto i : adjList) index[i.first] = idx++;               //  so, its important to use ordered map here
		for(auto x : adjList) {
			T u = x.first;
			for(auto y : x.second) {
				T v = y.first;
				int wt = y.second;
				int i = index[u];                                   //  converting the vertices vi and vj to indices i & j
				int j = index[v];
				adjMat[i][j] = wt;                                  //  and the adjMat[i][j] stores the weight of the edge vi to vj
			}
		}
        printAdjMat();
        vector<vector<int>> dist = adjMat;                          //  Floyd-Warshall algo begins
		for(int k=0; k<n; k++) {                                    //  here we make a copy of adjMat in dist, so, auxiliary space = O(n^2)
			for(int i=0; i<n; i++) {
				for(int j=0; j<n; j++) {
					if(dist[i][k]!=INT_MAX && dist[k][j]!=INT_MAX)
						dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
				}
			}
		}
		cout<<"The matrix dist[][] is:\n"; printSquareMat(dist);
		return dist;
	}
	bool hasCycleFW() {
        vector<vector<int>> dist = floydWarshallAlgo();             //  To detect a negative cycle, run a Floyd-Warshall algo
        int n = dist.size();                                        //  If a dist[i][i] < 0 => distance from the node to itself is -ve
        for(int i=0; i<n; i++) {                                    //  This can only happen if there is a negative cycle in the graph
            if(dist[i][i]<0) return 1;
        }
        return 0;
	}
};

int main () {
	graph<string> G;
	G.addEdge("A1", "B2", 5);	G.addEdge("A1", "C3", 4);
	G.addEdge("B2", "D4", 6);	G.addEdge("E5", "D4", -2);
	G.addEdge("F6", "A1", -3);	G.addEdge("G7", "B2", 1);
	G.addEdge("D4", "A1", -12); //  Creates a negative cycle in the graph
	G.printAdjList();
	vector<vector<int>> ans = G.floydWarshallAlgo();
	if(G.hasCycleFW()) cout<<"The given graph G has a negative cycle\n";
	else cout<<"The given graph G does not have a negative cycle\n";
	return 0;
}
