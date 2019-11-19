#include "xe_blocks_pass1.cpp"
using namespace std;

void pass2()
{
    cout<<endl<<"Pass 2:"<<endl;
    ifstream fin;
    ofstream fout; 
    fin.open("inter.asm", ios::in);
    fout.open("out.asm");

    vector<string> row; 
    string line;

    while (getline(fin, line))
    {
        cout<<endl<<line<<"\t";
        row = tokenize(line);
        string instr ="";
        if(row[3]=="START")
        {
            fout<<"H^"<<setw(6)<<row[2]<<"^"<<setw(6)<<setfill('0')<<hex<<STADR<<"^"<<setw(6)<<setfill('0')<<hex<<SIZE<<endl;
            cout<<"H^"<<setw(6)<<row[2]<<"^"<<setw(6)<<setfill('0')<<hex<<STADR<<"^"<<setw(6)<<setfill('0')<<hex<<SIZE<<endl;
            continue;
        }
        else if(row[3]=="END")
        {
            fout<<"E^"<<setw(6)<<setfill('0')<<hex<<SYMTAB[row[3]].address<<endl;
            cout<<"E^"<<setw(6)<<setfill('0')<<hex<<SYMTAB[row[3]].address<<endl;
            continue;
        }
        else if(row[3]=="USE" || row[3]=="LTORG" || row[3]=="RESW" || row[3]=="RESB" || row[3]=="BYTE")
            continue;
        
        string op;
        int OPCODE, XBPE = 0, DISPL = 0;
        stringstream INSTR;
        int fmt=0;
        if(stcut(row[3], '+').size() == 2)
            {   op = stcut(row[3], '+')[1];
                fmt=4;  } 
        else
            op = row[3];
        
        if(OPTAB[op].exists=='y')
            OPCODE = strhex2int(OPTAB[op].opcode);
            //cout<<OPCODE<<" "<<OPTAB[op].opcode<<endl;
        
        if(row.size() == 5)
        {
            vector<string> operand = stcut(row[4], ',');

            if(OPTAB[op].format==2)
            {
                if(operand.size() == 1)
                    cout<<OPCODE<<REGTAB[operand[0]].num<<endl;
                else if(operand.size() == 2)
                    cout<<OPCODE<<REGTAB[operand[0]].num<<REGTAB[operand[1]].num<<endl;
                continue;
            }

            if(fmt == 4)
            {
                if(operand.size() == 1)
                {
                    OPCODE += 3;
                    XBPE = 1;
                    DISPL = SYMTAB[operand[0]].address;
                    cout<<setw(2)<<OPCODE<<setw(1)<<XBPE<<setw(5)<<DISPL<<endl;
                    continue;
                }
            }

            if(operand.size() == 1)
            {
                string hash(1,operand[0][0]);
                if(hashcmp(hash))
                {
                    OPCODE += 1;
                    XBPE = 0;
                    vector<string> im_operand = stcut(operand[0], '#');
                    cout<<im_operand[0]<<endl;
                    DISPL = str2int(im_operand[1]);
                    //cout<<setw(2)<<OPCODE<<setw(1)<<XBPE<<setw(3)<<DISPL<<endl;
                    continue;
                }

                if(SYMTAB[operand[0]].exists=='y')
                {
                    OPCODE += 3;
                    DISPL = SYMTAB[operand[0]].address - ( str2int(row[0]) + OPTAB[row[3]].format );
                    if(DISPL<2048 and DISPL>-2048)   
                        XBPE = 2;
                    else if(DISPL<4095)
                        XBPE = 4;
                    else
                        cout<<"Memory out of range";
                }
                cout<<setw(2)<<OPCODE<<setw(1)<<XBPE<<setw(3)<<DISPL<<endl;
            }
        }
    }
}

int main()
{
    pass1();
    pass2();
}