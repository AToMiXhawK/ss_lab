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
     char num;
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
  REGTAB["R0"].num='0';
  REGTAB["R0"].exists='y';

  REGTAB["R1"].num='1';
  REGTAB["R1"].exists='y';

  REGTAB["R2"].num='2';
  REGTAB["R2"].exists='y';

  REGTAB["R3"].num='3';
  REGTAB["R3"].exists='y';

  REGTAB["R4"].num='4';
  REGTAB["R4"].exists='y';

  REGTAB["R5"].num='5';
  REGTAB["R5"].exists='y';

  REGTAB["R6"].num='6';
  REGTAB["R6"].exists='y';

  REGTAB["R7"].num='7';
  REGTAB["R7"].exists='y';

  REGTAB["R8"].num='8';
  REGTAB["R8"].exists='y';

  REGTAB["R9"].num='9';
  REGTAB["R9"].exists='y';

  REGTAB["R10"].num='a';
  REGTAB["R10"].exists='y';

  REGTAB["R11"].num='b';
  REGTAB["R11"].exists='y';

  REGTAB["R12"].num='c';
  REGTAB["R12"].exists='y';

  REGTAB["R13"].num='d';
  REGTAB["R13"].exists='y';

  REGTAB["R14"].num='e';
  REGTAB["R14"].exists='y';

  REGTAB["R15"].num='f';
  REGTAB["R15"].exists='y';
}

void load_OPTAB(){

  OPTAB["ADD"].opcode="0";
  OPTAB["ADD"].format=3;
  OPTAB["ADD"].exists='y';

  OPTAB["SUB"].opcode="1";
  OPTAB["SUB"].format=3;
  OPTAB["SUB"].exists='y';

  OPTAB["MUL"].opcode="2";
  OPTAB["MUL"].format=3;
  OPTAB["MUL"].exists='y';

  OPTAB["DIV"].opcode="3";
  OPTAB["DIV"].format=3;
  OPTAB["DIV"].exists='y';

  OPTAB["JZ"].opcode="4";
  OPTAB["JZ"].format=4;
  OPTAB["JZ"].exists='y';

  OPTAB["JNZ"].opcode="5";
  OPTAB["JNZ"].format=4;
  OPTAB["JNZ"].exists='y';

  OPTAB["JGTZ"].opcode="6";
  OPTAB["JGTZ"].format=4;
  OPTAB["JGTZ"].exists='y';

  OPTAB["JLTZ"].opcode="7";
  OPTAB["JLTZ"].format=4;
  OPTAB["JLTZ"].exists='y';

  OPTAB["CALL"].opcode="8";
  OPTAB["CALL"].format=5;
  OPTAB["CALL"].exists='y';

  OPTAB["RET"].opcode="9";
  OPTAB["RET"].format=1;
  OPTAB["RET"].exists='y';

  OPTAB["LD"].opcode="a";
  OPTAB["LD"].format=4;
  OPTAB["LD"].exists='y';

  OPTAB["ST"].opcode="b";
  OPTAB["ST"].format=4;
  OPTAB["ST"].exists='y';

  OPTAB["LDI"].opcode="c";
  OPTAB["LDI"].format=4;
  OPTAB["LDI"].exists='y';

  OPTAB["PUSH"].opcode="d";
  OPTAB["PUSH"].format=2;
  OPTAB["PUSH"].exists='y';

  OPTAB["POP"].opcode="e";
  OPTAB["POP"].format=2;
  OPTAB["POP"].exists='y';

  OPTAB["HLT"].opcode="f";
  OPTAB["HLT"].format=1;
  OPTAB["HLT"].exists='y';

}

void load_tables(){
  load_OPTAB();
  load_REGTAB();
}