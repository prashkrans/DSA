/* 3. Alternating Characters
https://www.hackerrank.com/challenges/alternating-characters/problem?h_l=interview&isFullScreen=true&playlist_slugs%5B%5D%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D%5B%5D=strings
*/

//	Running time = O(n) where n = s.size();
//	Auxiliary space = O(n-1) ~ O(n)

int alternatingCharacters(string s) {
    int count = 0;
    char curr = s[0];
    for(int i=1; i<s.size(); i++) {
        if(curr == s[i]) {
            count++;
        }
        else curr = s[i];
    }
    return count;
}