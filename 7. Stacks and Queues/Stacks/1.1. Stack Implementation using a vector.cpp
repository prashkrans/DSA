/*Stack:
leetcode - https://leetcode.com/explore/learn/card/queue-stack/230/usage-stack/

Stack implementation:
The implementation of a Stack is easier than a Queue.
1. 	Using a dynamic array i.e. a vector
2.	Using a linked list
*/

//	1. Stack implementation using a dynamic array i.e. a vector
//	A dynamic array is sufficient to implement a stack structure since,
//	the vector STL supports pop_back() and back() methods

#include<iostream>
#include<vector>
using namespace std;

class myStack {
	vector<int> a;
public:
	void push(int val) {
		a.push_back(val);
	}
	void pop() {
		if(!isEmpty()) a.pop_back();
	}
	int top() {
		return a.back();		//	Since the vector STL supports pop_back() and back() methods
		// or return a[a.size()-1];
	}
	int size() {
		return a.size();
	}
	bool isEmpty() {
		return a.empty();
	}
};

int main() {
	myStack S;
	S.push(3);
	S.push(2);
	S.push(1);
	cout<<"Size of the stack = "<<S.size()<<"\n";
	cout<<"The top most element is = "<<S.top()<<"\n";
	S.pop();
	cout<<"Printing all the elements of the stack: \n";
	while(!S.isEmpty()) {
		cout<<S.top()<<"\n";
		S.pop();
	}
	if(S.isEmpty()) cout<<"The stack is empty\n";
	return 0;
}
