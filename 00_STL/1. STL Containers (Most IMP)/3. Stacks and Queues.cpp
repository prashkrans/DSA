#include<iostream>
#include<stack>
#include<queue>
using namespace std;

/*
Stack => LIFO (Last In First Out)
The general declaration syntax for stack container is:
stack<objectType> stackName;

The functions associated with stack are:
stack<node*> S;
1.  S.empty() – Returns whether the stack is empty – Time Complexity : O(1)
2.  S.size() – Returns the size of the stack – Time Complexity : O(1)
3.  S.top() – Returns a reference to / the top most element of the stack – Time Complexity : O(1)
4.  S.push(head) – Adds the element ‘head’ at the top of the stack – Time Complexity : O(1)
5.  S.pop() – Deletes the top most element of the stack – Time Complexity : O(1)
6.  S.swap(S2) - Exchanges the contents of two stacks but the stacks must be of the same type, although sizes may differ
        Input:  stack1 = {1, 2, 3}
                stack2 = {5, 6, 7, 8}
                stack1.swap(stack2);
        Output: stack1 = {5, 6, 7, 8}
                stack2 = {1, 2, 3}
Note - Generally S.top() and S.pop() are used together
*/

/*
Queue => FIFO (First In First Out)
The general declaration syntax for stack container is:
queue<objectType> queueName;

The functions associated with queue are :
queue<int> Q;
1.  Q.empty() – Returns whether the queue is empty.
2.  Q.size() – Returns the size of the queue.
3.  Q.front() - Returns a reference to / the element at the front of the queue
4.  Q.back() - Returns a reference to the element at the back of the queue
5.  Q.push(intVal) - Adds the element 'intVal' at the back of the queue
6.  Q.pop() - Deletes the element at the front of the queue
7.  Q.swap(Q2) - Exchanges the contents of two queues but the queues must be of same type, although sizes may differ
        Input :  queue1 = {1, 2, 3}
                queue2 = {5, 6, 7, 8}
                queue1.swap(queue2);
        Output : queue1 = {5, 6, 7, 8}
                queue2 = {1, 2, 3}
8.  Q.emplace(intVal) - Similar to Q.push() i.e. adds the element 'intVal' at the back of the queue
    So, if you want to add a copy of an existing instance of the class to the container, use push.
    If you want to create a new instance of the class, from scratch, use emplace.
    Generally use push instead of emplace
Note - Generally Q.front() and Q.pop() are used together
*/

struct listNode{
    int data;
    listNode* next;
    listNode(int data) : data(data), next(NULL) {}
};

struct BTnode{
    int val;
    BTnode* left;
    BTnode* right;
    BTnode(int val) : val(val), left(NULL), right(NULL) {}
    BTnode(int val, BTnode* left, BTnode* right) : val(val), left(left), right(right) {}
};

int main(){
stack<int> intStack;
stack<char> charStack;
stack<listNode*> llStack;
stack<BTnode*> BTstack;
queue<int> intQueue;
queue<char> charQueue;
queue<listNode*> llQueue;
queue<BTnode*> BTqueue;
return 0;
}
