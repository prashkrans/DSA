/* 2. Making Anagrams
https://www.hackerrank.com/challenges/ctci-making-anagrams/problem?isFullScreen=true&h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=strings
*/

// 	Running time = O(n+m)
//	Auxiliary space = O(n+m) where n = a.size() and m = b.size()

int makeAnagram(string a, string b) {
    int count = 0;
    unordered_map<char, int> mpA, mpB;
    for(int i=0; i<a.size(); i++) mpA[a[i]]++;
    for(int j=0; j<b.size(); j++) mpB[b[j]]++;
    unordered_map<char, int>::iterator it;
    for(it = mpA.begin(); it!=mpA.end(); it++) {
        if(mpB[it->first]>0) {
            if(it->second > mpB[it->first]) {
                count += mpB[it->first];
                it->second -= mpB[it->first];
                mpB[it->first] = 0;
            }
            else {
                count += it->second;
                mpB[it->first] -= it->second;
                it->second = 0;
            }
        }
    }
    return (a.size()+b.size()-2*count);
}