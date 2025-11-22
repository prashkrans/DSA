// Basics of hashmaps using the hashtable STL (unordered maps)
#include<iostream>
#include<utility>   //  Optional, used for using pair STL
#include<unordered_map>     //  Mandatory to use unordered maps
using namespace std;

int main() {
    unordered_map<string, int> map1;
    // 1. insertion
    // 1a. using the pair STL
    pair<string, int> p1;
    p1 = make_pair("abc", 3);
    cout<<p1.first<<" ";
    cout<<p1.second<<"\n";
    map1.insert(p1);
    // 1b. using [] operator
    map1["cde"] = 3;
    map1["ef"] = 2;
    // 1c. using make_pair() function
    map1.insert(make_pair("g", 1));
    // 1d. using the insert function and {} brackets
    map1.insert({"hi", 2});
    //  2. iteration
    cout<<"2a. Iteration in a map using an iterator: \n";
    unordered_map<string, int>::iterator it;
    for(it = map1.begin(); it!=map1.end(); it++)
        cout<<"Key = "<<it->first<<" Value = "<<it->second<<"\n";    // Note the use of -> operator for the iterator of the umap
    cout<<"2b. Iteration in a map without using an iterator: \n";
    for(auto i : map1)
        cout<<"Key = "<<i.first<<" Value = "<<i.second<<"\n";        //  Note the use of . operator for the element of the umap
    //  3. find or access values for a given key
    //  3a. using [] operator
    cout<<"The value of key abc = "<<map1["abc"]<<"\n";
    cout<<"The value of key xyz = "<<map1["xyz"]<<"\n";             //  This does not throw an error and instead adds "xyz" into the map with a default value assigned (here 0)
    //  3b. using .at() function
    cout<<"The value of key cde = "<<map1.at("cde")<<"\n";
    //cout<<"The value of key stu = "<<map1.at("stu")<<"\n";        //  This throws an error
    //  4. size of the map
    cout<<"The size of the unordered map1 is = "<<map1.size()<<"\n";
    //  5. erase the key-value pair
    //  5a. using a key
    cout<<"Erasing the element = {xyz, 0}\n";
    map1.erase("xyz");
    //  5b. using an iterator
    unordered_map<string, int>::iterator it1;
    it1 = map1.begin();
    it1++;  //  Note it1 = it1 + 2 is not correct
    it1++;
    cout<<"Erasing the element = "<<it1->first<<", "<<it1->second<<"\n";
    map1.erase(it1);
    cout<<"The size of the unordered map1 is = "<<map1.size()<<"\n";
    //  6. using the find() function
    if(map1.find("mno") == map1.end()) cout<<"mno is not found in the given umap\n";
    string key = "hi";
    if(map1.find(key) != map1.end()) cout<<key<<" is found in the given umap with value = "<<map1[key]<<"\n";
	//	7. clear the hashmap
	cout<<"Clearing the contents of the hashmap map1\n";
	map1.clear();
	cout<<"The size of the unordered map1 is = "<<map1.size()<<"\n";
	//	8. check whether the hashmap is empty
	if(map1.empty()) cout<<"The hashmap is empty\n";
    return 0;
}
