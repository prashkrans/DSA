/* Array Prob. #x. 
Given an array with N elements, the task is to rotate the array to the left by K steps, where K is non-negative.
*/

//	Running time = O(n) i.e. linear time
//	Auxiliary space = O(n) due to the array b

#include <iostream>
using namespace std;

void rotateLeft(int n, int a[], int k) {
    k %= n;
    int b[k];
    for(int i=0; i<k; i++) b[i] = a[i];
    for(int i=k; i<n; i++) a[i-k] = a[i];
    for(int i=n-k; i<n; i++) a[i] = b[i-n+k];
}

int main() {
    int n, k;
    cin>>n;
    int a[n];
    for(int i=0; i<n; i++) cin>>a[i];
    cin>>k;
    rotateLeft(n, a, k);
    for(int i=0; i<n; i++) cout<<a[i]<<" ";
    return 0;
}