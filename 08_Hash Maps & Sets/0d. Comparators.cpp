#include<iostream>
#include<map>
#include<set>
using namespace std;
//  Note -
//  1.  A comparator only works for ordered containers like map, set, multimap, multiset, list, etc.
//  2.  A comparator changes the insert order itself, hence the traversal order gets modified. However O(insert) is still O(nlogn)
class setCmp {
public:
    bool operator() (int a, int b) const {
        return a < b;
    }
};

class mapCmpByLen {                          //  mapCmp takes two keys and not two values for comparison
public:
    bool operator() (string a, string b) const {
        return (a.size() > b.size());
    }
};

int main() {
	map<string, int> mp;
	mp["abc"] = -3;     mp["d"] = -1;   mp["efgh"] = -4;    mp["ij"] = -2;
	auto printMap = [](auto mp) {       //  Lambda function to print a map
	    cout<<"Printing map:\n";
		for(auto i : mp) cout<<i.first<<" "<<i.second<<"\n";
	};
	printMap(mp);                       //  Printing mp map which is without any comparator
	set<int> mySet;                     //  By default, a set stores the elements in an ascending order
	mySet.insert(1); mySet.insert(3); mySet.insert(4); mySet.insert(2);
	auto printSet = [] (auto mySet) {   //  Lambda function to print a set
	    cout<<"Printing set:\n";
        for(auto i : mySet) cout<<i<<" ";
        cout<<"\n";
	};
	printSet(mySet);
	set<int, greater<int>> mySet2;      //  greater<int> creates a descending order for the set mySet2
	mySet2.insert(1); mySet2.insert(3); mySet2.insert(4); mySet2.insert(2);
	printSet(mySet2);
	set<int, less<int>> mySet3;         //  less<int> creates an ascending order for the set mySet3, however a set in by default in ascending order so no need to use less<dT>
	mySet3.insert(1); mySet3.insert(3); mySet3.insert(4); mySet3.insert(2);
	printSet(mySet3);
	map<string, int, mapCmpByLen> mp2;  //  mapCmp takes two keys and not two values for comparison
	mp2["abc"] = 3;     mp2["d"] = 1;   mp2["efgh"] = 4;    mp2["ij"] = 2;
	//  mp2["klmn"] = 5; or mp2.insert({"klmn", 5}); Either does not insert the pair {"klmn", 5} as "efgh" of size 4 has already been inserted in the map
	printMap(mp2);
	multimap<string, int, mapCmpByLen> multimp;
	//  multimp["abc"] = 3 ;            //  Cannot use operator [] for a multimap so, instead need to use .insert()
	multimp.insert({"abc", 3});     multimp.insert({"d", 1});   multimp.insert({"efgh", 4});  multimp.insert({"ij", 2});
	multimp.insert({"klmn", 0});        //  Even this will create a duplicate string of length = 4, it would be inserted as a multimap can take duplicate values
    printMap(multimp);                  //  Here, {"efgh", 4} gets printed before {"klmn", 0}.
    //  So, now we need to modify our order such that if lengths or two strings are equal then we need to print the pair with the smaller int value
    //  This cannot be achieved by a map or a multimap hence we need to use a multiset as a set cannot take duplicate values

	return 0;
}
