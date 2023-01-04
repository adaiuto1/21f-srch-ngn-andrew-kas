#ifndef INC_21F_FINAL_PROJ_TEMPLATE_HASHTABLE_H
#define INC_21F_FINAL_PROJ_TEMPLATE_HASHTABLE_H

#include <vector>
#include <algorithm>
using namespace std;
template<typename K, typename V>
class Hashtable{
private:
    vector<pair<K, V>>* table;
    int capacity = 0;
    int size = 0;
    vector<pair<K, V>>* newTable;
public:
    Hashtable<K, V>();
    ~Hashtable<K, V>();
    int getCapacity();
    V& insert(const K&, const V&);
    V& operator[](const K&);
    void resize();
    bool has(const K&);
};
template<typename K, typename V>
Hashtable<K, V>::Hashtable(){
    capacity = 100000;
    table = new vector<pair<K, V>>[capacity];
}
template<typename K, typename V>
Hashtable<K, V>::~Hashtable(){
    capacity = 0;
    delete[] table;
}
template<typename K, typename V>
int Hashtable<K, V>::getCapacity(){
    return capacity;
}
template<typename K, typename V>
bool Hashtable<K, V>::has(const K& tr){
    unsigned int hashVal = hash<K>{}(tr);
    int index = hashVal%100000;
    int inst = 0;
    for(int checkBucket = 0; checkBucket < table[index].size(); checkBucket++){
        if(table[index].at(checkBucket).first == tr){
            inst++;
        }
    }
    return inst > 0;
}
template<typename K, typename V>
void Hashtable<K, V>::resize(){
    cout << "capacity:" << capacity << endl;
    newTable = new vector<pair<K, V>>[capacity*2];
    cout << "notskipped" << endl;
    for(int copy = 0; copy < capacity; copy++){
        for(pair<K, V> v : table[copy]){
            newTable[copy].push_back(v);
            cout << v.first << " " << newTable[copy].back().first << endl;
        }
    }
    table = newTable;
    cout << "copydone" << endl;
}
template<typename K, typename V>
V& Hashtable<K, V>::insert(const K& key, const V& val){
    if(size == capacity-1){
        resize();
    }
    unsigned int hashVal = hash<K>{}(key);
    int index = hashVal%capacity;
    table[index].push_back(pair<K, V>(key, val));
    size++;
    return table[index].back().second;
}
template<typename K, typename V>
V& Hashtable<K, V>::operator[](const K& key){
    unsigned int hashVal = hash<K>{}(key);
    int index = hashVal%100000;
    if(table[index].size() > 0){
        for(int i = 0; i < table[index].size(); i++){
            if(table[index].at(i).first == key){
                return table[index].at(i).second;
            }
        }
    }
}
#endif //INC_21F_FINAL_PROJ_TEMPLATE_HASHITEM_H
