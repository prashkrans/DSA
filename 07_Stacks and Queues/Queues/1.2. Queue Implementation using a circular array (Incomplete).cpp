/*Queue:
LC#622. Design Circular Queue
https://leetcode.com/problems/design-circular-queue/

Implementation the MyCircularQueue class:
1.  MyCircularQueue(k): Initializes the object with the size of the queue to be k.
2.  int Front(): Gets the front item from the queue. If the queue is empty, return -1.
3.  int Rear(): Gets the last item from the queue. If the queue is empty, return -1.
4.  boolean enQueue(int value): Inserts an element into the circular queue. Return true if the operation is successful.
5.  boolean deQueue(): Deletes an element from the circular queue. Return true if the operation is successful.
6.  boolean isEmpty(): Checks whether the circular queue is empty or not.
7.  boolean isFull(): Checks whether the circular queue is full or not.
Implement MyCircularQueue without using the built-in queue data structure in your programming language.
*/

//	2. Queue implementation using a circular array i.e. fixed-size array + two pointers (head and tail)
//  A more efficient way than method 1 is to use a circular queue. Specifically, we may use a fixed-size
//  array and two pointers to indicate the starting position and the ending position. And the goal is to
//  reuse the wasted storage we mentioned previously.
//  The circular queue is a linear data structure in which the operations are performed based on FIFO
//  (First In First Out) principle and the last position is connected back to the first position to make a
//  circle. It is also called "Ring Buffer".
//  Drawback - The size of the queue is already fixed.

#include<iostream>
#include<vector>
using namespace std;

class MyCircularQueue {
    vector<int> a;
    int head;
    int tail;
    int n;
public:
    MyCircularQueue(int k) {
        a.resize(k);
        head = -1;
        tail = -1;
        n = k;
    }
    bool isFull() {
        if((tail+1)%n==head) return true;   //  This covers both cases i.e. if tail < n-1 and tail == n-1
        return false;
    }
    bool isEmpty() {
        if(head==-1&&tail==-1) return 1;
        else return 0;
    }
    bool enQueue(int val) {
        if(!isFull()) {
            if(head==-1) head++;
            tail = (tail+1)%n;              //  enQueue operation only increments the tail. It increments both head and tail only when head == -1
            a[tail] = val;
            return true;
        }
        return false;                       //  This implies that the queue is full so cannot insert more elements
    }
    bool deQueue() {
        if(!isEmpty()) {
            if(head==tail) {
                head = -1;
                tail = -1;
            }
            else head = (head+1)%n;
            return true;
        }
        return false;                       //  This implies that the queue is empty so cannot dequeue any further
    }
    int Front() {
        if(!isEmpty()) {
            return a[head];
        }
        else return -1;
    }
    int Rear() {
        if(!isEmpty()) {
            return a[tail];
        }
        else return -1;
    }
};

int main() {
	MyCircularQueue Q(3);
	Q.enQueue(1);
	Q.enQueue(2);
	if(!Q.isEmpty()) cout<<Q.Front()<<"\n";
	Q.deQueue();
	if(!Q.isEmpty()) cout<<Q.Front()<<"\n";
	Q.deQueue();
	if(!Q.isEmpty()) cout<<Q.Front()<<"\n";
	if(!Q.deQueue()) cout<<"Cannot dequeue as the queue is already empty\n";
	Q.enQueue(4);
    Q.enQueue(5);
    Q.enQueue(6);
	if(Q.isFull()) cout<<"The queue is full\n";
	if(!Q.enQueue(7)) cout<<"Cannot enqueue as the queue is already full\n";
	else cout<<"The queue is not yet full\n";
	cout<<"Front = "<<Q.Front()<<"\t";
	cout<<"Rear = "<<Q.Rear()<<"\n";
	return 0;
}
