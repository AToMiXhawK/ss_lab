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

    while (getline(fin, line))
    {
        //cout<<endl<<line<<"\t";
        row = tokenize(line);
        string instr ="";
        if(row[2]=="START")
        {
            STADR = str2int(row[3]);
            fout<<"H^"<<setw(6)<<row[1]<<"^"<<setw(6)<<setfill('0')<<hex<<STADR<<"^"<<setw(6)<<setfill('0')<<hex<<SIZE<<endl;
            cout<<"H^"<<setw(6)<<row[1]<<"^"<<setw(6)<<setfill('0')<<hex<<STADR<<"^"<<setw(6)<<setfill('0')<<hex<<SIZE<<endl;
            continue;
        }
    }
}


int main()
{
    int SIZE;
    SIZE = pass1();
    pass2(SIZE);
}