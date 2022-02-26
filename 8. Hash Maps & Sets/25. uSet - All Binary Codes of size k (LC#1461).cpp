/* Set - Problem 1 (LC#1461)
Check If a String Contains All Binary Codes of Size K :
Given a binary string s and an integer k. Return true if every binary code of length k is a substring of s. 
Otherwise, return false.

Example 1:
Input: s = "00110110", k = 2
Output: true
Explanation: The binary codes of length 2 are "00", "01", "10" and "11". They can be all found as substrings at 
indicies 0, 1, 3 and 2 respectively.

Example 2:
Input: s = "0110", k = 2
Output: false
Explanation: The binary code "00" is of length 2 and doesn't exist in the array.
*/

//	1. 	My Code - 	a. Create a vector of all the binary no. of size == k i.e. 2^k-1 (Recursion - Bottom Up)
//					b. Find all the binary codes in the given string. Iff all are present return true else return false
// 		157 / 196 test cases passed. Rest for k>19 the time limit exceeds. 
// 		Running time = O(2^k)
// 		Space Complexity = O(2^k)
	
class Solution {
public:
    bool findSubstr(string s1, string s2){			// 	No need of the this function as we use inbuilt function called s1.find(s2)
        vector<int> pos;							// 	which finds the string s2 in s1 and returns 
        for(int i=0; i<s1.size(); i++){				//	a. the posn if s2 found in s1 
            if(s2[0]==s1[i]) pos.push_back(i);		//	b. string::npos if s2 is not found in s1
        }											// 	However this function also works just fine
        if(pos.empty()) return false;	
        else{
            for(int i=0; i<pos.size(); i++){
                if(s1.size()-pos[i]>=s2.size()){
                    string s3 = s1.substr(pos[i], s2.size());
                    if(s3==s2) return true;
                }
            }
        }
        return false;
    }
	
	int createBinaryCodes(string s, int k, vector<string> &out){// In the shorter version there is no need to create all the binary codes
        if(k==1){
            out[0]="0";
            out[1]="1";
            return 2;
        }
        int rec = createBinaryCodes(s, k-1, out);
        int l = 0;
        for(int i = 0; i<rec; i++) out[l++] = "0" + out[i]; // Just add "0" & "1" to the result of previous recursion
		for(int i = 0; i<rec; i++) out[l++] = out[i];
        for(int i = rec; i<2*rec; i++) out[i][0] = '1';        
        return 2*rec;        
    }
    
    bool findSubstring(string s, vector<string> out, int size){
        if(size==0) return false;
        for(int i=0; i<size; i++){
            if(s.find(out[i])==string::npos)
                return false;
        }
        return true;
    }    
    
    bool hasAllCodes(string s, int k) {
        vector<string> out(pow(2,k));
        int size = createBinaryCodes(s, k, out);
        //for(int i = 0; i<size; i++) cout<<out[i]<<"\n";
        //cout<<"Size = "<<size<<"\n";
        return findSubstring(s, out, size);
    }
};

//	2. 	Using a set. 
//		No need to create all the binary codes instead we just get all the substrings of size == k and store in a set.
//		If the size of the set is equal to 2^k then return true else return false. The only thing we need to take care of 
//		is that we don't store duplicate substrings i.e. use a lookup/find function.
//		Note we can also use a vector instead of a set but here lookup function takes O(N) time while lookup function for a set
//		takes O(logN) time where N <= 2^k. Hence a set is prefered over a vector 
// 		Running time = O(S*log2(2^k)) = O(Sk) (Quadratic) where S is the size of the string.
// 		Space Complexity = O(Sk)

class Solution {
public:   
    bool hasAllCodes(string s, int k) {
        if(k>s.size()) return false;        //  if k>s.size() then ans is false & also s.substr fails  
        set<string> output;
        for(int i=0; i<=s.size()-k; i++){
            output.insert(s.substr(i, k));  //  inserts a unique value i.e. does not insert a duplicate value
        }
        //cout<<"Output size = "<<output.size()<<" 2^"<<k<<" = "<<pow(2,k);
        if(output.size()==pow(2,k)) return true;
        else return false;
    }
};    

//	3. 	Using a hash function.
//		Running time = O(S) (Linear) where S is the size of the string.
// 		Space Complexity = O(2^k)
    