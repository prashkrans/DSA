/* Graph problem - 28. LC#752. Open the Lock
You have a lock in front of you with 4 circular wheels. Each wheel has 10 slots: '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'. 
The wheels can rotate freely and wrap around: for example we can turn '9' to be '0', or '0' to be '9'. Each move consists of turning
one wheel one slot.
The lock initially starts at '0000', a string representing the state of the 4 wheels.
You are given a list of deadends dead ends, meaning if the lock displays any of these codes, the wheels of the lock will stop turning 
and you will be unable to open it.
Given a target representing the value of the wheels that will unlock the lock, return the minimum total number of turns required to open 
the lock, or -1 if it is impossible.

Example 1:
Input: deadends = ["0201","0101","0102","1212","2002"], target = "0202"
Output: 6
Explanation:
A sequence of valid moves would be "0000" -> "1000" -> "1100" -> "1200" -> "1201" -> "1202" -> "0202".
Note that a sequence like "0000" -> "0001" -> "0002" -> "0102" -> "0202" would be invalid,
because the wheels of the lock become stuck after the display becomes the dead end "0102".

Constraints:
1 <= deadends.length <= 500
deadends[i].length == 4
target.length == 4
target will not be in the list deadends.
target and deadends[i] consist of digits only.

BFS is used for the solution here. Since BFS gives the shortest path in an unweighted graph, we can use it to get to 
the target starting from "0000". If a deadend value is encountered, that path is not considered to reach the target 
i.e. a deadend value is not an adjacent node of the current node u. So, each value of the lock (u) would have 8 
potential neighbours (v) if v is not a deadend.
Now, each node v is searched for in deadends vector which takes O(x) where x is the size of the deadends vector.
So, it is better to convert the vector deadends to an unordered_map or unordered_set so that node v can be looked up
in O(1) time instead of O(x) time.

*/
//	Method 1 - BFS + variable currLevel (instead of a level array)
//	This is just a shortened version of the method 2
//	1.	vector deadends is converted to an unordered_set setDeadends
//	2.	unordered_set visited is used instead of an unordered_map visited
//	3.	
//	Running time = O(BFS) = O(n+m) ~ O(m) (Note - O(BFS) is O(n+4m) ~ O(4m) ~ O(m))
//	Auxiliary space = O(n) due to the visited array

class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
		unordered_set<string> setDeadends(deadends.begin(), deadends.end());		
        string src = "0000";							//	Starting node is fixed i.e. "0000"
		if(setDeadends.count(src) > 0) return -1;		//	If "0000" itself is in deadends => it is impossible to reach the target
		if(src==target) return 0;						//	IMP - If target == "0000" => 0 steps are required. It is imp to use it here as we eventually compare v and target and not u and target
        queue<string> Q;								//	Modified BFS implementation
        unordered_set<string> visited;					//	Using a set instead of a map for a visited array
        Q.push(src);									
        visited.insert(src);
        vector<vector<int>> dir = {{1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1}, {-1,0,0,0}, {0,-1,0,0}, {0,0,-1,0}, {0,0,0,-1}};		//	i.e. each node may have atmost 8 adjacent nodes i.e. 2 options, up or down for each digit
        int currLevel = 0;								//	No. of steps reqd == the level at which target is found
		while(!Q.empty()) {
			int currSize = Q.size();					//	currSize denotes the no. of nodes at the same level = currLevel
			for(int i=0; i<currSize; i++) {				// 	A for loop inside the main while loop does not increase R.T. of BFS but only helps in incrementing the currLevel when all the nodes in a current level have been visited
				string u = Q.front();
				Q.pop();
				for(int i=0; i<8; i++) {				//	Creating v and checking if v is a valid neighbour of u or not
					string v = u;
					for(int j=0; j<4; j++) {			//	Using a nested loop instead of writing similar statements four times
						v[j] = v[j] + dir[i][j];
						if(v[j]=='/') v[j] = '9';		//	These two lines just make sure 	that '0' comes after '9' and '9' comes before '0'	
						else if(v[j]==':') v[j] = '0';
					}        
					if(setDeadends.count(v)==0 && visited.count(v)==0) {	//	If v is present in deadends or v is already visited then do nothing else insert v in Q and mark v as visited
						Q.push(v);
						visited.insert(v);
						if(v==target) return currLevel+1;					//	If(v==target) return currLevel + 1 as v is present at one level below u i.e. the currLevel
					}														//	currLevel of the source node is 0
				}
			}
			currLevel++;													//	If all the nodes in the current level are traversed, increase the level by 1
        }
        return -1;
    }
};

