/* Graph prob. #35.1. Balanced Forest
This problem accepts two cases as a solution
Case 1. Split the given graph into three components and then add the new node to the components with the smaller sum
Say, half1 == half2 and sumThird = half1 or half2
Case 2. Split the given graph into two components of equal sums then add the new node as a third component with sum = sum1/2;
Say, Of first, second and third, exactly two are equal and one is not equal as well as smaller than equal larger sums.

There are 3 methods to solve this problem. (For detailed solution see the .odt doc)
Method 1. Pick any two edges and delete them and find the sum of the three components then compare them
R.T. = O(nC2 * DFS) = O(n^2 * DFS) = O(n^2 * (n+m)) ~ O(n^3) i.e. cubic hence highly inefficient
A.S. = O(n) due to arrays arr, dep, visited, sum, etc.

Method 2. Storing the sum from leaves to a node for each node 1 to n (Easier to understand and remember)
R.T. = O(DFS + nC2*isAncestor()) = O(n^2)
A.S. = O(n) due to arrays arr, dep, visited, sum, etc.

Method 3. (Did not consider as difficult to remember due to tricky cases)
R.T. = O(nlogxn) where x = is the max children a node has. This solution passes all the test cases.
A.S. = O(n)
*/

//  Method 1a. My Method  - Gets TLE for 3 test cases (Prefer 1a over 1b)
//  Running time = O(nC2*3DFS) = O(n^2*(n+m)) ~ O(n^3) i.e. cubic thus highly inefficient
//  Auxiliary space = O(n+m) ~ O(n^2) i.e. quadratic space where n = #V and m = #E but since the given
//  undirected graph is a tree m = n-1.

#include<bits/stdc++.h>
using namespace std;

typedef pair<int, int> pr;

class graph {
map<pr, set<pr>> adjL;
public:
    void addEdge(pr u, pr v) {
        adjL[u].insert(v);
        adjL[v].insert(u);
    }

    void print(map<pr, set<pr>> a) {
        for(auto i : a) {
            cout<<"("<<i.first.first<<", "<<i.first.second<<") -> ";
            for(auto j : i.second) cout<<"("<<j.first<<", "<<j.second<<"), ";
            cout<<"\n";
        }
    }

    void deleteEdge(pr u, pr v, map<pr, set<pr>> &a) {
        a[u].erase(v);
        a[v].erase(u);
    }

    void dfs(pr u, vector<int> &visited, long &sum, map<pr, set<pr>> &a) {
        visited[u.first-1] = 1;
        sum += u.second;
        for(auto v : a[u])
            if(!visited[v.first-1]) dfs(v, visited, sum, a);
    }

