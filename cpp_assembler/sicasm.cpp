#include "utility.cpp" 
#include "tables.cpp"

using namespace std;

int main()
{
    load_tables();
    ifstream fin;
    ofstream fout, fsymb; 
    fin.open("in.asm", ios::in);
    fout.open("inter.asm");

    map <string, int> SYMTAB;
    vector<string> row; 
    string line;
    int START=0, LOCCTR=0, SIZE=0;
    while (getline(fin, line))
    {
        row = tokenize(line);

        if(row[1]=="START")
        { LOCCTR = START = str2int(row[2]); continue;}

        else if(row[1]=="END")
        { SIZE=LOCCTR-START; break;}

        if(row[0] != "\0")
        {
            if(SYMTAB.find(row[0])==SYMTAB.end())
                SYMTAB[row[0]]=LOCCTR;
            else
            { cout<<"\nDuplicate Symbol"<<endl; break; }
        }

        int len=0;
        if(OPTAB[row[1]].exists=='y')
            len = OPTAB[row[1]].format;
        else if(row[1] == "WORD")
            len = 3;
        else if(row[1] == "RESW")
            len = 3*str2int(row[2]);
        else if(row[1] == "RESB")
            len = str2int(row[2]);
        else if(row[1] == "BYTE")
            len = stlen(row[2]);
        else
            cout<<"Error: Invalid Opcode "<<row[1]<<endl;
        
        LOCCTR += len;
        
        cout<<LOCCTR-len<<"\t";
        for(int i=0; i<row.size(); i++)
            cout<<row[i]<<"\t";
        cout<<endl;
    }

    
    for(map<string, int>::iterator i=SYMTAB.begin(); i!=SYMTAB.end(); i++)
    {
        cout<<i->first<<" "<<i->second<<endl;
    }
    return 0; 
}