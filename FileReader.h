//
// Created by Kas on 11/14/21.
//

#ifndef INC_21F_FINAL_PROJ_TEMPLATE_FILEREADER_H
#define INC_21F_FINAL_PROJ_TEMPLATE_FILEREADER_H



#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/ostreamwrapper.h"
#include <unordered_set>
#include <algorithm>
//#include <cctype>
#include <cstdio>
#include "porter2_stemmer.h"
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <filesystem>
#include "AvlNode.h"
#include "AvlTree.h"
#include "Hashtable.h"
#include "vector"


using namespace rapidjson;
using namespace std;
namespace fs = std::filesystem;
using namespace std;

struct Corpus_token{
    std::string key;
    std::vector<std::string> document_ids;
    Corpus_token& operator=(const Corpus_token& as){
        key = as.key;
        document_ids = as.document_ids;
        return *this;
    }
    bool operator<(const Corpus_token &token) const {
        return key.compare(token.key) < 0;
    }
    bool operator>(const Corpus_token &token) const {
        return key.compare(token.key) > 0;
    }
    bool operator==(const Corpus_token eq){
        return key == eq.key;
    }

};


class FileReader {

public:
    //    int open_dir_using_dirent(char* path);
    ofstream oFile;
    ifstream inFile;
    void preFile(AvlNode<Corpus_token>*&);
    void printPersistence();
    AvlTree<Corpus_token>tree;
    Hashtable<string, vector<string>> orgs;
    Hashtable<string, vector<string>> people;
    vector<string> orgsToPersist;
    vector<string> peopleToPersist;
    void open_dir_using_filesystem(const char* path);
    void Parse(const char* filename);
    int getFrequency(const char*, string&);
    void titleParser(const char* filename);
    void refillMetadata(const char*);
    void extractPeopleOrgs(const char*);
    void readPersistence(const char* persistence);
    void getOrgs(const char* filename);
    void getPeople(const char* filename);
};


#endif //INC_21F_FINAL_PROJ_TEMPLATE_FILEREADER_H