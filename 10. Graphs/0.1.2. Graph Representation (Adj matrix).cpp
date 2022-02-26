//  Adjacency matrix is always a square matrix i.e. of size(n x n)

#include<iostream>
#include<vector>
using namespace std;

class graph {
	vector<vector<int>> adjMat;
	public:
	graph(vector<vector<int>> mat) {
	    adjMat = mat;
	}
	void printAdjMat() {
		for(int i=0; i<adjMat.size(); i++) {
			cout<<"Vertex "<<i<<" is connected to vertices: ";
			for(int j=0; j<adjMat[0].size(); j++) {
				if(adjMat[i][j] > 0) cout<<"("<<j<<", "<<adjMat[i][j]<<") ";
			}
			cout<<"\n";
		}
	}
	void update(int i, int j, int weight) {
	    adjMat[i][j] = weight;
	}
};


int main() {
	int n;
	//cin>>m;
	n = 5;
	vector<vector<int>> mat(n, vector<int>(n));
	//for(int i=0; i<m; i++)
	//	for(int j=0; j<n; j++) cin>>mat[i][j];
	mat = {{0, 200, 100, 0, 400}, {100, 0, 0, 200, 0,}, {200, 400, 0, 0, 500}, {0, 0, 300, 0, 800}, {200, 100, 400, 500, 0}};
	cout<<"The adjacency matrix is = \n";
	for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) cout<<mat[i][j]<<" ";
        cout<<"\n";
	}
	graph G(mat);
	G.printAdjMat();
	G.update(2, 4, 200);
	G.update(1, 4, 300);
	G.update(0, 1, 100);
	G.update(3, 2, 0);
	cout<<"After modifying the edges of the graph: \n";
	G.printAdjMat();
	return 0;
}
