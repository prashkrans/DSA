/* Greedy Solution
Given a string “aaa bb cc ddddd” and line width as 6.
Greedy method will produce following output.
aaa bb
cc
ddddd
But the above solution is not the best solution. Following arrangement has more balanced spaces.
Therefore less value of total cost function.
aaa
bb cc
ddddd
*/

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
    vector<vector<int>> costTable(n, vector<int>(n));
    for(int i=0; i<n; i++){
        int size = 0;
        for(int j=i; j<n; j++){
            size += words[j].size();
            if(j>i) size++;
            int extraSpace = x-size;
            if(extraSpace>=0){
                int cost = extraSpace*extraSpace*extraSpace;
                costTable[i][j] = cost;
            }
            else costTable[i][j] = INT_MAX;
        }
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++) cout<<costTable[i][j]<<" ";
        cout<<"\n";
    }
    int i=0;
    vector<string> jWords;
    while(i<n){
        int j = i;
        int minVal = INT_MAX;
        int lineBreakPos = 0;
        while(j<n){
            if(costTable[i][j] <= minVal){
                minVal = costTable[i][j];
                lineBreakPos = j;
            }
            j++;
        }
        string line;
        for(int k=i; k<=lineBreakPos; k++){
            if(k==i) line = line + words[k];
            else line = line + ' ' + words[k];
        }
        jWords.push_back(line);
        i = lineBreakPos+1;
    }
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
