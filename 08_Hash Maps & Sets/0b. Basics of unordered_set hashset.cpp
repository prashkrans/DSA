#include<iostream>
#include <unordered_set>                // 0. include the library
using namespace std;

int main() {
    // 1. initialize a hash set
    unordered_set<int> hashset;
    // 2. insert a new key
    hashset.insert(3);
    hashset.insert(2);
    hashset.insert(1);
    // 3. delete a key
    hashset.erase(2);
    // 4. check if the key is in the hash set
    if (hashset.count(2) == 0) {
        cout << "Key 2 is not in the hash set." << endl;
    }
    if (hashset.count(1) == 0)
        cout << "Key 1 is not in the hash set." << endl;
    else
        cout<<"Key 1 is in the hash set." << endl;
    // 5. get the size of the hash set
    cout << "The size of hash set is: " << hashset.size() << endl;
    // 6. iterate the hash set
    // a. using auto
    for (auto it = hashset.begin(); it != hashset.end(); ++it) {
        cout << (*it) << " ";
    }
    cout << "are in the hash set." << endl;
    // b. without using auto
    unordered_set<int>::iterator itr;
    for (itr = hashset.begin(); itr != hashset.end(); itr++) cout<<(*itr)<<" ";
    cout << "are in the hash set." << endl;
    // 7. clear the hash set
    hashset.clear();
    // 8. check if the hash set is empty
    if (hashset.empty()) {
        cout << "hash set is empty now!" << endl;
    }
}

/*
Commonly used tables are:
int[26] for Letters 'a' - 'z' or 'A' - 'Z'
int[128] for ASCII
int[256] for Extended ASCII
*/