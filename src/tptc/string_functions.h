#ifndef STRING_FUNCTIONS_H
#define STRING_FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>
using namespace std;

string get_inside_str(string test, char i1, char i2);
string ChangeString(string test, char i1, char i2);
vector<string> withoutstrings (vector<string> textsplit);
vector<string> remove_after (vector<string> textsplit, string after);
vector<string> removeidentation (vector<string> textsplit);
bool str_starts_with(string full_string, string prefix);
string rm_prefix(string full_string, string prefix);
string rm_suffix(string full_string, string suffix);
bool str_in(string s1, string s2);
string ident(int num);
bool keyword_in(string line, string keyword);
bool str_ends_with(string full_string, string prefix);


string ident(int num){
	string nident = "	";
	string tident;
	for (int i = 0; i< num; i++){
		tident = tident + nident;
	}
	return tident;
}

string rm_prefix(string full_string, string prefix){
	string result = full_string.substr(prefix.length());
	return result;
}
string rm_suffix(string full_string, string suffix){
	string result = full_string.substr(0, full_string.length() - suffix.length());
	return result;
}

vector<string> removeidentation (vector<string> textsplit){
	int size = textsplit.size();
	for (int i = 0; i<size; i++){
		while (str_starts_with(textsplit.at(i), ident(1) ) || str_starts_with(textsplit.at(i), " " ) ){
			if ( str_starts_with(textsplit.at(i), ident(1) ) ){
				textsplit.at(i) = rm_prefix(textsplit.at(i), ident(1));
			} else if (str_starts_with(textsplit.at(i), " " ) ) {
				textsplit.at(i) = rm_prefix(textsplit.at(i), " ");
			}
		}
	}
	return textsplit;
}

vector<string> remove_after (vector<string> textsplit, string after){
	int size = textsplit.size();
	for (int i = 0; i<size; i++){
		textsplit.at(i) = textsplit.at(i).substr(0, textsplit.at(i).find(after));
	}
	return textsplit;
}

vector<string> withoutstrings (vector<string> textsplit){
	int size = textsplit.size();
	for (int i = 0; i<size; i++){
		textsplit.at(i) = ChangeString(textsplit.at(i), '"', '"');
	}
	return textsplit;
}

string ChangeString(string test, char i1, char i2){
    bool inbracket = false;
    string outStr;
    for (size_t i = 0; i < test.size(); ++i)
    { 
        char ch = test[i];
        if (ch == i1 && inbracket == false) 
           inbracket = true;
        else
        if ( ch == i2 && inbracket == true)
           inbracket = false;
        else
        if ( !inbracket )
           outStr += ch;
     }
     test = outStr;
     return test;
}

string get_inside_str(string test, char i1, char i2){
    bool inbracket = true;
    string outStr;
    for (size_t i = 0; i < test.size(); ++i)
    { 
        char ch = test[i];
        if (ch == i1 && inbracket == true) 
           inbracket = false;
        else
        if ( ch == i2 && inbracket == false)
           inbracket = true;
        else
        if ( !inbracket )
           outStr += ch;
     }
     test = outStr;
     return test;
}

bool str_in(string s1, string s2){
	if(strstr(s1.c_str(),s2.c_str()))
	{
	   return true;
	} else{
		return false;
	}
}

/* This function use the str_in and str_starts_with functions
 * to detect if the keyword was written on the line.
 */
bool keyword_in(string line, string keyword){
    string line_wos = ChangeString(line, '"', '"');
    vector<string> spaces = {" ", "\n", "	", "(", ")", "{", "}", "[", "]"};
    string new_keyword = "";
    
    
    int size = spaces.size();
    
    if (keyword == line){
	return true;
    }
    
    for (int i = 0; i<size; i++){
	new_keyword = keyword + spaces.at(i);
	if (str_starts_with(line_wos, new_keyword)){
	    return true;
	}
	new_keyword = spaces.at(i) + keyword;
	if (str_ends_with(line_wos, new_keyword)){
	    return true;
	}
	
	for (int j = 0; j<size; j++){
	    new_keyword = spaces.at(i) + keyword + spaces.at(j);
	    if (str_in(line_wos, new_keyword)){
		return true;
	    }
	}
	
    }
    return false;
}

bool str_starts_with(string full_string, string prefix){
	if (full_string.rfind(prefix, 0) == 0) {
		return true;
	} else {
		return false;
	}
}

bool str_ends_with (string full_string, string suffix) {
    if (full_string.length() >= suffix.length()) {
        return (0 == full_string.compare (full_string.length() - suffix.length(), suffix.length(), suffix));
    } else {
        return false;
    }
}
#endif
