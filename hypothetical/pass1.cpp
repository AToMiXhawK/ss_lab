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
            {
                SYMTAB[row[0]].address = LOCCTR;
                SYMTAB[row[0]].name = row[0];
                SYMTAB[row[0]].exists = 'y';
            }
            else
            { cout<<"\nDuplicate Symbol"<<endl; break; }
        }

        int len = 0;
        if(OPTAB[row[1]].exists=='y')
            OPTAB[row[1]].format>2?len=2:len=1;
        else if(row[1] == "DB")
            len = 1;
        else if(row[1] == "EQU")
            len = 0;
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
    for(map<string, struct_label>::iterator i=SYMTAB.begin(); i!=SYMTAB.end(); i++)
    {
        cout<<hex<<i->first<<"\t"<<i->second.address<<endl;
    }

}

int main()
{
    pass1();
    return 0;
}