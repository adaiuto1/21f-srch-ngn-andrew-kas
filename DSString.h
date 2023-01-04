//
// Created by Kas on 11/17/21.
//

#ifndef INC_21F_FINAL_PROJ_TEMPLATE_DSSTRING_H
#define INC_21F_FINAL_PROJ_TEMPLATE_DSSTRING_H

#include <iostream>
#include <cstring>

class DSString{

private:
    char* str;
    /**
     *  You will need to add some private data members here.
     *  This is up to your discretion.  However, we **strongly**
     *  encourage you to implement your string class as a wrapper
     *  for typical null-terminated c-strings.  In doing this, you
     *  may use c-sting functions in the methods in this class such
     *  as:
     *    * strlen(...)
     *    * strcpy(...)
     *    * strcmp(...)
     *    * strncpy(...)
     *    * strcat(...)
     *    * strncat(...)
     *
     *    A quick google search will return plenty of references on
     *    the c-string functions.
     **/


public:
    /**
     * Constructors and destructor
     *
     * Make sure you do proper memory management.
     **/
    DSString();
    DSString(const char*);
    DSString(const DSString&);
    ~DSString();
    void tolower();

    /**
     * Overloaded Assignment Operators
     */
    DSString& operator= (const char*);
    DSString& operator= (const DSString&);

    /**
     * Overloaded non-modifying string concat
     * @return
     */
    DSString operator+ (const DSString&);

    /**
     * Standard relational operators.  Feel free to add additieonal.
     *
     * Note that for each operator, there are two overloaded versions:
     *    one that takes a DSString object
     *    one that takes a null-terminated c-string
     *
     **/

    bool operator== (const char*) const;
    bool operator== (const DSString&) const;
    bool operator> (const DSString&) const;
    bool operator> (const char*) const;
    //functions that are required for using the map functionality
    bool operator< (const DSString&) const;
    bool operator< (const char*) const;

    /**
     * Subscript operator to access a particular character of a DSString object
     * @return the character requested by reference
     */
    char& operator[] (int) const;

    /**
     * getLength() returns the number (count) of characters in the string.
     **/
    int getLength() const;

    /**
     * The substring method returns a string object that contains a
     * sequence of characters from this string object.
     *
     * param start - the index of where to start
     * param numChars - the number (count) of characters to copy into
     *    the substring
     * @return a DSString object containing the requested substring
     **/
    DSString substring(int start, int numChars);

    /**
     * the c_str function returns a null-terminated c-string holding the
     * contents of this object.
     **/
    char* c_str();

    /**
     * Overloaded stream insertion operator to print the contents of this
     * string to the output stream in the first argument.
     **/
    friend std::ostream& operator<< (std::ostream&, const DSString&);

    //You are free to add more functionality to the class.  For example,
    //you may want to add a find(...) function that will search for a
    //string within a string.  (just an example)
    //
    //Further - you will be able to update and modify this class as the
    //semester progresses.

    //

    int find (const DSString &str, int position = 0) const;

    static const size_t npos = -1;
};



#endif //PA01_PART_2_NAME_DSSTRING_H
