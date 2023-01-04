//
// Created by ABD on 11/10/2021.
//OWNER: Andrew Daiuto
#include "AvlNode.h"
#include <iostream>
#include <fstream>
#ifndef INC_21F_FINAL_PROJ_TEMPLATE_AVLTREE_H
#define INC_21F_FINAL_PROJ_TEMPLATE_AVLTREE_H


template<typename T>
class AvlTree{
private:
    int setH = 0;
    std::string output;
    std::ofstream oFile;
public:
    AvlNode<T>* root;
    int size;
    int balFac;
    int max(int a, int b){return (a > b)? a : b;} //geeksforgeeks max strategy
    AvlTree<T>();
    ~AvlTree<T>();
    void empty(AvlNode<T>*&);
    void insert(const T&, AvlNode<T>*&);
    AvlNode<T>* rightRot(AvlNode<T>*&);
    AvlNode<T>* leftRot(AvlNode<T>*&);
    AvlNode<T>* find(const T&, AvlNode<T>*&);
    AvlNode<T>* deleteNode(const T&, AvlNode<T>*&);
    AvlNode<T>* getMinNode(AvlNode<T>*&);
    AvlNode<T>* getMaxNode(AvlNode<T>*&);
    int getNodeHeight(AvlNode<T>*&);
    void balance(AvlNode<T>*&);
    void preOrder(AvlNode<T>*&);
    void preOrdertoFile(const std::ostream&, AvlNode<T>*&);
    void postOrder(AvlNode<T>*&);
    void inOrder(AvlNode<T>*&);
};
template<typename T>
AvlTree<T>::AvlTree(){
    root = nullptr;
    size = 0;
}
template<typename T>
AvlTree<T>::~AvlTree<T>(){
    //empty(root);
}
template<typename T>
AvlNode<T>* AvlTree<T>::find(const T& data, AvlNode<T>*& token){
    if (token == nullptr) {
        return nullptr;
    }
    if(data > token->element){
        return find(data, token->right);
    }
    else if(data < token->element){
        return find(data, token->left);
    }
    else{
        return token;
    }
}

template<typename T>
void AvlTree<T>::insert(const T& val, AvlNode<T>*& ins){
    if(ins == nullptr){
        ins = new AvlNode<T>(val, nullptr, nullptr);
    }
    else if(val < ins->element){
        //inserting an element increments the height of all its parents
        ins->height++;
        insert(val, ins->left);
    }
    else if(val > ins->element){
        ins->height++;
        insert(val, ins->right);
    }
    balance(ins);
}

