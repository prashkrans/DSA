/*	Graph Problem #12.3. The Matrix (Similar to Kruskal's Algo to find MST)
*/

//  Method 1: Similar to Kruskal's Algo to find MST, we first sort the edges
//  in descending order and then merge two sets u and v only if they don't
//  form a cycle and both of them each don't have a machine. Hence, if both
//  the sets u and v each contain a machine, we add the weight of the edge(u, v)
//  into our answer. Finally we get the sum of all the edges/roads destroyed
//  to prevent a path connecting any machines.
//  Steps:
//  a. sort roads descending (big values first)
//  b. join cities unless both trees has machines
//  c. if both trees has machines, destroy current road

//  Running time = O(mlogm + O(union)*n-1 + O(findSet)*2m) ~ O(mlog2m) or O(Elog2E)
//  where m = no. of edges in the graph
//  Auxiliary space = O(n) or O(V) where n is the no. of nodes in the graph

#include <bits/stdc++.h>
using namespace std;

struct node {
    int val;
    int height;
    bool hasMachine;
    node *parent;
    node(int val_) : val(val_), height(1), hasMachine(0), parent(nullptr){}
};

node *findSet(node *u) {
    if(u->parent == u) return u;
    else return findSet(u->parent);
}

bool isMacFound(node *u) {
    node *rootU = findSet(u);
    return rootU->hasMachine;
}

void unionOfSets(node *u, node *v) {            //  Used union by height instead of union by rank (R.T. is same for both)
    node *rootU = findSet(u), *rootV = findSet(v);
    if(rootU->hasMachine || rootV->hasMachine) {
        rootU->hasMachine = 1;
        rootV->hasMachine = 1;
    }
    int heightU = rootU->height, heightV = rootV->height;
    if(heightU > heightV)
        rootV->parent = rootU;
    else if(heightU < heightV)
        rootU->parent = rootV;
    else {
        rootV->parent = rootU;
        rootU->height++;
    }
}

class cmp {
public:
    bool operator() (vector<int> a, vector<int> b) const {
        return a[2] > b[2];
    }
};

void printMap(unordered_map<int, node*> mp) {
    for(auto i : mp) {
        cout<<i.first<<" -> ";
        cout<<i.second->val<<", "<<i.second->height<<", "<<i.second->hasMachine<<", "<<i.second->parent->val<<"\n";
    }
}

int minTime(vector<vector<int>> roads, vector<int> machines) {
    int n = roads.size()+1, k = machines.size(), sum = 0;
    sort(roads.begin(), roads.end(), cmp());
    //for(auto i : roads) cout<<i[0]<<", "<<i[1]<<", "<<i[2]<<"\n";
    set<int> macSet;
    for(int i=0; i<k; i++) macSet.insert(machines[i]);
    unordered_map<int, node*> mp;
    for(int i=0; i<n; i++) {
        mp[i] = new node(i);
        mp[i]->parent = mp[i];              //  [#[IMP] - It is really important to make a new node parent of itself
        if(macSet.count(i)) mp[i]->hasMachine = 1;
    }
    for(int i=0; i<roads.size(); i++) {
        int u = roads[i][0], v = roads[i][1], wt = roads[i][2];
        node *nodeU = mp[u], *nodeV = mp[v];
        if(findSet(nodeU) != findSet(nodeV)) {
            if(!(isMacFound(nodeU)&&isMacFound(nodeV)))         //  Both sets should not have a machine i.e. {{0, 0}, {0, 1}, {1, 0}}
                unionOfSets(nodeU, nodeV);                      //  should only be merged
            else sum += wt;
        }
    }
    //printMap(mp);
    return sum;
}

int main() {
    int n, k;
    cin>>n>>k;
    vector<vector<int>> roads(n-1, vector<int>(3));
    vector<int> machines(k);
    for(int i=0; i<n-1; i++)
        cin>>roads[i][0]>>roads[i][1]>>roads[i][2];
    for(int i=0; i<k; i++)
        cin>>machines[i];
    cout<<minTime(roads, machines);
    return 0;
}
