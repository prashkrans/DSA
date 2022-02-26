/* DP-Problem 12 - Rod Cutting Problem II or Minimum cost to cut a stick (LC#1547)
Given a wooden stick of length n units. The stick is labelled from 0 to n. For example, a stick of length 6 is 
labelled as follows:	0	1	2	3	4	5	6
Given an integer array cuts where cuts[i] denotes a position you should perform a cut at.
You should perform the cuts in order, you can change the order of the cuts as you wish.
The cost of one cut is the length of the stick to be cut, the total cost is the sum of costs of all cuts. 
When you cut a stick, it will be split into two smaller sticks (i.e. the sum of their lengths is the length of the 
stick before the cut). 

Input: n = 7, cuts = [1,3,4,5]
Output: 16
Explanation: Using cuts order = [1, 3, 4, 5] as in the input leads to the following scenario:
The first cut is done to a rod of length 7 so the cost is 7. The second cut is done to a rod of length 6 (i.e. the second 
part of the first cut), the third is done to a rod of length 4 and the last cut is to a rod of length 3. The total cost is 7 + 6 + 4 + 3 = 20.
Rearranging the cuts to be [3, 5, 1, 4] for example will lead to a scenario with total cost = 16 (7 + 4 + 3 + 2 = 16).

*/

//	1.	DP - Tabulation (Top Down) - My Code
//		Running Time = O(L^3*n) - Biquadratic therefore slower hence fails to pass all the test cases due to time limit
//		Extra Space = O(L^2)
//		Refer DP-Problem 5b. Unbounded Knapsack Problem

class Solution {
public:
    int minCost(int L, vector<int>& c) {
        sort(c.begin(), c.end());
        vector<vector<int>> DP(L+1, vector<int>(L+1, 0));
        for(int diff = 2; diff<=L; diff++){
            for(int i=0; i<=L-diff; i++){
                int j = i+diff;
                int minVal = INT_MAX;
                for(int k=i+1; k<j; k++){
                    int found = 0;
                    for(int l=0; l<c.size(); l++){
                        if(c[l]==k){
                            found = 1;
                            break;
                        }
                    }
                    if(found==1){
                        int kVal = DP[i][k] + DP[k][j];
                        if(kVal<minVal) minVal = kVal;
                    }
                }
                if(minVal == INT_MAX) DP[i][j] = 0;
                else DP[i][j] = minVal + j-i;
            }
        }
        return DP[0][L];
    }
};

//	2. 	DP - Tabulation (Top Down)
//		Running Time = O(n^3) - Cubic therefore much better solution than code no. 1
//		Extra Space = O(n^2) < O(L^2)
//		Refer to discuss page in leetcode for this problem
//		Make sure to write the code later