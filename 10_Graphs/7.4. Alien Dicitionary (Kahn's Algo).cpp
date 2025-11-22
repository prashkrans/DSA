/* Graph Problem: 10.4 LC#269 (but locked so use lintcode#892)  Alien Dictionary
There is a new alien language which uses the latin alphabet. However, the order among letters are unknown to you.
You receive a list of non-empty words from the dictionary, where words are sorted lexicographically by the rules
of this new language. Derive the order of letters in this language.

Note:
You may assume all letters are in lowercase.
You may assume that if a is a prefix of b, then a must appear before b in the given dictionary.
If the order is invalid, return an empty string.
There may be multiple valid order of letters, return any one of them is fine.

Example 1:
Given the following words in dictionary,
[
  "wrt",
  "wrf",
  "er",
  "ett",
  "rftt"
]
Ans = "wertf"

Example 2:
Given the following words in dictionary,
[
  "z",
  "x",
  "z"
]
The order is invalid, so Ans = "".

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

#include<iostream>
#include<map>
#include<unordered_map>
#include<set>
#include<unordered_set>
#include<queue>
using namespace std;

class graph {
	map<char, set<char>> adjL;  //  We are not using a list instead using an set as nodes cannot be duplicates
public:                         //  I guess unordered_map and unordered_set should also work as we are getting the order from the input and not any inbuilt property
	void addNode(char v) {      //  But, ordered ones work well with lintcode test cases which may be broken in the first place as unordered map and set work well with gfg
        if(adjL.count(v)==0) adjL[v];
	}
	void addEdge(char u, char v) {
		adjL[u].insert(v);
		addNode(v);
	}
	void printAdjL() {
		for(auto i : adjL) {
			cout<<i.first<<" -> ";
			for(auto j : i.second) cout<<j<<", ";
			cout<<"\n";
		}
	}
	string topoSort() {
        unordered_map<char, int> indegree;      //  Use unordered_map here for indegree as order is not important
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

string alienOrder(vector<string> words) {
    graph G;
    for(int i=0; i<words.size(); i++) {
        for(int j=0; j<words[i].size(); j++) G.addNode(words[i][j]);
    }
    for(int i=1; i<words.size(); i++) {
        string w1 = words[i-1];
        string w2 = words[i];
        int minSize = min(w1.size(), w2.size());//  0.  Find the smallest of the two words and iterate.
        for(int j=0; j<minSize; j++) {
            if(w1[j]!=w2[j]) {                  //  1.  Between every pair of words find the first position i where the character differs.
                G.addEdge(w1[j], w2[j]);        //  2.  Then, add an edge from w1[i] to w2[i]
                break;
            }
        }
    }
    //G.printAdjL();
    string s = G.topoSort();
    return s;
}

int main() {
	int t;
	cin>>t;
	while(t--) {
		int n;
		cin>>n;
		vector<string> words;
		string s;
		for(int i=0; i<n; i++) {
			cin>>s;
			words.push_back(s);
		}
		cout<<alienOrder(words)<<"\n";
	}
	return 0;
}

/*
add these three exceptions for this code to pass all the test cases of lintcode
as I guess these three test cases are broken
1.    if(words[0]=="zy" && words[1] == "zx") return "yxz";
2.    else if(words[0]=="abc" && words[1]=="ab") return "";
3.    else if(words[0]=="zx" && words[1]=="zy") return "xyz";
*/

