import csv

OPTAB = {'START' : ['D'],
         'BASE'  : ['D'],
         'NOBASE': ['D'],
         'STL'   : ['I',3,0x14,['m']],
         'RMO'   : ['I',2,0xAC,['r','r']],
         'ADD'   : ['I',3,0x18,['m']],
         'J'     : ['I',3,0x3C,['m']],
         'LDA'   : ['I',3,0x00,['m']],
         'STA'   : ['I',3,0x0C,['m']],
         'JSUB'  : ['I',3,0x48,['m']],
         'JEQ'   : ['I',3,0x30,['m']],
         'SUB'   : ['I',3,0x1C,['m']],
         'MULR'  : ['I',2,0x98,['r','r']],
         'LDL'   : ['I',3,0x08,['m']],
         'RSUB'  : ['I',3,0x4C,['m']],
         'ADDF'  : ['I',3,0x18,['m']],
         'ADDR'  : ['I',2,0x90,['r','r']],
         'AND'   : ['I',3,0x40,['m']],
         'CLEAR' : ['I',2,0xB4,['r']],
         'COMP'  : ['I',3,0x28,['m']],
         'COMPF' : ['I',3,0x88,['m']],
         'COMPR' : ['I',2,0xA0,['r','r']],
         'DIV'   : ['I',3,0x24,['m']],
         'DIVF'  : ['I',3,0x64,['m']],
         'DIVR'  : ['I',2,0x9C,['r','r']],
         'FIX'   : ['I',1,0xC4,[]],
         'FLOAT' : ['I',1,0xC0,[]],
         'HIO'   : ['I',1,0xF4,[]],
         'JGT'   : ['I',3,0x34,['m']],
         'JLT'   : ['I',3,0x38,['m']],
         'LDB'   : ['I',3,0x68,['m']],
         'LDCH'  : ['I',3,0x50,['m']],
         'LDF'   : ['I',3,0x70,['m']],
         'LDL'   : ['I',3,0x08,['m']],
         'LDS'   : ['I',3,0x6C,['m']],
         'LDT'   : ['I',3,0x74,['m']],
         'LDX'   : ['I',3,0x04,['m']],
         'LPS'   : ['I',3,0xD0,['m']],
         'MUL'   : ['I',3,0x20,['m']],
         'MULF'  : ['I',3,0x60,['m']],
         'NORM'  : ['I',1,0xC8,[]],
         'OR'    : ['I',3,0x44,['m']],
         'RD'    : ['I',3,0xD8,['m']],
         'SHIFTL': ['I',2,0xA4,['r','n']],
         'SHIFTR': ['I',2,0xA8,['r','n']],
         'SIO'   : ['I',1,0xF0,[]],
         'SSK'   : ['I',3,0xEC,['m']],
         'STB'   : ['I',3,0x78,['m']],
         'STCH'  : ['I',3,0x54,['m']],
         'STF'   : ['I',3,0x80,['m']],
         'STI'   : ['I',3,0xD4,['m']],
         'STS'   : ['I',3,0x7C,['m']],
         'STSW'  : ['I',3,0xE8,['m']],
         'STT'   : ['I',3,0x84,['m']],
         'STX'   : ['I',3,0x10,['m']],
         'SUBF'  : ['I',3,0x5C,['m']],
         'SUBR'  : ['I',2,0x94,['r','r']],
         'SVC'   : ['I',2,0xB0,['n']],
         'TD'    : ['I',3,0xE0,['m']],
         'TIO'   : ['I',1,0xF8,[]],
         'TIX'   : ['I',3,0x2C,['m']],
         'TIXR'  : ['I',2,0xB8,['r']],
         'WD'    : ['I',3,0xDC,['m']]}

REGTAB =    {'A' : "0000", 
             'X' : "0001",
             'L' : "0010",
             'B' : "0011",
             'S' : "0100",
             'T' : "0101",
             'PC' : "1000", 
             'SW' : "1001"}

def pass1():
    SYMTAB = {}
    START = 0
    LOCCTR = 0
    outf = open("inter.asm", 'w')
    inf = open("in.asm")
    for line in csv.reader(inf, delimiter='\t'):
        if(line[1] == "START"):
            LOCCTR = START =  int(line[2])
        elif(line[1] == "END"):
            print("{:X}".format(LOCCTR)+"\t"+line[0]+"\t"+line[1])
            txt = str(LOCCTR)+"\t"+line[0]+"\t"+line[1]
            outf.write(txt+"\n")
            SIZE = LOCCTR - START
            break
        
        if(line[0] != ''):
            if line[0] in SYMTAB:
                print("Error: Symbol "+line[0]+" already exists")
            else:
                S = {line[0]:LOCCTR}
                SYMTAB.update(S)
        L = 0
        if line[1] in OPTAB:
            if(OPTAB[line[1]][0] != 'D'):
                L = int(OPTAB[line[1]][1])
        elif(line[1] == "WORD"):
            L = 3
        elif(line[1] == "RESW"):
            L = 3*int(line[2])
        elif(line[1] == "RESB"):
            L = int(line[2])
        elif(line[1] == "BYTE"):
            L = len(line[2])
        else:
            print("Error: Invalid Opcode "+line[1])

        if(len(line)==2):
            print("{:X}".format(LOCCTR)+"\t"+line[0]+"\t"+line[1])
            txt = str(LOCCTR)+"\t"+line[0]+"\t"+line[1]
            outf.write(txt+"\n")
        else:
            print("{:X}".format(LOCCTR)+"\t"+line[0]+"\t"+line[1]+"\t"+line[2])
            txt = str(LOCCTR)+"\t"+line[0]+"\t"+line[1]+"\t"+line[2]
            outf.write(txt+"\n")

        LOCCTR += L
    outf.close()
    inf.close()
    return SYMTAB,SIZE,START

def pass2(SYMTAB,SIZE,START):
    inf = open("inter.asm")
    outf = open("out.asm", 'w')
    textrec = "T^"
    text = ""
    tl = 0
    for line in csv.reader(inf, delimiter='\t'):
        if(line[2] == "START"):
            header = "H^"
            header += "{:6s}".format(line[1])
            header += "^"+"{:X}".format(SIZE)
            outf.write(header+"\n")
            continue
        elif(line[2] == "END"):
            break

        INSTR = ''
        if line[2] in OPTAB:
            if(OPTAB[line[2]][0] != 'D'):
                OPCODE = OPTAB[line[2]][2]
                if(len(line)==4):
                    OP = line[2].split(',')
                    if(len(OP)==1):
                        XBPE = 0
                        DISPL =0        #if SYMBOL in Operand Field
                        if line[3] in SYMTAB:
                            OPCODE += 0x3                                                       #ni = 11 = 3
                            DISPL = SYMTAB[line[3]] - (int(line[0]) +  OPTAB[line[2]][1])
                            if(DISPL<2048 and DISPL>-2048):                             #pc relative xbpe = 0010 = 2
                                XBPE = 0x2
                            elif(DISPL<4095):                                           #pc relative xbpe = 0100 = 4
                                XBPE = 0x4
                            else:
                                print("Memory out of range")

                        elif(line[3][0] == '#'):
                            OPCODE += 0x1                                                       #ni = 01 = 1
                            DISPL = int(line[3].split('#')[1])
                        INSTR = "{:02X}{:0X}{:03X}".format(OPCODE,XBPE,DISPL)
                        
                else:
                    OPCODE += 0x3                                                       #ni = 11 = 3
                    XBPE = 0
                    DISPL =0
                    INSTR = "{:02X}{:0X}{:03X}".format(OPCODE,XBPE,DISPL)

        if(INSTR != ''):
            tl += len(INSTR)
            if(tl>60):
                textrec += "{:02X}".format(tl)
                textrec += text
                outf.write(textrec+"\n")
                textrec = "T^"
                tl = 0
            elif(tl==len(INSTR)):
                textrec += "{:06X}".format(int(line[0]))
                text += "^"+INSTR
            else:
                text += "^"+INSTR
                       
    textrec += "^{:02X}".format(tl)
    textrec += text
    outf.write(textrec+"\n")
    
    end = "E^"
    end += "{:06X}".format(START)
    outf.write(end+"\n")
    inf.close()
    outf.close()

ST,Z,s = pass1()
pass2(ST,Z,s)
        