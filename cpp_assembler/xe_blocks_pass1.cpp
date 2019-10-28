#include "utility.cpp" 
#include "tables.cpp"

using namespace std;

void pass1()
{
    load_tables();
    ifstream fin;
    ofstream fout; 
    fin.open("in.asm", ios::in);
    fout.open("inter.asm");

    vector<string> row; 
    string line;
    int SIZE=0;
    string block = "DEFAULT";
    int blkid = 0;
    cout<<endl<<"Pass 1: Intermediate File"<<endl<<endl;
    while (getline(fin, line))
    {
        row = tokenize(line);
        if(row[1]=="START")
        { 
            BLOCKS[block].LOCCTR = BLOCKS[block].startAddress = str2int(row[2]);
            cout<<hex<<BLOCKS[block].LOCCTR<<"\t"<<BLOCKS[block].number<<"\t"<<line<<endl;
            fout<<BLOCKS[block].LOCCTR<<"\t"<<BLOCKS[block].number<<"\t"<<line<<endl; 
            continue;
        }

        else if(row[1]=="END")
        { 
            SIZE+=BLOCKS[block].LOCCTR;
            cout<<hex<<BLOCKS[block].LOCCTR<<"\t"<<BLOCKS[block].number<<"\t"<<line<<endl;
            fout<<BLOCKS[block].LOCCTR<<"\t"<<BLOCKS[block].number<<"\t"<<line<<endl;  
            break;
        }

        if(row[1]=="USE")
        {
            if(row.size()==2)
                block = "DEFAULT";
            else
                if(BLOCKS[row[2]].exists=='y')
                    block = row[2];
                else
                {
                    BLOCKS[row[2]].name = row[2];
                    BLOCKS[row[2]].exists = 'y';
                    BLOCKS[row[2]].startAddress = 0;
                    BLOCKS[row[2]].number= ++blkid;
                    BLOCKS[row[2]].LOCCTR = 0;
                    block = row[2];
                }
            cout<<hex<<BLOCKS[block].LOCCTR<<"\t"<<BLOCKS[block].number<<"\t"<<line<<endl;
            fout<<BLOCKS[block].LOCCTR<<"\t"<<BLOCKS[block].number<<"\t"<<line<<endl;
            continue;
        }

        if(row[1]=="LTORG")
        {
            for(map<string, struct_literal>::iterator i=LITTAB.begin(); i!=LITTAB.end(); i++)
            {
                if(i->second.exists=='n')
                {
                    i->second.address = BLOCKS[i->second.blockName].LOCCTR;
                    BLOCKS[i->second.blockName].LOCCTR += i->second.size;
                    i->second.exists = 'y';
                }
            }
            cout<<"\t\t"<<line<<endl;
            fout<<"\t\t"<<line<<endl;
            continue;
        }

        if(row[0] != "\0")
        {
            if(SYMTAB[row[0]].exists=='y')
            { cout<<"\nDuplicate Symbol"<<endl; break; }
            else
            {
                SYMTAB[row[0]].name = row[0];
                SYMTAB[row[0]].address = BLOCKS[block].LOCCTR;
                SYMTAB[row[0]].blockNumber = BLOCKS[block].number;
                SYMTAB[row[0]].exists = 'y';
            }      
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
        
        fout<<BLOCKS[block].LOCCTR<<"\t"<<BLOCKS[block].number<<"\t"<<line<<endl;
        cout<<hex<<BLOCKS[block].LOCCTR<<"\t"<<BLOCKS[block].number<<"\t";
        for(int i=0; i<row.size(); i++)
            cout<<row[i]<<"\t";
        cout<<endl;
        BLOCKS[block].LOCCTR += len;
        SIZE+=len;

        if(row.size()==3)
        if(row[2][0]=='=')
        {
            LITTAB[row[2]].value = row[2].substr(3,row[2].length()-4);
            LITTAB[row[2]].blockNumber = BLOCKS[block].number;
            LITTAB[row[2]].blockName = block;
            if(row[2][1]=='X')
            {
                LITTAB[row[2]].size = ceil(float(row[2].length() - 4)/2);
                LITTAB[row[2]].type = 'X';
            }
            else if(row[2][1]=='C')
            {
                LITTAB[row[2]].size = row[2].length() - 4;
                LITTAB[row[2]].type = 'C';
            }
        }
    }

    cout<<endl<<"SYMTAB"<<endl;
    for(map<string, struct_label>::iterator i=SYMTAB.begin(); i!=SYMTAB.end(); i++)
    {
        cout<<hex<<i->first<<"\t"<<i->second.address<<"\t"<<i->second.blockNumber<<endl;
    }

    cout<<endl<<"LITTAB"<<endl;
    for(map<string, struct_literal>::iterator i=LITTAB.begin(); i!=LITTAB.end(); i++)
    {
        if(i->second.exists=='n')
        {
            i->second.address = BLOCKS[i->second.blockName].LOCCTR;
            BLOCKS[i->second.blockName].LOCCTR += i->second.size;
            i->second.exists = 'y';
        }
        cout<<hex<<i->second.value<<"\t"<<i->second.address<<"\t"<<i->second.blockNumber<<endl;
    }
}

int main()                        // Uncomment these to run pass1 seperately
{                                   // Comment this main function to include in pass2
    pass1();
}