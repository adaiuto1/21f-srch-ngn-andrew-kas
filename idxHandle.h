//
// Created by ABD on 11/30/2021.
//OWNER: Andrew Daiuto
#include <fstream>
#include <iostream>
#include <algorithm>
#include "AvlTree.h"
#include "FileReader.h"
#include "porter2_stemmer.h"
#ifndef INC_21F_FINAL_PROJ_TEMPLATE_IDXHANDLE_H
#define INC_21F_FINAL_PROJ_TEMPLATE_IDXHANDLE_H
using namespace std;
class idxHandle{
private:
    ifstream inFile;
    ofstream oFile;
    string persFile;
public:
    idxHandle();
    vector<string>& search(AvlTree<Corpus_token>&, string&);
    vector<string>& searchAND(AvlTree<Corpus_token>&, string&, string&);
    vector<string>& searchOR(AvlTree<Corpus_token>&, string&, string&);
    vector<string>& filterNOT(vector<string>&, vector<string>&);
    vector<string>& filter(vector<string>&, Hashtable<string, vector<string>>&, const string&);
    void sortOutput(vector<pair<string, int>>&, vector<string>&);
    AvlTree<Corpus_token>& reconstruct(const string&);
};
idxHandle::idxHandle(){
}
vector<string>& idxHandle::search(AvlTree<Corpus_token>& tree, string& st){
    Corpus_token solo;
    Porter2Stemmer::trim(st);
    Porter2Stemmer::stem(st);
    solo.key = st;
    cout << st << endl;
    vector<string>* rslt = new vector<string>;
    AvlNode<Corpus_token>* cpt = tree.find(solo, tree.root);
    if(cpt != nullptr){
        for(string o : cpt->element.document_ids){
            rslt->push_back(o);
        }
    }
    return *rslt;
}
vector<string>& idxHandle::filterNOT(vector<string>& in, vector<string>& ex){
    vector<string> *difference = new vector<string>;
    for(string bad : in){
        if(count(ex.begin(), ex.end(), bad) == 0){
            difference->push_back(bad);
        }
    }
    return *difference;
}
void idxHandle::sortOutput(vector<pair<string, int>>& possible, vector<string>& output){
    for(int i = possible.size()-1; i > 0; i--){
        for(int j = 0; j < possible.size(); j++){
            if(possible.at(j).second < possible.at(i).second){
                pair<string, int> temp = possible.at(i);
                possible.at(i) = possible.at(j);
                possible.at(j) = temp;
            }
        }
    }
    for(int f = 0; f < possible.size(); f++){
        if(output.size() < 15){
            output.push_back(possible.at(f).first);
        }
    }
}
vector<string>& idxHandle::searchAND(AvlTree<Corpus_token>& tree, string& t1, string& t2) {
    Corpus_token term1;
    Porter2Stemmer::trim(t1);
    Porter2Stemmer::stem(t1);
    term1.key = t1;
    Corpus_token term2;
    Porter2Stemmer::trim(t2);
    Porter2Stemmer::stem(t2);
    term2.key = t2;
    vector<string> *intersection = new vector<string>;
    AvlNode<Corpus_token>* r1 = tree.find(term1, tree.root);
    AvlNode<Corpus_token>* r2 = tree.find(term2, tree.root);
    if(r1 != nullptr && r2 != nullptr){
        for(string o : r1->element.document_ids){
            for(string i : r2->element.document_ids){
                if(o == i){
                    intersection->push_back(o);
                }
            }
        }
    }
    else{
        cout << "NO RESULTS FOUND" << endl;
    }
    return *intersection;
}
vector<string>& idxHandle::searchOR(AvlTree<Corpus_token>& tree, string& t1, string& t2){
    Corpus_token term1;
    Porter2Stemmer::trim(t1);
    Porter2Stemmer::stem(t1);
    term1.key = t1;
    Corpus_token term2;
    Porter2Stemmer::trim(t2);
    Porter2Stemmer::stem(t2);
    term2.key = t2;
    vector<string> *un = new vector<string>;
    AvlNode<Corpus_token>* r1 = tree.find(term1, tree.root);
    AvlNode<Corpus_token>* r2 = tree.find(term2, tree.root);
    for(string t1p : r1->element.document_ids){
        un->push_back(t1p);
    }
    for(string t2p : r2->element.document_ids){
        un->push_back(t2p);
    }
    return *un;
}
vector<string>& idxHandle::filter(vector<string>& res, Hashtable<string, vector<string>>& cand, const string& target){
    vector<string>* contains = new vector<string>;
    if(cand.has(target)){
        vector<string>* subset = &cand[target];
        for(string check : res){
            for(string i : *subset){
                if(check == i){
                    contains->push_back(check);
                }
            }
        }
    }
    return *contains;
}
AvlTree<Corpus_token> &idxHandle::reconstruct(const string& pers) {
    string curr;
    inFile.open(pers);
    if(!inFile.is_open()){
        throw out_of_range("persistence file not found");
    }
    else{
        //curr
    }
}

#endif //INC_21F_FINAL_PROJ_TEMPLATE_idxHANDLE_H
