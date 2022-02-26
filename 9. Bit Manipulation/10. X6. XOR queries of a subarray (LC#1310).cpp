/* Bit Manipulation problem: 10. (XOR problem 6.) LC#1310. XOR Queries of a Subarray
Given the array arr of positive integers and the array queries where queries[i] = [Li, Ri], for each query i 
compute the XOR of elements from Li to Ri (that is, arr[Li] xor arr[Li+1] xor ... xor arr[Ri] ). Return an array 
containing the result for the given queries.

Example 1:
Input: arr = [1,3,4,8], queries = [[0,1],[1,2],[0,3],[3,3]]
Output: [2,7,14,8] 
Explanation: 
The binary representation of the elements in the array are:
1 = 0001 
3 = 0011 
4 = 0100 
8 = 1000 
The XOR values for queries are:
[0,1] = 1 xor 3 = 2 
[1,2] = 3 xor 4 = 7 
[0,3] = 1 xor 3 xor 4 xor 8 = 14 
[3,3] = 8

Constraints:
1 <= arr.length <= 3 * 10^4
1 <= arr[i] <= 10^9
1 <= queries.length <= 3 * 10^4
queries[i].length == 2
0 <= queries[i][0] <= queries[i][1] < arr.length
*/

//	Method 1 - Creating a prefix array that stores the xor of all the elements till the ith position
//	Running time = O(n)
//	Auxiliary space = O(n)

class Solution {
public:
    vector<int> xorQueries(vector<int>& arr, vector<vector<int>>& q) {
        ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);  //  For fast input/output
        int n = arr.size();
        vector<int> ans;
        vector<int> prefix(n, 0);
        for(int i=0; i<n; i++) {
            if(i==0) prefix[i] ^= arr[i];
            else prefix[i] = prefix[i-1] ^ arr[i];	//	Using the property that A^A == 0
        }
        for(int i=0; i<q.size(); i++) {
            int L = q[i][0];
            int R = q[i][1];
            if(L==0) ans.push_back(prefix[R]);
            else ans.push_back(prefix[R]^prefix[L-1]);
        }
        return ans;
    }
};