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

bool str2strcmp(string s1, string s2)
{
    char cstr1[s1.size() + 1];
	s1.copy(cstr1, s1.size() + 1);
	cstr1[s1.size()] = '\0';

    char cstr2[s2.size() + 1];
	s2.copy(cstr2, s2.size() + 1);
	cstr2[s2.size()] = '\0';

    if(strcmp(cstr1,cstr2))
        return false;
    else
        return true;
}

bool hashcmp(string s1)
{
    if(s1 == "#")
        return true;
    else
        return false;
}