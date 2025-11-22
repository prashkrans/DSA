/* Stack Problem 1 - LC#155. Min Stack
Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.
Implement the MinStack class:
1.	MinStack() initializes the stack object.
2.	void push(val) pushes the element val onto the stack.
3.	void pop() removes the element on the top of the stack.
4.	int top() gets the top element of the stack.
5.	int getMin() retrieves the minimum element in the stack.

Constraints:
All the aboove methods should run in constant time i.e. O(1)
Methods pop, top and getMin operations will always be called on non-empty stacks.
*/

//	Method 1 - Using a vector to store the values of the minStack and a stack to store the minimum values only
//	Running time = O(1) for each of the above mentioned operations
//	Auxiliary space = O(n) where n is the no. elements in the minStack

class MinStack {
    vector<int> a;      //  This stores the values of the minStack
    stack<int> S;       //  This stores the values in such a manner that S.top() is always the minimum value of the minStack
public:
    MinStack() {}       //  The constructor does nothing here
    void push(int val) {
        a.push_back(val);
        if(S.empty()) S.push(val);  //  If the first element is pushed in minStack, push it to stack too
        else if(val<=S.top()) S.push(val);  //  If val > S.top() => val cannot be a min elemeent => won't be pushed in the stack S
    }    
    void pop() {        
        if(!a.empty()) {                            
            if(S.top()==a.back()) S.pop();  //  If the element being popped is the min element => pop it from the stack S too, so a greater element now becomes the min element in minStack
            a.pop_back();            
        }            
    }    
    int top() {
        return a.back();
    }
    
    int getMin() {
        return S.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */