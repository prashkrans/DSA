/* DP Problem 17 - Text Justification :
Given a sequence of words, and a limit on the number of characters that can be put in one line (line width). Put line breaks
in the given sequence such that the lines are printed neatly. Assume that the length of each word is smaller than the line width.
The extra spaces includes spaces put at the end of every line except the last one.
The problem is to minimize the following total cost.
Cost of a line = (Number of extra spaces in the line)^3 or (No. of extra spaces in the line)^2
Eg. Given string s = "aaa bb cc ddddd" and limit on line width = 6
Soln.
aaa   |	=> 3
bb cc |	=> 1
ddddd |	=> 1
Thus the minimum cost = 3^3 + 1^3 + 1^3 = 27 + 1 + 1 = 29
*/

//	Need to convert the string into vector<string> words containing each words individually
//	Running Time = O(n^2) => CostTable[n-1][n-1] + for all i from n-1 to 0, j iterates from n-1 to i
//	Extra Space = O(n^2)

#include<iostream>
#include<vector>
#include<string>
using namespace std;

vector<string> senToWords(string s){
	vector<string> words;
	int j = 0;
	for(int i=0; i<s.size(); i++){
		if(s[i] == ' '){
			words.push_back(s.substr(j, i-j));
			j = i+1;
			i++;
		}
		else if(i == s.size()-1)
			words.push_back(s.substr(j, i-j+1));
	}
	return words;
}

vector<string> textJustn(vector<string> words, int n, int x){
    vector<vector<int>> c(n, vector<int>(n));       //  c represent the costTable i.e. if fits extraspace^3 else INF
    for(int i=0; i<n; i++){
        int size = 0;
        for(int j=i; j<n; j++){
            size += words[j].size();
            if(j>i) size++;
            int extraSpace = x-size;
            if(extraSpace>=0){
                int cost = extraSpace*extraSpace*extraSpace;
                //  or int cost = extraSpace*extraSpace;
                c[i][j] = cost;
            }
            else c[i][j] = INT_MAX;
        }
    }
    cout<<"The costTable = \n";
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++) cout<<c[i][j]<<" ";
        cout<<"\n";
    }
    vector<int> DP(n, INT_MAX);             //  So, need three storage objects i.e. costTable[][], DP[] and LB[]
    vector<int> LB(n, 0);                   //  DP[0] stores the minimum cost of arrangement
    for(int i=n-1; i>=0; i--){
        for(int j=n-1; j>=i; j--){          //  Note that its important that j varies from n-1 to i else if it varies from n-1 to i+1, we need to initialize DP[n-1] and LB[n-1]
            if(j==n-1 && c[i][j]!=INT_MAX){ //  The condition not for split but just copy the last val
                DP[i] = c[i][j];
                LB[i] = j+1;                //  Note - LB i.e. lineBreaks stores the value of j s.t words[j] is not included
                                            //  in the current line. Thus here its j+1 as j+1 == n
            }
            //  Two conditions for split i.e. 1. c[i][j] != INF or 2. c[i][j] = INF and c[i][j-1] != INF
            //  When c[i][j] = INF and c[i][j-1] = INF then just continue reducing j by 1
            else if(c[i][j]!=INT_MAX||(c[i][j]==INT_MAX && c[i][j-1] != INT_MAX)){
                if(DP[j]+c[i][j-1]<DP[i]){
                    DP[i] = DP[j] + c[i][j-1];  //  #IMP - Learn this formula
                    LB[i] = j;              //  Here LB stores j instead of j as the words[j] is not included in the line
                }
            }
        }
    }
    cout<<"DP = ";
    for(int i=0; i<n; i++) cout<<DP[i]<<" ";
    cout<<"\n";
    cout<<"LB = ";
    for(int i=0; i<n; i++) cout<<LB[i]<<" ";
    cout<<"\n";
    vector<string> jWords;
    int i=0;                                // We start from LB[0] and to all such LB[i] which corresponds to the minimum cost
    while(i<n){
        string line;
        for(int j=i; j<LB[i]; j++) line = line + words[j] + ' ';    //  i jumps from 0 to LB[0] to LB[i] and so on
        i = LB[i];
        jWords.push_back(line);                                     //  line stores a particular line
    }
    cout<<"The arrangement with the minimum cost = "<<DP[0]<<" is as follows: \n";
    return jWords;
}

int main(){
    cout<<"Enter the sentence/phrase = \n";
	string s;           //  Note - There needs to be only one space between the words
	getline (cin, s);   //  as cin>>s would stop taking input when it encounters the first space
	//cout<<s<<"\n";
	vector<string> words = senToWords(s);
	cout<<"The given sentence is converted to a vector of words = \n";
	for(int i=0; i<words.size(); i++){
		cout<<words[i]<<"\n";
	}
	int n = words.size();   //  n = no. of words in the given sentence
	cout<<"Enter the max width of a line = \n";
	int x;
	cin>> x;                //  limit on the line width
	vector<string> jWords = textJustn(words, n, x);
	for(int i=0; i<jWords.size(); i++) cout<<jWords[i]<<"\n";
	return 0;
}
