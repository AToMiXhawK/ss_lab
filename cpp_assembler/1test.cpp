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

int main()
{
    fstream fin; 
    fin.open("in.asm", ios::in);
    vector<string> row; 
    string temp;
    while (getline(fin, temp))
    {
        row = tokenize(temp);

        for(int i=0; i<row.size(); i++)
            cout<<row[i]<<"\t";
        cout<<row.size()<<endl;
    } 
    return 0; 
}