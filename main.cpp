#include <iostream>
#include "AvlTree.h"
#include "AvlNode.h"
#include "idxHandle.h"
using namespace std;
int main(int argc, char* argv[]) {
    //AUTHOR/CORP PARSING AND STORAGE- not done
    //SEARCH BY AUTHOR/CORP - DONE
    //AVLTREE DESTRUCTOR -not done
    idxHandle p;
    int selection = 0;
    int sub = 0;

    FileReader file;
    AvlTree<Corpus_token>* wordIndex = &file.tree;
    Hashtable<string, int> t;
    Hashtable<string, vector<string>>* orgTable = &file.orgs;
    Hashtable<string, vector<string>>* personTable = &file.people;
    vector<string> results;
    vector<string> exclude;
    vector<string> finalOutput;
    vector<pair<string, int>> relevantResults;
    string duo, entry, fpath, word1, word2, ext1, ext2, ext3, clar1, clar2, clar3;
    while(1){
        cout << "enter selection #" << endl;
        cout << "[0] Parse dataset" << endl;
        cout << "[1] Parse from persistence" << endl;
        cout << "[2] Search Data" << endl;
        cout << "[9] Exit" << endl;
        cin >> selection;
        if(selection == 9){
            break;
        }
        switch(selection){
            case 0:
                cout << "Enter dataset path" << endl;
                cin >> fpath;
                cout << "parsing" << endl;
                file.open_dir_using_filesystem(fpath.c_str());
                cout << "complete" << endl;
                cout << "Save to persistence? {1/0}" << endl;
                cin >> selection;
                if(selection == 1){
                    cout << "printing to persistence.txt" << endl;
                    file.printPersistence();
                    cout << "complete" << endl;
                }
                else{
                    break;
                }
            case 2:
                cout << "Enter Query: " << endl;
                cin >> duo;
                if(duo == "AND" || duo == "OR"){
                    getline(cin, entry);
                    word1 = entry.substr(1, entry.substr(1, entry.length()).find(" "));
                    entry = entry.substr(word1.length() + 2, entry.length());
                    word2 = entry.substr(0, entry.find(" "));
                    cout << word1 << endl;
                    cout << word2 << endl;
                    entry = entry.substr(word2.length(), entry.length());
                    if(duo == "AND"){ results = p.searchAND(*wordIndex, word1, word2);}
                    else if(duo == "OR"){ results = p.searchOR(*wordIndex, word1, word2);}
                }
                else{
                    word1 = duo;
                    getline(cin, entry);
                    results = p.search(*wordIndex, word1);
                }
                if(entry.length() > 0){
                    ext1 = entry.substr(1, entry.substr(1, entry.length()).find(" "));
                    entry = entry.substr(ext1.length() + 2, entry.length());
                    clar1 = entry.substr(0, entry.find(" "));
                    entry = entry.substr(clar1.length(), entry.length());
                    if(ext1 == "ORG"){
                        results = p.filter(results, *orgTable, clar1);
                    }
                    else if(ext1 == "PERSON"){
                        results = p.filter(results, *personTable, clar1);
                    }
                    else if(ext1 == "NOT"){
                        cout << clar1 << endl;
                        results = p.filterNOT(results, p.search(*wordIndex, clar1));
                    }
                    if(entry.length() > 0){
                        ext2 = entry.substr(1, entry.substr(1, entry.length()).find(" "));
                        entry = entry.substr(ext2.length() + 2, entry.length());
                        clar2 = entry.substr(0, entry.find(" "));
                        entry = entry.substr(clar2.length(), entry.length());
                        cout << ext2 << endl;
                        cout << clar2 << endl;
                        if(ext2 == "ORG"){
                            results = p.filter(results, *orgTable, clar2);
                        }
                        else if(ext2 == "PERSON"){
                            results = p.filter(results, *personTable, clar2);
                        }
                    }
                    if(entry.length() > 0){
                        ext3 = entry.substr(1, entry.substr(1, entry.length()).find(" "));
                        entry = entry.substr(ext3.length() + 2, entry.length());
                        clar3 = entry.substr(0, entry.find(" "));
                        entry = entry.substr(clar3.length(), entry.length());
                        if(ext3 == "ORG"){
                            results = p.filter(results, *orgTable, clar3);
                        }
                        else if(ext3 == "PERSON"){
                            results = p.filter(results, *personTable, clar3);
                        }
                    }
                }
                if(results.empty()){
                    cout << "Search found no results" << endl;
                }
                else{
                    for(string re : results){
                          relevantResults.push_back(pair<string, int>(re, file.getFrequency(re.c_str(), word1)));
                    }
                    p.sortOutput(relevantResults, finalOutput);
                    for(string rf : finalOutput){
                        file.titleParser(rf.c_str());
                    }
                }
                ext1 = "";
                ext2 = "";
                ext3 = "";
                word1 = "";
                word2 = "";
                clar1 = "";
                clar2 = "";
                clar3 = "";
                relevantResults.clear();
                results.clear();
                finalOutput.clear();
            case 9:
                break;
        }
    }
    return 0;
}
