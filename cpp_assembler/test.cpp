#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<iomanip>
#include<map>
#include<algorithm>
#include<cstring>

using namespace std;

/*char* stochar(string st)
{
    char str[st.size() + 1];
	strcpy(str, st.c_str());
    return &str;
}*/
int main()
{
    string st = "Geeks-for-Geeks"; 
    char *str = new char[st.length() + 1];

    
    // Returns first token  
    char *token = strtok(*str, "-"); 
    
    // Keep printing tokens while one of the 
    // delimiters present in str[]. 
    while (token != NULL) 
    { 
        printf("%s\n", token); 
        token = strtok(NULL, "-"); 
    } 
  
    return 0; 
}