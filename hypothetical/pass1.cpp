#include "utility.cpp" 
#include "tables.cpp"

using namespace std;
int SIZE = 0, STADR = 0;
void pass1()
{
    load_tables();
    ifstream fin;
    ofstream fout; 
    fin.open("in.asm", ios::in);
    fout.open("inter.asm");

    vector<string> row; 
    string line;
    int START=0, LOCCTR=0, SIZE=0;
    cout<<endl<<"Pass 1: Intermediate File"<<endl<<endl;
    while (getline(fin, line))
    {
        row = tokenize(line);
        if(row[1]=="START")
        { 
            LOCCTR = START = str2int(row[2]);
            cout<<hex<<LOCCTR<<"\t"<<line<<endl;
            fout<<LOCCTR<<"\t"<<line<<endl; 
            continue;
        }
    }
}