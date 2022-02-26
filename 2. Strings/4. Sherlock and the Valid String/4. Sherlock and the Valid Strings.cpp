/* 4. Sherlock and the Valid Strings
https://www.hackerrank.com/challenges/sherlock-and-valid-string/problem?h_l=interview&isFullScreen=true&playlist_slugs%5B%5D%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D%5B%5D=strings
*/

//	Running time = O(n) or O(nlog(n)) where n = s.size();
//	Auxiliary space = O(n)

string isValid(string s) {
    string ans = "NO";
    unordered_map<char, int> mp;		
    map<int, int> freq;							//	To store the count of frequencies
    for(int i=0; i<s.size(); i++) mp[s[i]]++;
    for(auto m : mp) freq[m.second]++;			//	Three cases: 1. f.size() == 1 	2. f.size() == 2  3. f.size() == 3
    if(freq.size()==2) {						//	If there are two different frequencies, then there could be 2 sub-casees 
        auto it = freq.begin();					//	a. f2 - f1 == 1  	b. f1 == 1 & f2 != 1 or 2 where f1 > f2
        auto jt = next(it, 1);
        int minV = min(it->second, jt->second);
        if(jt->first - it->first == 1 && minV == 1) ans = "YES";
        else if(it->first==1 and it->second==1) ans = "YES";        
    }
    else if(freq.size()==1) ans = "YES";
    //for(auto f : freq) cout<<f.first<<" "<<f.second<<"\n";
    return ans;
}
