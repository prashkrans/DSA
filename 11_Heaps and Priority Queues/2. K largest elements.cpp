#include<iostream>
#include<vector>
#include<queue>                 // For using the STL => priority_queue<dataType> variableName
#include<algorithm>             // For using the sort() function
using namespace std;

//  Note - All the tree methods have the running time of O(nlogn) i.e.
//  O(PQ) = O(heapSort) = O(quickSort)
//  Method 1 - Using the priority queue STL and its inbuilt methods
vector<int> kLargestElementsUsingSTL(vector<int> arr, int size, int k){
    priority_queue<int> pq;
    for(int i=0; i<size; i++) pq.push(arr[i]);
    vector<int> kLargestElem;
    while(k--){
        int currElem = pq.top(); pq.pop();
        kLargestElem.push_back(currElem);
    }
    return kLargestElem;
}

//  Method 2 - Using a heap implementation using a vector/array and
//  three helper functions i.e.
//  1. maxHeapify() 2. buildMaxHeap() 3. deleteMin()
void maxHeapify(vector<int> &arr, int n, int i){
    int left = 2*i;
    int right = 2*i+1;
    int largest=i;
    if(left<=n && arr[left]>arr[i]) largest = left;
    if(right<=n && arr[right]>arr[largest]) largest = right;
    if(largest!=i){
        swap(arr[i], arr[largest]);
        maxHeapify(arr, n, largest);
    }
}

int deleteMax(vector<int> &arr, int n){
    int maxVal = arr[1];
    swap(arr[1], arr[n]);
    arr[0]--;
    maxHeapify(arr, n-1, 1);
    return maxVal;
}

void buildMaxHeap(vector<int> &arr, int n){
    for(int i=n/2; i>=1; i--) maxHeapify(arr, n, i);
}

vector<int> kLargestElements(vector<int> &A, int k) {
    A.push_back(-1);                    // Increasing the size of the vector by 1
    for(int i=A.size()-1; i>0; i--){
        A[i] = A[i-1];                  // Shifting the elements rightwards by 1
    }                                   // as the starting index should be 1 instead of 0
    A[0] = A.size()-1;                  // Using A[0] to store the size of the heap
    buildMaxHeap(A, A[0]);              // Building the heap : O(n)
    vector<int> C;                      // C is the array that stores the k largest elements
    int val;
    for(int i=1; i<=k; i++){
        val = deleteMax(A, A[0]);       // DeleteMax() returns the max element and then deletes it
        C.push_back(val);               // Building the array C
    }
    return C;
}

//  Method 3 - Using quickSort() to sort the array in increasing order hence the last k
//  elements are the k largest elements in the array.
vector<int> kLargestElementsUsingQS(vector<int> &A, int k){
    sort(A.begin(), A.end());           // Built-in quickSort() function
    vector<int> ans;
    int i = A.size()-1;
    while(k--){
        ans.push_back(A[i]);
        i--;
    }
    return ans;
}
int main(){
    cout<<"Enter the size followed by the elements of the array = \n";
    int size;
    int val;
    vector<int> arr;
    vector<int> arrCopy;
    vector<int> arrCopy2;
    cin>>size;
    for(int i=0; i<size; i++){
        cin>>val;
        arr.push_back(val);
    }
    arrCopy = arr;
    arrCopy2 = arr;
    cout<<"Enter the value of k (k > 0 and k <= arrSize) = \n";
    int k;
    cin>>k;
    cout<<"Using the kLargestElementsUsingSTL() function \n";
    vector<int> kLargestElem = kLargestElementsUsingSTL(arr, size, k);
    for(int i=0; i<k; i++) cout<<kLargestElem[i]<<" ";
    cout<<"\n";
    cout<<"Using the kLargestELements() function which uses maxHeap()\n";
    vector<int> kLargestElem2 = kLargestElements(arrCopy, k);
    for(int i=0; i<k; i++) cout<<kLargestElem2[i]<<" ";
    cout<<"\n";
    cout<<"Using the kLargestELementsUsingQS() function \n";
    vector<int> kLargestElem3 = kLargestElementsUsingQS(arrCopy2, k);
    for(int i=0; i<k; i++) cout<<kLargestElem3[i]<<" ";
    cout<<"\n";
    return 0;
}