    long splittingTree(vector<pr> nodes, vector<vector<int>> edges) {
        int n = nodes.size();
        long ans = LONG_MAX;
        //print(adjL);
        for(int i=0; i<edges.size(); i++) {                     //  1. The first loop takes care of the special case when only one split
            map<pr, set<pr>> cpy = adjL;                        //  is required and the node to be added becomes the third tree
            int u = edges[i][0], v = edges[i][1];
            deleteEdge(nodes[u-1], nodes[v-1], cpy);
            long leftSum = 0, rightSum = 0;
            vector<int> visited(n, 0);
            dfs(nodes[u-1], visited, leftSum, cpy);
            dfs(nodes[v-1], visited, rightSum, cpy);
            if(leftSum==rightSum) ans = min(ans, leftSum);      //  Don't return ans just yet as we may get a lower value of ans
        }                                                       //  in the next loop
        for(int i=0; i<edges.size(); i++) {                     //  2. Second loop i.e. the main loop for picking any two edges out n-1 edges
            for(int j=i+1; j<edges.size(); j++) {               //  Total ways to pick 2 edges out of n-1 edges = (n-1)C2 i.e. O(n^2)
                map<pr, set<pr>> cpy = adjL;                    //  j begins from i+1 as it is an undirected graph
                int u1 = edges[i][0], v1 = edges[i][1];
                deleteEdge(nodes[u1-1], nodes[v1-1], cpy);      //  3a. The two edges are then removed from the graph using set.erase() in O(1)
                int u2 = edges[j][0], v2 = edges[j][1];
                deleteEdge(nodes[u2-1], nodes[v2-1], cpy);
                cout<<"Edges to be cut: ("<<u1<<", "<<v1<<") & ("<<u2<<", "<<v2<<")\n";
                print(cpy);
                vector<long> sum(3, 0);                         //  3b. After the removal of two edges the tree is split into three trees
                vector<int> visited(n, 0);
                int k = 0;
                for(int i=0; i<n; i++) {
                    if(!visited[i])
                        dfs(nodes[i], visited, sum[k++], cpy);  //  4.  Using DFS/BFS we can get the sum of values of nodes in each of the three trees
                }
                cout<<"Sums = "<<sum[0]<<", "<<sum[1]<<", "<<sum[2]<<"\n\n";        //  5. When we get two equal and larger sums and one smaller sum
                if(sum[0]==sum[1] && sum[0]>sum[2]) ans = min(ans, sum[0]-sum[2]);  //  we put the diff = any one larger sum - smaller sum in the
                else if(sum[0]==sum[2] && sum[0]>sum[1]) ans = min(ans, sum[0] - sum[1]);   //  ans iff it is smaller than the value already present
                else if(sum[1]==sum[2] && sum[1]>sum[0]) ans = min(ans, sum[1] - sum[0]);   //  in ans, to minimize the answer.
            }
        }
        if(ans==LONG_MAX) return -1;
        else return ans;
    }
};

long balancedForest(vector<int> c, vector<vector<int>> edges) {
    int n = c.size();
    vector<pr> nodes(n);
    for(int i=0; i<n; i++) nodes[i] = make_pair(i+1, c[i]);
    graph G;
    for(int i=0; i<n-1; i++) {
        int u = edges[i][0], v = edges[i][1];
        G.addEdge(nodes[u-1], nodes[v-1]);
    }
    return G.splittingTree(nodes, edges);
}


int main() {
    int t;
    cin>>t;
    while(t--) {
        int n;
        cin>>n;
        vector<int> c(n);
        for(int i=0; i<n; i++) cin>>c[i];
        vector<vector<int>> edges(n-1, vector<int>(2));
        for(int i=0; i<n-1; i++) cin>>edges[i][0]>>edges[i][1];
        long ans = balancedForest(c, edges);
        cout<<"Ans = ";
        cout<<ans<<"\n";
    }
    return 0;
}

/* Sample Input
3
5
1 2 2 1 1
1 2
1 3
3 5
1 4
3
1 3 5
1 3
1 2
6
100 100 99 99 98 98
1 3
3 5
1 2
2 4
4 6
*/

