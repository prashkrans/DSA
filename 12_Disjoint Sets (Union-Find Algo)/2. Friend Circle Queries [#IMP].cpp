/* Disjoint Sets Prob. #2. Friend Circle Queries [#IMP]
*/
//  Method 1. We may also approach this problem as a graph of 2q nodes in which initially there
//  were zero edges. As we process queries we keep adding an edge in our graph and to report the
//  maximum group size, we can run a DFS over all the connected components and get the max size
//  out of them for each query qi.

//  Running time = O(4q^2) ~ O(q^2) i.e. quadratic thus inefficient. It won't be O(n^2) as n-2*q nodes are
//  not even used since the graph can have maximum of 2*q nodes where n = 10^9 as given in the problem.
//  Auxiliary space = O(q^2) due to max no. of nodes being 2*q.

//  Method 2. Using optimized disjoint sets data structure i.e. union-find algo (union by rank) where max
//  rank is the max size of a friend circle. It is also important to use a map (unordered) to map the node
//  value with the node itself thus enabling us to retrieve the node in O(1) just from the node value.

//  Running time = O(2*(log1 + log2 + log3 + ... + log(q))) ~ O(qlog2q) thus, efficient where q=queries.size()
//  Auxiliary space = O(q) i.e. linear space

#include <bits/stdc++.h>
using namespace std;

struct node {
    int val;
    int rank;
    node *parent;
    node(int val_, int rank_) : val(val_), rank(rank_), parent(nullptr) {}
};

node *findRoot(node *a) {
    while(a->parent!=a)
        a = a->parent;
    return a;
}

void unionOfSets(node* a, node *b) {
    node *rootA = findRoot(a);  int rankA = rootA->rank;
    node *rootB = findRoot(b);  int rankB = rootB->rank;
    if(rankA >= rankB) {
        rootB->parent = rootA;
        rootA->rank = rankA + rankB;

    }
    else {
        rootA->parent = rootB;
        rootB->rank = rankA + rankB;
    }
}

// Complete the maxCircle function below.
vector<int> maxCircle(vector<vector<int>> queries) {
    vector<int> ans;
    int maxVal = 0;
    int maxSize = 1000000000;
    unordered_map<int, node*> mp;           //  This map helps to store the nodes in a friend circle of size > 1
    int q = queries.size();                 //  If a node has no friends it is not considered here
    for(int i=0; i<q; i++) {
        int a = queries[i][0], b = queries[i][1];
        node *nodeA = nullptr, *nodeB = nullptr;
        if(!mp.count(a)) {
            nodeA = new node(a, 1);
            nodeA->parent = nodeA;          //  A node without any friend is the parent of itself
            mp[a] = nodeA;
        }
        else nodeA = mp[a];                 //  If a node already exists in a friend circle just get it in O(1)
        if(!mp.count(b)) {
            nodeB = new node(b, 1);
            nodeB->parent = nodeB;
            mp[b] = nodeB;
        }
        else nodeB = mp[b];
        if(findRoot(nodeA)!=findRoot(nodeB))
            unionOfSets(nodeA, nodeB);
        for(auto i : mp) cout<<"{"<<i.first<<"->"<<i.second->val<<", "<<i.second->rank<<", "<<(i.second->parent)->val<<"}, "; cout<<"\n";
        int currRank = max(findRoot(nodeA)->rank, findRoot(nodeB)->rank);       //  Since, we are only updating only one of the roots after the union
        maxVal = max(maxVal, currRank);     //  Keeps the global maximum size of the friend circle which may or may not change after each union
        ans.push_back(maxVal);
    }
    return ans;
}

int main(){
    int q;
    cin>>q;
    vector<vector<int>> queries(q, vector<int>(2));
    for(int i=0; i<q; i++)
        cin>>queries[i][0]>>queries[i][1];
    vector<int> ans = maxCircle(queries);
    for(int i=0; i<ans.size(); i++) cout<<ans[i]<<"\n";
}

/*Sample input
6
1 2
3 4
1 3
5 7
5 6
7 4
*/
