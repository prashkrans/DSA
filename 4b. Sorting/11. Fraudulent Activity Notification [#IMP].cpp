/* 	Sort Prob. #11. Fraudulent Activity Notification
*/
//  Method 3. (Best Method but slightly complicated) Using only the countArr of a counting sort but instead of finding
//	median in O(d) as in method 2 here, we find it in O(201) i.e. O(1) since k = 201.
//  Running time = O(n*k) = O(201n) ~ O(n) i.e. linear thus, efficient
//  Auxiliary space = O(k) but where k is the range of integers 0 to maxVal in the given array
//  But k is constant here i.e. max(k) = 200 so O(k) ~ O(200) ~ O(1) i.e. constant space

#include <bits/stdc++.h>
using namespace std;

float findMedian(vector<int> &countArr, int d) {
    int count = 0;                                      //  The variable count helps us ascertain the median
    for(int i=0; i<201; i++) {                          //  through two cases count > d/2 and count == d/2
        count += countArr[i];
        if(count*2 > d) return i;
        else if(count*2 == d) {
            for(int j = i+1; j<201; j++)
                if(countArr[j]>0) return ((i+j)/2.0);
        }
    }
    return -1.0;                                        //  Program control never reaches here as we always find a median
}

int activityNotifications(vector<int> arr, int d) {
    int n = arr.size();
    if(d>=n) return 0;
    int notification = 0;
    vector<int> countArr(201, 0);
    for(int i=0; i<n; i++) {                            //  Note: Here we keep modifying the countArr as per the current trailing array
        countArr[arr[i]]++;                             //  i.e. simply reduce the count of the first element by 1 and increase the count
        if(i>=d) {                                      //  of the last element by 1 of of the current trailing array
            if(arr[i] >= 2*findMedian(countArr, d))
                notification++;
            countArr[arr[i-d]]--;
        }

    }
    return notification;
}

int main() {
    int n, d;
    cin>>n>>d;
    vector<int> expenditure(n);
    for(int i=0; i<n; i++) cin>>expenditure[i];
    cout<<activityNotifications(expenditure, d);
    return 0;
}

/* Sample Input
5 4
1 2 3 4 4

9 5
2 3 4 2 3 6 8 4 5
*/
/*
//  Method 2. Using counting sort to get the median of an unsorted array in O(d) instead of O(dlog2d)
//  Running time = O(n*d) i.e. quadratic thus, inefficient
//  Auxiliary space = O(k) where k is the range of integers 0 to maxVal in the given array

#include <bits/stdc++.h>
using namespace std;

vector<int> countingSort(vector<int> arr) {
    int n = arr.size(), maxVal = INT_MIN;
    for(int i=0; i<n; i++) maxVal = max(maxVal, arr[i]);    //  try and run this only once
    int range = maxVal+1;
    vector<int> res(n);
	vector<int> idx(range, 0);
	for(int i=0; i<n; i++)
        idx[arr[i]]++;
    for(int i=1; i<idx.size(); i++)
        idx[i] = idx[i-1] + idx[i];
    for(int i=idx.size()-1; i>0; i--)
		idx[i] = idx[i-1];
    idx[0]=0;                                               //  [#IMP] - To make idx[0] = 0 due to the right shift
    for(int i=0; i<n; i++) {
        res[idx[arr[i]]] = arr[i];
        idx[arr[i]]++;
    }
    return res;
}

float findMedian(vector<int> arr, int i, int d) {
    int s = i-d, e = i-1;
    vector<int> brr;
    brr.assign(arr.begin()+s, arr.begin()+i);       //  i.e. start to end+1
    for(auto b : brr) cout<<b<<" "; cout<<" -> ";
    vector<int> res = countingSort(brr);
    if(d%2==0) return (res[d/2-1] + res[d/2] + 0.0)/2;
    else return res[d/2];
}

int activityNotifications(vector<int> arr, int d) {
    int n = arr.size();
    if(d>=n) return 0;
    int notices = 0;
    float currMed;
    for(int i=d; i<n; i++) {
        currMed = findMedian(arr, i, d);
        cout<<currMed<<" ";
        if(arr[i] >= 2*currMed) {
            cout<<"Notice sent\n";
            notices++;
        }
        else cout<<"Notice not sent\n";
    }
    return notices;
}

int main() {
    int n, d;
    cin>>n>>d;
    vector<int> expenditure(n);
    for(int i=0; i<n; i++) cin>>expenditure[i];
    cout<<activityNotifications(expenditure, d);
    return 0;
}

//  Method 1a. [My method] - Time taken to return median is O(nlog2n) due to quickSort()
//  Running time = O(n*dlog2d) as:
//  No. of traversals = O(n-d) and each traversal takes O(d + dlog2d) time
//  => R.T. = O(n-d)*O(d+dlog2d) ~ O(n)*O(dlog2d) = O(n*dlog2d)
//  Auxiliary space = O(d) due to the trailArr array


double findMedian(vector<double> a, int d) {
    sort(a.begin(), a.end());
    //for(auto i : a) cout<<i<<" "; cout<<"\n";
    //cout<<a[d/2-1]<<" "<<a[d/2]<<"\n";
    if((d&1)==0)
        return ((a[d/2-1]+a[d/2])/2);
    else return (a[d/2]);
}

int activityNotifications(vector<int> exp, int d) {
    int count = 0, n = exp.size();
    double currMed;
    vector<double> trailArr;
    if(d==n) return count;
    for(int i=d; i<n; i++) {
        trailArr.clear();
        for(int j=i-d; j<i; j++) trailArr.push_back(exp[j]);
        currMed = findMedian(trailArr, d);
       //cout<<"currMed = "<<currMed<<"\n";
        if(exp[i]>=2*currMed) count++;
    }
    return count;
}

//  Method 1b. Using assign function same as method 1a.
//  Running time = O(n*dlog2d)
//  Auxiliary space = O(d) due to the brr array.

double findMedian(vector<int> arr, int i, int d) {
    int s = i-d;
    int e = i-1;
    static vector<int> brr;
    brr.assign(arr.begin()+s, arr.begin()+e+1);
    //for(int i=0; i<d; i++) cout<<brr[i]<<" "; cout<<"\n";
    double median;
    sort(brr.begin(), brr.end());
    //for(int i=0; i<d; i++) cout<<brr[i]<<" "; cout<<"\n";
    if((d&1)==0)
        median = ((brr[d/2]+brr[d/2+1]+0.0)/2);
    else median = brr[d/2];
    return median;
}

int activityNotifications(vector<int> exp, int d) {
    int count = 0, n = exp.size();
    double currMed;
    if(d>=n) return count;
    for(int i=d; i<n; i++) {
        currMed = findMedian(exp, i, d);
        //cout<<"currMed = "<<currMed<<"\n";
        if(exp[i]>=2*currMed) count++;
    }
    cout<<"Count = "<<count<<"\n";
    return count;
}
*/

