/* Array Prob. #4. Minimum swaps to sort n natural numbers in O(n)
*/

//	My method:
//  Note: This not counting sort.
//	Running time = O(n)
//	Auxiliary space = O(n) due to the brr array

void swap(vector<int> &arr, vector<int> &brr, int i) {
    int aVal = arr[i];
    int val = i+1;
    int pos = brr[val];
    arr[i] = val;				//	Swapping values in the arr array
    arr[pos] = aVal;
    brr[val] = brr[aVal];		//	Swapping index values in the brr array
    brr[aVal] = pos;
}

int minimumSwaps(vector<int> arr) {
    int n = arr.size(), count = 0;
    vector<int> brr(n+1, 0);	//	brr array stores the indices of the values arr[i] which vary from 1 to n.
    for(int i=0; i<n; i++) brr[arr[i]] = i;
    for(int i=0; i<n; i++) {
        if(arr[i]==i+1) continue;
        else {
            count++;
            swap(arr, brr, i);
        }
    }
    return count;
}
