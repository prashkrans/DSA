/*Queue:
leetcode - https://leetcode.com/explore/learn/card/queue-stack/228/first-in-first-out-data-structure/

A. Queue: First In First Out
#include<queue>
queue<dataType> Q;
A queue has three important operations:
Q.push(element) :	Insert operation or enqueue
Q.front();
Q.pop();		:	Delete operation or dequeue
Other operations are:
Q.back();
Q.empty();
Q.size();

Queue implementation:
1. 	Using a dynamic array i.e. a vector
2.	Using a circular array
3.	Using a linked list

Applications
1.	When we want to process the elements in order, using a queue might be a good choice.
2.	BFS - The first path found in BFS is always the shortest path, unlike DFS in an unweighted graph.

Note - We cannot empty a stack or a queue in O(1) time directly as there is no inbuilt function.
So, we can use two methods to empty a stack or a queue
1. 	Using the pop() function: O(n) time
	while(!Q.empty or !S.empty()) {
		Q.pop(); or S.pop();
	}
2. 	Using an empty queue/stack and copying this empty queue/stack in the original queue/stack: O(1)
	queue<dataType> Q2;
	Q1 = Q2;
	or Q1.swap(Q2);
*/
