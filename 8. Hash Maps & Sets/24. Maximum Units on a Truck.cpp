/*Hashmap/set problem #24. LC#1710. Maximum Units on a Truck (Amazon interview problem)
You are assigned to put some amount of boxes onto one truck. You are given a 2D array boxTypes, where 
boxTypes[i] = [numberOfBoxesi, numberOfUnitsPerBoxi]: 
numberOfBoxesi is the number of boxes of type i. 
numberOfUnitsPerBoxi is the number of units in each box of the type i.
You are also given an integer truckSize, which is the maximum number of boxes that can be put on the truck. 
You can choose any boxes to put on the truck as long as the number of boxes does not exceed truckSize.
Return the maximum total number of units that can be put on the truck.

Example 1:
Input: boxTypes = [[5,10],[2,5],[4,7],[3,9]], truckSize = 10
Output: 91
*/

//	Method 1. Creating a vector/multiset of pairs and then sorting/already sorted while inserting w.r.t. to 
//	the number of units in a non-increasing manner. Then simply loading x boxes if x < currentTruckSize else
//	loading currentTruckSize boxes. Hence, the sum of the units of the loaded boxes is the answer.
//	Running time = O(nlogn + n) ~ O(nlogn) due to sorting of the given vector of size n.
//	Auxiliary space = O(n) as we copy the contents to a new vector/multiset.
//	This method is faster but consumes more space. 

class Solution {
public:
    int maximumUnits(vector<vector<int>>& bT, int tS) {
        vector<pair<int, int>> desc;
        for(int i=0; i<bT.size(); i++) desc.push_back({bT[i][1], bT[i][0]});
        sort(desc.begin(), desc.end(), greater<pair<int, int>>());
        //for (auto i : desc) cout<<i.first<<" "<<i.second<<"\n";
        auto it = desc.begin();
        int sum = 0;
        while(tS>0 && it!=desc.end()) {
            int currBoxes = min(tS, it->second);
            tS = tS - currBoxes;
            sum = sum + currBoxes*it->first;
            it++;
        }
        return sum;
    }
};

//	Method 2. Sorting the given 2D vector itself using a custom comparator and following the steps mentioned in 
//	method 1. 
//	Running time = O(nlogn) due to sorting of the given vector of size n.
//	Auxiliary space = O(1) i.e. constant as we are sorting the given 2D vector itself instead of creating a new
//	vector/multiset of pairs.
//	This method is slower but consumes less space. 

class Solution {
public:
    static bool cmp(vector<int> a, vector<int> b) {		//	For some reason, sort() function in leetcode needs us to 
        return a[1] > b[1];								//	use the keyword static before bool cmp() to make it work.
    }    
    int maximumUnits(vector<vector<int>> &bT, int tS) {
        sort(bT.begin(), bT.end(), cmp);
        //for (auto i : bT) cout<<i[0]<<" "<<i[1]<<"\n";
        int sum = 0;
        auto it = bT.begin();
        while(tS>0 && it!=bT.end()) {
            vector<int> curr = *it;
            int currBoxes = min(tS, curr[0]);
            tS = tS - currBoxes;
            sum = sum + currBoxes*(curr[1]);
            it++;
        }
        return sum;
    }
};