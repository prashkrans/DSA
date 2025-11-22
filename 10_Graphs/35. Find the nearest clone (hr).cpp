/* Graph problem #35. Find the nearest clone
The solution may not be fully correct so verify.
I think it gives the shortest distance only from a node with the lower value.
Anyways the correction is easy i.e. eliminate all the elements with different
color value from the dist map and just sort the dist map in terms of distance
and get the minimum difference between two adjacent values thus giving us the
shortest distance.
Thus R.T. becomes O(n+m) + O(nlog2n).
*/

//	Running time = O(BFS) ~ O(V+E) i.e. O(n+m)
//	Auxiliary space = O(1)


#include <bits/stdc++.h>
using namespace std;

vector<string> split_string(string);

// Complete the findShortest function below.

/*
 * For the unweighted graph, <name>:
 *
 * 1. The number of nodes is <name>_nodes.
 * 2. The number of edges is <name>_edges.
 * 3. An edge exists between <name>_from[i] to <name>_to[i].
 *
 */

struct node {
    int val;
    int clr;
};

class cmp {
public:
    bool operator() (node a, node b) const {
        return a.val < b.val;
    }
};

class graph {
    map<node, list<node>, cmp> adj;
    int n;
public:
    graph(int nodes, vector<long> ids) {
        n = nodes;
        for(int i=0; i<n; i++) adj[{i+1, ids[i]}] = list<node>();
    }

    void addEdges(node u, node v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void printAdj() {
        for(auto u : adj) {
            cout<<"("<<u.first.val<<", "<<u.first.clr<<") -> ";
            for(auto v : u.second) cout<<"("<<v.val<<", "<<v.clr<<"), ";
            cout<<"\n";
        }
    }

    int bfs(node src) {
        int distance = -1;
        map<node, int, cmp> visited;
        map<node, int, cmp> dist;
        queue<node> Q;
        Q.push(src);
        visited[src] = 1;
        dist[src] = 0;
        while(!Q.empty()) {
            node u = Q.front();
            Q.pop();
            for(auto v : adj[u]) {
                if(!visited[v]) {
                    Q.push(v);
                    visited[v] = 1;
                    dist[v] = dist[u]+1;
                }
            }
        }
        //for(auto i : dist) cout<<i.first.val<<", "<<i.first.clr<<" -> "<<i.second<<"\n";
        for(auto i : dist) {
            if(i.first.val!=src.val && i.first.clr == src.clr) {
                distance = i.second;
                break;
            }
        }
        //cout<<"Dist = "<<distance<<"\n";
        return distance;
    }
};

int findShortest(int nodes, vector<int> from, vector<int> to, vector<long> ids, int clrVal) {
    int count = 0;
    for(int i=0; i<ids.size(); i++) {
        if(ids[i]==clrVal) count++;
    }
    if(count<2) return -1;
    cout<<"check 2\n";
    graph G(nodes, ids);
    for(int i=0; i<from.size(); i++) {
        node u, v;
        u.val = from[i];    u.clr = ids[from[i]-1];
        v.val = to[i];      v.clr = ids[to[i]-1];
        G.addEdges(u, v);
    }
    //G.printAdj();
    int minVal = INT_MAX;
    node src;
    for(int i=0; i<ids.size(); i++) {
        if(ids[i]==clrVal) {
            src.val = i+1;
            src.clr = clrVal;
            break;
        }
    }
    minVal = G.bfs(src);
    cout<<"MinVal = "<<minVal<<"\n";
    return minVal;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int graph_nodes;
    int graph_edges;

    cin >> graph_nodes >> graph_edges;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> graph_from(graph_edges);
    vector<int> graph_to(graph_edges);

    for (int i = 0; i < graph_edges; i++) {
        cin >> graph_from[i] >> graph_to[i];
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    string ids_temp_temp;
    getline(cin, ids_temp_temp);

    vector<string> ids_temp = split_string(ids_temp_temp);

    vector<long> ids(graph_nodes);

    for (int i = 0; i < graph_nodes; i++) {
        long ids_item = stol(ids_temp[i]);

        ids[i] = ids_item;
    }

    int val;
    cin >> val;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int ans = findShortest(graph_nodes, graph_from, graph_to, ids, val);

    fout << ans << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}

/* Sample Input
5 4
1 2
1 3
2 4
3 5
1 2 3 3 2
2

4 3
1 2
1 3
4 2
1 2 1 1
1

4 3
1 2
1 3
4 2
1 2 3 4
2
*/
