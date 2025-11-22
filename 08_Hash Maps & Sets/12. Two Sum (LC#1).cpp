/*	Hashmap Problem #11 - LC#1. Two Sum
Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
You may assume that each input would have exactly one solution, and you may not use the same element twice.
You can return the answer in any order.

Example 1:
Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Output: Because nums[0] + nums[1] == 9, we return [0, 1].

Example 2:
Input: nums = [3,3], target = 6
Output: [0,1]
*/
// 	Running time = O(n) (0 ms in LC beats 100%)
//	Auxiliary space = O(n)

//	returnType funcName(vector<int> vectorname, int k) {
//		map and returnType declaration
//		for(auto key : keys) {
//			if(map.count(key)>0) {
//				if(map[key] satisfies the requirement {
//					return reqd. information;
//				}
//			}
//			map[key] = value //	any information that needs to be stored in the map as value e.g. index
//		}
//		return reqd. information;
//	}

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> mp;
        vector<int> ans;
        for(int i=0; i<nums.size(); i++) {
            if(mp.count(target-nums[i])>0) {
                ans.push_back(i);
                ans.push_back(mp[target-nums[i]]);
                break;
            }
            mp[nums[i]] = i;
        }
        return ans;
    }
};


// Same code as above except for a different naming convention.
class Solution {
    public:
        vector<int> twoSum(vector<int>& nums, int target) {
            unordered_map<int, int> uMap;
            vector<int> ans;
            for(int i=0; i<nums.size(); i++) {
                if(uMap.count(target - nums[i])) {
                    ans.push_back(uMap[target-nums[i]]);
                    ans.push_back(i);
                    break;
                }
                else uMap[nums[i]] = i;
            }
            return ans;
        }
    };