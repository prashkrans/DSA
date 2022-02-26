/* Array Prob. #5. Array Manipulation
Starting with a 1-indexed array of zeros and a list of operations, for each operation add a value to each the array 
element between two given indices, inclusive. Once all operations have been performed, return the maximum value in 
the array.
*/

//	Running time = O(n+m) i.e. linear instead of O(n*m) in naive solution
//	Auxiliary space = O(n) due to the arr array
//	arr[a] = arr[a]+k; and arr[b+1] = arr[b+1]-k;

long arrayManipulation(int n, vector<vector<int>> queries) {
    int a, b, k, m = queries.size();
    long sum = 0, maxVal = -1;
    vector<int> arr(n, 0);
    for(int i=0; i<m; i++) {
        a = queries[i][0];
        b = queries[i][1];
        k = queries[i][2];
        arr[a-1] = arr[a-1] + k;        //  Since, a & b are 1-indexed we reduce a and b+1 by 1.
        if(b<n) arr[b] = arr[b] - k;
    }
    for(int i=0; i<n; i++) {            
        sum = sum + arr[i];             //  Cumulative sum 
        if(maxVal < sum) maxVal = sum;
    }
    return maxVal;
}