// LC#210. NCG8 Course Schedule II


// This is basically a problem to check whether the graph is DAG (Directed Acyclic Graph)

// Method 1. Create adjacency list from the given m edges and then use Kahns' Algo:
// a. Create Indegree array and fill it using a directed edge as u to v then indegree[v]++
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