/*	Graph Problem #9.2b. - Is the given directed graph acyclic?
	Given a Directed Graph with V vertices (Numbered from 0 to V-1) and E edges, 
	check whether it contains any cycle or not.
	gfg - https://practice.geeksforgeeks.org/problems/detect-cycle-in-a-directed-graph/1
*/
//	Method 2. - Using BFS (Kahn's Algorithm for Topological Sorting) + Count Variable
//	Steps:
//	1. 	Compute in-degree (number of incoming edges) for each of the vertex present in the graph and 
//		initialize the count of visited nodes as 0.
//	2. 	Pick all the vertices with in-degree as 0 and add them into a queue (Enqueue operation)
//	3.	Remove a vertex from the queue (Dequeue operation) and then.
//		a.	Increment count of visited nodes by 1.
//		b. 	Decrease in-degree by 1 for all its neighboring nodes.
//		c.	If in-degree of a neighboring nodes is reduced to zero, then add it to the queue.
//	4. 	Repeat Step 3 until the queue is empty.
//	5.	If count of visited nodes is not equal to the number of nodes in the graph then it is cyclic, otherwise not.

//	Running time = O(BFS) = O(n+m) = O(V+E) which becomes O(m) or O(E) if m>=n
//	Auxiliary space = O(n) or O(V) due the indegree[] array

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
	//Function to detect cycle in a directed graph.
	bool isCyclic(int V, vector<int> adj[]) {
	   	vector<int> inDeg(V, 0);
	   	queue<int> Q;
	   	int count = 0;
	   	for(int i=0; i<V; i++) {
	   	    for(vector<int>::iterator it = adj[i].begin(); it!=adj[i].end(); it++) {
	   	        inDeg[*it]++;
	   	    }
	   	}
	   	for(int i=0; i<V; i++) {
	   	    if (inDeg[i]==0) {
	   	        Q.push(i); 
	   	        count++;
	   	    }
	   	}
	   	while(!Q.empty()) {
	   	    int v = Q.front();
	   	    Q.pop();
	   	    for(vector<int>::iterator w = adj[v].begin(); w!=adj[v].end(); w++) {
	   	        inDeg[*w]--;
	   	        if(inDeg[*w]==0) {
	   	            Q.push(*w);
	   	            count++;
	   	        }
	   	    }
	   	}
	   	if(count!=V) return 1;
	   	else return 0;
	}
};

int main() {    
    int t;
    cin >> t;
    while(t--) {
    	int V, E;
    	cin >> V >> E;
    	vector<int> adj[V];
    	for(int i = 0; i < E; i++) {
    		int u, v;
    		cin >> u >> v;
    		adj[u].push_back(v);
    	}
    	Solution obj;
    	cout << obj.isCyclic(V, adj) << "\n";
    }
    return 0;
}