/* 31. Triple Sum
Note:
Use ordered set as we need sorted and unique elements only.
Can also be solved using map but would be a waste of space
*/

// 	Running time = O(2(x+y+z)) ~ O(x+y+z) where x = a.size(), y = b.size(), z = c.size()
//	Auxiliary space = O(x+y+z) 

#include <bits/stdc++.h>
using namespace std;

// Complete the triplets function below.
long triplets(vector<int> a, vector<int> b, vector<int> c) {
    long count = 0, m = 0, n = 0;
    set<int> sA, sB, sC;
    for(int i=0; i<a.size(); i++) sA.insert(a[i]);
    for(int i=0; i<b.size(); i++) sB.insert(b[i]);
    for(int i=0; i<c.size(); i++) sC.insert(c[i]);
    set<int>::iterator it = sA.begin(), jt = sB.begin(), kt = sC.begin();
    for(jt = sB.begin(); jt!=sB.end(); jt++) {			//	For each b[i] we find no. of a[i] <= b[i] in m and no. of c[i] <= in n
        while((*it)<=(*jt) && it!=sA.end()) {			//	#IMP to use it!=sA.end() else loops endlessly
            m++;										//	Note: We traverse each set A, B, and C only once. Hence sorted data save time.
            advance(it, 1);
        }
        while((*kt)<=(*jt) && kt!=sC.end()) {
            n++;
            advance(kt, 1);
        }
        count += m*n;									//	Hence, for each b[i], no. of different triplets possible are m*n
    }	
    return count;
}

int main() {
    int n, m, p;
    cin>>n>>m>>p;
    vector<int> a(n), b(m), c(p);
    for(int i=0; i<n; i++) cin>>a[i];
    for(int i=0; i<m; i++) cin>>b[i];
    for(int i=0; i<p; i++) cin>>c[i];
    cout<<"Count = "<<triplets(a, b, c)<<"\n";
    return 0;
}
