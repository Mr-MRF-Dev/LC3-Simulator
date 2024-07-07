#include "assembly.h"

string Assembly::getMsg() { return msg; }

Assembly::Assembly() : msg("OK!") {
    assembly_labels = { "ORG", "ADD", "AND",  "BR",  "JMP", "JSR", "JSRR",
                        "LD",  "LDI", "LDR",  "LEA", "NOT", "RET", "RTI",
                        "ST",  "STR", "TRAP", "BIN", "HEX", "DEC" };

    assembly_codes = { { "ADD", 0x1000 }, { "AND", 0x5000 }, { "BR", 0x0000 },
                       { "JMP", 0xc000 }, { "JSR", 0x4000 }, { "JSRR", 0x4000 },
                       { "LD", 0x2000 },  { "LDI", 0xa000 }, { "LDR", 0x6000 },
                       { "LEA", 0xe000 }, { "NOT", 0x9000 }, { "RET", 0xc000 },
                       { "RTI", 0x8000 }, { "ST", 0x3000 },  { "STR", 0x7000 },
                       { "TRAP", 0xf000 } };

    REGs = { { "R0", 0 }, { "R1", 1 }, { "R2", 2 }, { "R3", 3 },
             { "R4", 4 }, { "R5", 5 }, { "R6", 6 }, { "R7", 7 } };
}

bool Assembly::isOpcode(string op_code) {

    if (find(assembly_labels.begin(), assembly_labels.end(), op_code) !=
        assembly_labels.end()) {
        return true;
    }

    return false;
}

bool Assembly::isORG(string str) { return (str == assembly_labels.front()); }

errorCode Assembly::encode(_16_BIT pc, _16_BIT* src, vector<string> code,
                           map<string, _16_BIT>& labels) {

    string front = code.front();

    if (front == "ADD") {
        return ADD(src, code);
    }

    else if (front == "AND") {
        return AND(src, code);
    }

    else if (front == "NOT") {
        return NOT(src, code);
    }

    else if (front == "LD") {
        return LD(pc, src, code, labels);
    }

    else if (front == "LDI") {
        return LDI(pc, src, code, labels);
    }

    else if (front == "LDR") {
        return LDR(src, code);
    }

    else if (front == "LEA") {
        return LEA(pc, src, code, labels);
    }

    else if (front == "ST") {
        return ST(pc, src, code, labels);
    }

    else if (front == "STI") {
        return STI(pc, src, code, labels);
    }

    else if (front == "STR") {
        return STR(src, code);
    }

    else if (front.substr(0, 2) == "BR") {
        return BR(src, code, labels);
    }

    else if (front == "JMP") {
        return JMP(src, code);
    }

    else if (front == "RET") {
        return RET(src, code);
    }

    else if (front == "JSR") {
        return JSR(src, code, labels);
    }

    else if (front == "JSRR") {
        return JSRR(src, code);
    }

    else if (front == "BIN" || front == "DEC" || front == "HEX") {
        return Variable(src, code);
    }

    msg = "Error in codes: invalid opcode\n";
    return INVALID_OPCODE;
}

errorCode Assembly::Variable(_16_BIT* final, vector<string> vec) {

    int num;
    string num_str;

    if (vec[0] == "BIN") {
        num_str = "B";
    } else if (vec[0] == "DEC") {
        num_str = "#";
    } else if (vec[0] == "HEX") {
        num_str = "X";
    } else {
        return OTHER_ERROR;
    }

    num_str += vec[1];

    errorCode lab = convertNumberFormat(&num, num_str);

    if (lab != OK_VALID) {
        return lab;
    }

    *final = 0;
    shiftCopy(final, num, 16);
}

