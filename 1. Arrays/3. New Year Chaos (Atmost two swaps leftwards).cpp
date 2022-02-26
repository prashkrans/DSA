/* Array Prob. #3. New Year Chaos (Atmost two swaps leftwards)
*/

//	Running time = O(n)
//	Auxiliary space = O(1) 

void swap(vector<int> &arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void minimumBribes(vector<int> arr) {
    int n = arr.size();
    int count = 0;
    for(int i = n-1; i>=0; i--) {
        if(arr[i]==i+1) continue;
        else {
            if(arr[i-1]==i+1) {
                count++;
                swap(arr, i-1, i);
            }
            else if(arr[i-2]==i+1) {
                count += 2;
                swap(arr, i-2, i-1);
                swap(arr, i-1, i);
            }
            else {
                cout<<"Too chaotic\n";
                return;
            }
        }
    }
    cout<<count<<"\n";
}
