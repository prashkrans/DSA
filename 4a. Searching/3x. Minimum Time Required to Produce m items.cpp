/* Searching Prob. #3x. Minimum time required to produce m items
Note - There would be a range of days for the same number of items to be produced
hence, we need the minimum days to produce m items and not the maximum days.

//  Method 1: Naive Solution or Brute Force Method
//  Running time = O(days*n) i.e. quadratic thus inefficient
//  Auxiliary space = O(1) i.e. constant space

#include <bits/stdc++.h>
using namespace std;

long minTime(vector<long> machines, long goal) {
    long numMac, days;
    for(days = 0; ; days++) {
        numMac = 0;
        for(int i=0; i<machines.size(); i++)
            numMac += days/machines[i];
        if(numMac>=goal) return days;
    }
}

int main() {
    long n, g;
    cin>>n>>g;
    vector<long> arr(n);
    for(long i=0; i<n; i++) cin>>arr[i];
    cout<<minTime(arr, g);
}
*/

//  Method 2: Binary search
//  Running time = O(n*log2(maxPossibleTime)) i.e. log-linear complexity
//  Auxiliary space = O(1) i.e. constant space


#include <bits/stdc++.h>
using namespace std;

long minTime(vector<long> machines, long goal) {
    int n = machines.size();
    long maxVal = 0;
    for(int i=0; i<n; i++) maxVal = max(maxVal, machines[i]);
    long low = 1, high = maxVal*goal, mid;
    long numOfMacProd;
    while(low != high) {         //  Finally low == high in this binary search as we need the min days to achieve the goal.
        mid = (low+high)/2;
        numOfMacProd = 0;
        for(int i=0; i<n; i++)
            numOfMacProd += (mid/machines[i]);
        if(numOfMacProd >= goal) high = mid;        //  Note - Do not make high = mid-1 as it itself stores the min value
        else low = mid+1;
    }
    return high;                                    //  Or return low would also work as finally low becomes equal to high
}

int main() {
    long n, g;
    cin>>n>>g;
    vector<long> arr(n);
    for(long i=0; i<n; i++) cin>>arr[i];
    cout<<minTime(arr, g);
}


/* Note:
while(low < high) {
    cout<<low<<" "<<high<<"\n";
    mid = (low+high)/2;
    numOfMacProd = 0;
    for(int i=0; i<n; i++)
        numOfMacProd += (mid/machines[i]);
    if (numOfMacProd == goal) return mid;
    else if(numOfMacProd > goal) high = mid-1;
    else if(numOfMacProd < goal) low = mid+1;
}

The above snippet won't give the correct answer as it gives the max days in which the goal
can be achieved while we need the min days in which the goal can be achieved which is only
possible when low == high
*/

//  Method 3. Using LCM of all the elements in the array (Incomplete)
//  There is a possibility this may be totally incorrect so verify thoroughly.
//  Running time = O(n)
//  Auxiliary space = O(1)
/*
#include <bits/stdc++.h>
using namespace std;

long gcd(long a, long b) {
    if(a%b==0) return b;
    return gcd(b, a%b);
}

long lcm(vector<long> arr) {
    long lcmOfArr = 1;
    for(int i=0; i<arr.size(); i++) {
        long a = arr[i], b = lcmOfArr;
        lcmOfArr = (a * b)/gcd(a, b);
    }
    return lcmOfArr;
}

// Complete the minTime function below.
long minTime(vector<long> machines, long goal) {
    long lcmVal = lcm(machines);
    long q = goal/lcmVal;
    long r = goal%lcmVal;
    long denom = 0;
    for(int i=0; i<machines.size(); i++)
        denom += lcmVal/machines[i];
    cout<<"LCM = "<<lcmVal<<" Q = "<<q<<" r = "<<r<<" denom = "<<denom<<"\n";
    return (q*lcmVal) + ceil((r*lcmVal*1.0)/denom);
}

int main() {
    long n, g;
    cin>>n>>g;
    vector<long> arr(n);
    for(long i=0; i<n; i++) cin>>arr[i];
    cout<<minTime(arr, g);
}
*/