errorCode Assembly::ADD(_16_BIT* final, vector<string> vec) {

    // dr = vec[1]
    // sr1 = vec[2]
    // sr2 = vec[3]

    // ADD  DR  SR1 0 00 SR2
    // 0001 000 000 0 00 000

    // ADD  DR  SR1 1 imm5
    // 0001 000 000 1 00000

    *final = assembly_codes["ADD"];
    _16_BIT dr, sr1, sr2;

    if (REGs.find(vec[1]) == REGs.end()) {
        msg = "Error Add: bad DR\n";
        return INVALID_REG;
    }

    dr = REGs[vec[1]];

    if (REGs.find(vec[2]) == REGs.end()) {
        msg = "Error Add: bad SR1\n";
        return INVALID_REG;
    }

    sr1 = REGs[vec[2]];

    if (REGs.find(vec[3]) == REGs.end()) {

        int imm5;
        errorCode lab = convertNumberFormat(&imm5, vec[3]);

        if (lab != OK_VALID) {
            return lab;
        }

        lab = imm5Range(imm5);

        if (lab != OK_VALID) {
            return lab;
        }

        // set the flag
        *final += 32;  // 1 00000

        // shfit the 5 bit of imm5 into final
        shiftCopy(final, imm5, 5);
    }

    else {
        // set the sr2
        sr2 = REGs[vec[3]];
        *final += sr2;
    }

    // set the sr1 and dr
    sr1 <<= 6;
    *final += sr1;
    dr <<= 9;
    *final += dr;

    return OK_VALID;
}

errorCode Assembly::AND(_16_BIT* final, vector<string> vec) {

    // AND  DR  SR1 0 00 SR2
    // 0101 000 000 0 00 000

    // AND  DR  SR1 1 imm5
    // 0101 000 000 1 00000

    *final = assembly_codes["AND"];
    _16_BIT dr, sr1, sr2;

    if (REGs.find(vec[1]) == REGs.end()) {
        msg = "Error And: bad DR\n";
        return INVALID_REG;
    }

    dr = REGs[vec[1]];

    if (REGs.find(vec[2]) == REGs.end()) {
        msg = "Error And: bad SR1\n";
        return INVALID_REG;
    }

    sr1 = REGs[vec[2]];

    if (REGs.find(vec[3]) == REGs.end()) {

        int imm5;
        errorCode lab = convertNumberFormat(&imm5, vec[3]);

        if (lab != OK_VALID) {
            return lab;
        }

        lab = imm5Range(imm5);

        if (lab != OK_VALID) {
            return lab;
        }

        // set the flag
        *final += 32;  // 1 00000

        // shfit the 5 bit of imm5 into final
        shiftCopy(final, imm5, 5);
    }

    else {
        // set the sr2
        sr2 = REGs[vec[3]];
        *final += sr2;
    }

    // set the sr1 and dr
    sr1 <<= 6;
    *final += sr1;
    dr <<= 9;
    *final += dr;

    return OK_VALID;
}

errorCode Assembly::NOT(_16_BIT* final, vector<string> vec) {

    // NOT  DR  SR1
    // 1001 000 000 1 11111

    *final = assembly_codes["NOT"];
    _16_BIT dr, sr1;

    if (REGs.find(vec[1]) == REGs.end()) {
        msg = "Error Not: bad DR\n";
        return INVALID_REG;
    }

    dr = REGs[vec[1]];

    if (REGs.find(vec[2]) == REGs.end()) {
        msg = "Error Not: bad SR1\n";
        return INVALID_REG;
    }

    sr1 = REGs[vec[2]];

    *final += 63;  // 1 11111

    // set the sr1 and dr
    sr1 <<= 6;
    *final += sr1;
    dr <<= 9;
    *final += dr;

    return OK_VALID;
}

errorCode Assembly::LD(_16_BIT pc, _16_BIT* final, vector<string> vec,
                       map<string, _16_BIT>& labels) {

    // LD   DR  PCoffest9
    // 0010 000 111111111

    *final = assembly_codes["LD"];
    _16_BIT dr, addr;
    errorCode lab;

    if (REGs.find(vec[1]) == REGs.end()) {
        msg = "Error Ld: bad DR\n";
        return INVALID_REG;
    }

    dr = REGs[vec[1]];

    if (labels.find(vec[2]) == labels.end()) {
        lab = convertNumberFormat(&addr, vec[2]);
        if (lab != OK_VALID) {
            msg += "Error ld: bad addr\n";
            return lab;
        }
    }

    else {
        addr = labels[vec[2]];
    }

    lab = PCoffest9Range(addr);

    if (lab != OK_VALID) {
        return lab;
    }

    int sum = (int)addr - (int)pc;
    shiftCopy(final, sum, 9);

    // 111 111 111
    // or use shiftCopy
    // set the dr

    dr <<= 9;
    *final += dr;

    return OK_VALID;
}

