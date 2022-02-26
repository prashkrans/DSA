/* Stack Problem #7 - LC#733. Flood Fill
An image is represented by an m x n integer grid image where image[i][j] represents the pixel value of the image.
You are also given three integers sr, sc, and newColor. You should perform a flood fill on the image starting from the pixel image[sr][sc].
To perform a flood fill, consider the starting pixel, plus any pixels connected 4-directionally to the starting pixel of the same color as 
the starting pixel, plus any pixels connected 4-directionally to those pixels (also with the same color), and so on. Replace the color of 
all of the aforementioned pixels with newColor.
Return the modified image after performing the flood fill.

It can be solved using two methods
1. 	DFS (recursion or using a explicit stack)
2.	BFS 
R.T. = O(N) for both methods
*/

// 	Method 1 - DFS 
//	Running time = O(n*m) or O(N) i.e. linear in no. of pixels N
//	Auxiliary space = O(1) if recursion stack is not included
//					= O(n*m) or O(N) if recursion stack is included

class Solution {
public:
    void DFS(int i, int j, int n, int m, int cC, int nC, vector<vector<int>> &image) {
        if(i<0||i>=n||j<0||j>=m) return;
        if(image[i][j]!=cC||image[i][j]==nC) return;
            image[i][j] = nC;
            DFS(i, j+1, n, m, cC, nC, image);
            DFS(i+1, j, n, m, cC, nC, image);
            DFS(i, j-1, n, m, cC, nC, image);
            DFS(i-1, j, n, m, cC, nC, image);
    }  
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        int n = image.size();
        if(n==0) return {{}};
        int m = image[0].size();
        int currColor = image[sr][sc];
        if(currColor != newColor) DFS(sr, sc, n, m, currColor, newColor, image);
        return image;   //  If (currColor == newColor) => image remains unchanged, hence no need to call the DFS.
    }
};

// 	Method 1 - BFS 
//	Running time = O(n*m) or O(N) i.e. linear in no. of pixels N
//	Auxiliary space = = O(n*m) or O(N) if recursion stack is included

class Solution {
public:
    bool isValid(pair<int, int> v, int n, int m) {
        int i = v.first;
        int j = v.second;
        if(i<0||j<0||i>=n||j>=m) return false;
        else return true;
    }
    void BFS(int i, int j, int n, int m, int cC, int nC, vector<vector<int>> &image) {
        queue<pair<int, int>> Q;    
        map<pair<int, int>, int> visited;
        Q.push({i, j});
        visited[{i, j}] = 1;
        image[i][j] = nC;
        vector<pair<int, int>> nbrs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        while(!Q.empty()) {
            pair<int, int> u = Q.front();
            Q.pop();
            for(auto nbr : nbrs) {
                pair<int, int> v = {u.first + nbr.first, u.second + nbr.second};
                if(isValid(v, n, m) && image[v.first][v.second] == cC && !visited[v]) {
                    visited[v] = 1;
                    image[v.first][v.second] = nC;
                    Q.push(v);
                    cout<<"("<<v.first<<", "<<v.second<<"), ";
                }    
            }
        }
    }
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        int n = image.size();
        int m = image[0].size();
        int currColor = image[sr][sc];
        if(currColor!=newColor) BFS(sr, sc, n, m, currColor, newColor, image);
        return image;
    }
};
