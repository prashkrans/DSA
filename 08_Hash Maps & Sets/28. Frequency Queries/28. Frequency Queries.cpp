/* 28. Frequency Queries
https://www.hackerrank.com/challenges/frequency-queries/problem?h_l=interview&isFullScreen=true&playlist_slugs%5B%5D%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D%5B%5D=dictionaries-hashmaps
*/

vector<int> freqQuery(vector<vector<int>> q) {
    vector<int> res;
    int freq;
    unordered_map<int, int> mp, fMp;		//	mp stores {num, freq} while fMp stores {freq, count of freq}
    for(int i=0; i<q.size(); i++) {			//	So, while inserting and removing we need to update both mp and fMp
        int a = q[i][0];					//	Thus, we can access freq in O(1) insetead of O(n) thus becoming more efficient
        int b = q[i][1];
        if(a==1) {
            freq = mp[b];            
            mp[b]++;					
            fMp[freq]--;					// Since in insertion the frequency increases thus oount of current freq is reduced and next freq is increased
            fMp[freq+1]++;
        }
        else if(a==2) {
            if(mp[b]>0) {
                freq = mp[b];
                mp[b]--;
                fMp[freq]--;
                fMp[freq-1]++;
                if(mp[b]==0) mp.erase(b);
            }
        }
        else if(a==3) {
            int f = 0;
            if(fMp[b]>0) f = 1;
            res.push_back(f);
        }
    }
    return res;
}
