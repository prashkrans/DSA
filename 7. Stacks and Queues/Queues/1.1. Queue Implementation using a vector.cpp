/*Queue:
leetcode - https://leetcode.com/explore/learn/card/queue-stack/228/first-in-first-out-data-structure/

Queue implementation:
1. 	Using a dynamic array i.e. a vector
2.	Using a circular array
3.	Using a linked list
*/

//	1. Queue implementation using a dynamic array i.e. a vector
//  Drawback - The implementation above is straightforward but is inefficient in some cases. With the
//  movement of the start pointer, more and more space is wasted. And it will be unacceptable when we only
//  have a space limitation.

#include<iostream>
#include<vector>
using namespace std;

class myQueue {
	vector<int> a;
	int startIndex;
public:
	myQueue() {
		startIndex=0;
	}
	void enqueue(int val) {
		a.push_back(val);
	}
	void dequeue() {
		if(!isEmpty()) startIndex++;
	}
	int front() {
		if(!isEmpty()) return a[startIndex];
	}
	bool isEmpty() {
		if(startIndex >= a.size()) return 1;
		else return 0;
	}
};

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






