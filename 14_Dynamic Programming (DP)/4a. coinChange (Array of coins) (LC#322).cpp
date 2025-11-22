/* DP-Problem 4 (LC#322) : Coin Change
You are given coins of different denominations and a total amount of money amount. Write a function to compute
the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by
any combination of the coins, return -1.
You may assume that you have an infinite number of each kind of coin.

Example 1:
Input: coins = [1,2,5], amount = 11
Output: 3


// Recursion Algo : return 1+minOf(func(n-coin1), func(n-coin2), ..., func(n-coinM)

*/

//  1.  Dynamic programming - Top down. Using a DP array.
//      Running Time = O(n*c) where n is the amount and c is the total no. of different coins.
//      Space complexity : O(n), where n is the amount to change. We use extra space for the memoization array.

#include<iostream>
#include<algorithm>
using namespace std;

void printArr(int a[], int n){
    for(int i=0; i<n; i++) cout<<a[i]<<" ";
    cout<<"\n";
}

int coinChange(int c[], int n, int DP[], int cSize){
	if(n<0) return INT_MAX; // Don't write DP[n] = INT_MAX-1 as n is negative and DP[n] does not exist
	else if(n==0) DP[n] = 0;
	else if(DP[n] == -5){
		int noOfRec[cSize];
		int minVal = INT_MAX;
		for(int i=0; i<cSize; i++){
			noOfRec[i] = coinChange(c, n-c[i], DP, cSize);
			if(noOfRec[i]<minVal) minVal = noOfRec[i];
		}
		if(minVal==INT_MAX) DP[n] = INT_MAX;
		else DP[n] = 1 + minVal; // The value 1 represents the cost of adding a coin
		//int ans = 1 + minOf3(coinChange(n-1), coinChange(n-2), coinChange(n-5)); 	//	Without memoization
	}
	return DP[n];
}


int main(){
	int n;
	char input = 'y';
	cout<<"The available coins are = \n";
	int c[3];
	c[0] = 1, c[1] = 2; c[2] = 5;
    c[0] = 45, c[1] = 71; c[2] = 101;
	int cSize = 3;
    printArr(c, cSize);
	while(input=='y'){
		cout<<"Enter the value of n (0 to 10000) = \n";
		cin>>n;
		int DP[n+1];        // Size of DP array is n+1 i.e. 0 to n
		for(int i=0; i<=n; i++) DP[i] = -5;     //  a value of DP[i] = -5 would represent that DP[i] is yet to be calculated
		//printArr(DP, n+1);
		int ans = coinChange(c, n, DP, cSize);
		if (ans == INT_MAX) ans = -1;
		cout<<"Printing the coinChange(i) for i = 0 to n : \n";
		cout<<"i    "<<"coinChange(i)\n";
		for(int i=0; i<=n; i++){
            cout<<i<<"      "<<DP[i]<<"\n";
		}
		cout<<"The minimum number of coins required are = "<<ans<<"\n";
		cout<<"Wanna continue? => coinChange() (y/n) = ";
		cin>>input;
	}
	return 0;
}

//	2.	Dynamic programming - Bottom Up. 
//	2a. Using 2D DP table - 
//		Running time = O(n*c)
// 		Space Comlexity = O(n*c)
class Solution {
public:
    int coinChange(vector<int>& coins, int n) {
        if(n==0) return 0;
        int m = coins.size();
        vector<vector<int>> DP(n, vector<int>(m+1));
        for(int i = 0; i<n; i++){
            int min = INT_MAX-1;
            for(int j = 0; j<m; j++){
                int val = (i+1)-coins[j]; // At i = 0, the value of the amount should be i+1
                if(val==0) DP[i][j] = 0;
                else if(val<0) DP[i][j] = INT_MAX-1;
                else if(val>0) DP[i][j] = DP[val-1][m];
                if(DP[i][j]<min) min = DP[i][j];
            }
            DP[i][m] = 1 + min; 
        }
        return (DP[n-1][m]==INT_MAX)?-1:DP[n-1][m];
    }
};

// 	2b.	#(Best Solution) Now, there is no actual need to create a 2D DP array for the same approach. We just to need store the previous element 
// 		in a row in a another varable say minVal. Hence an improved Bottom Up approach is given below.
//		Running time = O(n*c) {83%}
// 		Space Comlexity = O(n) {66%}
class Solution {
public:
    int coinChange(vector<int>& coins, int n) {
       if(n==0) return 0;
        vector<int> DP(n+1);
        DP[0] = 0;		// Base Case
        for(int i=1; i<=n; i++){
            int minVal = INT_MAX-1;
            for(int j=0; j<coins.size(); j++){
                if(i>=coins[j]){
                    if(DP[i-coins[j]]<minVal) minVal = DP[i-coins[j]];
                }
            }
            DP[i] = 1 + minVal;
        }
        return (DP[n]==INT_MAX)?-1:DP[n];
    }
};

//  3.  Dynamic programming - Top down. Using a DP vector.
//      Running Time = O(n*c) where n is the amount and c == cSize i.e. the total no. of different coins.
//      Space complexity = O(n), where n is the amount to change. We use extra space for the memoization array.

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

void printArr(vector<int> a){
    int n = a.size();
    for(int i=0; i<n; i++) cout<<a[i]<<" ";
    cout<<"\n";
}

int coinChange(vector<int> &c, int n, vector<int> &DP){
	if(n<0) return INT_MAX; // Don't write DP[n] = INT_MAX-1 as n is negative and DP[n] does not exist
	else if(n==0) DP[n] = 0;
	else if(DP[n] == 0){
		vector<int> noOfRec(c.size());
		int minVal = INT_MAX;
		for(int i=0; i<c.size(); i++){
			noOfRec[i] = coinChange(c, n-c[i], DP);
			if(noOfRec[i]<minVal) minVal = noOfRec[i];
		}

		if(minVal==INT_MAX) DP[n] = INT_MAX;
		else DP[n] = 1 + minVal;
		//int ans = 1 + minOf3(coinChange(n-1), coinChange(n-2), coinChange(n-5)); 	//	Without memoization
	}
	return DP[n];
}


int main(){
	int n;
	char input = 'y';
	cout<<"The available coins are = \n";
	//vector<int> c;
	//c.push_back(1); c.push_back(2);	c.push_back(5);
	vector<int> c(3);                       //  Creates a vector of size 3
	c[0] = 1, c[1] = 2; c[2] = 5;
    c[0] = 15, c[1] = 33; c[2] = 101;
    printArr(c);
	while(input=='y'){
		cout<<"Enter the value of n (0 to 10000) = \n";
		cin>>n;
		vector<int> DP(n+1, 0);              //  Creates a vector of size n with all value = -5
		//printArr(DP);
		int ans = 0;
		ans = coinChange(c, n, DP);
		cout<<"Printing the coinChange(i) for i = 0 to n : \n";
		cout<<"i    "<<"coinChange(i)\n";
		for(int i=0; i<=n; i++){
            cout<<i<<"      "<<DP[i]<<"\n";
		}
        if(ans==INT_MAX) ans = -1;
		cout<<"The minimum number of coins required are = "<<ans<<"\n";
		cout<<"Wanna continue? => coinChange() (y/n) = ";
		cin>>input;
	}
	return 0;
}

