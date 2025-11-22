/* Search Prob. #5. Maximum Sum Modulo m Subarray Problem

//  Method 1: Naive Solution or Brute Force Method
//  Running time = O(n^2) i.e. quadratic thus inefficient
//  Auxiliary space = O(1) i.e. constant space

//  Method 2: Efficient method (Rote Learn)
/*  The idea is to compute prefix sum of array. We find maximum sum ending with every index and finally
return overall maximum. To find maximum sum ending  at an index, we need to find the starting point
of maximum sum ending with i. Below steps explain how to find the starting point.
Steps:
Let prefix sum for index i be prefixi, i.e.,
prefixi = (arr[0] + arr[1] + .... arr[i] ) % m
Let maximum sum ending with i be, maxSumi.
Let this sum begins with index j.
maxSumi = (prefixi - prefixj + m) % m
From above expression it is clear that thevalue of maxSumi becomes maximum when prefixj is greater than
prefixi and closest to prefixi. We mainly have two operations in above algorithm.
1.  Store all prefixes.
2.  For current prefix, prefixi, find the smallest value greater than or equal to prefixi + 1.
For the above operations, a self-balancing-binary-search-trees like AVL Tree, Red-Black Tree, etc are best suited.
In below implementation we use set in STL which implements a self-balancing-binary-search-tree.
*/
//  Running time = O(n^2) i.e. quadratic thus inefficient
//  Auxiliary space = O(1) i.e. constant space

#include<bits/stdc++.h>
using namespace std;

long maximumSumModuloM(vector<long> a, long m) {
    long prefix = 0, maxVal = 0;
    set<long> S;
    S.insert(0);
    for(int i=0; i<a.size(); i++) {
        prefix = (prefix + a[i])%m;
        maxVal = max(maxVal, prefix);
        auto it = S.lower_bound(prefix+1);
        if(it!=S.end()) maxVal = max(maxVal, prefix - (*it) + m);
        S.insert(prefix);
    }
    return maxVal;
}

int main() {
    int t;
    cin>>t;
    while(t--) {
        long n, m;
        cin>>n>>m;
        vector<long> a(n);
        for(long i=0; i<n; i++) cin>>a[i];
        //cout<<"Maximum sum modulo m of a subarray is = ";
        cout<<maximumSumModuloM(a, m)<<"\n";
    }
    return 0;
}
