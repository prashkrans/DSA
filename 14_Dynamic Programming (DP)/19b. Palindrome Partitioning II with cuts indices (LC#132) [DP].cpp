/* DP Problem 19 - Palindrome Partitioning II (LC#132)*/

//	Running time = O(n^3) i.e. cubic
//	Auxiliary space = O(n^2)

#include<iostream>
#include<vector>
using namespace std;

bool isPalin(string s, int i, int j) {	//	Can also use a bool matrix storing the values if substr(i, j) is a palindrome as in method 2
    int n = j-i+1;
    string str = s.substr(i, n);
    for(int k=0; k<n/2; k++) {
		if(str[k]!=str[n-1-k]) return false;
	}
	return true;
}

void cutsIndices(int i, int j, vector<vector<int>> &K, vector<int> &cuts) {
    if(K[i][j] == -1) return ;
    else {
        cuts.push_back(K[i][j]);
        cutsIndices(i, K[i][j], K, cuts);
        cutsIndices(K[i][j]+1, j, K, cuts);
    }
    //cout<<"Hello World\n";
    return;
}

int palinPartitionMin(string s) {
	int n = s.size();
	vector<vector<int>> DP(n, vector<int>(n));
	vector<vector<int>> K(n, vector<int>(n));
	for(int len = 1; len<=n; len++) {
        for(int i=0; i<n-len+1; i++) {
            int j = i+len-1;
            if(isPalin(s, i, j)) {
                DP[i][j] = 0;
                K[i][j] = -1;
            }
            else {
                int minVal = INT_MAX;
                int kVal = -1;
                for(int k=i; k<j; k++) {
                    int val = DP[i][k] + 1 + DP[k+1][j];
                    if(val < minVal) {
                        minVal = val;
                        kVal = k;
                    }
                }
            DP[i][j] = minVal;
            K[i][j] = kVal;
            }
        }
	}
	cout<<"DP table = \n";
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) cout<<DP[i][j]<<" ";
        cout<<"\n";
	}
	cout<<"K table = \n";
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) cout<<K[i][j]<<" ";
        cout<<"\n";
	}
	vector<int> cuts;
    cutsIndices(0, n-1, K, cuts);
    if(!cuts.empty()) {
        cout<<"The cuts are made at the following indices = ";
        for(int i=0; i<cuts.size(); i++) cout<<cuts[i]+1<<" ";
        cout<<"\n";
        cout<<"The cuts are made as follows = ";
        int k = 0;
        for(int i=0; i<n; i++){
            cout<<s[i];
            if(i==cuts[k]) {
                cout<<"|";
                k++;
            }
        }
        cout<<"\n";
    }
	cout<<"Thus, the minimum no. of cuts required are = ";
	return DP[0][n-1];
}

int main() {
	string s;
	cin>>s;
	//vector<string> ans = palinPartitionMin(s);
	cout<<palinPartitionMin(s);
	return 0;
}
