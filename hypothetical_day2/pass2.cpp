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
            OPCODE = str2int(OPTAB[row[2]].opcode); 
            fmt = OPTAB[row[2]].format; 

            if(fmt==1)
            {
                int op = OPCODE * 32;
                cout<<setw(1)<<setfill('0')<<hex<<op;
                fout<<setw(1)<<setfill('0')<<hex<<op<<endl;
                len = 2;
            }

            else if(fmt == 2)
            {
                int op = OPCODE*32;
                int reg = REGTAB[row[3]].num * 8;
                op += reg;
                cout<<setw(1)<<setfill('0')<<hex<<op;
                fout<<setw(1)<<setfill('0')<<hex<<op<<endl;
                len = 2;
            }

            else if(fmt == 3)
            {
                int op = OPCODE*32;
                vector<string> regs = stcut(row[3], ',');
                int reg1 = REGTAB[regs[0]].num * 8;
                int reg2 = REGTAB[regs[1]].num * 2;
                op += reg1; op+= reg2;
                cout<<setw(1)<<setfill('0')<<hex<<op;
                fout<<setw(1)<<setfill('0')<<hex<<op<<endl;
                len = 2;
            }

            else if(fmt == 4)
            {
                int op = OPCODE*32;
                vector<string> ops = stcut(row[3], ',');
                int reg1 = REGTAB[ops[0]].num * 8;
                int reg2 = REGTAB[ops[1]].num * 2;
                op += reg1; op+= reg2;
                op *= 256;
                if(SYMTAB[ops[2]].is_equ)
                    DISPL = SYMTAB[ops[2]].address;
                else
                {
                    int f_len; OPTAB[row[2]].format>3?f_len=2:f_len=1;
                    LOCCTR = str2int(row[0]) + f_len;
                    DISPL = SYMTAB[ops[2]].address - LOCCTR;
                    if(DISPL<0)
                            DISPL -= 0xffffff00;
                }
                op += DISPL;
                cout<<setw(1)<<setfill('0')<<hex<<op;
                fout<<setw(1)<<setfill('0')<<hex<<op<<endl;
                len = 4;
            }

            else if(fmt == 5)
            {
                int op = OPCODE*32*256;
                if(SYMTAB[row[3]].is_equ)
                    DISPL = SYMTAB[row[3]].address;
                else
                {
                    int f_len; OPTAB[row[2]].format>3?f_len=2:f_len=1;
                    LOCCTR = str2int(row[0]) + f_len;
                    DISPL = SYMTAB[row[3]].address - LOCCTR;
                    if(DISPL<0)
                            DISPL -= 0xffffff00;
                }
                op += DISPL;
                cout<<setw(1)<<setfill('0')<<hex<<op;
                fout<<setw(1)<<setfill('0')<<hex<<op<<endl;
                len = 4;
            }
        }
        cout<<"\t\t"<<line<<endl;
    }
}


int main()
{
    int SIZE;
    SIZE = pass1();
    pass2(SIZE);
}