errorCode Assembly::LDI(_16_BIT pc, _16_BIT* final, vector<string> vec,
                        map<string, _16_BIT>& labels) {

    // LDI  DR  PCoffest9
    // 1010 000 111111111

    *final = assembly_codes["LDI"];
    _16_BIT dr, addr;
    errorCode lab;

    if (REGs.find(vec[1]) == REGs.end()) {
        msg = "Error Ldi: bad DR\n";
        return INVALID_REG;
    }

    dr = REGs[vec[1]];

    if (labels.find(vec[2]) == labels.end()) {
        lab = convertNumberFormat(&addr, vec[2]);
        if (lab != OK_VALID) {
            msg += "Error ldi: bad addr\n";
            return lab;
        }
    }

    else {
        addr = labels[vec[2]];
    }

    lab = PCoffest9Range(addr);

    if (lab != OK_VALID) {
        return lab;
    }

    int sum = (int)addr - (int)pc;
    shiftCopy(final, sum, 9);

    // set the dr
    dr <<= 9;
    *final += dr;

    return OK_VALID;
}

errorCode Assembly::LDR(_16_BIT* final, vector<string> vec) {

    // LDR  DR  baseR offest6
    // 0110 000 111   111111

    *final = assembly_codes["LDR"];
    _16_BIT dr, baseR;

    if (REGs.find(vec[1]) == REGs.end()) {
        msg = "Error Ldr: bad DR\n";
        return INVALID_REG;
    }

    dr = REGs[vec[1]];

    if (REGs.find(vec[2]) == REGs.end()) {
        msg = "Error Ldr: bad baseR\n";
        return INVALID_REG;
    }

    baseR = REGs[vec[2]];

    int off;
    errorCode lab = convertNumberFormat(&off, vec[3]);

    if (lab != OK_VALID) {
        return lab;
    }

    lab = offest6Range(off);

    if (lab != OK_VALID) {
        return lab;
    }

    *final += off;

    // set the dr
    baseR <<= 6;
    *final += baseR;
    dr <<= 9;
    *final += dr;

    return OK_VALID;
}

errorCode Assembly::LEA(_16_BIT pc, _16_BIT* final, vector<string> vec,
                        map<string, _16_BIT>& labels) {

    // LEA  DR   PCoffest9
    // 1110 000 111 111 111

    *final = assembly_codes["LEA"];
    _16_BIT dr, addr;
    errorCode lab;

    if (REGs.find(vec[1]) == REGs.end()) {
        msg = "Error Lea: bad DR\n";
        return INVALID_REG;
    }

    dr = REGs[vec[1]];

    if (labels.find(vec[2]) == labels.end()) {
        lab = convertNumberFormat(&addr, vec[2]);
        if (lab != OK_VALID) {
            msg += "Error lea: bad addr\n";
            return lab;
        }
    }

    else {
        addr = labels[vec[2]];
    }

    lab = PCoffest9Range(addr);

    if (lab != OK_VALID) {
        return lab;
    }

    int sum = (int)addr - (int)pc;
    shiftCopy(final, sum, 9);

    // set the dr
    dr <<= 9;
    *final += dr;

    return OK_VALID;
}

errorCode Assembly::ST(_16_BIT pc, _16_BIT* final, vector<string> vec,
                       map<string, _16_BIT>& labels) {

    // ST   DR  PCoffest9
    // 0011 000 111111111

    *final = assembly_codes["ST"];
    _16_BIT dr, addr;
    errorCode lab;

    if (REGs.find(vec[1]) == REGs.end()) {
        msg = "Error St: bad DR\n";
        return INVALID_REG;
    }

    dr = REGs[vec[1]];

    if (labels.find(vec[2]) == labels.end()) {
        lab = convertNumberFormat(&addr, vec[2]);
        if (lab != OK_VALID) {
            msg += "Error st: bad addr\n";
            return lab;
        }
    }

    else {
        addr = labels[vec[2]];
    }

    lab = PCoffest9Range(addr);

    if (lab != OK_VALID) {
        return lab;
    }

    int sum = (int)addr - (int)pc;
    shiftCopy(final, sum, 9);

    // set the dr
    dr <<= 9;
    *final += dr;

    return OK_VALID;
}

