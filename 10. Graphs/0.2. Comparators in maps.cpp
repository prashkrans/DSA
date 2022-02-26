/* Comparators in maps:

Note: Only if the key is a custom data type, comparators are used else if key is a standard data type like
int, double or even pair<dt1, dt2> there is no need to use a comparator.
Thus, if key is a standard data type and value is a used defined data type there is no need to use a
comparator.

a. Ordered Maps
If we are using custom data types i.e. structures in a map then it is mandatory to use class cmp while
declaring the map.

b. Unordered Maps
We can use custom data types i.e. structures in an unordered_map but the process is tedious.
So, as a rule of thumb just use ordered maps with cmp to work with user defined data types.
*/

#include<bits/stdc++.h>
using namespace std;

struct node {
    int val;
    string clr;
};

class cmp {
public:
    bool operator() (node a, node b) const {
        return a.val < b.val;				//	 Ascending order of val
    }
};

int main() {
	map<node, list<node>, cmp> adjL;        //  map<node, list<node>> adjL
	map<node, int, cmp> visited;            //  map<node, int> visited      => Both lines won't work without cmp class
	adjL[{1, "Blue"}].push_back({2, "Red"});
	adjL[{1, "Blue"}].push_back({3, "Green"});
	adjL[{2, "Red"}];
	adjL[{3, "Green"}];
	for(auto u : adjL) {
        cout<<u.first.val<<", "<<u.first.clr<<" -> ";
        for(auto v : u.second) cout<<v.val<<", "<<v.clr<<" | ";
        cout<<"\n";
	}
	cout<<"Visited: \n";
	visited[{1, "Blue"}] = 1;
	visited[{2, "Red"}] = 0;
	visited[{3, "Green"}] = 1;
	for(auto v : visited) cout<<v.first.val<<", "<<v.first.clr<<" -> "<<v.second<<"\n";
	//unordered_map<node, list<node>> adjL2;
	//unordered_map<node, int> visited;
	return 0;
}

