/*  DP Problem 24. LC#494. Target Sum
You are given an integer array nums and an integer target.
You want to build an expression out of nums by adding one of the symbols '+' and '-' before each integer
in nums and then concatenate all the integers.
For example, if nums = [2, 1] and target = 1, you can add a '+' before 2 and a '-' before 1 and concatenate 
them to build the expression "+2-1" == "1".
Return the number of different expressions that you can build, which evaluates to target.

Example 1:
Input: nums = [1,1,1,1,1], target = 3
Output: 5
Explanation: There are 5 ways to assign symbols to make the sum of nums be target 3.
-1 + 1 + 1 + 1 + 1 = 3		+1 - 1 + 1 + 1 + 1 = 3
+1 + 1 - 1 + 1 + 1 = 3		+1 + 1 + 1 - 1 + 1 = 3
+1 + 1 + 1 + 1 - 1 = 3

Constraints:
1 <= nums.length <= 20
0 <= nums[i] <= 1000
0 <= sum(nums[i]) <= 1000
-1000 <= target <= 1000

It can be solved using three methods: 
1.	DP (recursive DP)
2. 	DP (iterative)
3.	Recursion without memoization
*/

//	Method 1. Recursion with memoization i.e. recursive DP tabultaion
//	Recursion here acts as a DFS traversal for a binary tree
//	Note - We could use a DP table as a vector of vectors or as a map (we cannot use unordered_map as it does not support pair<int, int>)
//	Also, DP table as a 2D vector would be faster than a map as insertion takes place in O(1) time instead of O(logn).
//	It's not good to use the constraint as a parameter such as 1000, 2000. So, its better to use a map here or define an variable offset = (2*summation(nums[i])+1)
//	i.e. twice the sum of all the elements in the nums[] array plus one and then define memo as vector<vector<int>> memo(n, vector<int>(offset, INT_MIN)) and 
//	use memo as memo[i][sum + offset/2]

//	Running time = O(n*m) where n is the size of nums array and m is the range of sum in the recursion (here -1000 to 1000)
//	Auxiliary space = O(n*m) i.e. the size of the DP table


class Solution {
public:
    int recnWithMemo(int n, vector<int> nums, int target, vector<vector<int>> &memo, int sum, int i, int offset) {
    //int recnWithMemo(int n, vector<int> nums, int target, map<pair<int, int>, int> &memo, int sum, int i) {
        if(i==n) {  //  Note this base case should be at the top because if (i==n) memo[i][sum + 1000] does not exist.
                if(sum==target) return 1;
                else return 0;
            }
        else {
            if(memo[i][sum + offset/2] != INT_MIN) return memo[i][sum + offset/2];
            //if(memo.count({i, sum}) > 0) return memo[{i, sum}];
            else {                      
                int left = recnWithMemo(n, nums, target, memo, sum+nums[i], i+1, offset);	//	Left child is sum + nums[i]
                int right = recnWithMemo(n, nums, target, memo, sum-nums[i], i+1, offset);	//	Right child is sum - nums[i]
                memo[i][sum + offset/2] = left + right;									//	Add the results of both left and right 
                return memo[i][sum + offset/2];
                //memo[{i, sum}] = left + right;
                //return memo[{i, sum}];
            }
        }
    }    
    int findTargetSumWays(vector<int>& nums, int target) {
        int n = nums.size();
        int offset = 0;
        for(int i=0; i<n; i++) offset += nums[i];
        offset = 2*offset + 1;
        vector<vector<int>> memo(n, vector<int>(offset, INT_MIN));    // -1000 to 1000 => we need the array size to be as (n x 2001)
        //  i.e. 0 maps -1000, 1 maps -999, ... 1000 maps 0, ... 2000 maps 1000
        //map<pair<int, int>, int> memo;
        int ans = recnWithMemo(n, nums, target, memo, 0, 0, offset);        // Both sum and i are 0 initially.
        return ans;
    }
};
//	Method 2. DP using a 2D DP array (iterative)
//	Incomplete

//	Method 3. Recursion without memoization
//	Running time = O(2^n) i.e. exponential since each element has two options whether to be added or be subtracted.
//	=> 2.2.2....n times 
//	Auxiliary space  = O(count) if recursion call stack is not considered, else O(2^n) 

class Solution {
public:
    void numWays(int n, vector<int>::iterator it, int target, int &count) {
        if(n==0) {										//	if the size of the nums array is zero then
            if(target==0) count++;						//	we might make target == 0 or not 0
            return;										//	if target == 0, an arrangement exists so, increment count
        }        										//	else just return without incrementing count
        int curr = *it;
        numWays(n-1, it+1, target+curr, count);			//	each element here nums[0] has two options 
        numWays(n-1, it+1, target-curr, count);        	//	i.e. to be added or to be subtracted
    }
    int findTargetSumWays(vector<int>& nums, int target) {
        int count = 0;
        int n = nums.size();
        numWays(n, nums.begin(), target, count);
        return count;
    }
};

