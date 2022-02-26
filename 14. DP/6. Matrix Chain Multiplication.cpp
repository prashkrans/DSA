/* DP-Problem 6
GFG - https://www.geeksforgeeks.org/matrix-chain-multiplication-dp-8/
Given an array d[] which represents the chain of matrices such that the ith matrix Ai is of dimension d[i-1] x d[i].
Write a function matrixChainMultiplication() that should return the minimum number of multiplications needed to multiply the chain.
Example 1 -
Input: p[] = {40, 20, 30, 10, 30}
Output: 26000
There are 4 matrices of dimensions 40x20, 20x30, 30x10 and 10x30.
Let the input 4 matrices be A, B, C and D.  The minimum number of
multiplications are obtained by putting parenthesis in following way
(A(BC))D --> 20*30*10 + 40*20*10 + 40*10*30
*/
//  Running time = O(n^3) (cubic) {exponential without memoization}
//  Space Complexity = O(n^2)

#include<iostream>
#include<vector>
using namespace std;

int matrixChainMultiplication(vector<int> d, int n){    //  For simplicity of the program, one extra row and one extra column are allocated in cost and kVal.
	vector<vector<int>> cost(n+1, vector<int>(n+1));  	//	0th row and 0th column of cost and kVal are not used and hence (i,j) begin from (1,1)
	vector<vector<int>> kVal(n+1, vector<int>(n+1));    //  The DP table is named cost & kVal table is only used only when we need to print the order of parenthesization
	for(int i=0; i<=n; i++) cost[i][i] = 0;			    //	Base cases
	int i = 1; int j = 1;
	for(int diff = 1; diff<n; diff++){                  //  Using the difference between to i and j to iterate diagonally in the DP table. It varies between 1 to n-1
		i = 1;                                          //  i is made 1 again after all the entries in a diagonal is calcd to move to the next diagonal
		j = i + diff;                                   //  j is ahead of i
		while(j<=n){
			int minVal = INT_MAX;
			int kMin;                                   //  k varies from i to j-1 i.e. j-i choices for k
			for(int k = i; k<j; k++){                   //  Three nested loops hence the time required is O(n^3)
				int kCost = cost[i][k] + cost[k+1][j] + d[i-1]*d[k]*d[j];
				if(kCost<minVal) {
					minVal = kCost;
					kMin = k;
                }
			}
			cost[i][j] = minVal;
			kVal[i][j] = kMin;
			i++; j++;                                   //  Moving diagonally down (i, j) to (i+1, j+1)
		}
	}
	cout<<"Cost Table = \n";
	for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++) cout<<cost[i][j]<<" ";
        cout<<"\n";
	}
	cout<<"kVal Table = \n";
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++) cout<<kVal[i][j]<<" ";
        cout<<"\n";
	}
	return cost[1][n];                                  // The final result is stored in the last column of the row with i = 1;
}



int main(){
	vector<int> d(5);// n = 5-1 = 4
	int n = 4;
	d[0] = 3;
	d[1] = 2;
	d[2] = 4;
	d[3] = 2;
	d[4] = 5;
    int minCost = matrixChainMultiplication(d, n);
    cout<<"The minimum cost of MCM1 = \n"<<minCost<<"\n";
    cout<<"Wanna input custom values? (y/n)\n";
    char input = 'y';
    cin>>input;
    while(input=='y'){
        cout<<"Enter the the number of matrices = \n";
        cin>>n;
        vector<int> d2(n+1);
        cout<<"Enter the dimensions of the matrices as array (size == n+1) = \n";
        for(int i=0; i<=n; i++){
            int val;
            cin>>val;
            d2[i] = val;
        }
        minCost = matrixChainMultiplication(d2, n);
        cout<<"The minimum cost of the given MCM = \n"<<minCost<<"\n";
        cout<<"Wanna continue? => (y/n) = \n";
        cin>>input;
    }
	return 0;
}

/* To print the order of parenthesis. NOT VERIFIED but the idea seems correct
cout<<"The order of parenthesis with minimum cost = \n";
	string pOrder;
	for(int i=0; i<n; i++){
        char ch = i+1+'0';
        pOrder = pOrder + ch;
	}
	cout<<pOrder<<"\n";
	j = n;
	int incSize = 0;
    while(j>2){
        int pos = kVal[1][j];
        pOrder = pOrder.substr(0, pos+incSize) + ")" + pOrder.substr(pos+incSize);
        pOrder = "(" + pOrder;
        incSize += 1;
        j--;
    }
    cout<<pOrder<<"\n";
    */
