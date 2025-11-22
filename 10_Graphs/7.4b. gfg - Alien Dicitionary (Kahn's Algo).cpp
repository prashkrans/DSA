/* Graph Problem: 10.4b. LC#269 (but locked so use lintcode#892)  Alien Dictionary
Given a sorted dictionary of an alien language having N words and k starting alphabets of standard dictionary.
Find the order of characters in the alien language.
Note: Many orders may be possible for a particular test case, thus you may return any valid order and output will
be 1 if the order of string returned by the function is correct else 0 denoting incorrect string returned.

gfg - https://practice.geeksforgeeks.org/problems/alien-dictionary/1

Note:
You may assume all letters are in lowercase.
You may assume that if a is a prefix of b, then a must appear before b in the given dictionary.
If the order is invalid, return an empty string.
There may be multiple valid order of letters, return any one of them is fine.

//	This problem could be solved using two methods i.e. Kahn's Algo or using DFS and a stack.
//	Steps:
//  1)  Create a graph g with number of vertices equal to the size of alphabet in the given alien language. For example, if the alphabet size is 5, then there can be 5 characters in words. Initially there are no edges in graph.
//  2)  Do following for every pair of adjacent words in given sorted array.
//          a) Let the current pair of words be word1 and word2. One by one compare characters of both words and find the first mismatching characters.
//          b) Create an edge in g from the first mismatching character of word1 to that of word2.
//  3)  Print topological sorting of the above created graph using either Kahn's Algo or using DFS and a stack.
*/

//  Method 2. Kahn's Algo
//  Running time:
//  n = number of vertices = number of unique characters in the given alien language
//  N = number of words
//  m = number of edge = number of pairs = N-1 => R.T. = O(n+m) = O(n+N-1) [#IMP]
//  Auxiliary space = O(n+m) = O(n+N-1) as we build a graph

#include <bits/stdc++.h>
using namespace std;

class graph {
	unordered_map<char, unordered_set<char>> adjL;  //  We are not using a list instead using an unordered_set as nodes cannot be duplicates
public:
	void addEdge(char u, char v) {
		adjL[u].insert(v);
		if(adjL.count(v)==0) adjL[v];
	}
	void printAdjL() {
		for(auto i : adjL) {
			cout<<i.first<<" -> ";
			for(auto j : i.second) cout<<j<<", ";
			cout<<"\n";
		}
	}
	string topoSort() {
		unordered_map<char, int> indegree;

		queue<char> Q;
		string s;
		int count = 0;
		for(auto i : adjL) indegree[i.first]=0;
		for(auto i : adjL) {
			for(auto v : i.second) indegree[v]++;
		}
		for(auto i : adjL) {
			if(indegree[i.first]==0) Q.push(i.first);
		}
		while(!Q.empty()) {
			char u = Q.front();
			Q.pop();
			s = s + u;
			count++;
			for(auto v : adjL[u]) {
				indegree[v]--;
				if(indegree[v]==0) Q.push(v);
			}
		}
		if(count!=adjL.size()) return "";
		else return s;
	}
};

class Solution{
    public:
    string findOrder(string words[], int N, int K) {
        graph G;
        for(int i=1; i<N; i++) {
            string w1 = words[i-1];
            string w2 = words[i];
            int minSize = min(w1.size(), w2.size());
            for(int j=0; j<minSize; j++) {
                if(w1[j]!=w2[j]) {
                    G.addEdge(w1[j], w2[j]);
                    break;
                }
            }
        }
    //G.printAdjL();
    return G.topoSort();
    }
};

string order;
bool f(string a, string b) {
    int p1 = 0;
    int p2 = 0;
    for (int i = 0; i < min(a.size(), b.size()) and p1 == p2; i++) {
        p1 = order.find(a[i]);
        p2 = order.find(b[i]);
        //	cout<<p1<<" "<<p2<<endl;
    }

    if (p1 == p2 and a.size() != b.size()) return a.size() < b.size();

    return p1 < p2;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int N, K;
        cin >> N >> K;
        string dict[N];
        for (int i = 0; i < N; i++) cin >> dict[i];

        Solution obj;
        string ans = obj.findOrder(dict, N, K);
        order = "";
        for (int i = 0; i < ans.size(); i++) order += ans[i];

        string temp[N];
        std::copy(dict, dict + N, temp);
        sort(temp, temp + N, f);

        bool f = true;
        for (int i = 0; i < N; i++)
            if (dict[i] != temp[i]) f = false;

        if(f)cout << 1;
        else cout << 0;
        cout << endl;
    }
    return 0;
}

/* Sample input
2
5 4
baa abcd abca cab cada
3 2 aba bba aaa
*/
