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

void printMat(vector<vector<int>> mat) {
    for(int i=0; i<mat.size(); i++) {
        for(int j=0; j<mat[0].size(); j++) cout<<mat[i][j]<<" ";
        cout<<"\n";
    }
}

vector<vector<int>> multiply(vector<vector<int>> A, vector<vector<int>> B) {
    int n = A.size(), m = A[0].size(), x = B.size(), y = B[0].size();
    vector<vector<int>> ans(n, vector<int>(y, 0));				//	multiplication only occurs when m == x and dim of ans becomes n x y
    for(int i=0; i<n; i++) {
        for(int j=0; j<y; j++) {
            for(int k=0; k<m; k++) {							//	m == x
                ans[i][j] += A[i][k]*B[k][j];
            }
        }
    }
    return ans;
}

vector<vector<int>> identityMatrix(int n) {                     //  A square matrix raised to power 0 is an identity matrix
    vector<vector<int>> ideM(n, vector<int>(n, 0));             //  i.e. A^0 = I
    for(int i=0; i<n; i++) ideM[i][i] = 1;
    return ideM;
}

vector<vector<int>> pow(vector<vector<int>> A, int n) {			//	int pow(int x, int n) {
    if(n==0) return identityMatrix(A.size());                   //	    if(n==0) return 1;
    vector<vector<int>> B = pow(A, n/2);                        //	    int y = pow(x, n/2);
    if(n%2==1) return multiply(A, multiply(B, B));              //	    if(n%2==1) return x*y*y;
    else return multiply(B, B);                                 //	    else return y*y;
}                                                               //	}

int fib(int n) {
    if(n==0 || n==1) return n;
    vector<vector<int>> A(2, vector<int>(2, 0)), B(2, vector<int>(1, 0));
    A = {{1, 1}, {1, 0}};
    B = {{1}, {0}};
    A = pow(A, n-1);
    vector<vector<int>> ans = multiply(A, B);
    return ans[0][0];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin>>t;
    while(t--) {
        int n;
        cin>>n;
        cout<<"The "<<n<<"th Fibonacci Number is = "<<fib(n)<<"\n";
    }
}

