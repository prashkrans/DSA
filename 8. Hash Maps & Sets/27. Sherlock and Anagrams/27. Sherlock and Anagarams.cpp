/*27. Sherlock and Anagrams
https://www.hackerrank.com/challenges/sherlock-and-anagrams/problem?h_l=interview&isFullScreen=true&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=dictionaries-hashmaps

*/

int nC2(int n) {								//	The total no. of pairs of particular group = nC2 where n = mp[anagram]
    return(n*(n-1)/2);
}

int sherlockAndAnagrams(string s) {				
    int count = 0;
    map<string, int> mp;
    for(int i=1; i<s.size(); i++) {
        for(int j=0; j<=s.size()-i; j++) {
            string curr = s.substr(j, i);
            cout<<curr<<" ";            
            sort(curr.begin(), curr.end());		//	This groups anagrams i.e. {aba, aab, baa} -> aab
            mp[curr]++;							//	It counts the no. of words that belong to a particular anagram group
        }
        cout<<"\n";
    }
    for(auto i : mp) {
        if(i.second>1) count += nC2(i.second);
        cout<<i.first<<" "<<i.second<<"\n";
    }
    return count;
}