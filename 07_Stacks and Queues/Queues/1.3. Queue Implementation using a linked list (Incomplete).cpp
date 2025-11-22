/*Queue:
leetcode - https://leetcode.com/explore/learn/card/queue-stack/228/first-in-first-out-data-structure/

A. Queue: First In First Out
#include<queue>
queue<dataType> Q;
Q.push(element) :	Insert operation or enqueue
Q.front();
Q.pop();		:	Delete operation or dequeue

Queue implementation:
1. 	Using a dynamic array i.e. a vector
2.	Using a circular array
3.	Using a linked list
*/

//	1. Using a dynamic array i.e. a vector
#include<iostream>
#include<vector>
using namespace std;


int main() {
	myQueue Q;
	Q.enqueue(1); Q.enqueue(2);
	if(!Q.isEmpty()) cout<<Q.front()<<"\n";
	Q.dequeue();
	if(!Q.isEmpty()) cout<<Q.front()<<"\n";
	Q.dequeue();
	if(!Q.isEmpty()) cout<<Q.front()<<"\n";
	return 0;
}






