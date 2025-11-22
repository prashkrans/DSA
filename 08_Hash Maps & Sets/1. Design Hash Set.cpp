/* https://leetcode.com/explore/learn/card/hash-table/182/practical-applications/1139/
Design a HashSet without using any built-in hash table libraries.
Implement MyHashSet class:
void add(key) Inserts the value key into the HashSet.
bool contains(key) Returns whether the value key exists in the HashSet or not.
void remove(key) Removes the value key in the HashSet. If key does not exist in the HashSet, do nothing.

Constraints:
0 <= key <= 106
At most 104 calls will be made to add, remove, and contains.
*/

class MyHashSet {
public:
    /** Initialize your data structure here. */
    int a[1000001];
    MyHashSet() {
        for(int i=0; i<1000001; i++) a[i] = 0;
    }

    void add(int key) {
        if(a[key]==0) a[key] = 1;
    }

    void remove(int key) {
        if(a[key]==1) a[key] = 0;
    }

    /** Returns true if this set contains the specified element */
    bool contains(int key) {
        if(a[key]==1) return 1;
        else return 0;
    }
};

/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet* obj = new MyHashSet();
 * obj->add(key);
 * obj->remove(key);
 * bool param_3 = obj->contains(key);
 */
