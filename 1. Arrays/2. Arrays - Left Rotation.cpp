/* Array Prob. #2. Arrays - Left Rotation
Given an array a of n integers and a number d, perform d left rotations on the array. Return the updated array 
to be printed as a single line of space-separated integers.

*/
vector<int> rotLeft(vector<int> a, int d) {
    vector<int> left;
    int n = a.size();
    d = d%n;
    for(int i=0; i<d; i++) left.push_back(a[i]);
    vector<int>::iterator it = left.begin();
    for(int i=d; i<n; i++) a[i-d] = a[i];
    for(int i=n-d; i<n; i++) {
        a[i] = *it;
        it++;
    }
    return a;
}