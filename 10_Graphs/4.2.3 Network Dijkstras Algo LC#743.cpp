// LC#743. NCAG1. Network Delay Time

// Approach: Use Dijkstra's algo
// Running time: O(ElogV) i.e. O(mlogn) 
// Auxiliary space: O(n+m) due to the adjacency list

class Solution {
    public:
        int networkDelayTime(vector<vector<int>>& times, int n, int k) {
            int minTime = -1;
            vector<vector<pair<int, int>>> adjL(n+1, vector<pair<int, int>>()); // Using n+1 since nodes vary from 1 to n
            for(int i=0; i<times.size(); i++) {
                int u = times[i][0];
                int v = times[i][1];
                int wt = times[i][2];
                adjL[u].push_back({v, wt});
                // if(!adjL.count(v)) adjL[v]; This is not required as we are declaring adjL with size n
            }
            
            set<pair<int, int>> setPq;
            vector<int> dist(n+1, INT_MAX);
            for(int i=1; i<=n; i++) {
                if(i!=k) setPq.insert({dist[i], i});
            }
            dist[k] = 0;
            setPq.insert({dist[k], k});      
    
            while(!setPq.empty() && setPq.begin()->first != INT_MAX) {
                int u = setPq.begin()->second; // we need the node only 
                setPq.erase(setPq.begin());
                for(auto i: adjL[u]) {
                    int v = i.first;
                    int wt_uTov = i.second;
                    if(dist[u] + wt_uTov < dist[v]) {
                        auto it = setPq.find({dist[v], v});
                        if(it!=setPq.end()) setPq.erase(it);
                        dist[v] = dist[u] + wt_uTov;
                        setPq.insert({dist[v], v});
                    }
                }
            }
    
            for(int i=1; i<=n; i++) {
                // cout<<dist[i]<<" ";
                minTime = max(minTime, dist[i]);
            }
    
            return (minTime == INT_MAX) ? -1 : minTime;
        }
    };