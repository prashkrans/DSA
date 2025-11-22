/*
STL provides priority_queue, but the provided priority queue doesn’t support decrease key operation or delete
an element not at the top operation.
And in Dijkstra’s algorithm, we need a priority queue and below operations on priority queue :
a.	findMin(): from all those vertices whose shortest distance is not yet found, we need to get vertex
		     with minimum distance.
b.	decreaseKey(key, value): after extracting vertex we need to update distance of its adjacent vertices, and if new distance
	      is smaller, then update that in data structure.

We can implement a priority queue to be used in Dijkstra's algorithm in three ways:

1.  STL set as set<pair<int, int>> pqSet and a custom findMin() and decreaseKey() function:
    #IMP - This is the best solution. Always use this method.
	Above operations can be easily implemented by set data structure (Ordered set) of C++ STL.
	a. 	findMin(): STL set keeps all its keys in sorted order so minimum distant vertex will always be at beginning which, we can
		extract in O(1) time
		i.e. setName.begin()->second is the vertex with minimum distance
	b.	decreaseKey(key, value):  We can update other adjacent vertex accordingly if any vertex’s distance becomes smaller by
		deleting its previous entry and inserting the new updated entry.
		i.e. setName.erase(setName.find(make_pair(dist[v], v)); setName.insert(make_pair(updated dist[v], v);
		Note - We cannot update a value in a set, we'll always have to delete previous value and add the new value.

2.  STL priority_queue  as priority_queue<pair<int, T>, vector<pair<int, T>, greater<pair<int, T>> pq which is a minHeap
    #IMP - Second best solution
    Priority Queue: Priority queue is the extension of the queue in which elements associated with priority and
    elements having higher priority is popped first.
    Priority queue can contain elements with various data types such as integer, pair of integers, custom data type.
    But one thing is common that there is one element that defines the priority of the element. Therefore, the priority
    queue of pairs can have two types of ordering –
        a.  Ordered by the first element of pair (default)
        b.  Ordered by the second element of pair (by the use of a comparator)
    In C++ if the element is in the form of pairs, then by default the priority of the elements is dependent
    upon the first element. Therefore, we just have to use the priority queue of pairs only.
    #IMP - However, the problem is, priority_queue doesn’t support decrease key. To resolve this problem, we do not
    update a key, but insert one more copy of it. So we allow multiple instances of same vertex in priority queue.
    This approach doesn’t require decrease key operation and has below important properties.
    ->  Whenever distance of a vertex is reduced, we add one more instance of vertex in priority_queue. Even if there are multiple
        instances, we only consider the instance with minimum distance and ignore other instances.
    ->  The time complexity remains O(ELogV)) as there will be at most O(E) vertices in priority queue and O(Log E) is same as O(Log V)
    Note - The duplicates v may come out multiple times however all the w adjacent nodes to v will get the correct distance allocated to
    them because of the duplicate with the least distance itself


3.  Custom priority queue of pairs which supports both deleteAnyElement() and decreaseKey() functions
    It is the most complex solution.


*/
