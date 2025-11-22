#include<iostream>
using namespace std;

int minOf3(int a, int b, int c){
	return min(a, min(b, c));
}

int coinChange(int n){
	if(n<0) return INT_MAX-1;
	else if(n==0) return 0;
	int ans = 1 + minOf3(coinChange(n-1), coinChange(n-2), coinChange(n-5));
	if(ans == INT_MAX) return -1;
	else return ans;
}


int main(){
	int n;
	char input = 'y';
	cout<<"The available coins are = {1, 2, 5}\n";
	while(input=='y'){
		cout<<"Enter the value of n = \n";
		cin>>n;
		cout<<"The minimum number of coins required are = "<<coinChange(n)<<"\n";
		cout<<"Wanna continue? => coinChange() (y/n) = ";
		cin>>input;
	}
	return 0;
}
