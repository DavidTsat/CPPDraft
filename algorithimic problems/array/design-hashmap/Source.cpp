#include <iostream>
#include <vector>

using namespace std;

class MyHashMap {
    const size_t sz = 100000;
    vector<int> v;
    hash<int> h{};
public:
    MyHashMap() {
        v = vector<int>(sz, -1);
    }

    void put(int key, int value) {
        int c = int(h(key) % sz);
        v[int(h(key) % sz)] = value;
    }

    int get(int key) {
        if (v[int(h(key) % sz)] == -1) return -1;
        return v[int(h(key) % sz)];
    }

    void remove(int key) {
        v[int(h(key) % sz)] = -1;
    }
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */

int main()
{

    MyHashMap* myHashMap = new MyHashMap();
    myHashMap->put(1, 1); // The map is now [[1,1]]
    myHashMap->put(2, 2); // The map is now [[1,1], [2,2]]
    myHashMap->get(1);    // return 1, The map is now [[1,1], [2,2]]
    myHashMap->get(3);    // return -1 (i.e., not found), The map is now [[1,1], [2,2]]
    myHashMap->put(2, 1); // The map is now [[1,1], [2,1]] (i.e., update the existing value)
    myHashMap->get(2);    // return 1, The map is now [[1,1], [2,1]]
    myHashMap->remove(2); // remove the mapping for 2, The map is now [[1,1]]
    myHashMap->get(2);    // return -1 (i.e., not found), The map is now [[1,1]]

    return 0;
}