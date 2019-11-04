#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <map>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cmath>

using namespace std;

vector<string> tokenize(string temp)	// function to tokenize string with "\t" delimiter
{ 
    string line, word;
    vector<string> row;  
    row.clear(); 
    stringstream s(temp);
    while (getline(s, word, '\t'))
        row.push_back(word);
    return row;
} 

int str2int(string s)		// function to convert string to int
{							// since atoi can only used for in case of char array
	char cstr[s.size() + 1];
	s.copy(cstr, s.size() + 1);
	cstr[s.size()] = '\0';
	return atoi(cstr);
}

int stlen(string s)			// function to find length of string 
{							// since strlen can only used for length of char array
	char cstr[s.size() + 1];
	s.copy(cstr, s.size() + 1);
	cstr[s.size()] = '\0';
	return strlen(cstr);
}

vector<string> stcut(string temp, char c)	// function to tokenize string with "\t" delimiter
{ 
    string line, word;
    vector<string> row;  
    row.clear(); 
    stringstream s(temp);
    while (getline(s, word, c))
        row.push_back(word);
    return row;
} 

int strhex2int(string s)
{
    char cstr[s.size() + 1];
	s.copy(cstr, s.size() + 1);
	cstr[s.size()] = '\0';
    return strtoul(cstr,NULL,16);
}