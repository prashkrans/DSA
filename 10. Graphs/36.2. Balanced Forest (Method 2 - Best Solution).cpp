/* Graph prob. #36.2. Balanced Forest
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

//  Method 2. Storing the sum of the current node.val + its descendants.val in an array for each node.
//  This is the best solution to understand but still gets TLE for 3 cases which require R.T. = O(nlogn)
//  However, the O(nlogn) solution has multiple cases therefore slightly difficult to understand.
//  So,

//  Running time = (O(DFS + n + n^2*O(isAncestor()) = O(n+n-1+n+n^2*O(isAncestor())) ~ O(n^2*O(inAncestor())
//  Now, O(isAncestor()) = O(1) => R.T. = O(n^2) if we use arr[] and dep[] to store the arrival and departure time of a node in DFS
//  Auxiliary space = O(n) due to arrays arr, dep, visited, sum, etc.


#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

struct node {           //  We can use a pair<int, int> or node to store two values for a node
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
map<node, list<node>, cmp> adjL;
public:
    graph(int n_) : n(n_) {}

    void addEdge(node u, node v) {
        adjL[u].push_back(v);
        adjL[v].push_back(u);
    }

    void print() {
        for(auto i : adjL) {
            cout<<"("<<i.first.idx<<", "<<i.first.val<<") -> ";
            for(auto j : i.second) cout<<"("<<j.idx<<", "<<j.val<<"), ";
            cout<<"\n";
        }
        cout<<"\n";
    }

    ll dfs(node u, vector<int> &visited, vector<ll> &sum, vector<int> &arr, vector<int> &dep, int &time) {
        visited[u.idx-1] = 1;           //  DFS gets the sum of each node from leaves to that node as well as also
        arr[u.idx-1] = time++;          //  gets the arrival and departure time of each node
        ll currSum = 0;
        for(auto v : adjL[u]) {
            if(!visited[v.idx-1]) {
                currSum += dfs(v, visited, sum, arr, dep, time);
            }
        }
        currSum += u.val;
        sum[u.idx-1] = currSum;
        dep[u.idx-1] = time++;
        return currSum;
    }

    bool isAncestor(int x, int y, vector<int> arr, vector<int> dep) {       //  If x is an ancestor of y then returns true else false
        if(arr[x-1] < arr[y-1] && dep[x-1] > dep[y-1])
            return true;
        else return false;
    }
};

ll balancedForest(vector<int> c, vector<vector<int>> edges) {
    int n = c.size();
    ll ans = LONG_MAX;
    vector<node> nodes(n);
    for(int i=0; i<n; i++) nodes[i] = {i+1, c[i]};
    graph G(n);
    for(int i=0; i<n-1; i++)
        G.addEdge(nodes[edges[i][0]-1], nodes[edges[i][1]-1]);
    //G.print();
    vector<int> visited(n, 0);
    vector<ll> sum(n, 0);
    vector<int> arr(n, 0), dep(n, 0);
    int time = 0;
    G.dfs(nodes[0], visited, sum, arr, dep, time);
    // cout<<"Sum:\t"; for(int i=0; i<n; i++) cout<<sum[i]<<"\t"; cout<<"\n";
    // cout<<"Node:\t"; for(int i=0; i<n; i++) cout<<i+1<<"\t"; cout<<"\n";
    // cout<<"Arr:\t"; for(int i=0; i<n; i++) cout<<arr[i]<<"\t";  cout<<"\n";
    // cout<<"Dep:\t"; for(int i=0; i<n; i++) cout<<dep[i]<<"\t";  cout<<"\n";
    ll sum1 = sum[0], sumZ, half1, half2;
    for(int i=2; i<=n; i++) {           //  Case 1.
        sumZ = sum[i-1];
        half1 = sum1 - sumZ;
        half2 = sumZ;
        if(half1 == half2) ans = min(ans, half1);       //  Do not return ans here, since we may have a lower value in the next case
    }
    ll sumX, sumY, first, second, third;
    for(int i=2; i<=n; i++) {           //  Case 2.
        for(int j=2; j<=n; j++) {       //  Both x and y varies from 2 to n-1 but if (x==y) just continue
            if(i==j) continue;
            sumX = sum[i-1];
            sumY = sum[j-1];
            if(G.isAncestor(i, j, arr, dep) || G.isAncestor(j, i, arr, dep)) {      //  It is important to check both the cases
                first = sum1 - sumX;
                second = sumX - sumY;
                third = sumY;
            }
            else {
                first = sum1 - sumX - sumY;
                second = sumX;
                third = sumY;
            }
            //cout<<"x = "<<i<<" y = "<<j<<" sum1 = "<<sum1<<" sumX = "<<sumX<<" sumY = "<<sumY<<"\n";
            //cout<<"first = "<<first<<" second = "<<second<<" third = "<<third<<"\n";
            if(first == second && first > third) ans = min(ans, first - third);
            else if(first == third && first > second) ans = min(ans, first - second);
            else if(second == third && second > first) ans = min(ans, second - first);
        }
    }
    if(ans == LONG_MAX) return -1;
    else return ans;
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
