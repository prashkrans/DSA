/** 
1. unordered_map<pair<int, int>, int> is incorrect. So, simply use map<pair<int, int>, int> visited or a 2D array for visited

2. unordered_set doesn't work with pair<int, int> so use set<pair<int, int>> st; or convert the pair to a string or long long

3. union find algo is the same as disjoint set algo (two types union by rank or union by height) + path compression
    3.1. find() + path compression could be both iterative or recursive

4. Whether a graph is cyclic.
    a. Undirected:
        a. DFS + Parent variable
        b. BFS + Parent array
    
    b. Directed:
        a. DFS + recStack(using a vector) + backtrack
        b. Kahn's Algorithm

    
**/