errorCode Assembly::STI(_16_BIT pc, _16_BIT* final, vector<string> vec,
                        map<string, _16_BIT>& labels) {

    // STI   DR  PCoffest9
    // 1011 000 111111111

    *final = assembly_codes["STI"];
    _16_BIT dr, addr;
    errorCode lab;

    if (REGs.find(vec[1]) == REGs.end()) {
        msg = "Error Sti: bad DR\n";
        return INVALID_REG;
    }

    dr = REGs[vec[1]];

    if (labels.find(vec[2]) == labels.end()) {
        lab = convertNumberFormat(&addr, vec[2]);
        if (lab != OK_VALID) {
            msg += "Error st: bad addr\n";
            return lab;
        }
    }

    else {
        addr = labels[vec[2]];
    }

    lab = PCoffest9Range(addr);

    if (lab != OK_VALID) {
        return lab;
    }

    int sum = (int)addr - (int)pc;
    shiftCopy(final, sum, 9);

    // set the dr
    dr <<= 9;
    *final += dr;

    return OK_VALID;
}

errorCode Assembly::STR(_16_BIT* final, vector<string> vec) {

    // STR  DR  baseR offest6
    // 0111 000 111   111111

    *final = assembly_codes["STR"];
    _16_BIT dr, baseR;

    if (REGs.find(vec[1]) == REGs.end()) {
        msg = "Error STR: bad DR\n";
        return INVALID_REG;
    }

    dr = REGs[vec[1]];

    if (REGs.find(vec[2]) == REGs.end()) {
        msg = "Error STR: bad baseR\n";
        return INVALID_REG;
    }

    baseR = REGs[vec[2]];

    int off;
    errorCode lab = convertNumberFormat(&off, vec[3]);

    if (lab != OK_VALID) {
        return lab;
    }

    lab = offest6Range(off);

    if (lab != OK_VALID) {
        return lab;
    }

    *final += off;

    // set the dr
    baseR <<= 6;
    *final += baseR;
    dr <<= 9;
    *final += dr;

    return OK_VALID;
}

errorCode Assembly::BR(_16_BIT* final, vector<string> vec,
                       map<string, _16_BIT>& labels) {

    // BR   nzp  PCoffest9
    // 0000 000 111111111

    *final = assembly_codes["BR"];
    _16_BIT n = 0, z = 0, p = 0, pcoff;

    if (vec[0].length() >= 3) {
        if (vec[0][2] == 'n' and n != 1)
            n = 1;
        else if (vec[0][2] == 'z' and z != 1)
            z = 1;
        else if (vec[0][2] == 'p' and p != 1)
            p = 1;
        else {
            msg = "Error Br: n z p flags\n";
            return INVALID_NZP;
        }
    }

    if (vec[0].length() >= 4) {
        if (vec[0][3] == 'n' and n != 1)
            n = 1;
        else if (vec[0][3] == 'z' and z != 1)
            z = 1;
        else if (vec[0][3] == 'p' and p != 1)
            p = 1;
        else {
            msg = "Error Br: n z p flags\n";
            return INVALID_NZP;
        }
    }

    if (vec[0].length() >= 5) {
        if (vec[0][4] == 'n' and n != 1)
            n = 1;
        else if (vec[0][4] == 'z' and z != 1)
            z = 1;
        else if (vec[0][4] == 'p' and p != 1)
            p = 1;
        else {
            msg = "Error Br: n z p flags\n";
            return INVALID_NZP;
        }
    }

    if (labels.find(vec[1]) == labels.end()) {
        msg = "Error Br: bad label not found\n";
        return INVALID_LABEL;
    }

    pcoff = labels[vec[1]];

    errorCode lab = PCoffest9Range(pcoff);

    if (lab != OK_VALID) {
        return lab;
    }

    *final += pcoff;  // 111 111 111
    // or use shiftCopy
    // shiftCopy(final, pcoff, 9);

    // set the nzp
    p <<= 9;
    *final += p;
    z <<= 10;
    *final += z;
    n <<= 11;
    *final += n;

    return OK_VALID;
}

errorCode Assembly::JMP(_16_BIT* final, vector<string> vec) {

    // JMP      baseR
    // 1100 000 000 000000

    *final = assembly_codes["JMP"];
    _16_BIT baseR;

    if (REGs.find(vec[1]) == REGs.end()) {
        msg = "Error JMP: bad reg not found\n";
        return INVALID_REG;
    }

    baseR = REGs[vec[1]];

    // set the reg
    baseR <<= 6;
    *final += baseR;

    return OK_VALID;
}

