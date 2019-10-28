#include<iostream>
#include<fstream>
#include<map>
#include<sstream>

using namespace std;
int main()
{
    ifstream fop, fin;
    ofstream fout, fsymb;
    string cmd, address, symbol, opcode, con, s;
    stringstream s_1;
    int loc=0x0, start=0x0;
    map <string, string> optab;
    map <string, int> symtab;
    fop.open("optab.txt");
    fin.open("in.asm");
    fout.open("intermediate.txt");
    while(fop>>cmd && fop>>hex>>address)
        optab[cmd]=address;
    fop.close();
    fin>>symbol; fin>>opcode;
    if(opcode.compare("START")==0)
    {
        fin>>s;
        s_1<<hex<<s;
        s_1>>loc;
        start = loc;
        fout<<hex<<loc<<" "<<symbol<<" "<<opcode<<" "<<loc<<endl;
        fin>>symbol; fin>>opcode; fin>>con;
    }
    while(opcode.compare("END"))
    {
        cout<<"\n"<<hex<<loc<<dec<<" "<<symbol<<" "<<opcode<<" "<<con;
        fout<<hex<<loc<<" ";
        if(symbol.compare("-"))
        {
            if(symtab.find(symbol)==symtab.end())
                symtab[symbol]=loc;
            else
            {
                cout<<"\nDuplicate Symbol";
                break;
            }
        }
        if(optab.find(opcode)==optab.end())
        {   int x;
            stringstream con_1(con);
            con_1>>x;
            if(opcode.compare("WORD")==0)
                loc+=3;
            else if(opcode.compare("RESW")==0)
                loc += 3*x;
            else if(opcode.compare("RESB")==0)                
                loc += x;
            else if(opcode.compare("BYTE")==0)
            {
                if(con[0]=='X')
                    loc++;
                else
                    loc+=con.length()-3;
            }
            else
            {
                cout<<"\nInvalid opcode";
                break;
            }
        }
        else
            loc+=3;
        fout<<symbol<<" "<<opcode<<" "<<con<<endl;
        fin>>symbol; fin>>opcode; fin>>con;
    }
    fin>>symbol; fin>>opcode; fin>>con;
    fout<<loc<<" "<<opcode<<" "<<con;
    cout<<"\nLength: "<<loc-start;
    fin.close();
    fout.close();    
    fsymb.open("symtab.txt");
    for(map<string, int>::iterator i=symtab.begin(); i!=symtab.end(); i++)
    {
        fsymb<<i->first<<" "<<i->second<<endl;
    }
}