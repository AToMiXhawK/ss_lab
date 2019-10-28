#include "utility.cpp" 
#include "tables.cpp"

using namespace std;

struct INTERMIDIETE_DATA
{
    int SIZE;
    int START;
    map <string, int> SYMTAB;
};

struct INTERMIDIETE_DATA pass1()
{
    struct INTERMIDIETE_DATA data;
    load_tables();
    ifstream fin;
    ofstream fout; 
    fin.open("in.asm", ios::in);
    fout.open("inter.asm");

    map <string, int> SYMTAB;
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

        else if(row[1]=="END")
        { 
            SIZE=LOCCTR-START;
            cout<<hex<<LOCCTR<<"\t"<<line<<endl;
            fout<<LOCCTR<<"\t"<<line<<endl;  
            break;
        }

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
            if(row[2][0]=='X')
                len = ceil(float(row[2].length() - 3)/2);
            else if(row[2][0]=='C')
                len = row[2].length() - 3;
        else
            { cout<<"Error: Invalid Opcode "<<row[1]<<endl; break; }
        fout<<LOCCTR<<"\t"<<line<<endl;

        cout<<hex<<LOCCTR<<"\t";
        for(int i=0; i<row.size(); i++)
            cout<<row[i]<<"\t";
        cout<<endl;
        LOCCTR += len;
    }

    cout<<endl<<"SYMTAB"<<endl;
    for(map<string, int>::iterator i=SYMTAB.begin(); i!=SYMTAB.end(); i++)
    {
        cout<<hex<<i->first<<"\t"<<i->second<<endl;
    }

    data.SIZE=SIZE;
    data.START=START;
    data.SYMTAB=SYMTAB;
    return data; 
}

/*int main()                        // Uncomment these to run pass1 seperately
{                                   // Comment this main function to include in pass2
    struct INTERMIDIETE_DATA d;
    d = pass1();
}*/