/* Graph Prob. #5.2. (LC#547.) Number of Provinces
There are n cities. Some of them are connected, while some are not. If city a is connected directly with 
city b, and city b is connected directly with city c, then city a is connected indirectly with city c.
A province is a group of directly or indirectly connected cities and no other cities outside of the group.
You are given an n x n matrix isConnected where isConnected[i][j] = 1 if the ith city and the jth city are 
directly connected, and isConnected[i][j] = 0 otherwise.
Return the total number of provinces.

Example 1:
Input: isConnected = [[1,1,0],[1,1,0],[0,0,1]]
Output: 2

Constraints:
1 <= n <= 200
n == isConnected.length
n == isConnected[i].length
isConnected[i][j] is 1 or 0.
isConnected[i][i] == 1
isConnected[i][j] == isConnected[j][i]

This problem basically reduces to finding the number of connected components in an undirected graph represented
using an adjacency matrix. There are three methods to solve this problem:
1. BFS: R.T. = (n^2) | A.S. = O(n) due to the visited array
2. DFS: R.T. = (n^2) | A.S. = O(n) due to the visited array
3. Disjoint Set (Union-Find Algo): R.T. = O(n^2 + nlog2n + n) ~ O(n^2) | A.S. = O(3*n) ~ O(n) due to the struct node
*/

//	Method 1: BFS

class Solution {
public:
    void bfs(vector<vector<int>> G, vector<int> &visited, int i) {
        int n = G.size();
        queue<int> Q;
        Q.push(i);
        visited[i] = 1;
        while(!Q.empty()) {
            int u = Q.front();
            Q.pop();
            for(int v=0; v<n; v++) {
                if(G[u][v] == 1 && !visited[v]) {
                    Q.push(v);
                    visited[v] = 1;                    
                }
            }
        }
    }
    
    int findCircleNum(vector<vector<int>>& G) {
        int n = G.size(), numCC = 0;
        vector<int> visited(n, 0);
        for(int i=0; i<n; i++) {
            if(!visited[i]) {
                numCC++;
                bfs(G, visited, i);
            }
        }
        return numCC;
    }
};

//	Method 1: DFS

class Solution {
public:
    void dfs(vector<vector<int>> &isC, vector<int> &visited, int i) {
        int n = isC.size();
        if(!visited[i]) {
            visited[i] = 1;
            for(int j=0; j<n; j++) {
                //if(i==j) continue;
                if(isC[i][j] == 1) dfs(isC, visited, j);
            }
        }
    }
    
    int findCircleNum(vector<vector<int>>& isConnected) {
        int numCC = 0, n = isConnected.size();
        vector<int> visited(n, 0);
        for(int i=0; i<n; i++) {
            if(!visited[i]) {
                numCC++;
                dfs(isConnected, visited, i);
            }
        }
        return numCC;
    }
};

//	Method 3: Disjoint Sets - Union-Find Algorithm

class Solution {
public:
    struct node {
        int val;
        int rank;
        node *parent;
        node(int val_, int rank_) : val(val_), rank(rank_), parent(nullptr) {}
    };
    
    node *findSet(node *a) {
        if(a->parent == a) return a;
        return findSet(a->parent);
    }
    
    void unionOfSets(node *a, node* b) {
        node *rootA = findSet(a);
        node *rootB = findSet(b);
        int rankA = rootA->rank;
        int rankB = rootB->rank;
        if(rankA >= rankB) {
            rootB->parent = rootA;
            rootA->rank = rankA + rankB;
        }
        else {
            rootA->parent = rootB;
            rootB->rank = rankA + rankB;
        }
    }
    
    int findCircleNum(vector<vector<int>>& adjMat) {
        int n = adjMat.size(), numCC = 0;
        vector<node*> arrNodes(n, nullptr); 
        for(int i=0; i<n; i++) {
            arrNodes[i] = new node(i, 1);
            arrNodes[i]->parent = arrNodes[i];  //arrNodes[i] = new node(i, 1, arrNodes[i]); -> This does not work
        }
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                if(adjMat[i][j] == 1) {
                    if(findSet(arrNodes[i]) != findSet(arrNodes[j]))
                        unionOfSets(arrNodes[i], arrNodes[j]);
                }
            }
        }
        set<int> st;
        for(int i=0; i<n; i++) {
            node *uniqueParent = findSet(arrNodes[i]);			//	No. of unique roots == the number of connected components in the undirected graph
            st.insert(uniqueParent->val);
        }
        numCC = st.size();
        return numCC;        
    }
};