/* https://leetcode.com/explore/learn/card/hash-table/182/practical-applications/1140/
Design a HashMap without using any built-in hash table libraries.
Implement the MyHashMap class:
MyHashMap() initializes the object with an empty map.
void put(int key, int value) inserts a (key, value) pair into the HashMap. If the key already exists in the map, update the corresponding value.
int get(int key) returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key.
void remove(key) removes the key and its corresponding value if the map contains the mapping for the key.

Constraints:
0 <= key, value <= 106
At most 104 calls will be made to put, get, and remove.
*/

class MyHashMap {
public:
    /** Initialize your data structure here. */
    int a[1000001];
    MyHashMap() {
        for(int i=0; i<1000001; i++) a[i] = -1;
    }

    /** value will always be non-negative. */
    void put(int key, int value) {
        a[key] = value;
    }

    /** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
    int get(int key) {
        if(a[key]!=-1)
            return a[key];
        else return -1;
    }

    /** Removes the mapping of the specified value key if this map contains a mapping for the key */
    void remove(int key) {
        a[key] = -1;
    }
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */
