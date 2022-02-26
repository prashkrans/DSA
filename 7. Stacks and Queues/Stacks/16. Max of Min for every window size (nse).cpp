/* Stack Prob. #15. Maximum of minimum for every window size

Uses the concept of "near smaller element" to the right and left i.e. nseL and nseR. Stack just helps to find nseL and nseR 
for an element at i in O(1) instead of O(n) for a regular search. 

*/

// 	Method 1: Naive Solution – Character Table or 2 nested loops. R.T. = O(n^2)
/*
vector<long> riddle(vector<long> arr) {
    int n = arr.size();
    long maxVal, j;
    vector<long> res;
    vector<vector<long>> table(n, vector<long>(n,0));
    for(long len = 1; len<=n; len++) {
        maxVal = -1;
        for(long i=0; i<=n-len; i++) {
        j = len + i - 1;
        //cout<<i<<", "<<j<<": ";
        if(i==j) table[i][j] = arr[i];
        else table[i][j] = min(table[i][j-1], arr[j]);
        maxVal = max(maxVal, table[i][j]);
        }
        res.push_back(maxVal);
    }
    for(int i=0; i<n; i++) {
        for(int j=i; j<n; j++) {
            cout<<table[i][j]<<" ";
        }
        cout<<"\n";
    }
    cout<<"Result = \n"; for(auto r : res) cout<<r<<" "; cout<<"\n";
    return res;
}
*/

//	Method 2: Using stacks to find left and right bounds in O(1) instead of O(N) thus R.T. =  O(4n) ~ O(n).
//	Running time = O(4n) ~ O(n) due to four traversals in arrays of size n. 
//	Auxiliary space = O(n) due to the stack
#include <bits/stdc++.h>
using namespace std;


void print(int n, vector<long> arr, vector<long> nseLeft, vector<long> nseRight, vector<long> lenMap) { //  Helper function to verify the computations
    cout<<"indices =\t"; for(int i=0; i<n; i++) cout<<i<<"\t"; cout<<"\n";
	cout<<"arr[i] =\t";  for(auto i : arr) cout<<i<<"\t"; cout<<"\n";
	cout<<"nseLeft =\t"; for(auto i : nseLeft) cout<<i<<"\t"; cout<<"\n";
	cout<<"nseRight =\t"; for(auto i : nseRight) cout<<i<<"\t"; cout<<"\n";
	vector<int> spread(n);
	for(int i=0; i<n; i++) spread[i] = nseRight[i]-nseLeft[i]+1;
	cout<<"spread =\t"; for(auto i : spread) cout<<i<<"\t"; cout<<"\n";
	cout<<"lenMap =\t"; for (auto mp : lenMap) cout<<mp<<"\t"; cout<<"\n";
}

vector<long> riddle(vector<long> arr) {
    int n = arr.size();
	vector<long> res, nseLeft(n), nseRight(n);
	stack<long> s;
	for(int i=0; i<n; i++) {
		if(s.empty()) {
			nseLeft[i] = 0;
			s.push(i);
		}
		else {
			while(!s.empty() && arr[s.top()] >= arr[i])
				s.pop();
			if(s.empty()) nseLeft[i] = 0;
			else nseLeft[i] = s.top()+1;
			s.push(i);
		}
	}
	while(!s.empty()) s.pop();
	for(int i=n-1; i>=0; i--) {
		if(s.empty()) {
			nseRight[i] = n-1;
			s.push(i);
		}
		else {
			while(!s.empty() && arr[s.top()] >= arr[i])
				s.pop();
			if(s.empty()) nseRight[i] = n-1;
			else nseRight[i] = s.top()-1;
			s.push(i);
		}
	}
	vector<long> lenMap(n);             //  Note: len varies from 1 to n but indices of lenMap varies from 0 to n-1
	long currLen;                       //  i.e lenMap[i] gives arrVal for length = i+1
	for(int i=0; i<n; i++) {
        currLen = nseRight[i] - nseLeft[i] + 1;
        lenMap[currLen-1] = max(lenMap[currLen-1], arr[i]);
	}
	for(int i=n-2; i>=0; i--) {
        lenMap[i] = max(lenMap[i], lenMap[i+1]);	//	#IMP - if lm[i+1] > lm[i] then lm[i] is replaced by lm[i+1];
	}
	print(n, arr, nseLeft, nseRight, lenMap);		//	Optional print() function
	return lenMap;
}

int main() {
    int n;
    cin >> n;
    vector<long> arr(n);
    for(int i=0; i<n; i++) cin>>arr[i];
    vector<long> res = riddle(arr);
    for (int i = 0; i < res.size(); i++) {
        cout << res[i];
        if (i != res.size() - 1) {
            cout << " ";
        }
    }
    return 0;
}

/* Sample input
5
6 3 5 1 1 12

17
1 32 71 1 86 85 18 27 9 68 87 54 41 70 76 13 38

Output:
Incorrect - 87 85 54 18 41 41 13 13 9 9 9 9 9 1 1 1 1
Correct - 	87 85 54 41 41 41 13 13 9 9 9 9 9 1 1 1 1
*/