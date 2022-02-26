/* DP Problem 22 - LC#279. Perfect Squares
Given an integer n, return the least number of perfect square numbers that sum to n.
A perfect square is an integer that is the square of an integer; in other words, it 
is the product of some integer with itself. For example, 1, 4, 9, and 16 are perfect 
squares while 3 and 11 are not.

Example 1:
Input: n = 12
Output: 3
Explanation: 12 = 4 + 4 + 4.

Example 2:
Input: n = 13
Output: 2
Explanation: 13 = 4 + 9.

Note - The running time for methods 1 - DP, 2 - BFS, 3 - Static DP and 5 - My method is the same i.e. O(n*sqrt(n)) however,
the differences are due to usage of DP table or queue individually for each test case while static vector only does computations
and builds the DP table only if (next test case) n2 > n1 (previous test case) else just uses the values of the DP table without 
doing any computation if n2 < n1. 
*/
//	Remember methods 1 and 2 only
//	Method 3 just demonstrates the use of static keyword before a vector in a class 

//	Method 1 - Dynamic Programming (Easiest solution but slightly slower than static DP)
//	R.T. = 200ms
//	Running time = O(n*sqrt(n)) 
//	Auxiliary space = O(n)

class Solution {
public:
    int numSquares(int n) {
        vector<int> DP(n+1, INT_MAX);						//	Note - Here static keyword does not work
        DP[0] = 0;
        for(int i=1; i<=n; i++) {							//	i : 1 to n
            for(int j=1; j*j<=i; j++) {						//	j : 1 to j*j<=i
                DP[i] = min(DP[i], DP[i-j*j] + 1);		
            }
        }
        //for(int i=0; i<=n; i++) cout<<DP[i]<<" "; cout<<"\n";
        return DP[n];
    }
};


//	Method 2 - BFS Search (Slightly slower than method 1)
//	R.T. = 372ms
//	R.T. = O(n*sqrt(n)) 
//	Auxiliary space = O(n)
class Solution {
public:
    int numSquares(int n) {
        queue<int> Q; 				//	At first, we may think that visited is not required since it is a tree and not a graph
        map<int, int> visited;		//	IMP - but as a node can be again visited in the same level or the levels below,  
        map<int, int> level;		//	the values of level and parent will update as per the latest finding of the node which is incorrect.
        map<int, int> parent;		//	So, visited array/map becomes important even if it is a tree
        Q.push(n);					//	No need of parent array/map if we don't need the path information
        visited[n] = 1;
        level[n] = 0;
        parent[n] = n;
        bool found = 0;
        while(!Q.empty()) {
            int u = Q.front();
            Q.pop();
            for(int i=1; i*i<=u; i++) {
                int v = u - i*i;
                if(!visited[v]) {
                    Q.push(v);
                    visited[v] = 1;
                    level[v] = level[u] + 1;
                    parent[v] = u;
                    if(v==0) {
                        found = 1;
                        break;
                    }
                }
            }
            if(found == 1) break;
        }
        stack<int> S;
        int v = 0;
        int u = parent[v];
        while(u!=v) {
            S.push(v);
            v = parent[v];
            u = parent[v];
        }
        S.push(u);
        while(!S.empty()) {
            cout<<S.top()<<" -> ";
            S.pop();
        }
        cout<<"\n";
        return level[0];
    }
};
//	Shorter version of method 2 without the path information
class Solution {
public:
    int numSquares(int n) {
        queue<int> Q;
        map<int, int> visited;
        map<int, int> level;
        Q.push(n);
        visited[n] = 1;
        level[n] = 0;
        while(!Q.empty()) {
            int u = Q.front();
            Q.pop();
            //for(int i=1; i*i<=u; i++) {		//	This implies mere reversal in traversal direction i.e. from 1 to sqrt(n) instead from sqrt(n) to 1
            for(int i = sqrt(u); i>0; i--) {
                int v = u - i*i;
                if(!visited[v]) {
                    Q.push(v);
                    visited[v] = 1;
                    level[v] = level[u] + 1;
                    if(v==0) return level[0];
                }
            }
        }
        return level[0];
    }
};

//	Method 3 - Static Dynamic Programming (Faster than method 1 and 2)
//	Note - If we remove the keyword static, the program runs slower, while
//	with the keyword static the program runs really fast.
//	The keyword static here allows the vector DP to declared just once even when multiple instances of the class Solution are declared.
//	Thus, reducing the running time significantly as it already stores the values for say n1 < n2 which can be used in n2.
//	R.T. = 0ms
//	Running time = O(n*sqrt(n)) 
//	Auxiliary space = O(n)

class Solution {
public:
    int numSquares(int n) {
        static vector<int> DP({0});		//	This even works without the keyword static, but will run slower i.e. as fast as method 1
        while(DP.size()<=n) {			
			int i = DP.size();
			DP.push_back(INT_MAX);		//	DP[i] == INT_MAX until a smaller value is found
            for(int j=1; j*j<=i; j++) {
				DP[i] = min(DP[i], DP[i-j*j] + 1);
            }
        }
        //for(int i=0; i<=n; i++) cout<<DP[i]<<" "; cout<<"\n";
        return DP[n];
    }
};

//	Method 4 - Mathematical solution (Fastest solution)
//	Incomplete
//	Four square theorem
//	Running time = ?
//	Auxiliary space = ?

//	Method 5 - (My method) - Similar to method 1 but slight change in the initialization and the DP formula.
//	(Slowest solution)
//	R.T. = 400ms
//	Running time = O(n*sqrt(n)) 
//	Auxiliary space = O(n)

class Solution {
public:
    int numSquares(int n) {
        vector<int> DP(n+1, -1);
        DP[0] = 0;
        DP[1] = 1;
        for(int i=2; i<=n; i++) {
            int x = sqrt(i);
            if(x*x==i) DP[i] = 1;
        }
        for(int i=2; i<=n; i++) {
            for(int j=0; j*j<i; j++) {
                if(DP[i]==-1)
                    DP[i] = DP[j*j] + DP[i-j*j];
                else  DP[i] = min(DP[i], DP[j*j] + DP[i-j*j]);
            }
        }
        //for(int i=0; i<=n; i++) cout<<DP[i]<<" "; cout<<"\n";
        return DP[n];
    }
};