/* Stack problem - 9. LC#841. Keys and Rooms
There are N rooms and you start in room 0.  Each room has a distinct number in 0, 1, 2, ..., N-1, and each 
room may have some keys to access the next room.
Formally, each room i has a list of keys rooms[i], and each key rooms[i][j] is an integer in [0, 1, ..., N-1] 
where N = rooms.length.  A key rooms[i][j] = v opens the room with number v.
Initially, all the rooms start locked (except for room 0). You can walk back and forth between rooms freely.
Return true if and only if you can enter every room.

Example 1:
Input: [[1],[2],[3],[]]
Output: true
Explanation: room 0 -> room 1 -> room 2 -> room 3 thus, visit all the rooms.

Example 2:
Input: [[1,3],[3,0,1],[2],[0]]
Output: false
Explanation: We can't enter the room with number 2.

Note:
1 <= rooms.length <= 1000
0 <= rooms[i].length <= 1000
The number of keys in all rooms combined is at most 3000.

This problem can be reduced to a directed graph where each room is a node and then we just need to check that 
if we start from the node 0, can we visit all the nodes? So, starting from the node 0 if we visit all the 
nodes 1 to n-1 in a simple DFS or BFS, it means all the rooms are visited.
*/

// 	Method 1. DFS 
//	Running time = O(n+m) ~ O(n)
//	Auxiliary space = O(n) due to the visited array

class Solution {
public:
    void DFS(int u, vector<int>& visited, vector<vector<int>> rooms) {
        visited[u] = 1;
        for(int i=0; i<rooms[u].size(); i++) {
            int v = rooms[u][i];
            if(!visited[v]) DFS(v, visited, rooms);
        }
    }
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        int n = rooms.size();
        if(n==0) return true;
        vector<int> visited(n, 0);
        DFS(0, visited, rooms);
        for(int i=0; i<n; i++) {
            if(visited[i]==0) return false;
        }
        return true;
    }
};

//	Method 2. BFS
//	Running time = O(n+m) ~ O(n)
//	Auxiliary space = O(n) due to the visited array and the queue

class Solution {
public:
	void BFS(int src, vector<int> &visited, vector<vector<int>> rooms) {
		queue<int> Q;
		Q.push(src);
		visited[src]=1;
		while(!Q.empty()) {
			int u = Q.front();
			Q.pop();
			for(auto v : rooms[u]) {
				if(!visited[v]) {
					Q.push(v);
					visited[v] = 1;
				}
			}
		}
	}
					
	bool canVisitAllRooms(vector<vector<int>> &rooms) {
		int n = rooms.size();
		if(n==0) return true;
        vector<int> visited(n, 0);
		BFS(0, visited, rooms);
		for(int i=0; i<n; i++) {
			if(visited[i]==0) return false;
		}
		return true;
	}
};