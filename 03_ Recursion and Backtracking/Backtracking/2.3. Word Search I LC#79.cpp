/**
LC#79. Word Search

**/

// Method 1: Backtracking DFS
// Running time: O(n*m*4^l) as each cell has four options and we search cells upto a length of 4.
// Auxiliary space: O(n*m) due to the visited map or 2D array
// where n = no. of rows, m = no. of cols and l = length of the word to be searched

class Solution {
    // This is a different dfs since we are backtracking we need to make visited[{i, j}] = 0 when its processed.
    bool dfsBacktrack(int i, int j, int n, int m, vector<vector<char>> &board, string word, map<pair<int, int>, int> &visited) {
        if(word.empty()) return true;
        else if(i<0 || i==n || j<0 || j==m) return false;
        else if(visited[{i, j}]) return false; 
        else {
            if(word[0] != board[i][j]) return false;
            visited[{i, j}] = 1;
            bool result = (
                dfsBacktrack(i, j+1, n, m, board, word.substr(1), visited) 
                || dfsBacktrack(i+1, j, n, m, board, word.substr(1), visited) 
                || dfsBacktrack(i, j-1, n, m, board, word.substr(1), visited) 
                || dfsBacktrack(i-1, j, n, m, board, word.substr(1), visited) // Don't put || after the last comparison
            );
            visited[{i, j}] = 0; // Backtracking - [#IMP]
            return result;
        }
    }

public:
    bool exist(vector<vector<char>>& board, string word) {
        int n = board.size();
        int m = board[0].size();
        map<pair<int, int>, int> visited;
        for(int i=0; i<n; i++) {
            for(int j=0; j<m; j++) {
                if(!visited[{i, j}]) {
                    if(dfsBacktrack(i, j, n, m, board, word, visited)) return true;
                }
            }
        }
        return false;
    }
};

