/*	Graph Problem #12.2.2. - Minimum Spanning Tree (MST) using Prim's Algorithm
	MST is only defined if the graph is
	a. connected and
	b. undirected
	Given a connected and a undirected graph, find its MST.
	There are two ways to find the MST of a graph. Both are greedy algorithms
	1. Kruskal's Algorithm
	2. Prim's Algorithm
		2a. Prim's Algorithm (Heap of edges)
		2b.	Prim's Algorithm modified (Heap of vertices) (similar to Dijkstra's Algo)
*/

//	Method 2.1 - Prim's algorithm (Greedy Algo) - Slightly slower than modified Prim's Algo
//	Steps:


//	Running time = summation over(degree(v))*log(m or n)) = O(mlogm) or O(mlogn)
//	a. 	Prim's Algo: Heap of edges => O(logm) for insert() and delete() => R.T. = O(mlogm)
//	b. 	Modified Prim's Algo: Heap of vertices => O(logn) for decreasePriority() => R.T. = O(mlogn)
//	Auxiliary space = O(n) or O(V) as the size of the MST = m = n-1.

#include<iostream>
#include<map>
#include<list>
#include<vector>
#include<set>
using namespace std;

// 	complete it later