/* 29. Count Triplets
https://www.hackerrank.com/challenges/count-triplets-1/problem?h_l=interview&isFullScreen=true&playlist_slugs%5B%5D%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D%5B%5D=dictionaries-hashmaps
*/

//	Method 1. Naive Solution
//	For each a in arr find a/r before it and a*r after it using nested loops
//	Running time = O(n^3)
//  Auxiliary space = O(n)

//	Method 1. Double pass and using a/r, a, ar^2 with two unordered_maps (Easier to understand)
//  yt - https://www.youtube.com/watch?v=KZ8k9-22JmQ&ab_channel=CodingCart
//	before ... a ... after
//	We need the number of a/r before a (l) and the number of a*r after a (r) so that no. of triplets including a becomes l*r
//	Running time = O(nlog2n)
//  Auxiliary space = O(n)

long countTriplets(vector<long> arr, long r) {
    long count = 0;
    unordered_map<long, long> before, after;
    for(int i=0; i<arr.size(); i++) after[arr[i]]++;	//	First populate the map after while the map before is empty
    for(int i=0; i<arr.size(); i++) {
        long a = arr[i];
        after[a]--;										//	 Imp. to have after[a]-- before calculating count to take care of the case 1*1 = 1 .
        long left = a/r, right = a*r;
        if(before.count(left) && a%r==0 && after.count(right))	//	It is important to include (a%r)==0 due to the int data type as 28/3 = 27/3 = 9
            count += before[left]*after[right];        
        before[a]++;
    }
    return count;
}
		


//	Method 2. Single pass and using a & ar and two unordered maps (Tricky)

long countTriplets(vector<long> arr, long r) {
    long count = 0;
    unordered_map<long, long> leftMp, rightMp;
    for(int i=0; i<arr.size(); i++) {
        long a = arr[i];
        count += rightMp[a];
        rightMp[a*r] += leftMp[a];
        leftMp[a*r] += 1;
    }
    return count;
}