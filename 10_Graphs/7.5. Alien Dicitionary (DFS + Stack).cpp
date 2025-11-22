/* Graph Problem: 10.5. LC#269 (but locked so use lintcode#892)  Alien Dictionary [Verified]
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

//  Method 1. DFS + 2 Stacks (1. To find out if the graph is cyclic & 2. To store the topological sort)
//  Running time:
//  n = number of vertices = number of unique characters in the given alien language. So, insertion takes O(n) time as we are using an unordered_set
//  N = number of words
//  m = number of edges = number of pairs = N-1 => R.T. = O(n+m) = O(n+N-1) [#IMP]
//  Auxiliary space = O(n+m) = O(n+N-1) as we build a graph

#include<iostream>
#include<unordered_map>
#include<unordered_set>
#include<stack>
#include<vector>
using namespace std;

class graph {
	unordered_map<char, unordered_set<char>> adjL;  //  We are not using a list instead using an set as nodes cannot be duplicates
public:                                             //  Verified that unordered_map and unordered_set work properly as we are getting the order from the input and not any inbuilt property
	void addNode(char v) {                          //  Verified in gfg practice problem. However, ordered map and set would also work just fine
        if(adjL.count(v)==0) adjL[v];               //  Another way to add a node is adjL[v] = set<char>();
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
	bool DFS(char u, unordered_map<char, int> &visited, stack<char> &TSstack, unordered_map<char, int> &cycleStack) {
        visited[u] = 1;
        cycleStack[u] = 1;
        for(auto v : adjL[u]) {
            if(!visited[v]) {					//	Note: The {} brackets are important here, else use (visited[v] && DFS(v, visited, TS, cS)==0)
				if(DFS(v, visited, TSstack, cycleStack)==0) return 0;
			}
            else if(cycleStack[v]==1) return 0;
        }
        cycleStack[u] = 0;
        TSstack.push(u);
        return 1;
	}
	string topoSort() {
        unordered_map<char, int> visited;
        unordered_map<char, int> cycleStack;    //  The two stacks are the important here, a. cycleStack is used to find out whether the graph is cyclic or not
        stack<char> TSstack;                    //  b.  TSstack is used to store the topological sort
        string str;                             //  So, it uses two concepts 1. find a cycle in a directed graph and 2. get the topological sort, both using the same DFS [#IMP]
        bool isDAG;
        for(auto i : adjL) {                    //  Using a for loop since the graph so obtained may not be a strongly connected graph or even a connected graph.
            char src = i.first;
            if(!visited[src]) {
				isDAG = DFS(src, visited, TSstack, cycleStack);
				if(!isDAG) break;                   //  If even a part of a graph is cyclic, we stop.
			}
        }
        if(isDAG) {
            while(!TSstack.empty()) {
                str = str + TSstack.top();
                TSstack.pop();
            }
        }
        return str;
	}
};

string alienOrder(vector<string> words) {
    graph G;
    for(int i=0; i<words.size(); i++) {
        for(int j=0; j<words[i].size(); j++) G.addNode(words[i][j]);    //  This is important as there can be nodes without any edges either incoming or outgoing i.e. a disconnected graph
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
