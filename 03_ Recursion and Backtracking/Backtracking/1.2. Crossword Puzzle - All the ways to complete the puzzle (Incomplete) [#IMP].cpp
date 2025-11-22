#include <bits/stdc++.h>
using namespace std;

void print(vector<string> cw) {
    int n = cw.size();
    for(int i=0; i<n; i++)
        cout<<cw[i]<<"\n";
    cout<<"\n";
}

bool canPlaceHorizontally(vector<string> &cw, string currWord, int i, int j) {
    int n = cw.size();
    if(j-1>=0 && cw[i][j-1]!='+') return false;
    if(j+currWord.size() < n && cw[i][j+currWord.size()]!='+') return false;
    for(int x=0; x<currWord.size(); x++) {
        if(j+x >= n) return false;
        if(cw[i][j+x]=='-' || cw[i][j+x]==currWord[x]) continue;
        else return false;
    }
    return true;
}

vector<bool> placeHorizontally(vector<string> &cw, string currWord, int i, int j) {
    vector<bool> placeArr(currWord.size(), 0);
    for(int k=0; k<currWord.size(); k++) {
        if(cw[i][j+k]=='-') {
            placeArr[k] = true;
            cw[i][j+k] = currWord[k];
        }
        else placeArr[k] = false;
    }
    return placeArr;
}

void unplaceHorizontally(vector<string> &cw, int i, int j, vector<bool> placeArr) {
    for(int k=0; k<placeArr.size(); k++) {
        if(placeArr[k]==1) cw[i][j+k] = '-';
    }
}

bool canPlaceVertically(vector<string> &cw, string currWord, int i, int j) {
    int n = cw.size();
    if(i-1>=0 && cw[i-1][j]!='+') return false;
    if(i+currWord.size() < n && cw[i+currWord.size()][j]!='+') return false;
    for(int x=0; x<currWord.size(); x++) {
        if(i+x >= n) return false;
        if(cw[i+x][j]=='-' || cw[i+x][j]==currWord[x]) continue;
        else return false;
    }
    return true;
}

vector<bool> placeVertically(vector<string> &cw, string currWord, int i, int j) {
    vector<bool> placeArr(currWord.size(), 0);
    for(int k=0; k<currWord.size(); k++) {
        if(cw[i+k][j]=='-') {
            placeArr[k] = true;
            cw[i+k][j] = currWord[k];
        }
        else placeArr[k] = false;
    }
    return placeArr;
}

void unplaceVertically(vector<string> &cw, int i, int j, vector<bool> placeArr) {
    for(int k=0; k<placeArr.size(); k++) {
        if(placeArr[k]==1) cw[i+k][j] = '-';
    }
}

bool rec(vector<string> &cw, vector<string> words, int index) {
    //cout<<"index = "<<index<<" w.size() = "<<words.size()<<"\n";
    if(index == words.size()) {
        //print(cw);
        return true;
    }
    string currWord = words[index];
    bool h = false, v = false;
    int n = cw.size();
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            if(cw[i][j]=='-' || cw[i][j]==currWord[0]) {
                if(canPlaceHorizontally(cw, currWord, i, j)) {
                    vector<bool> placeArr = placeHorizontally(cw, currWord, i, j);
                    h = rec(cw, words, index+1);                                //  Recursive call
                    if(h) return true;
                    unplaceHorizontally(cw, i, j, placeArr);                //  Backtracking
                }
                if(canPlaceVertically(cw, currWord, i, j)) {
                    vector<bool> placeArr = placeVertically(cw, currWord, i, j);
                    v = rec(cw, words, index+1);
                    if(v) return true;
                    unplaceVertically(cw, i, j, placeArr);
                }
            }
        }
    }
    return false;
}

vector<string> crosswordPuzzle(vector<string> crossword, string w) {
    vector<string> words;
    int x, k = 0;
    for(x=0; x<w.size(); x++) {
        if(w[x]==';') {
            words.push_back(w.substr(k, x-k));
            k = x+1;
        }
    }
    words.push_back(w.substr(k, w.size()-k));
    //cout<<"Words:\t"; for(auto i : words) cout<<i<<"\t"; cout<<"\n";
    rec(crossword, words, 0);
    return crossword;
}

int main() {
    int n = 10;
    vector<string> crossword;
    string w, s;
    for(int i=0; i<n; i++) {
        cin>>s;
        crossword.push_back(s);
    }
    cin>>w;
    vector<string> cw = crosswordPuzzle(crossword, w);
    print(cw);
    return 0;
}

/* Sample input:
+-++++++++
+-++++++++
+-------++
+-++++++++
+-++++++++
+------+++
+-+++-++++
+++++-++++
+++++-++++
++++++++++
AGRA;NORWAY;ENGLAND;GWALIOR

++++++-+++
++------++
++++++-+++
++++++-+++
+++------+
++++++-+-+
++++++-+-+
++++++++-+
++++++++-+
++++++++-+
ICELAND;MEXICO;PANAMA;ALMATY
*/
