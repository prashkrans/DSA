/* Graph problem #24. Clone a connected undirected graph
Given an adjacency list representation of a connected undirected graph. Return a deep copy (clone) of the graph.
Here, map<T, list<T>> is used to represent an adjacency list.

Example 1:
Input: adjList = [[2,4],[1,3],[2,4],[1,3]]
Output: [[2,4],[1,3],[2,4],[1,3]]

Example 2:
Input: adjList = [[]]
Output: [[]]
Here, a node with value == 1 exists with no neighbors.

Example 3:
Input: adjList = []
Output: []
Here, no node exists.
*/

//	Method 1 - Using DFS + map/vector called visitedNodes to help include backedges in O(1) time.
//	There are only two different edges in an undirected graph
//	a.	if(!visited[v]) => tree edges => we'd have to create new nodes for the clone graph and add the tree edges
//	b.	if(visited[v] && parent[u]!=v) => back edges i.e. cycle exists => just add the back edges in the cloned graph 
//		between nodes with val == u and val == v
//	Running time = O(DFS) = O(n+m) ~ O(m)
//	Auxiliary space = O(V) = O(n)