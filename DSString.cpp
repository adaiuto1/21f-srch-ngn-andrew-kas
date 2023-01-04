//
// Created by Kas on 11/17/21.
//
#include "DSString.h"
#include <iostream>
#include <cstring>

DSString::DSString() {
    str = nullptr;
}

DSString::DSString(const char* k) {
    str = new char[strlen(k)+1];
    strcpy(str, k);
}

DSString::DSString(const DSString &arg) {
    if (arg.str == nullptr) {
        str = nullptr;
    } else {
        this->str = new char[strlen(arg.str) + 1];
        strcpy(str, arg.str);
    }
}

DSString::~DSString() {
    delete [] this->str;
}

DSString& DSString::operator=(const char *stringCharacters) {
    if(str != nullptr){
        delete []str;
    }
    str = new char[strlen(stringCharacters)+1];
    strcpy(str, stringCharacters);
    return *this;
}

DSString &DSString::operator=(const DSString &s) {
    if(str != nullptr){
        delete []str;
    }
    str = new char[strlen(s.str)+1];
    strcpy(str, s.str);
    return *this;
}

DSString DSString::operator+(const DSString &a) {
    DSString temp;
    if(a.str == nullptr && str == nullptr){
        return temp;
    }else if(a.str == nullptr ){
        temp = str;
        return temp;
    }else if(str == nullptr){
        temp = a.str;
        return temp;
    }
    temp.str = new char[strlen(a.str) + strlen(str) + 1];
    strcpy(temp.str, str);
    strcat(temp.str,a.str);
    return temp;
}

bool DSString::operator==(const char *arg) const {
    return strcmp(str, arg) == 0;
}

bool DSString::operator==(const DSString &arg) const{
    return strcmp(str,arg.str ) == 0;
}

bool DSString::operator>(const DSString &arg) const {
    return strcmp(str, arg.str) > 0;
}

bool DSString::operator>(const char *arg) const {
    return strcmp(str, arg) > 0;
}

bool DSString::operator < (const DSString &arg) const {
    return strcmp(str, arg.str) < 0;
}

bool DSString::operator < (const char *arg) const {
    return strcmp(str, arg) < 0;
}

char &DSString::operator[]( int i) const {
    return str[i];
}

int DSString::getLength() const {
    return strlen(str);
}

DSString DSString::substring(int start, int numChars) {
    DSString temp;
    temp.str = new char[numChars + 1];
    for (int i = 0; i < numChars; i++) {
        temp.str[i] = str[start + i];
    }
    temp.str[numChars] = '\0';

    return temp;
}

char* DSString::c_str() {
    return str;
}

std::ostream &operator<<(std::ostream &outPut, const DSString &thisObject) {
    if (thisObject.str == nullptr) {
        outPut << "";
    } else {
        outPut << thisObject.str;
    }
    return outPut;

}
// finding a string

int DSString::find(const DSString &parsingChar, int position) const {
    int foundIndex = DSString::npos;
    bool found = false;
    for(int i = 0; (!found && i < strlen(str)); i++){

        // check if the first character in parsingChar matches the iterated character
        if (str[i] == parsingChar[0]) {
            foundIndex = i;
            found = true;
            for (int j = 1; j < parsingChar.getLength(); j++) {
                // check for all the characters in the parsingChar and if they don't then break
                if (str[i+1] != parsingChar[j]) {
                    foundIndex = DSString::npos;
                    found = false;
                    break;
                }
            }
        }
    }

    return foundIndex;
}

void DSString::tolower() {

    for (int i = 0; i < getLength(); i++){
        if (isalpha(str[i])) {
            str[i] = std::tolower(str[i]);

        }
    }
}
