/*Stack:
leetcode - https://leetcode.com/explore/learn/card/queue-stack/230/usage-stack/

B. Stack: Last In First Out
In a LIFO data structure, the newest element added to the queue will be processed first.
#include<stack>
stack<dataType> S;
A stack has three important operations:
S.push(element) :	Insert operation or enqueue
S.top();
S.pop();		:	Delete operation or dequeue
Other operations are:
S.empty();
S.size();

Stack implementation:
The implementation of a Stack is easier than a Queue.
1. 	Using a dynamic array i.e. a vector
2.	Using a linked list

Applications
1.	When we want to process the elements in reverse order, using a stack might be a good choice.
2.	DFS

2.	DFS:
The processing order of the nodes in DFS is the exact opposite order as how they were added to the 
stack, which is Last-in-First-out(LIFO). That's why we use a stack in DFS.
DFS can be implemented using

a.	a stack (i.e. iterative DFS similar to how BFS uses a queue)
	The advantage of the recursion solution is that it is easier to implement. However, there is a huge 
	disadvantage: if the depth of recursion is too high, you will suffer from stack overflow. 
	In that case, you might want to use BFS instead or implement DFS using an explicit stack.
	
b.	recursion (i.e. recursion stack)
	It seems like we don't have to use any stacks when we implement DFS recursively. But actually, 
	we are using the implicit stack provided by the system, also known as the Call Stack.
	It is easier to implement than using an explicit stack for DFS.

The first path found in DFS is not always the shortest path, unlike BFS in an unweighted graph.

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
