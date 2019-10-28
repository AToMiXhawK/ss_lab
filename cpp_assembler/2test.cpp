#include <iostream>
#include <string>
#include<cstdlib>
using namespace std;

int str2int(string s)
{
    char cstr[s.size() + 1];
	s.copy(cstr, s.size() + 1);
	cstr[s.size()] = '\0';
    return atoi(cstr);
}

int main()
{
	std::string s = "10";
    int a = str2int(s);
    cout<<a;
	return 0;
}