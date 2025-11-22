/* DP Prob. 29.2. Number of ordered ways to reach a target
This variation is easier than Prob. 29.1. which did not allow ordered pairs
*/

#include<iostream>
#include<map>
#include<vector>
using namespace std;

//	Method 1. Recursion without memoization (Top down approach)
//	Running time = O(k*k*...*k) = O(k^k) i.e. exponential time thus, highly inefficient
//  n^n has a higher order of growth than n! as illustrated below:
//  n! = n * (n-1) * (n-2) * ... * 2 * 1
//  n^n = n * n * n * n * ... * n * n
//	Auxiliary space = O(k^k) due to the recursion stack

int rec(int n, int k) {
	if(n<0) return 0;
	if(n==0) return 1;
	int sum = 0;
	for(int i=1; i<=k; i++) sum += rec(n-i, k);
	return sum;
}

//	Method 2. Recursion with memoization = DP (Top down approach)
//	Running time = O(n*k) i.e. quadratic time hence, better than method 1 [Verify]
//  I guess R.T. = O(n*k) as n varies from 0 to N while k varies from 1 to K
//	Auxiliary space = O(n) due to the array DP which is less than O(n*k) for Prob. 29.1.

int recDP(int n, int k, map<int, int> &DP) {
	if(n<0) return 0;
	if(n==0) return 1;
	if(DP.count(n)>0) return DP[n];
	int sum = 0;
	for(int i=1; i<=k; i++)
        sum += rec(n-i, k);                     //  Note: i starts from i = 1 but in each recursive call
	DP[n] = sum;                                //  This ensures that 1 + 2 + 2 = 5 is valid as well as 2 + 2 + 1 = 5 is also valid
	return DP[n];                               //  i.e. allows ordered sequence unlike in Prob. 29.1.
}

//	Method 3. DP (Bottom Up approach - Iterative)
//	Running time = O(n*k) i.e. quadratic time hence, better than method 1 [Verified]
//  R.T. = O(n*k) as n varies from 1 to N while k varies from 1 to K in a nested loop
//	Auxiliary space = O(n) due to the array DP which is less than O(n*k) for Prob. 29.1.

int botUpDP(int n, int k, vector<int> &DP) {    //  We are building the DP table starting from DP[1] to DP[n]
    for(int i=1; i<=n; i++) {                   //  given DP[0] = 1 and taking care of DP[-ve]
        for(int j=1; j<=k; j++) {
            if(i-j<0) break;                    //  [#IMP] as negative indices do not exist
            DP[i] += DP[i-j];                   //  The same formula which is used in method 1 and method 2
        }                                       //  Two for loops nested thus R.T. = O(n*k)
    }
    return DP[n];
}

int numOfWays(int n, int k) {
	int method1 = rec(n, k);
	map<int, int> DP;
	int method2 = recDP(n, k, DP);
	vector<int> DP2(n+1, 0);
	DP2[0] = 1;
	int method3 = botUpDP(n, k, DP2);
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

20 9
*/
