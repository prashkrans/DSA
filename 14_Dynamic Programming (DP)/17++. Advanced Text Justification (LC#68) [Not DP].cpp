/* (LC#68) - Text Justification :
Given an array of words and a width maxWidth, format the text such that each line has exactly maxWidth characters 
and is fully (left and right) justified. You should pack your words in a greedy approach; that is, pack as many words 
as you can in each line. Pad extra spaces ' ' when necessary so that each line has exactly maxWidth characters.
Extra spaces between words should be distributed as evenly as possible. If the number of spaces on a line do not divide 
evenly between words, the empty slots on the left will be assigned more spaces than the slots on the right.
For the last line of text, it should be left justified and no extra space is inserted between words.
Note:
A word is defined as a character sequence consisting of non-space characters only.
Each word's length is guaranteed to be greater than 0 and not exceed maxWidth.
The input array words contains at least one word.*/

//	Running time = O(length * maxWidth)
//	Extra space = O(length + maxWidth)
//	Here length means the sum of the lengths of all the words in the vector<string>
//	Solution - https://www.youtube.com/watch?v=GqXlEbFVTXY&ab_channel=MichaelMuinos

class Solution {
public:    
string leftJustify(vector<string>& words, int diff, int i, int j){	//	Two different types of justification used
    string lAns = words[i];
    for(int k=i+1; k<j; k++){
        lAns = lAns + ' ' + words[k];
        diff--;
    }
    for(int l=0; l<diff; l++) lAns = lAns + ' ';        //  Appends the extra spaces at the end i.e. left justified
    return lAns;
}

string midJustify(vector<string>& words, int diff, int i, int j){
    string midAns = words[i];
    int noOfSpaces = j-i-1;
    if(noOfSpaces!=0){
        int equalSpaces = diff/noOfSpaces;              //  Value of equal spaces if no extra spaces are present
        int extraSpaces = diff%noOfSpaces;              //  Adding the extra spaces at the left 
        for(int k=i+1; k<j; k++){
            for(int x = 0; x<equalSpaces; x++) midAns = midAns + ' ';
            if(extraSpaces>0){
                midAns = midAns + ' ';              
                extraSpaces--;
            }
        midAns = midAns + words[k];
        }
    }
    return midAns;
}   

vector<string> fullJustify(vector<string>& words, int maxWidth) {
    vector<string> ans;
    int i = 0;
    int n = words.size();
    while(i<n){
        int j = i+1;
        int lineLen = words[i].size();
        while(j<n && lineLen + words[j].size() + (j - i) <= maxWidth){
            lineLen += words[j].size();
            j++;                            // Note - j is already incremented so we need to add from i to j-1
        }
        int diff = maxWidth - lineLen;
        int noOfWords = j - i;              // j -  i gives the no. of words to be added in a given line
        if(noOfWords == 1 || j>=n) ans.push_back(leftJustify(words, diff, i, j));       //  Two cases when left justify is used
        else ans.push_back(midJustify(words, diff, i, j));                              //  The only case when mid justify is used
        i = j;
    }
    return ans;
    }
};