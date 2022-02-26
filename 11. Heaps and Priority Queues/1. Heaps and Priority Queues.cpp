#include<iostream>
using namespace std;

//  Note - Since the array to be used as heap the first element should be at index = 1 instead of 0.
//  We can use to A[0] to store the size of the heap i.e. (size of the array = size of heap + 1).
//  But need to make sure to update A[0] when deleting and inserting or any other function that changes
//  the size of the heap.

//  There are two types of heaps i.e. minHeap and maxHeap. An array is used here for minHeap while a
//  vector is used here for maxHeap.

void minHeapify(int arr[], int n, int i){
    if(n==0||n==1) return;
    int left = 2*i;
    int right = 2*i+1;
    int smallest;
    if(left<=n && arr[left]<arr[i]) smallest = left;
    else smallest = i;
    if(right<=n && arr[right]<arr[smallest]) smallest = right;
    if(smallest!=i){
        swap(arr[i], arr[smallest]);
        minHeapify(arr, n, smallest);
    }
}

void minHeapifyIter(int arr[], int n, int i){
    if(n==0||n==1) return;
    int left;
    int right;
    int smallest;
    while(i<=n/2){
        left = 2*i;
        right = 2*i+1;
        if(left<=n && arr[left]<arr[i]) smallest = left;
        else smallest = i;
        if(right<=n && arr[right]<arr[smallest]) smallest = right;
        if(smallest!=i){
            swap(arr[i], arr[smallest]);
            i = smallest;
        }
        else if(smallest==i) break;
    }
}

void buildMinHeap(int arr[],int n){
    for(int i=n/2; i>=1; i--){
        minHeapify(arr, n, i);
    }
}

void minHeapSort(int arr[], int n){
    int heapSize = n;
    for(int i=1; i<=n; i++){
    swap(arr[1], arr[heapSize]);
    heapSize--;
    minHeapify(arr, heapSize, 1);
    }
}

void maxHeapify(vector<int> &arr, int n, int i){    // We use vector<int> &arrayName in func defn and can be called simply by using arrayName in func calling
    int left = 2*i;
    int right = 2*i+1;
    int largest = i;
    if(left<=n && arr[left]>arr[i]) largest = left;
    if(right<=n && arr[right]>arr[largest]) largest = right;
    if(largest!=i){
        swap(arr[i], arr[largest]);
        maxHeapify(arr, n, largest);
    }
}

void buildMaxHeap(vector<int> &arr, int n){
    for(int i=n/2; i>=1; i--) maxHeapify(arr, n, i);
}

void maxHeapSort(vector<int> &arr, int n){
    int heapSize = n;
    for(int i=1; i<=n; i++){
    swap(arr[1], arr[heapSize]);
    heapSize--;
    maxHeapify(arr, heapSize, 1);
    }
}

int deleteMax(vector<int> &arr, int n){
    int maxVal = arr[1];
    swap(arr[1], arr[n]);
    arr[0]--;
    maxHeapify(arr, n-1, 1);
    return maxVal;
}


int main(){
    cout<<"Heaps & Priority Queues \n";

    cout<<"End of program";
    return 0;
}
