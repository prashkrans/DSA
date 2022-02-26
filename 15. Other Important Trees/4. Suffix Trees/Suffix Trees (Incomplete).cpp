#include<iostream>
using namespace std;

struct node {
	int val;
	vector<node*> edges(26, NULL); // Incorrect. Maybe graph could be used to build the suffix tree
};

int main() {
	string s;
	s = "xabxacy";
	node *curr = new node;
	for(int i=0; i<s.size(); i++) {
		int idx = s[i]-'a';
		if(curr->edges[idx]!=NULL) curr = curr->edges[idx];
		else curr->edges[idx] = new node;
	}
	return 0;
}