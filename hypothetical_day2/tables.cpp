#include<iostream>
#include<map>
#include<string>

using namespace std;

struct struct_opcode{
    string opcode;
    int format;
    char exists;
    struct_opcode(){
      opcode="undefined";
      format=0;
      exists='n';
    }
};

struct struct_label{
     int address;
     string name;
     bool is_equ;;
     char exists;
     struct_label(){
       name="undefined";
       address=0;
       exists='n';
       is_equ = false;
     }
};

struct struct_register{
     int num;
     char exists;
     struct_register(){
       num = 'F';
       exists='n';
     }
};

typedef map<string,struct_label> SYMBOL_TABLE_TYPE;
typedef map<string,struct_opcode> OPCODE_TABLE_TYPE;
typedef map<string,struct_register> REG_TABLE_TYPE;

SYMBOL_TABLE_TYPE SYMTAB;
OPCODE_TABLE_TYPE OPTAB;
REG_TABLE_TYPE REGTAB;

void load_REGTAB(){
  REGTAB["R0"].num=0;
  REGTAB["R0"].exists='y';

  REGTAB["R1"].num=1;
  REGTAB["R1"].exists='y';

  REGTAB["R2"].num=2;
  REGTAB["R2"].exists='y';

  REGTAB["R3"].num=3;
  REGTAB["R3"].exists='y';
}

void load_OPTAB(){

  OPTAB["ADD"].opcode="0";
  OPTAB["ADD"].format=3;
  OPTAB["ADD"].exists='y';

  OPTAB["NEG"].opcode="1";
  OPTAB["NEG"].format=2;
  OPTAB["NEG"].exists='y';

  OPTAB["LOAD"].opcode="2";
  OPTAB["LOAD"].format=4;
  OPTAB["LOAD"].exists='y';

  OPTAB["STORE"].opcode="3";
  OPTAB["STORE"].format=4;
  OPTAB["STORE"].exists='y';

  OPTAB["JE"].opcode="4";
  OPTAB["JE"].format=5;
  OPTAB["JE"].exists='y';

  OPTAB["JL"].opcode="5";
  OPTAB["JL"].format=5;
  OPTAB["JL"].exists='y';

  OPTAB["JG"].opcode="6";
  OPTAB["JG"].format=5;
  OPTAB["JG"].exists='y';

  OPTAB["HLT"].opcode="7";
  OPTAB["HLT"].format=1;
  OPTAB["HLT"].exists='y';
}

void load_tables(){
  load_OPTAB();
  load_REGTAB();
}