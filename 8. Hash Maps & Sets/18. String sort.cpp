/*	Hashmap Problem #17 - Sort a string in O(n)
Given a string containing only lowercase letters, sort it in O(n) time

Example 1:
Input: s = "dbacab"
Output: "aabbcd"
*/

#include<iostream>
#include<algorithm>
#include<unordered_map>
using namespace std;

//	Method 1 - Using a hashmap
//	Running time = O(n)
//	Auxiliary space = O(1) ans only 26 lower case letter are present thus O(26) ~ O(1)

string sortString(string s) {
	unordered_map<char, int> mp;
	int n = s.size();
	string sortedS;
	for(int i=0; i<n; i++) mp[s[i]]++;
	for(char ch = 'a'; ch<='z';) {
		if(mp[ch]==0) ch++;                     //  ch is incremented only if mp[ch]==0
		else if(mp.count(ch)>0 && mp[ch]>0) {
			sortedS = sortedS + ch;
			mp[ch]--;
		}
	}
	return sortedS;
}

//	Method 2 - Using an array[26] as a hashmap
//	Running time = O(n)
//	Auxiliary space = O(1) ans only 26 lower case letter are present thus O(26) ~ O(1)

string sortString2(string s) {
    int arr[26] = {0};
    int n = s.size();
    string ans;
    for(int i=0; i<n; i++) arr[s[i]-'a']++;     //  It implies that 0 -> 'a', 1 -> 'b', ... and 25 -> 'z'
    for(int i=0; i<26; i++) {
        for(int j=0; j<arr[i]; j++) {
            char ch = 'a' + i;
            ans = ans + ch;                     //  Note - ans = ans + 'a' + i does not work
        }
    }
    return ans;
}

//  Method 3 - Using the inbuilt sort() function i.e. quicksort the given string
//  Running time = O(nlogn)
//  Auxiliary space = O(1) as we change the given array itself in quicksort

string sortString3(string s) {
    sort(s.begin(), s.end());
    return s;
}

int main() {
	cout<<"Enter the string to be sorted = \n";
	string s;
	cin>>s;
	string s1 = sortString(s);
	cout<<"The sorted string is = \n";
	cout<<s1<<"\n";
	string s2 = sortString2(s);
	cout<<"The sorted string is = \n";
	cout<<s2<<"\n";
	string s3 = sortString3(s);
	cout<<"The sorted string is = \n";
	cout<<s3<<"\n";
	return 0;
}
