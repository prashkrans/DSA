/* DP Prob. 29.1. Number of unordered ways (sorted order) to reach a target
This variation is slightly trickier than Prob. 29.2. which allows ordered pairs
*/

#include<iostream>
#include<map>
#include<vector>
#include<cmath>
using namespace std;

//	Method 1. Recursion without memoization (Top down approach)
//	Running time = O(k*(k-1)*(k-2)*...*1) = O(k!) i.e. factorial time thus, highly inefficient
//	Auxiliary space = O(k!) due to the recursion stack

int rec(int n, int k, int start) {
	if(n<0) return 0;
	if(n==0) return 1;
	int sum = 0;
	for(int i=start; i<=k; i++) sum += rec(n-i, k, i);
	return sum;
}

//	Method 2. Recursion with memoization = DP (Top down approach)
//	Running time = O(n*k) i.e. quadratic hence, better than method 1 [Verify]
//  I guess R.T. = O(n*k) as n varies from 0 to N while k varies from 1 to K
//	Auxiliary space = O(n*k) due to the map/table DP

int recDP(int n, int k, int start, map<pair<int, int>, int> &DP) {
	if(n<0) return 0;
	if(n==0) return 1;
	if(DP.count({n, start})>0) return DP[{n, start}];
	int sum = 0;
	for(int i=start; i<=k; i++)
        sum += rec(n-i, k, i);                              //  Note: i does not start from i = 1 but from the start value
	DP[{n, start}] = sum;                                   //  This ensures that 1 + 2 + 2 = 5 is valid but not 2 + 2 + 1 = 5
	return DP[{n, start}];                                  //  i.e. does not allow ordered sequence
}

//	Method 3. DP (Bottom Up approach - Iterative) (#Incomplete)
//	Running time = O(n*k) i.e. quadratic time hence, better than method 1 [Verified]
//  R.T. = O(n*k) as n varies from 1 to N while k varies from 1 to K in a nested loop
//	Auxiliary space = O(n) due to the array DP which is less than O(n*k) for Prob. 29.1.

int botUpDP(int n, int k, vector<int> &DP, int start) {     //  Complete it later as it is incorrect
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=k; j++) {
            if(i-j<0) break;
            //if(i-j<j) break;
            DP[i] += DP[i-j];                               //  Currently it gives the count for ordered sequence i.e. Same as prob 29.2.
        }
    }
    return DP[n];
}

int numOfWays(int n, int k) {
	int method1 = rec(n, k, 1);
	map<pair<int, int>, int> DP;
	int method2 = recDP(n, k, 1, DP);
	//vector<vector<int>> DP2(n, vector<int>(k, 0));
	vector<int> DP2(n+1, 0);
	DP2[0] = 1;
	int method3 = botUpDP(n, k, DP2, 1);
	cout<<"Ans: "<<method1<<" == "<<method2<<" == "<<method3<<"\n";
	return method2;
}

int main() {
	int n, k;
	cin>>n>>k;
	numOfWays(n, k);
	return 0;
}

/* Sample input:
5 3

100 4
*/
