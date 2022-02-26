/* Graph problem - #7.3b. LC#743. Network Delay Time
You are given a network of n nodes, labeled from 1 to n. You are also given times, a list of travel 
times as directed edges times[i] = (ui, vi, wi), where ui is the source node, vi is the target node, 
and wi is the time it takes for a signal to travel from source to target.
We will send a signal from a given node k. Return the time it takes for all the n nodes to receive the 
signal. If it is impossible for all the n nodes to receive the signal, return -1.

Example 1:
Input: times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
Output: 2
*/

//	Method 1 - Bellman Ford algorithm
//	Running time = O(nm)
//	Auxiliary space = O(n+m) as we are converting the given edges into an adjacency list representation
class Solution {
public:
    
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        map<int, list<pair<int, int>>> adjL;
        for(int i=1; i<=n; i++) adjL[i];	//	Note - Here there can be nodes with both in & out degree = 0, and they are not included in 
        for(int i=0; i<times.size(); i++) {	//	the vector of vectors edges. But since we know that there are 1 to n nodes, already include them in the adjL;
            int u = times[i][0];
            int v = times[i][1];
            int wt = times[i][2];
            adjL[u].push_back({v, wt});
        }
        map<int, int> dist;
        for(auto i : adjL) {
            int v = i.first;
            dist[v] = INT_MAX;
        }
        dist[k] = 0;
        for(int i=1; i<=n-1; i++) {
            for(auto i : adjL) {
                int u = i.first;
                for(auto j : i.second) {
                    int v = j.first;
                    int wt = j.second;
                    if(dist[u]!=INT_MAX)
                        dist[v] = min(dist[v], dist[u] + wt);                    
                }
            }
        }           
        for(auto i : dist) cout<<i.first<<" "<<i.second<<"\n";
        for(auto i : dist) if(i.second==INT_MAX) return -1;	// 	if dist[v] = INT_MAX => it is unreachable hence return -1
        int maxVal = -1;
        for(auto i : dist) if(i.second>maxVal) maxVal = i.second;	//	the last node to be reached can be any node, hence the one with the maximum dist[] is 
        return maxVal;												//	the last node to be reached
    }
};