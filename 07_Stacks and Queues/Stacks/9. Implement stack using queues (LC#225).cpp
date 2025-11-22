/* Stack Problem #8 - LC#225. Implement Stack using Queues
Implement a last-in-first-out (LIFO) stack using only two queues. The implemented stack should support all the functions of a 
normal stack (push, top, pop, and empty).

Implement the MyStack class:
1.	void push(int x) Pushes element x to the top of the stack.
2.	int pop() Removes the element on the top of the stack and returns it.
3.	int top() Returns the element on the top of the stack.
4.	boolean empty() Returns true if the stack is empty, false otherwise.

Notes:
You must use only standard operations of a queue, which means that only push to back, peek/pop from front, size and is empty 
operations are valid.

Constraints:
1 <= x <= 9
At most 100 calls will be made to push, pop, top, and empty.
All the calls to pop and top are valid. 

Follow-up: Can you implement the stack using only one queue?

//	Method 1: Using two queues with pop() has a running time = O(n)
*/

class MyStack {
    queue<int> Q;
public:
    /** Initialize your data structure here. */
    MyStack() {}
    
    /** Push element x onto stack. */
    void push(int x) {
        Q.push(x);
    }
    
    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        int top = -1;
        int n = Q.size();
        if(n!=0) {
            top = Q.back();
            n--;
            queue<int> Q2;
            for(int i=0; i<n; i++) {
                Q2.push(Q.front());
                Q.pop();
            }
            Q = Q2;
        }
        return top;
    }
    
    /** Get the top element. */
    int top() {
        int top = -1;
        int n = Q.size();
        if(n!=0) {
            top = Q.back();
        }
        return top;
    }
    
    /** Returns whether the stack is empty. */
    bool empty() {
        return Q.empty();
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */
 
//	Method 2: Using two stacks with pop() and peek() has a running time = O(1)
//	Incomplete

//	Method 2: Using a single queue with push() ~ O(n) and pop() ~ O(1)
//	Incomplete