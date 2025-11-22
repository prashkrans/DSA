/* D&C Prob. #1.1. Fast exponentiation
Given a number x and power n find x raised to the power n i.e. x^n.
This problem could be solve using two methods
1. Linear multiplication
2. Divide and Conquer (Fast exponentiation)
*/

//	Method 2.1. Divide and Conquer (Fast exponentiation) - Recursive (Prefer this over iterative)
//	Running time = O(log2n) i.e. logarithmic time hence faster than linear solution
//	Auxiliary space = O(1) i.e. constant space

#include <iostream>
using namespace std;

int pow(int x, int n) {
    if(n==0) return 1;
    int y = pow(x, n/2);
    if(n%2==1) return x*y*y;
    else return y*y;
}

int main() {
    int x, n;
    cin>>x>>n;
    cout<<pow(x, n);
}

//	Method 2.2. Divide and Conquer (Fast exponentiation) - Iterative (Bit trickier to understand)
//	Running time = O(log2n) i.e. logarithmic time hence faster than linear solution
//	Auxiliary space = O(1) i.e. constant space
/*
#include <iostream>
using namespace std;

int pow(int x, int n) {
    int res = 1;
	while(n) {
		if(n&1) res = res*x;
		n = n>>1;
		x = x*x;				//	This is the important part that in each iteration we are squaring curr x and storing it in x
	}
	return res;
}

int main() {
    int x, n;
    cin>>x>>n;
    cout<<pow(x, n);
}


//	Method 1. Linear multiplication
//	Running time = O(n) i.e. linear time
//	Auxiliary space = O(1) i.e. constant space


#include <iostream>
using namespace std;

int main() {
    int x, n;
    cin>>x>>n;
    int ans=1;		//	This takes care of the case when n==0
    while(n--)
    	ans *= x;
    cout<<ans;
    return 0;
}
*/
