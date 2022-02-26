/* Hashmap problem #1
Given an array of integers remove the duplicate elements and print it.
*/
//  Running time = O(n) for all the methods as we are using hashmaps or hashsets so O(n) * O(1)
//  Auxiliary space = O(n)

#include<iostream>
#include<unordered_map>
#include<unordered_set>
#include<vector>
using namespace std;
//  Method 1 - using umap without count function
vector<int> removeDuplicates(vector<int> a, int n) {    // Both functions are exactly the same except the use of count function
    unordered_map<int, bool> umap;
    vector<int> ans;
    for(int i=0; i<n; i++) {
        if(umap[a[i]]==0) {     //  Here the search operation is carried out by [] operator i.e. create a new a pair if key == a[i]
            umap[a[i]] = 1;     //  is not found and its value is set to default as 0 which is then later changed to 1
            ans.push_back(a[i]);    // Since a[i] is not found and just entered into the map, it is also entered into the ans array
        }
    }
    return ans;
}
//  Method 2 - using umap with count function
vector<int> removeDuplicates2(vector<int> a, int n) {
    unordered_map<int, bool> umap2;
    vector<int> ans2;
    for(int i=0; i<n; i++) {
        if(umap2.count(a[i])==0) {  //  Here the search operation is carried out by mapName.count(key) function
            umap2[a[i]] = true;     //  i.e. if the key is present just continue else if the key is not present add it to the map
            ans2.push_back(a[i]);   //  and set its value to 1 and thus also add it to the ans array
        }
    }
    return ans2;
}
//  Method 3 - using uset with count function
vector<int> removeDuplicates3(vector<int> a, int n) {
    unordered_set<int> uset;
    vector<int> ans;
    for(int i=0; i<n; i++) {
        if(uset.count(a[i])==0) {
            uset.insert(a[i]);
            ans.push_back(a[i]);
        }
    }
    return ans;
}


int main() {
    int n;
    cin>>n;
    vector<int> a(n);
    for(int i=0; i<n; i++) cin>>a[i];
    vector<int> ans = removeDuplicates(a, n);
    for(auto i : ans) cout<<i<<" ";
    cout<<"\n";
    vector<int> ans2 = removeDuplicates2(a, n);
    for(auto i : ans2) cout<<i<<" ";
    cout<<"\n";
    vector<int> ans3 = removeDuplicates3(a, n);
    for(auto i : ans3) cout<<i<<" ";
    cout<<"\n";
    return 0;
}
