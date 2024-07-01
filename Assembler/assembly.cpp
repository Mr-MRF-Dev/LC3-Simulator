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

    return OK_VALID;
}

errorCode Assembly::ADD(_16_BIT* final, vector<string> vec) {

    // s_dr = vec[1]
    // s_sr1 = vec[2]
    // s_sr2 = vec[3]

    // ADD  DR  SR1 0 00 SR2
    // 0001 000 000 0 00 000
    //// 0001 000 000 1 00000
    *final = 0x1000;
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
        msg = "Error Add: bad SR3\n";
        return INVALID_REG;
    }

    sr2 = REGs[vec[3]];

    *final += sr2;
    sr1 <<= 6;
    *final += sr1;
    dr <<= 9;
    *final += dr;

    return OK_VALID;
}

// EOF