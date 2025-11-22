// { Driver Code Starts
#include<bits/stdc++.h>
using namespace std;

 // } Driver Code Ends
class Solution {
public:
    vector<int> singleNumber(vector<int> nums) {
        vector<int> a(2, 0);
        int n = nums.size();
        for(int i=0; i<n; i++) {
            a[0] = a[0]^nums[i];
        }
        a[1] = a[0];
        cout<<"XOR = "<<a[0]<<"\n";
        int rmOne = a[0] & (-1*a[0]);
        cout<<"rmOne = "<<rmOne<<"\n";
        vector<int> v1, v2;
        for(int i=0; i<n; i++) {
            int pos = nums[i] & rmOne;
            if(pos!=0) v1.push_back(nums[i]);
            else v2.push_back(nums[i]);
        }
        cout<<"v1 = ";
        for(int i=0; i<v1.size(); i++) {
            cout<<v1[i]<<" ";
            a[0] = a[0]^v1[i];
        }
        cout<<"\n";
        cout<<"v2 = ";
        for(int i=0; i<v2.size(); i++) {
            cout<<v2[i]<<" ";
            a[1] = a[1]^v2[i];
        }
        cout<<"\n";
        sort(a.begin(), a.end());
        return a;
    }
};

// { Driver Code Starts.
int main(){
    int T;
    cin >> T;
    while(T--)
    {
    	int n;
    	cin >> n;
    	vector<int> v(2 * n + 2);
    	for(int i = 0; i < 2 * n + 2; i++) cin >> v[i];
    	Solution ob;
    	vector<int > ans = ob.singleNumber(v);
    	for(auto i: ans) cout << i << " ";
    	cout << "\n";
    }
	return 0;
}  // } Driver Code Ends
