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

void read_record() 
{ 
    fstream fin; 
    fin.open("in.asm", ios::in); 
    string line, word, temp;
    vector<string> row;  

    while (getline(fin, temp))
    { 
        row.clear(); 
        stringstream s(temp);
        while (getline(s, word, '\t'))
            row.push_back(word);
        
        for(int i=0; i<row.size(); i++)
            cout<<row[i]<<"\t";
        cout<<row.size()<<endl;
    }
} 

int main()
{
    read_record(); 
    return 0; 
}