//	Method 2 - BFS + level array 

//	Running time = O(BFS) 
//	if isValid1() function is used here O(BFS) != O(n+m) as for each vertex u it takes O(4(8*x)) time so R.T. = O(n + 4mx) ~ O(mx) 
//	where x is the size of the vector deadends
//	if isValid2() function is used then O(BFS) == O(n+4m) ~ O(m)
//	Auxiliary space = O(n) due to visited and level arrays

class Solution {
public:
    void make(string &v) {			//	make() function just makes sure that '0' comes after '9' and '9' comes before '0'
        for(int i=0; i<4; i++) {	//	It does not slow the program as compared to method 1
            if(v[i]=='/') v[i] = '9';
            else if(v[i]==':') v[i] = '0';
        }
    }
    bool isValid1(string v, vector<string> deadends) {	//	isValid() function checks whether a neighbour v is a deadend or not
        for(auto i : deadends) {						//	Running time = O(x) where x is the size of the deadends array
            if(v==i) return false;						//	It slows the program as compared to method 1
        }
        return true;
    }
	bool isValid2(string v, unordered_map<string, int> isDeadend) {	//	It reduces the running time for look up of v in the deadends to O(1) from O(x)
		if(isDeadend.count(v) > 0) return false;
		else return true;
	}
    int openLock(vector<string>& deadends, string target) {
		unordered_map<string, int> isDeadend;
		for(auto i : deadends) isDeadend[i] = 1;
        string src = "0000";							//	Starting node is fixed i.e. "0000"
        //if(!isValid1(src, deadends)) return -1;		//	If "0000" itself is a dead end then we cannont reach the target node
		if(!isValid2(src, isDeadend)) return -1;
        queue<string> Q;								//	Standard BFS implementation
        map<string, int> visited;
        map<string, int> level;							//	This stores the shortest distance from "0000" to the target as we are using a BFS
        Q.push(src);
        visited[src] = 1;
        level[src] = 0;	
        vector<vector<int>> dir = {{1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1}, {-1,0,0,0}, {0,-1,0,0}, {0,0,-1,0}, {0,0,0,-1}};		//	i.e. each node may have atmost 8 adjacent nodes i.e. 2 options, up or down for each digit
        while(!Q.empty()) {
            string u = Q.front();
            Q.pop();
            for(int i=0; i<8; i++) {					//	Creating v and checking if v is a valid neighbour of u or not
                string v = u;
                v[0] = v[0] + dir[i][0];
                v[1] = v[1] + dir[i][1];
                v[2] = v[2] + dir[i][2];
                v[3] = v[3] + dir[i][3];
                make(v);
                //if(isValid1(v, deadends) && !visited[v]) {	//	If(v is not a deadend and it is not visited) push v into the queue and its level is made 1 more than that of its parent
				if(isValid2(v, isDeadend) && !visited[v]) {
                    Q.push(v);
                    visited[v] = 1;
                    level[v] = level[u] + 1;
                    if(v==target) {
                        queue<string> emptyQ;				// 	If(v==target) => target has been reached along the shortest path so, we need not go any further 
                        Q = emptyQ;							//	So, just to come out of the for loop use break and to come out of the while loop make the queue empty
                        break;								//	Since, there is no inbuild function to clear a queue so, declaring an empty queue and copying it into the original Q to make it empty
                    }
                }
            }
        }
        if(level.find(target)==level.end()) return -1;
        else return level[target];
    }
};