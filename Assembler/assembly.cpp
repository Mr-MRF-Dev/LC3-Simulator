#include "assembly.h"

string Assembly::getMsg() { return msg; }

Assembly::Assembly() : msg("OK!") {
    assembly_labels = { "ORG",  "ADD", "AND", "BR",  "JMP", "JSR",
                        "JSRR", "LD",  "LDI", "LDR", "LEA", "NOT",
                        "RET",  "RTI", "ST",  "STR", "TRAP" };

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

errorCode Assembly::encode(_16_BIT* src, vector<string> code,
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
        return LD(src, code, labels);
    }

    msg = "Error in codes: invalid opcode\n";
    return INVALID_OPCODE;
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

errorCode Assembly::LD(_16_BIT* final, vector<string> vec,
                       map<string, _16_BIT>& labels) {

    // LD   DR  PCoffest9
    // 0010 000 111111111

    *final = assembly_codes["LD"];
    _16_BIT dr, pcoff;

    if (REGs.find(vec[1]) == REGs.end()) {
        msg = "Error Ld: bad DR\n";
        return INVALID_REG;
    }

    dr = REGs[vec[1]];

    if (labels.find(vec[2]) == labels.end()) {
        msg = "Error ld: bad label not found\n";
        return INVALID_REG;
    }

    pcoff = labels[vec[2]];

    errorCode lab = PCoffest9Range(pcoff);

    if (lab != OK_VALID) {
        return lab;
    }

    *final += pcoff;  // 111 111 111
    // or use shiftCopy
    // shiftCopy(final, pcoff, 9);

    // set the dr
    dr <<= 9;
    *final += dr;

    return OK_VALID;
}

errorCode Assembly::LDI(_16_BIT* final, vector<string> vec,
                        map<string, _16_BIT>& labels) {

    // LDI  DR  PCoffest9
    // 1010 000 111111111

    *final = assembly_codes["LDI"];
    _16_BIT dr, pcoff;

    if (REGs.find(vec[1]) == REGs.end()) {
        msg = "Error Ldi: bad DR\n";
        return INVALID_REG;
    }

    dr = REGs[vec[1]];

    if (labels.find(vec[2]) == labels.end()) {
        msg = "Error ldi: bad label not found\n";
        return INVALID_REG;
    }

    pcoff = labels[vec[2]];

    errorCode lab = PCoffest9Range(pcoff);

    if (lab != OK_VALID) {
        return lab;
    }

    *final += pcoff;  // 111 111 111

    // set the dr
    dr <<= 9;
    *final += dr;

    return OK_VALID;
}

errorCode Assembly::LDR(_16_BIT* final, vector<string> vec,
                        map<string, _16_BIT>& labels) {

    // LDI  DR  baser offest6
    // 1010 000 111   111111

    *final = assembly_codes["LDI"];
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