/*

//  Method 1b. My Method  - Gets TLE for 3 test cases
//  Running time = O(BFS*2DFS*(BFS*2DFS)) = O(BFS^2*DFS^2) = O((n+m)^4) ~ O(n^4) i.e. biquadratic thus inefficient
//  [Verify whether R.T. = O(n^4) or O(n^3). It is atleast O(n^3) and not less]
//  Auxiliary space = O(n+m) ~ O(n^2) i.e. quadratic space where n = #V and m = #E but since the given undirected
//  graph is a tree m = n-1.

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

struct node {
    int idx, val;
};

class cmp {
public:
    bool operator() (node a, node b) const {
        return a.idx < b.idx;
    }
};

class graph {
int n;
map<node, set<node, cmp>, cmp> adjL;
public:
graph(int n_) : n(n_) {}
    void addEdge(node u, node v) {
        adjL[u].insert(v);
        adjL[v].insert(u);
    }

    void print(map<node, set<node, cmp>, cmp> a) {
        for(auto i : a) {
            cout<<"("<<i.first.idx<<", "<<i.first.val<<") -> ";
            for(auto j : i.second) cout<<"("<<j.idx<<", "<<j.val<<"), ";
            cout<<"\n";
        }
        cout<<"\n";
    }

    void deleteEdge(node u, node v, map<node, set<node, cmp>, cmp> &a) {
        a[u].erase(v);
        a[v].erase(u);
    }

    void dfs(node u, map<node, int, cmp> &visited, ll &sum, map<node, set<node, cmp>, cmp> &a) {
        visited[u] = 1;
        sum += u.val;
        for(auto v : a[u])
            if(!visited[v]) dfs(v, visited, sum, a);
    }

    ll secondSplit(node u, map<node, int, cmp> &visited, map<node, set<node, cmp>, cmp> &a, ll smallSum) {
        queue<node> Q;
        Q.push(u);
        visited[u] = 1;
        while(!Q.empty()) {
            node u = Q.front();
            Q.pop();
            for(auto v : a[u]) {
                map<node, set<node, cmp>, cmp> a2 = a;
                cout<<"u = "<<u.idx<<" -> v = "<<v.idx<<"\n";
                if(!visited[v]) {
                    Q.push(v);
                    visited[v] = 1;
                    cout<<"2. Deleting edge e("<<u.idx<<", "<<v.idx<<")\n";
                    deleteEdge(u, v, a2);
                    print(a2);
                    map<node, int, cmp> visited2;
                    ll lS = 0, rS = 0;
                    dfs(u, visited2, lS, a2);
                    dfs(v, visited2, rS, a2);
                    cout<<"lS = "<<lS<<" rS = "<<rS<<" smallSum = "<<smallSum<<"\n";
                    if(lS == rS && lS > smallSum) return lS - smallSum;                 //  We need two equal larger trees, and one smaller tree.
                    else if(max(lS, rS) == smallSum) return smallSum - min(lS, rS);
                   //print(a);
                }
            }
        }
        return -1;
    }

    ll firstSplit(node src) {
        ll ans;
        map<node, int, cmp> mainVisited;
        queue<node> Q;
        Q.push(src);
        mainVisited[src] = 1;
        while(!Q.empty()) {
            node u = Q.front();
            Q.pop();
            for(auto v : adjL[u]) {
                map<node, set<node, cmp>, cmp> a1 = adjL;
                if(!mainVisited[v]) {
                    Q.push(v);
                    mainVisited[v] = 1;
                    cout<<"1. Deleting edge e("<<u.idx<<", "<<v.idx<<")\n";
                    deleteEdge(u, v, a1);
                    print(a1);
                    ll lSum = 0, rSum = 0, halfSum = -1;
                    map<node, int, cmp> visited;
                    dfs(u, visited, lSum, a1);
                    dfs(v, visited, rSum, a1);
                    cout<<"lSum = "<<lSum<<" rSum = "<<rSum<<"\n";
                    visited.clear();
                    if(lSum < rSum) ans = secondSplit(v, visited, a1, lSum);
                    else if(lSum > rSum) ans = secondSplit(u, visited, a1, rSum);
                    else ans = lSum;                            //  Special case or inconsistent with the prob. statement but is required for one test case
                    if(ans!=-1) return ans;                     //  Here, only one split is done and then the added node forms the third tree instead of merging
                    //print(adjL);                              //  with an already present tree
                    }
            }
        }
        return -1;
    }
};

ll balancedForest(vector<int> c, vector<vector<int>> edges) {
    int n = c.size();
    vector<node> nodes(n);
    for(int i=0; i<n; i++) nodes[i] = {i+1, c[i]};
    graph G(n);
    for(int i=0; i<n-1; i++)
        G.addEdge(nodes[edges[i][0]-1], nodes[edges[i][1]-1]);
    return G.firstSplit(nodes[0]);
}

int main() {
    int t;
    cin>>t;
    while(t--) {
        int n;
        cin>>n;
        vector<int> c(n);
        for(int i=0; i<n; i++) cin>>c[i];
        vector<vector<int>> edges(n-1, vector<int>(2));
        for(int i=0; i<n-1; i++) cin>>edges[i][0]>>edges[i][1];
        ll ans = balancedForest(c, edges);
        //cout<<"Ans = ";
        cout<<ans<<"\n";
    }
    return 0;
}
*/
