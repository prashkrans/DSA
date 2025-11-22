/* Array Prob. #6. 2D - Array: Max Sum of Hourglasses
*/

//	Running time = O(((n-2)^2)*9) i.e. quadratic and n = 6 here => R.T. = O(4*4*9) i.e. constant time
//	Auxiliary space = O(1) i.e. constant space

int sumOfHg(vector<vector<int>> arr, int i, int j) {
    int sum = 0;
    for(int r=i; r<i+3; r++) {
        for(int c=j; c<j+3; c++)
                sum += arr[r][c];
    }
    return (sum-arr[i+1][j]-arr[i+1][j+2]);
}

int hourglassSum(vector<vector<int>> arr) {
    int maxVal = INT_MIN;
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            int currSum = sumOfHg(arr, i, j);
            cout<<currSum<<"\t";
            maxVal = max(maxVal, currSum);
        }
        cout<<"\n";
    }
    return maxVal;
}