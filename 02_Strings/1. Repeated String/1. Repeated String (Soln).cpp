*/
https://www.hackerrank.com/challenges/repeated-string/problem?isFullScreen=true&h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=warmup
*/

long repeatedString(string s, long n) {
    long c1 = 0, c2 = 0, q, r;
    for(int i=0; i<s.size(); i++)
        if(s[i]=='a') c1++;
    q = n/s.size();
    r = n%s.size();
    for(int i=0; i<r; i++)
        if(s[i]=='a') c2++;
    return c1*q + c2;
}