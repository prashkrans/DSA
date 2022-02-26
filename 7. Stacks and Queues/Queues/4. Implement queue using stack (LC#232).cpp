/* Queue Problem #3 - LC#232. Implement Queue using Stacks
Implement a first in first out (FIFO) queue using only two stacks. The implemented queue should support
all the functions of a normal queue (push, peek, pop, and empty).

Implement the MyQueue class:
1.	void push(int x) Pushes element x to the back of the queue.
2.	int pop() Removes the element from the front of the queue and returns it.
3.	int peek() Returns the element at the front of the queue.
4.	boolean empty() Returns true if the queue is empty, false otherwise.
Notes:
You must use only standard operations of a stack, which means only push to top, peek/pop from top, size, and 
is empty operations are valid. 

Follow-up: Can you implement the queue such that each operation is amortized O(1) time complexity? In other words, 
performing n operations will take overall O(n) time even if one of those operations may take longer.

Constraints:
1 <= x <= 9
At most 100 calls will be made to push, pop, peek, and empty.
All the calls to pop and peek are valid.
*/

//	Method 1: Using two stacks with pop() ~ O(n)

class MyQueue {
    stack<int> S1;
    stack<int> S2;
    int front = -1;
public:
    /** Initialize your data structure here. */
    MyQueue() {}
    
    /** Push element x to the back of queue. */
    void push(int x) {
        if(S1.empty()) front = x;
        S1.push(x);
    }
    
    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        int popElem = -1; 
        if(!S1.empty()) {
            while(!S1.empty()) {
                S2.push(S1.top());
                S1.pop();
            }
            popElem = S2.top();
            S2.pop();
            if(!S2.empty()) front = S2.top();
            else front = -1;
            while(!S2.empty()) {
                S1.push(S2.top());
                S2.pop();
            }
        }        
        return popElem;
    }
    
    /** Get the front element. */
    int peek() {
        return front;
    }
    
    /** Returns whether the queue is empty. */
    bool empty() {
        return S1.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */
 
//	Method 2: Using two stacks along with a variable front to store the first element. [#IMP]
//	Also, here data of s2 is not transferred back to s1 rather, we wait for s2 to become empty.
//	Read the solution to #232 to understand better:
//	a. push(): 
//	Time complexity : O(1) Аppending an element to a stack is an O(1) operation.
//	Space complexity : O(n)O(n). We need additional memory to store the queue elements
//	b. pop():
//	Time complexity: Amortized O(1), Worst-case O(n).
//	Space complexity : O(1)O(1).
//	c. empty(): R.T. = O(1), A.S. = O(1)
//	d. front(): R.T. = O(1), A.S. = O(1)

class MyQueue {
stack<int> s1, s2;
int frontInStack1;
public:
    MyQueue() {}
    
    void push(int x) {	//	O(1)       		//	Changes front each time an element is inserted to s1 irrespective of the fact
        if(s1.empty()) frontInStack1 = x;	//	that s2 is empty or not
        s1.push(x);
    }
    
    int pop() {			//	Amortized O(1)	//  Note: pop() does not change frontInStack1.
        int popElem = -1;           
        if(s2.empty()) {            
            while(!s1.empty()) {    
                s2.push(s1.top());
                s1.pop();
            }
        }
        popElem = s2.top();					//	If s2 is empty, then s2.top() returns nothing as well s2.pop() does nothing 
        s2.pop();							//	hence popElem = -1 else popElem = s2.top() which is the front elem and != frontInStack1
        return popElem;
    }
    
    int peek() {							//	#IMP
        if(s2.empty()) 						//	Case 1. Only when s2 is empty frontInStack1 is actually the front element of the queue
			return frontInStack1;        
        else return s2.top();				//	Case 2. When s2 is not empty s2.top() is the front element of the queue 
    }
    
    bool empty() {
        return (s1.empty() && s2.empty());
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */
