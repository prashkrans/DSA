/* DP Problem 17 - Text Justification :
Given a sequence of words, and a limit on the number of characters that can be put in one line (line width). Put line breaks
in the given sequence such that the lines are printed neatly. Assume that the length of each word is smaller than the line width.
The extra spaces includes spaces put at the end of every line except the last one.
The problem is to minimize the following total cost.
Cost of a line = (Number of extra spaces in the line)^3 or (No. of extra spaces in the line)^2
Eg. Given string s = "aaa bb cc ddddd" and limit on line width = 6
Instead given length of strings as an array i.e. lenOfWords = {3, 2, 2, 5} and limit = 6
Soln.
aaa   |	=> 3    => 6-3 = 3
bb cc |	=> 5    => 6-5 = 1
ddddd |	=> 5    => 6-5 = 1
Thus the minimum cost = 3^3 + 1^3 + 1^3 = 27 + 1 + 1 = 29
*/

//	Running Time = O(n^2) => CostTable[n-1][n-1] + for all i from n-1 to 0, j iterates from n-1 to i
//	Extra Space = O(n^2)

#include<iostream>
#include<vector>
using namespace std;

vector<vector<int>> textJustnOrder(vector<int> lenOfWords, int n, int x){
    vector<vector<int>> c(n, vector<int>(n));       //  c represent the costTable i.e. if fits extraspace^2 else INF
    for(int i=0; i<n; i++){
        int size = 0;
        for(int j=i; j<n; j++){
            size += lenOfWords[j];
            if(j>i) size++;
            int extraSpace = x-size;
            if(extraSpace>=0){
                //int cost = extraSpace*extraSpace;   //  Here the cost is quadratic
                int cost = extraSpace*extraSpace*extraSpace;
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
    vector<vector<int>> jOrder;
    int i=0;                                // We start from LB[0] and to all such LB[i] which corresponds to the minimum cost
    while(i<n){
        vector<int> line(2);
        line[0] = i+1;
        line[1] = LB[i];
        i = LB[i];
        jOrder.push_back(line);                                     //  line stores a particular line
    }
    cout<<"The arrangement with the minimum cost = "<<DP[0]<<" is as follows: \n";
    return jOrder;
}

int main(){
    cout<<"Enter the size of the array lenOfWords = \n";
    int n;
    cin>>n;
    cout<<"Enter the length of the individual words = \n";
    vector<int> lenOfWords(n);
    for(int i=0; i<n; i++) cin>>lenOfWords[i];
	cout<<"Enter the max width of a line = \n";
	int x;
	cin>> x;                //  limit on the line width
	vector<vector<int>> jOrder = textJustnOrder(lenOfWords, n, x);
	for(int i=0; i<jOrder.size(); i++) cout<<"Line no. "<<i+1<<": "<<"contains word no. "<<jOrder[i][0]<<" to "<<jOrder[i][1]<<"\n";
	return 0;
}
