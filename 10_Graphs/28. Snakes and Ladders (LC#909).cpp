/* Graph problem 31. LC#909. Snakes and Ladders
You are given an n x n integer matrix board where the cells are labeled from 1 to n^2 in a Boustrophedon style starting 
from the bottom left of the board (i.e. board[n - 1][0]) and alternating direction each row.

You start on square 1 of the board. In each move, starting from square curr, do the following:
Choose a destination square next with a label in the range [curr + 1, min(curr + 6, n2)].
This choice simulates the result of a standard 6-sided die roll: i.e., there are always at most 6 destinations, 
regardless of the size of the board. If next has a snake or ladder, you must move to the destination of that snake or 
ladder. Otherwise, you move to next. The game ends when you reach the square n^2. 
A board square on row r and column c has a snake or ladder if board[r][c] != -1. The destination of that snake or ladder is board[r][c]. 
Squares 1 and n^2 do not have a snake or ladder.

Note that you only take a snake or ladder at most once per move. If the destination to a snake or ladder is the start of another snake or 
ladder, you do not follow the subsequent snake or ladder.

For example, suppose the board is [[-1,4],[-1,3]], and on the first move, your destination square is 2. You follow the ladder to square 3, 
but do not follow the subsequent ladder to 4.
Return the least number of moves required to reach the square n^2. If it is not possible to reach the square, return -1.

Constraints:
n == board.length == board[i].length
2 <= n <= 20
grid[i][j] is either -1 or in the range [1, n^2].
The squares labeled 1 and n^2 do not have any ladders or snakes.
*/
//	Method 1. Simple Stepwise BFS
//	Steps: 
//	1.	Convert the board 2D-vector to a 1D-vector. Note that the Boustrophedon style is used for the numbering in board => R.T. = O(n^2)
//	2.	Use a simple stepwise BFS to find the shortest path from source node == 1 to destination node == n^2 as the flat board can be considered
//		as an unweighted directed graph => R.T. = O(V+E)
//	[#IMP] Note : For the curr node u, there are 6 choices say j = u+1, ..., u+6 where j < V. Now if a cell j has value -1, then v = j. Else v = value(j)
//	where v is an adjacent node of u. Hence, a cell j with value != -1 is not even made a neighbour of u.

//	Running time = O(Conversion + BFS) = O(n^2+V+E) ~ O(V+E) = O(V+7V) = O(8V) ~ O(V) or O(n^2) (Note that here number of vertices != n instead n^2)
//	Here for each node u, we have either 6 edges or 7 edges => E = total no. of edges = 7V
//	Auxiliary space = O(n^2) or O(V) due to the flatBoard vector and queue Q.

class Solution {
public:
    vector<int> flattenBoard(int n, int V, vector<vector<int>> board) {	// Just converts 2D board to a 1D board
        vector<int> flatBoard(V+1, -1);
        int k = 1;
        for(int i=n-1; i>=0; i--)  {
            if((i%2==1 && n%2==0) || (i%2==0 && n%2==1)) {
                for(int j=0; j<n; j++) {
                    if(board[i][j]!=-1) flatBoard[k] = board[i][j];
                    k++;
                }
            }
            else if((i%2==0 && n%2==0) || (i%2==1 && n%2==1)) {
                for(int j=n-1; j>=0; j--) {
                    if(board[i][j]!=-1) flatBoard[k] = board[i][j];
                    k++;
                }
            }
        }
        //for(int i=1; i<=V; i++) cout<<i<<" "<<flatBoard[i]<<"\n";
        return flatBoard;        
    }
    
    int snakesAndLadders(vector<vector<int>>& board) {	//	Simple BFS to find the shortest distance in an unweighted graph
        int n = board.size();
        int V = n*n;									//	src == 1 and dest = V or n^2
        vector<int> flatBoard = flattenBoard(n, V, board);
        queue<int> Q;
        vector<int> visited(V+1, 0);       				//  As indexing starts from 1 and ends at V or n^2
        int minMoves = 0;
        Q.push(1);
        visited[1] = 1;
        while(!Q.empty()) {
            int qSize = Q.size();
            for(int i=0; i<qSize; i++) {
                int u = Q.front();
                Q.pop();
                if(u==V) return minMoves;					//	If the curr node u is the last node V, then return minMoves which is the shortest dist. between 1 and V
                for(int j = u+1; j <= min(u+6, V); j++) {	//	For each node u, we have 6 adjacent nodes
                    int v;
                    if(flatBoard[j]==-1) v = j;				//	If fB[j]==-1 => jth cell does not have a ladder or snake => v = j
                    else if(flatBoard[j]!=-1) v = flatBoard[j];	//	Else if fB[j]==-1 => jth cell has a snake or a ladder => v = fB[j];
                    if(!visited[v]) {						//	If v is not visited, push it to the Q and mark it as visited, else continue
                        Q.push(v);
                        visited[v] = 1;
                    }
                }
            }
            minMoves++;										//	When the for loop is exited, the step/level/dist is increased by 1	
        }
        //for(int i=1; i<=V; i++) cout<<i<<"\t"; cout<<"\n";
        //for(int i=1; i<=V; i++) cout<<visited[i]<<"\t"; cout<<"\n";        
        return -1;        									//	The program reaches here only when the destination node is not reached, hence return -1
    }
};