errorCode Assembly::RET(_16_BIT* final, vector<string> vec) {

    // RET      D7
    // 1100 000 111 000000

    *final = assembly_codes["RET"];
    _16_BIT baseR = REGs["R7"];

    // set the reg
    baseR <<= 6;
    *final += baseR;

    return OK_VALID;
}

errorCode Assembly::JSR(_16_BIT* final, vector<string> vec,
                        map<string, _16_BIT>& labels) {

    // JSR    PCoffset11
    // 0100 1 00000000000

    _16_BIT pcoff;

    *final = assembly_codes["JSR"];

    if (labels.find(vec[1]) == labels.end()) {
        msg = "Error jsr: bad label not found\n";
        return INVALID_LABEL;
    }

    pcoff = labels[vec[1]];
    *final += pcoff;

    _16_BIT flag = 1;
    flag <<= 11;
    *final += flag;

    return OK_VALID;
}

errorCode Assembly::JSRR(_16_BIT* final, vector<string> vec) {

    // JSRR      baseR
    // 0100 0 00 000 000000

    _16_BIT baseR;

    *final = assembly_codes["JSRR"];

    if (REGs.find(vec[1]) == REGs.end()) {
        msg = "Error JSRR: bad reg not found\n";
        return INVALID_REG;
    }

    baseR = REGs[vec[1]];

    baseR <<= 6;
    *final += baseR;

    return OK_VALID;
}

errorCode Assembly::convertNumberFormat(int* num, string str) {

    char begin_char = str.front();
    str.erase(str.begin());  // remove begin char

    int mabna;

    if (begin_char == '#') {
        mabna = 10;
    }

    else if (begin_char == 'b' || begin_char == 'B') {
        mabna = 2;

    }

    else if (begin_char == 'x' || begin_char == 'X') {
        mabna = 16;
    }

    else {
        msg = "Error: invalid number\n";
        return INVALID_NUMBER;
    }

    try {
        *num = stoi(str, 0, mabna);
    }

    catch (exception& e) {
        msg = string("Error: invalid number\n\n") + e.what();
        return INVALID_NUMBER;
    }

    return OK_VALID;
}

errorCode Assembly::convertNumberFormat(_16_BIT* num, string str) {

    char begin_char = str.front();
    str.erase(str.begin());  // remove begin char

    int mabna;

    if (begin_char == '#') {
        mabna = 10;
    }

    else if (begin_char == 'b' || begin_char == 'B') {
        mabna = 2;

    }

    else if (begin_char == 'x' || begin_char == 'X') {
        mabna = 16;
    }

    else {
        msg = "Error: invalid number\n";
        return INVALID_NUMBER;
    }

    try {
        int res = stoi(str, 0, mabna);
        if (res < 0) {
            msg = string("Error: invalid number\n\n") + "N number";
            return INVALID_NUMBER;
        }

        *num = res;
    }

    catch (exception& e) {
        msg = string("Error: invalid number\n\n") + e.what();
        return INVALID_NUMBER;
    }

    return OK_VALID;
}

errorCode Assembly::imm5Range(int num) {

    // imm5 / 5 bit ~ 31 number
    // p 15 & n 16

    if (num > 16 || num <= -16) {
        msg = "Error Number: out of range\n";
        return NUMBER_OUT_OF_RANGE;
    }

    return OK_VALID;
}

errorCode Assembly::orgRange(int num) {

    if (num < 0 or num >= PROGRAM_BORDER) {

        msg = "Error in number org, out of range\n";
        return NUMBER_OUT_OF_RANGE;
    }

    return OK_VALID;
}

errorCode Assembly::PCoffest9Range(int num) {

    if (num < 0 or num >= PROGRAM_BORDER) {

        msg = "Error in number PCoffest9, out of range\n";
        return NUMBER_OUT_OF_RANGE;
    }

    return OK_VALID;
}

errorCode Assembly::offest6Range(int num) {

    // offset6 / 6 bit ~ 63 number
    // p 31 & n 32

    if (num <= -32 or num > 32) {

        msg = "Error in number PCoffest6, out of range\n";
        return NUMBER_OUT_OF_RANGE;
    }

    return OK_VALID;
}

void Assembly::shiftCopy(_16_BIT* final, int num, int count) {

    for (int i = 0; i < count; i++, num >>= 1) {

        if (num % 2 != 0) {
            _16_BIT tmp = 1;
            tmp <<= i;
            *final += tmp;
        }
    }
}

// EOF