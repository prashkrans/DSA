#include<iostream>
#include<string>
using namespace std;

/*
1.  string::iterator itName = str.begin()+val<size or str.end()-val<=size;
2.  string::reverse_iterator ritName = str.rbegin()+val<size or srt.rend()-val<=size;
3.  s.end();    // after the last char
4.  s.rend();   // before the first char
5.  s.size(); or s.length();
6.  s.clear();  // clears the content of the string
7.  s.empty();  // returns true if the string is empty else returns false
8.  s[pos] or s.at(pos);
9.  s.append(s2) or s.append("any seq of chars") // this is the same as s = s+s2 or s = s + "any seq of chars";
10. s.find(s2); s.find("abc"); s.find(char c); s.find('a'); s.find(s2.substr(pos, len));
// If the string/character is found, it returns the position (first occurrence) at which it was found, else it
returns string::npos which is an invalid value that can never represent the index.
11. s.substr(pos); s.substr(pos, len); // # Most Important method.
//Here,     pos: Position of the first character to be copied
//          len: Length of the sub-string
// If the len is not mentioned it fetches the substring from the given pos to the end of the string
*/
void find_s2_in_s1(string s1, string s2){
    int pos = s1.find(s2);
    if(pos == string::npos) cout<<"s2 is not present in s1\n";
    else cout<<"s2 is present in s1\n";
}


int main(){
string str1 = "Hello";
string str2 = "World";
string str3, str4;
cin>>str3;           // Stops taking input at the first space
getline(cin, str4);  // Includes spaces but stops taking input at the first enter press (i.e. accpets one line only)
cout<<str1+str2<<"\n";
cout<<str3<<"\n";
cout<<str4<<"\n";
string s1 = "abcdef";
string s2 = "def";
string s3 = "ghij";
find_s2_in_s1(s1, s2);
find_s2_in_s1(s1, s3);
return 0;
}
