/* String Matching Problem:

Input 1:
acbacaacacacabacacabacacacababacacabacacabacacacacacabacacabacacac
acacabacacabacacac
Output:
Pattern P found at index i in text T = 8 30 48
Input 2:
abacacab
xyxy
Output: Pattern P was not found in the given text T

This problem could be solved using three methods:
1. 	Naive Solution: R.T. = O(mn) thus inefficient
2.	Knuth Morris Pratt (KMP) Algo: R.T. = O(m+n)
3.	Tries: R.T. = ??
where m = |P| and n = |T|.
*/

//	Method 2. KMP Algo
//	Running time = O(m+n)
//	Space complexity = O(m+n)


#include<iostream>
#include<vector>
using namespace std;

vector<int> buildArrayLPS(string P) {
	int i=1, j=0, m = P.size();
	vector<int> lps(m, 0);
	while(i<m){
		if(P[i]==P[j]) {
			lps[i] = j+1;
			i++;						//	i only moves forward when a match is found or or match is not found and j==0 unlike j which may backtrack
			j++;
		}
		else if(P[i]!=P[j]) {
            if(j!=0) j = lps[j-1];
            else if(j==0) i++;          //  lps[i] = 0 is already taken care initially
		}
	}
	return lps;
}

vector<int> KMPalgo(string T, string P, vector<int> lps) {
    int n = T.size(), m = P.size();
    int k = 0, i = 0;
    vector<int> foundAt;
    while(k<n) {
        if(T[k]==P[i]) {
            if(i==m-1) foundAt.push_back(k+1-m);	//	When i == m-1 => Pattern P is found in the text T.
            k++;									//	k does not backtrack and only moves forward if either match is found or match is not found and i==0
            i = (i+1)%m;							//	i should vary from 0 to m-1
        }
        else if(T[k]!=P[i]) {
            if(i!=0) i = lps[i-1];
			else if(i==0) k++;
        }
    }
    return foundAt;
}

int main() {
	string T, P;
	cin>>T>>P;
	int m = P.size(), n = T.size();
	vector<int> lps = buildArrayLPS(P);
	for(int i=0; i<m; i++) cout<<"("<<i<<", "<<lps[i]<<") "; cout<<"\n";
	vector<int> foundAt = KMPalgo(T, P, lps);
	if(foundAt.empty()) cout<<"Pattern P was not found in the given text T\n";
	else {
        int count=0;
        cout<<"Pattern P was found in the given text T at the following indices:\n";
        for(int i=0; i<foundAt.size(); i++) {
            cout<<foundAt[i]<<" ";
            count++;
        }
        cout<<"\nSo, P was found "<<count<<" time(s) in T\n";
	}
	return 0;
}
