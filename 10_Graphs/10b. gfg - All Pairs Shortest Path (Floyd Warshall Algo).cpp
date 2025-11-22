/* Graph problem - #13b. All Pairs Shortest Path using Floyd-Warshall Algorithm
The problem is to find shortest distances between every pair of vertices in a given edge weighted
directed graph. The graph is represented as adjancency matrix, and the matrix denotes the weight
of the edegs (if it exists) else -1 (not INT_MAX). Do it in-place i.e. auxiliary space = O(1)
gfg - https://practice.geeksforgeeks.org/problems/implementing-floyd-warshall2042/1#
*/

//	Method 1 - Floyd-Warshall Algorithm
//	Running time = O(n^3) i.e. cubic where n = the no. of vertices
//	Auxiliary space = O(1)

#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
	void shortest_distance(vector<vector<int>>&d) {
	    int n = d.size();
	    for(int k=0; k<n; k++) {
	        for(int i=0; i<n; i++) {
	            for(int j=0; j<n; j++) {
	                if(d[i][k] != -1 && d[k][j] != -1) {
	                    if(d[i][j] == -1) d[i][j] = d[i][k] + d[k][j];
	                    else if(d[i][j] > d[i][k] + d[k][j]) d[i][j] = d[i][k] + d[k][j];
	                }
	            }
	        }
	    }
    }
};

int main(){
	int tc;
	cin >> tc;
	while(tc--){
		int n;
		cin >> n;
		vector<vector<int>>matrix(n, vector<int>(n, -1));
		/*for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				cin >> matrix[i][j];
			}
		}*/
		//matrix = {{1, 2}, {3, 4}};
		matrix =   {{0,4,2,1,2,9,4,8,-1,4,-1,-1},
            {9,0,3,6,2,6,2,3,6,-1,-1,3},
            {7,1,0,10,8,9,1,3,-1,7,-1,10},
            {5,1,9,0,3,-1,1,10,7,1,-1,7},
            {-1,5,1,4,0,2,10,4,10,6,4,5},
            {7,8,3,7,5,0,5,1,3,5,7,2},
            {6,-1,6,1,10,7,0,10,-1,-1,7,7},
            {-1,3,2,7,4,-1,4,0,10,5,6,10},
            {10,6,1,10,4,4,7,10,0,4,7,4},
            {1,1,6,8,8,9,2,10,6,0,-1,3},
            {5,9,3,-1,4,3,-1,-1,-1,3,0,1},
            {2,2,8,6,2,4,4,3,-1,3,4,0}};
		Solution obj;
		obj.shortest_distance(matrix);
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				cout << matrix[i][j] << " ";
			}
			cout << "\n";
		}
	}
	return 0;
}
