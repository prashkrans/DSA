// LC#210. NCG8 Course Schedule II


// This is basically a problem to check whether the graph is DAG (Directed Acyclic Graph)

// Method 1. Using Kahns' Algo (BFS with indegree array and without visited array)
// Easier than Method 2 DFS
// Steps: Create adjacency list from the given m edges and then use Kahns' Algo:
// a. Create Indegree array
// b. Push all the nodes in a queue with indegree == 0
// c. For all v in out edges of u, reduce indgree of v by 1 and if indegree[v] becomes 0 push it to queue
// d. If the count of all the nodes pushed into queue and topoSort == no. of nodes in the graph, then return true else false

// Running time: O(n+m) or O(nodes + edges) 
// Auxiliary space: O(n) due to the bfs queue

class Solution {
    public:
        vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
            vector<int> topoSort;
            vector<vector<int>> adjL(numCourses, vector<int>());
            vector<int> indegree(numCourses, 0);
            for(auto i: prerequisites) {
                int u = i[1];
                int v = i[0];
                adjL[u].push_back(v);
                indegree[v]++;
            }
            queue<int> q;  
            for(int u=0; u<numCourses; u++) {
                if(indegree[u]==0) {
                    q.push(u);
                    topoSort.push_back(u);  // make sure to add u to topoSort as well
                }
            }
            while(!q.empty()) {
                int u = q.front();
                q.pop();
                for(auto v: adjL[u]) {
                    if(--indegree[v]==0) {  // decrease indegree first and then if indegree becomes 0 add v to queue
                        q.push(v);
                        topoSort.push_back(v);
                    }
                }
            }
            if(topoSort.size() == numCourses) return topoSort;
            else return {};        
        }
    };


// Method 2. DFS
// Running time: O(V+E) ~ O(n+m)
// Auxiliary space: O(n) due to the recursion stack

class Solution {
    public:
        bool dfs(int u, vector<vector<int>> &adjL, vector<int> &visited, vector<int> &dfsStack, vector<int> &topoSort) {
            visited[u] = 1;
            dfsStack[u] = 1;
            for(auto v: adjL[u]) {
                if(!visited[v]) {   // if not visited v
                    if(dfs(v, adjL, visited, dfsStack, topoSort)) return true;  
                    // works as a break i.e. if a cycle found return true no need to go any further
                }
                else if (dfsStack[v] == 1) return true; // if visited v and v already found in dfsStack => cycle exists
            }
            topoSort.push_back(u);
            dfsStack[u] = 0;
            return false;
        }
    
        vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
            vector<int> topoSort;
            vector<vector<int>> adjL(numCourses, vector<int>());
            vector<int> visited(numCourses, 0);
            vector<int> dfsStack(numCourses, 0);
            for(auto i: prerequisites) {
                int u = i[1];
                int v = i[0];
                adjL[u].push_back(v);
            }
            bool isCyclic = false;
            for(int u=0; u<numCourses; u++) {
                if(!visited[u]) isCyclic = (isCyclic || dfs(u, adjL, visited, dfsStack, topoSort));
            }
            reverse(topoSort.begin(), topoSort.end()); // Since topoSort is a stack via a vector, need to reverse it
            // return (isCyclic) ? {} : topoSort; // This is incorrect since {} is an array not a vector
            return (isCyclic) ? vector<int>() : topoSort;
        }
    };