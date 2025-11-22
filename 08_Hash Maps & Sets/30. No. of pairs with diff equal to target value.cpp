/* 30. No. of pairs with differece equal to the target value.
Note: Each integer a[i] is unique
*/

//	Running time = O(n) i.e. two traversals
//	Auxiliary space = O(n) due to the unordered map

int pairs(int k, vector<int> arr) {
    int n = arr.size(), count = 0;
    unordered_map<int, int> mp;
    for(int i=0; i<n; i++) mp[arr[i]]++;
    for(int i=0; i<n; i++) {
        if(mp.count(arr[i]+k)) count++;
    }
    return count;
}
