#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<iomanip>
#include<map>
#include<algorithm>
#include<cstring>
#include<vector>

using namespace std;

vector<string> tokenize(string temp) 
{ 
    string line, word;
    vector<string> row;  
    row.clear(); 
    stringstream s(temp);
    while (getline(s, word, '\t'))
        row.push_back(word);
    return row;
} 

int str2int(string s)
{
	char cstr[s.size() + 1];
	s.copy(cstr, s.size() + 1);
	cstr[s.size()] = '\0';
	return atoi(cstr);
}

int stlen(string s)
{
	char cstr[s.size() + 1];
	s.copy(cstr, s.size() + 1);
	cstr[s.size()] = '\0';
	return strlen(cstr);
}