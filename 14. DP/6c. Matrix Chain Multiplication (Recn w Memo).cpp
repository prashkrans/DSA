/* DP-Problem 6 - MCM using Recursion and Memoization
GFG - https://www.geeksforgeeks.org/matrix-chain-multiplication-dp-8/

//  Running time = O(n^3) (cubic) same as that of tabulation {exponential without memoization}
//  Space Complexity = O(n^2) same as that of tabulation
*/
#include<iostream>
using namespace std;

int MCMorder(int d[], int i, int j, int DP[100][100]){
	if(DP[i][j] != -1) return DP[i][j];
	if(i==j){
        DP[i][j]=0;    // Base Cases
        return DP[i][j];
	}
	int minVal = INT_MAX;
	for(int k=i; k<j; k++){								// Only write the small calculation part for (1, n) and let recursion handle the rest
		int kVal = MCMorder(d, i, k, DP) + MCMorder(d, k+1, j, DP) + d[i-1]*d[k]*d[j];	// k+1 increases the value of i
		if(kVal<minVal) minVal = kVal;
	}
	DP[i][j] = minVal;
	return DP[i][j];
}

int main(){
	int d[5];
	d[0] = 3;
	d[1] = 2;
	d[2] = 4;
	d[3] = 2;
	d[4] = 5;
	int n = 4;
	int DP[100][100]; // Not using the 0th row and column
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++) DP[i][j] = -1;
	}
	int i=1;
	int j=n;
	cout<<"The minimum cost of MCM = "<<MCMorder(d, i, j, DP)<<"\n";
	for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            cout<<DP[i][j]<<" ";
        }
        cout<<"\n";
	}
	cout<<"Wanna input custom values? (y/n)\n";
    char input = 'y';
    cin>>input;
    while(input=='y'){
        cout<<"Enter the the number of matrices = \n";
        cin>>n;
        int d2[n+1];
        cout<<"Enter the dimensions of the matrices as array (size == n+1) = \n";
        for(int i=0; i<=n; i++){
            int val;
            cin>>val;
            d2[i] = val;
        }
        for(int i=1; i<=n; i++){
            for(int j=1; j<=n; j++) DP[i][j] = -1;
        }
        int minCost = MCMorder(d2, 1, n, DP);
        cout<<"The minimum cost of the given MCM = "<<minCost<<"\n";
        for(int i=1; i<=n; i++){
            for(int j=1; j<=n; j++){
                cout<<DP[i][j]<<" ";
            }
        cout<<"\n";
        }
        cout<<"Wanna continue? => (y/n) = \n";
        cin>>input;
    }

	return 0;
}
