/* Heaps (minHeap and maxHeap) can be implemented using two ways
1.	Using the STL priority_queue<dataType> pqName; in the library #include<queue>
2. 	Using an array and three functions to convert the array in a heap:
	a.	heapify() (most important function) - O(logn)
	b.	deleteMax() or deleteMin()          - O(logn)
	c. 	insert()                            - O(logn)
	d.  findMax() or findMin()              - O(1)

1.	STL priority_queue
	a. 	maxHeap - priority_queue<int> pq is a maxHeap i.e. the largest element at the top
	b. 	minHeap -
		1. 	priority_queue<int, vector<int>, greater<int>> pq is a minHeap i.e. the largest element at the top
			#IMP - priority_queue supports a constructor that requires two extra arguments to make it minHeap.
		2.	Multiply all elements with (-1). Then, create a max heap (max heap is the default for priority queue).
			When accessing the data and want to print it, simply multiply those elements with (-1) again.
			This is frequently used in Competitive Programming.

	Methods of priority_queue STL are:
	a. 	Search operation: We can only search the max element = O(1)
		pq.top() => returns the value at the top of the heap
	b.	Insert operation: O(logn)
		pq.push(value) => pushes the value at a suitable position maintaining the heap
	c. 	Delete max or min operation: O(logn)
		pq.pop() => deletes the top most element and carries out operations to maintain the heap
		Note - We cannot delete any element except the top most
	d. 	pq.empty() = 0 if not empty or 1 if empty
	e.	pq.size() => returns the size of the priority queue
	f.	pq.swap(pq2) => swap the contents of pq and pq2
	g. 	pq.emplace(value) => similar to pq.push(value)

	Limitations of STL priority_queue
	It doesn’t support decrease key operation or delete an element not at the top operation.

*/
