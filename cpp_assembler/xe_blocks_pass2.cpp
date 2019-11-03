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
        row = tokenize(line);
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
    }
}

int main()
{
    pass1();
    pass2();
}