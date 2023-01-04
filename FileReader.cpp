//
// Created by Kas on 11/14/21.
//OWNER: Kas Taghavi
//

#include "FileReader.h"
#include "vector"
//--------- 12/4 NOTES---------------
// SEE LINE 205
// Using C++ filesystem to find and list all files in a directory
void FileReader::open_dir_using_filesystem(const char* path){
    for(const auto & entry : fs::directory_iterator(path)){

        const char* filename = entry.path().c_str();
        string cstr = filename;
        if(cstr.substr(cstr.length()-5, 5) != ".json"){
            if(cstr.substr(cstr.length()-5, 5) != "Store"){
                open_dir_using_filesystem(filename);
            }
        }
        else{
            if(cstr.substr(cstr.length()-5, 5) == ".json") {
                Parse(filename);
            }
        }
    }
}
int FileReader::getFrequency(const char* filename, string& token){
    int occurrences = 0;
    ifstream freqFile(filename);
    IStreamWrapper freqW(freqFile);
    Document f;
    f.ParseStream(freqW);
    string body_text = f["text"].GetString();
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    f.Accept(writer);
    Porter2Stemmer::trim(token);
    Porter2Stemmer::stem(token);
    std::transform(token.begin(), token.end(), token.begin(),
                   [](unsigned char c) { return std::tolower(c);});
    int l = body_text.length();
    char char_array[l + 1];
    strcpy(char_array, body_text.c_str());
    char uselessChars[] = ". ,;'/?12344567890!@#$%^&*()_=+[]{}|";
    char* data = strtok(char_array, uselessChars);
    while (data != nullptr) {
        string curr = string(data);
        Porter2Stemmer::trim(curr);
        Porter2Stemmer::stem(curr);
        std::transform(curr.begin(), curr.end(), curr.begin(),
                       [](unsigned char c) { return std::tolower(c);});
        if(strcmp(curr.c_str(), token.c_str()) == 0){
            occurrences++;
        }
        data = strtok(nullptr, uselessChars);
    }
    return occurrences;
}
void FileReader::Parse(const char* filename) {
    ifstream ifs(filename);
    IStreamWrapper isw(ifs);

    Document document;
    document.ParseStream(isw);
    //
    //    string paperID = document["uuid"].GetString();
    string body_text = document["text"].GetString();
    //    auto organization = document["organizations"]["name"].GetString();
    //    auto person = document["persons"]["name"].GetString();

    const rapidjson::Value& attributes = document["entities"]["organizations"];

    // using iterator to find all author info
    for (rapidjson::Value::ConstValueIterator itr = attributes.Begin(); itr != attributes.End(); ++itr) {
        const rapidjson::Value &attribute = *itr;

        for (rapidjson::Value::ConstMemberIterator itr2 = attribute.MemberBegin();
        itr2 != attribute.MemberEnd(); ++itr2) {
            if (itr2->name.IsString() && itr2->value.IsString()) {
                if (strlen(itr2->value.GetString()) > 0) {
                    string name = "name";
                    if (itr2->name.GetString() == name) {
                        if (!orgs.has(string(itr2->value.GetString()))) {
                            //                            cout << "We are going to insert into the hashmap" << endl;
                            orgs.insert(itr2->value.GetString(), vector<string>());
                            orgsToPersist.push_back(itr2->value.GetString());
                        }
                        string w = itr2->value.GetString();
                        vector<string> my_vec = orgs[w];
                        //                        string last_file = ;
                        //                        cout << "We found this file: " << last_file << endl;
                        if (my_vec.size() == 0 || my_vec.back() != filename) {
                            orgs[w].push_back(filename);
                        }
                        //                        cout << "  " << itr2->name.GetString() << " : " << itr2->value.GetString() << endl;
                    }
                    //                    cout << "  " << itr2->name.GetString() << " : " << itr2->value.GetString() << endl;
                }
            }
        }
    }

    // /Users/kasrataghavi/CLionProjects/21f-srch-ngn-andrew-kas/srch-ngn-data

    const rapidjson::Value& personsFile = document["entities"]["persons"];
    // using iterator to find all author info
    for (rapidjson::Value::ConstValueIterator itr = personsFile.Begin(); itr != personsFile.End(); ++itr) {
        const rapidjson::Value &attribute = *itr;

        for (rapidjson::Value::ConstMemberIterator itr2 = attribute.MemberBegin();
        itr2 != attribute.MemberEnd(); ++itr2) {
            if (itr2->name.IsString() && itr2->value.IsString()) {
                if (strlen(itr2->value.GetString()) > 0) {
                    string name = "name";
                    if (itr2->name.GetString() == name) {
                        if (!people.has(string(itr2->value.GetString()))) {
                            //                            cout << "We are going to insert into the hashmap" << endl;
                            people.insert(itr2->value.GetString(), vector<string>());
                            peopleToPersist.push_back(itr2->value.GetString());
                        }
                        string w = itr2->value.GetString();
                        vector<string> my_vec = people[w];
                        //                        string last_file = ;
                        //                        cout << "We found this file: " << last_file << endl;
                        if (my_vec.size() == 0 || my_vec.back() != filename) {
                            people[w].push_back(filename);
                        }
                        //                        cout << " perseons  " << itr2->name.GetString() << " : " << itr2->value.GetString() << endl;
                    }
                    //                    cout << "  " << itr2->name.GetString() << " : " << itr2->value.GetString() << endl;
                }
            }
        }
    }
    //
    //    if(!orgs.has(string(organization))){
    //        orgs.insert(organization, vector<string>());
    //    }
    //    if(orgs[organization].back() != filename){
    //        orgs[organization].push_back(filename);
    //    }

    //    if(!people.has(person)){
    //        people.insert(string(person), vector<string>());
    //    }
    //    if(people[person].back() != filename){
    //        people[person].push_back(filename);
    //    }



    //    DOM to string
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    document.Accept(writer);


    //   Tokenize all of body_text (remove whitespace, split into separate strings for each word
    char uselessChars[] = ". ,;'/?12344567890!@#$%^&*()_=+[]{}|";
    std::unordered_set<std::string> stopWords = {"able", "about", "above", "abroad", "according", "accordingly",
                                                 "across", "actually", "adj", "after", "afterwards", "again", "against",
                                                 "ago", "ahead", "ain't", "all", "allow", "allows", "almost", "alone",
                                                 "along", "alongside", "already", "also", "although", "always", "am",
                                                 "amid", "amidst", "among", "amongst", "an", "and", "another", "any",
                                                 "anybody", "anyhow", "anyone", "anything", "anyway", "anyways",
                                                 "anywhere", "apart", "appear", "appreciate", "appropriate", "are",
                                                 "aren't", "around", "as", "a's", "aside", "ask", "asking",
                                                 "associated", "at", "available", "away", "awfully", "back", "backward",
                                                 "backwards", "be", "became", "because", "become", "becomes",
                                                 "becoming", "been", "before", "beforehand", "begin", "behind", "being",
                                                 "believe", "below", "beside", "besides", "best", "better", "between",
                                                 "beyond", "both", "brief", "but", "by", "came", "can", "cannot",
                                                 "cant", "can't", "caption", "cause", "causes", "certain", "certainly",
                                                 "changes", "clearly", "c'mon", "co", "co.", "com", "come", "comes",
                                                 "concerning", "consequently", "consider", "considering", "contain",
                                                 "containing", "contains", "corresponding", "could", "couldn't",
                                                 "course", "c's", "currently", "dare", "daren't", "definitely",
                                                 "described", "despite", "did", "didn't", "different", "directly", "do",
                                                 "does", "doesn't", "doing", "done", "don't", "down", "downwards",
                                                 "during", "each", "edu", "eg", "eight", "eighty", "either", "else",
                                                 "elsewhere", "end", "ending", "enough", "entirely", "especially", "et",
                                                 "etc", "even", "ever", "evermore", "every", "everybody", "everyone",
                                                 "everything", "everywhere", "ex", "exactly", "example", "except",
                                                 "fairly", "far", "farther", "few", "fewer", "fifth", "first", "five",
                                                 "followed", "following", "follows", "for", "forever", "former",
                                                 "formerly", "forth", "forward", "found", "four", "from", "further",
                                                 "furthermore", "get", "gets", "getting", "given", "gives", "go",
                                                 "goes", "going", "gone", "got", "gotten", "greetings", "had", "hadn't",
                                                 "half", "happens", "hardly", "has", "hasn't", "have", "haven't",
                                                 "having", "he", "he'd", "he'll", "hello", "help", "hence", "her",
                                                 "here", "hereafter", "hereby", "herein", "here's", "hereupon", "hers",
                                                 "herself", "he's", "hi", "him", "himself", "his", "hither",
                                                 "hopefully", "how", "howbeit", "however", "hundred", "i'd", "ie", "if",
                                                 "ignored", "i'll", "i'm", "immediate", "in", "inasmuch", "inc", "inc.",
                                                 "indeed", "indicate", "indicated", "indicates", "inner", "inside",
                                                 "insofar", "instead", "into", "inward", "is", "isn't", "it", "it'd",
                                                 "it'll", "its", "it's", "itself", "i've", "just", "k", "keep", "keeps",
                                                 "kept", "know", "known", "knows", "last", "lately", "later", "latter",
                                                 "latterly", "least", "less", "lest", "let", "let's", "like", "liked",
                                                 "likely", "likewise", "little", "look", "looking", "looks", "low",
                                                 "lower", "ltd", "made", "mainly", "make", "makes", "many", "may",
                                                 "maybe", "mayn't", "me", "mean", "meantime", "meanwhile", "merely",
                                                 "might", "mightn't", "mine", "minus", "miss", "more", "moreover",
                                                 "most", "mostly", "mr", "mrs", "much", "must", "mustn't", "my",
                                                 "myself", "name", "namely", "nd", "near", "nearly", "necessary",
                                                 "need", "needn't", "needs", "neither", "never", "neverf", "neverless",
                                                 "nevertheless", "new", "next", "nine", "ninety", "no", "nobody", "non",
                                                 "none", "nonetheless", "noone", "no-one", "nor", "normally", "not",
                                                 "nothing", "notwithstanding", "novel", "now", "nowhere", "obviously",
                                                 "of", "off", "often", "oh", "ok", "okay", "old", "on", "once", "one",
                                                 "ones", "one's", "only", "onto", "opposite", "or", "other", "others",
                                                 "otherwise", "ought", "oughtn't", "our", "ours", "ourselves", "out",
                                                 "outside", "over", "overall", "own", "particular", "particularly",
                                                 "past", "per", "perhaps", "placed", "please", "plus", "possible",
                                                 "presumably", "probably", "provided", "provides", "que", "quite", "qv",
                                                 "rather", "rd", "re", "really", "reasonably", "recent", "recently",
                                                 "regarding", "regardless", "regards", "relatively", "respectively",
                                                 "right", "round", "said", "same", "saw", "say", "saying", "says",
                                                 "second", "secondly", "see", "seeing", "seem", "seemed", "seeming",
                                                 "seems", "seen", "self", "selves", "sensible", "sent", "serious",
                                                 "seriously", "seven", "several", "shall", "shan't", "she", "she'd",
                                                 "she'll", "she's", "should", "shouldn't", "since", "six", "so", "some",
                                                 "somebody", "someday", "somehow", "someone", "something", "sometime",
                                                 "sometimes", "somewhat", "somewhere", "soon", "sorry", "specified",
                                                 "specify", "specifying", "still", "sub", "such", "sup", "sure", "take",
                                                 "taken", "taking", "tell", "tends", "th", "than", "thank", "thanks",
                                                 "thanx", "that", "that'll", "thats", "that's", "that've", "the",
                                                 "their", "theirs", "them", "themselves", "then", "thence", "there",
                                                 "thereafter", "thereby", "there'd", "therefore", "therein", "there'll",
                                                 "there're", "theres", "there's", "thereupon", "there've", "these",
                                                 "they", "they'd", "they'll", "they're", "they've", "thing", "things",
                                                 "think", "third", "thirty", "this", "thorough", "thoroughly", "those",
                                                 "though", "three", "through", "throughout", "thru", "thus", "till",
                                                 "to", "together", "too", "took", "toward", "towards", "tried", "tries",
                                                 "truly", "try", "trying", "t's", "twice", "two", "un", "under",
                                                 "underneath", "undoing", "unfortunately", "unless", "unlike",
                                                 "unlikely", "until", "unto", "up", "upon", "upwards", "us", "use",
                                                 "used", "useful", "uses", "using", "usually", "v", "value", "various",
                                                 "versus", "very", "via", "viz", "vs", "want", "wants", "was", "wasn't",
                                                 "way", "we", "we'd", "welcome", "well", "we'll", "went", "were",
                                                 "we're", "weren't", "we've", "what", "whatever", "what'll", "what's",
                                                 "what've", "when", "whence", "whenever", "where", "whereafter",
                                                 "whereas", "whereby", "wherein", "where's", "whereupon", "wherever",
                                                 "whether", "which", "whichever", "while", "whilst", "whither", "who",
                                                 "who'd", "whoever", "whole", "who'll", "whom", "whomever", "who's",
                                                 "whose", "why", "will", "willing", "wish", "with", "within", "without",
                                                 "wonder", "won't", "would", "wouldn't", "yes", "yet", "you", "you'd",
                                                 "you'll", "your", "you're", "yours", "yourself", "yourselves",
                                                 "you've", "zero"};
    int n = body_text.length();

    // declaring character array
    char char_array[n + 1];

    // copying the contents of the
    // string to char array
    strcpy(char_array, body_text.c_str());

    //tokenizing
    char *data = strtok(char_array, uselessChars);

    //    AvlTree<Token> tree;
    while (data != nullptr) {

        if (stopWords.find(data) == stopWords.end()) {

            string test = string(data);
            Porter2Stemmer::trim(test);
            Porter2Stemmer::stem(test);
            std::transform(test.begin(), test.end(), test.begin(),
                           [](unsigned char c) { return std::tolower(c); });


            Corpus_token token_to_search_for;
            token_to_search_for.key = test;
            AvlNode<Corpus_token> *find_result = tree.find(token_to_search_for, tree.root);

            if (find_result == nullptr) {
                Corpus_token token;
                token.key = test;
                token.document_ids.push_back(filename);
                tree.insert(token, tree.root);

            } else {
                if (find_result->element.document_ids.back() != filename) {
                    find_result->element.document_ids.push_back(filename);
                }
            }
        }

        data = strtok(nullptr, uselessChars);
    }
}
void FileReader::printPersistence(){
    oFile.open("testwords.txt");
    preFile(tree.root);
    oFile.close();
    oFile.open("testOrgs.txt");
    for(string persOrg : orgsToPersist){
        oFile << persOrg << ",";
        for(string orgIDs : orgs[persOrg]){
            oFile << orgIDs << "-";
        }
        oFile << endl;
    }
    oFile.close();
    oFile.open("testPeople.txt");
    for(string persPers : peopleToPersist){
        oFile << persPers << ",";
        for(string persIDs : people[persPers]){
            oFile << persIDs << "-";
        }
        oFile << endl;
    }
    oFile.close();
}
void FileReader::preFile(AvlNode<Corpus_token>*& r){
    if(r == nullptr){
        return;
    }
    else{
        oFile << r->element.key << ",";
        for(string dk : r->element.document_ids){
            oFile << dk << "-";
        }
        oFile << endl;
        preFile(r->left);
        preFile(r->right);
    }
}
void FileReader::titleParser(const char *filename) {
    ifstream ifs(filename);
    IStreamWrapper isw(ifs);

    Document title;
    title.ParseStream(isw);

    string resultsTitle = title["title"].GetString();
    cout << resultsTitle << endl;
    //    cout<<"printing Title"<<endl;
}