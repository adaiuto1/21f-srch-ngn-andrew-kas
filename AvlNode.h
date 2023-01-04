//
// Created by ABD on 11/10/2021.
//

#ifndef INC_21F_SRCH_NGN_ANDREW_KAS_AVLNODE_H
#define INC_21F_SRCH_NGN_ANDREW_KAS_AVLNODE_H
template<typename T>
class AvlNode{
public:
    T element;
    int height;
    AvlNode* left;
    AvlNode* right;
    AvlNode();
    ~AvlNode();
    AvlNode(const T&);
    AvlNode(const T&, AvlNode<T>*, AvlNode<T>*);
    void setHeight(const int&);
};
template<typename T>
AvlNode<T>::AvlNode(){
    left = nullptr;
    right = nullptr;
    height = 0;
}
template<typename T>
AvlNode<T>::AvlNode(const T& t){
    element = t;
}
template<typename T>
AvlNode<T>::AvlNode(const T& val, AvlNode<T>* lt, AvlNode<T>* rt){
    height = 1; //height 0 is reserved for null nodes
    element = val;
    left = lt;
    right = rt;
}
template<typename T>
AvlNode<T>::~AvlNode(){
    //delete[] element;
}
template<typename T>
void AvlNode<T>::setHeight(const int& sh){
    height = sh;
}
#endif //INC_21F_SRCH_NGN_ANDREW_KAS_AVLNODE_H
