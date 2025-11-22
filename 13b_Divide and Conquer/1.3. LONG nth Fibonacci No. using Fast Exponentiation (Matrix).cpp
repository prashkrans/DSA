/* D&C Prob. #1.2. nth Fibonacci number using Matrix Exponentiation.
Given n, return the nth Fibonacci number using matrix exponentiation.
This problem could be solve using two methods
1. Linear multiplication: R.T. = O(r^3.n) i.e. biquadratic time
2. Divide and Conquer (Fast exponentiation): R.T. = O(r^3.log2(n)) i.e. log-cubic time
[#IMP] Just replace multiplication of two numbers by multiplication of two matrices.
*/

//	Method 2.1. Divide and Conquer (Fast exponentiation) - Recursive (Prefer this over iterative)
//	Running time = O(log2n) i.e. logarithmic time hence faster than linear solution
//	Auxiliary space = O(1) i.e. constant space

#include<iostream>
#include<vector>
using namespace std;

void printMat(vector<vector<long>> mat) {
    for(long i=0; i<mat.size(); i++) {
        for(long j=0; j<mat[0].size(); j++) cout<<mat[i][j]<<"\t";
        cout<<"\n";
    }
    cout<<"\n";
}

vector<vector<long>> multiply(vector<vector<long>> A, vector<vector<long>> B) {
    long n = 2, mV = 1e9+7;
    vector<vector<long>> ans(2, vector<long>(2, 0));
    for(long i=0; i<n; i++) {
        for(long j=0; j<n; j++) {
            for(long k=0; k<n; k++) {
                ans[i][j] = (ans[i][j] + ((A[i][k]*B[k][j])%mV))%mV;
                //ans[i][j] = (ans[i][j] + ((A[i][k]*B[k][j])));
            }
        }
    }
    return ans;
}

vector<vector<long>> pow(vector<vector<long>> A, long n) {			//	long pow(long x, long n) {
    if(n==0) return {{1, 0}, {0, 1}};                           //	    if(n==0) return 1;
    vector<vector<long>> B = pow(A, n>>1);                        //	    long y = pow(x, n/2);
    vector<vector<long>> res = multiply(B, B);
    if(n%2==1) res =  multiply(A, res);
    printMat(res);
    return res;                                                 //	    else return y*y;
}                                                               //	}

long fibonacciNumber(long n) {
    if(n==0 || n==1) return n;
    vector<vector<long>> A = {{1, 1}, {1, 0}};
    A = pow(A, n-1);
    return A[0][0];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    long t;
    cin>>t;
    while(t--) {
        long n;
        cin>>n;
        cout<<"The "<<n<<"th Fibonacci Number is = \n"<<fibonacciNumber(n)<<"\n";
    }
}