template<typename T>
void AvlTree<T>::balance(AvlNode<T>*& bal){
    balFac = getNodeHeight(bal->right) - getNodeHeight(bal->left);
    if(balFac >= 2){ //unbalanced from right side
        //check if right side is left/right heavy (can't be even since we are balancing at every insertion)
        if(getNodeHeight(bal->right->right) > getNodeHeight(bal->right->left)){ //case 4
            bal = leftRot(bal);
        }
        else{ //case 3
            bal->right = rightRot(bal->right);
            bal = leftRot(bal);
        }
    }
    else if(balFac <= -2){
        //check if left side is left/right heavy
        if(getNodeHeight(bal->left->left) > getNodeHeight(bal->left->right)){ //case 1
            bal = rightRot(bal);
        }
        else{ // case 2
            bal->left = leftRot(bal->left);
            bal = rightRot(bal);
        }
    }
}
template<typename T>
AvlNode<T>* AvlTree<T>::getMinNode(AvlNode<T>*& min){
    if(min->left == nullptr){
        return min;
    }
    else{
        return getMinNode(min->left);
    }
}
template<typename T>
AvlNode<T>* AvlTree<T>::getMaxNode(AvlNode<T>*& max){
    if(max->right == nullptr){
        return max;
    }
    else{
        return getMaxNode(max->right);
    }
}/*
template<typename T>
AvlNode<T>* AvlTree<T>::deleteNode(const T& val, AvlNode<T>*& del){
    if(del == nullptr){
        return nullptr;
    }
    else if(val < del->element){
        del->left = deleteNode(val, del->left);
    }
    else if(val > del->element){
        del->right = deleteNode(val, del->right);
    }
    else{
        if(del->left == nullptr || del->right == nullptr){
            AvlNode<T>* temp = del->left ? del->left : del->right;
            if(temp == nullptr){
                temp = del; //assign value of current node* to temp
                del = nullptr; //delete current node*
                //we want to delete both temp and del, using delete[] del; here wouldn't accomplish that
            }
            else{
                del = temp; //reassign current node to its child. stitching the wound
            }
            //wait until
            delete[] temp;
        }
        else{
            AvlNode<T>* temp;
            temp = getMinNode(del->right);
            del->element = temp->element;
            del->right = deleteNode(val, del->right);
        }
    }
    if(del == nullptr){
        return del;
    }
    //del->height = max(del->left->height, del->right->height);
    balance(del);
}*/
template<typename T>
AvlNode<T>* AvlTree<T>::rightRot(AvlNode<T>*& y){
    AvlNode<T>* x = y->left; //node to be pulled up
    AvlNode<T>* nc = x->right; //node to be reassigned as y's child
    x->right = y; //pull x "above" y, leaving y hanging down on the right
    y->left = nc; //reassign x's right child to be y's left child, now detached from x
    y->height = max(getNodeHeight(y->left), getNodeHeight(y->right)) + 1; //use height() to accommodate for 0 heights in any null subtrees
    x->height = max(getNodeHeight(x->left), getNodeHeight(x->right)) + 1;
    return x; //new root of current subtree
    //y's right child node/subtree remains the same
}
template<typename T>
AvlNode<T>* AvlTree<T>::leftRot(AvlNode<T>*& y){
    AvlNode<T>* x = y->right; //node to be pulled up
    AvlNode<T>* nc = x->left; //node to be reassigned as y's child
    x->left = y; //pull x "above" y, leaving y hanging down on the left
    y->right = nc; //reassign x's left child to be y's right child, now detached from x
    x->height = max(getNodeHeight(x->left), getNodeHeight(x->right)) + 1;
    y->height = max(getNodeHeight(y->left), getNodeHeight(y->right)) + 1;
    return x; //new root of current subtree
    //y's right child node/subtree remains the same
}
template<typename T>
void AvlTree<T>::preOrder(AvlNode<T>*& pre){
    if(pre == nullptr){
        return;
    }
    else{
        std::cout << pre->element << std::endl;
        preOrder(pre->left);
        preOrder(pre->right);
    }
}
template<typename T>
void AvlTree<T>::postOrder(AvlNode<T>*& post){
    if(post == nullptr){
        return;
    }
    else{
        postOrder(post->left);
        postOrder(post->right);
        std::cout << post->element << std::endl;
    }
}
template<typename T>
void AvlTree<T>::inOrder(AvlNode<T>*& in){
    if(in == nullptr){
        return;
    }
    else{
        inOrder(in->left);
        std::cout << in->element << std::endl;
        inOrder(in->right);
    }
}
template<typename T>
void AvlTree<T>::preOrdertoFile(const std::ostream& op, AvlNode<T>*& pre){
    if(pre == nullptr){
        return;
    }
    else{
        op << pre->element << std::endl;
        preOrdertoFile(op,pre->left);
        preOrdertoFile(op,pre->right);
    }
}

template<typename T>
void AvlTree<T>::empty(AvlNode<T>*& del){
    if(del != nullptr){
        empty(del->left);
        empty(del->right);
        delete[] del;
    }
    else{
        return;
    }
}
template<typename T>
int AvlTree<T>::getNodeHeight(AvlNode<T>*& gh){
    if(gh == nullptr){
        return 0; //height 0 reserved for null
    }
    else{
        return gh->height;
    }
}


#endif //INC_21F_FINAL_PROJ_TEMPLATE_AVLTREE_H
