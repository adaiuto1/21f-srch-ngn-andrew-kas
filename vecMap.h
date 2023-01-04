//
// Created by ABD on 11/16/2021.
//
#include "AvlTree.h"
#ifndef INC_21F_FINAL_PROJ_TEMPLATE_VECMAP_H
#define INC_21F_FINAL_PROJ_TEMPLATE_VECMAP_H
template<typename K, typename V>
class vecMap{
private:
    struct vecMapElement{
        K key;
        V value;
    };
    AvlTree<vecMapElement> data;
    int size;
    int capacity;
public:
    vecMap();
    V& getValue(const K& key);
    V& pushBack(const K& key, const V& val);
};
#endif //INC_21F_FINAL_PROJ_TEMPLATE_VECMAP_H
