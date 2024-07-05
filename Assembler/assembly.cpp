#include "assembly.h"

string Assembly::getMsg() { return msg; }

Assembly::Assembly() : msg("OK!") {
    assembly_label = { "ORG",  "ADD", "AND", "BR",  "JMP", "JSR",
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

    if (find(assembly_label.begin(), assembly_label.end(), op_code) !=
        assembly_label.end()) {
        return true;
    }

    return false;
}

bool Assembly::isORG(string str) { return (str == assembly_label.front()); }

errorCode Assembly::encode(_16_BIT* src, vector<string> code,
                           map<string, _16_BIT>& labels) {

    string front = code.front();

    if (!isOpcode(front)) {
        msg = "Error in codes: invalid opcode\n";
        return INVALID_OPCODE;
    }

    if (front == "ADD") {
        return ADD(src, code);
    }

    else if (front == "AND") {
        return AND(src, code);
    }

    return OTHER_ERROR;
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
        for (int i = 0; i < 5; i++, imm5 >>= 1) {

            if (imm5 % 2 != 0) {
                _16_BIT tmp = 1;
                tmp <<= i;
                *final += tmp;
            }
        }

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
    // 0001 000 000 0 00 000

    // AND  DR  SR1 1 imm5
    // 0001 000 000 1 00000

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
        for (int i = 0; i < 5; i++, imm5 >>= 1) {

            if (imm5 % 2 != 0) {
                _16_BIT tmp = 1;
                tmp <<= i;
                *final += tmp;
            }
        }

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

    if (num < 0 or num >= MEMORY_SIZE) {

        msg = "Error in number if org, out of range\n";
        return NUMBER_OUT_OF_RANGE;
    }

    return OK_VALID;
}

// EOF