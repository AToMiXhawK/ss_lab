#include "pass1.cpp"
using namespace std;

void pass2(int SIZE)
{
    cout<<endl<<"Pass 2:"<<endl;
    ifstream fin;
    ofstream fout; 
    fin.open("inter.asm", ios::in);
    fout.open("out.asm");

    vector<string> row; 
    string line;
    int STADR=0, LOCCTR=0;
    stringstream INSTR;
    int inst_len = 0;
    INSTR<<"T^";
    while (getline(fin, line))
    {
        //cout<<endl<<line<<"\t";
        int len = 0;
        row = tokenize(line);
        string instr ="";
        if(row[2]=="START")
        {
            STADR = str2int(row[3]);
            INSTR<<setw(6)<<hex<<STADR<<"^";
            fout<<"H^"<<setw(6)<<row[1]<<"^"<<setw(6)<<setfill('0')<<hex<<STADR<<"^"<<setw(6)<<setfill('0')<<hex<<SIZE<<endl;
            cout<<"H^"<<setw(6)<<row[1]<<"^"<<setw(6)<<setfill('0')<<hex<<STADR<<"^"<<setw(6)<<setfill('0')<<hex<<SIZE<<endl;
            continue;
        }

        else if(row[2]=="END")
        {
            fout<<"E^"<<setw(6)<<setfill('0')<<hex<<SYMTAB[row[3]].address<<endl;
            cout<<"E^"<<setw(6)<<setfill('0')<<hex<<SYMTAB[row[3]].address<<endl;
            continue;
        }

        else if(row[3]=="EQU")
            continue;

        int OPCODE, DISPL = 0;
        int fmt=0;

        if(OPTAB[row[2]].exists=='y')
        {   
            OPCODE = strhex2int(OPTAB[row[2]].opcode); 
            fmt = OPTAB[row[2]].format; 

            if(fmt==1)
            {
                INSTR<<setw(1)<<setfill('0')<<hex<<OPCODE<<"0"<<endl;
                len = 2;
            }

            else if(fmt == 2)
            {
                INSTR<<setw(1)<<setfill('0')<<hex<<OPCODE<<REGTAB[row[3]].num<<endl;
                len = 2;
            }

            else if(fmt == 3)
            {
                vector<string> regops = stcut(row[3], ',');
                INSTR<<setw(1)<<setfill('0')<<hex<<OPCODE<<REGTAB[regops[0]].num<<REGTAB[regops[1]].num<<REGTAB[regops[2]].num<<endl;
                len = 4;
            }

            else if(fmt == 4)
            {
                vector<string> ops = stcut(row[3], ',');
                if(SYMTAB[ops[1]].is_equ)
                    DISPL = SYMTAB[ops[1]].address;
                else
                {
                    int f_len; OPTAB[row[2]].format>2?f_len=2:f_len=1;
                    LOCCTR = str2int(row[0]) + f_len;
                    DISPL = SYMTAB[ops[1]].address - LOCCTR;
                    if(DISPL<0)
                        DISPL -= 0xffffff00;
                }
                INSTR<<setw(1)<<setfill('0')<<hex<<OPCODE<<REGTAB[ops[0]].num<<setw(1)<<setfill('0')<<hex<<DISPL<<endl;
                len = 4;
                //printf("%02hhx\n",DISPL);
            }

            else if(fmt == 5)
            {
                INSTR<<setw(1)<<setfill('0')<<hex<<OPCODE<<setw(3)<<setfill('0')<<hex<<SYMTAB[row[3]].address<<endl;
                len = 4;
            }
        }

        if(inst_len+len>60)
        {
            
        }

    }
}


int main()
{
    int SIZE;
    SIZE = pass1();
    pass2(SIZE);
}