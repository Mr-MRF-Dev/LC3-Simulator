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

    register_codes = { { "R0", 0 }, { "R1", 1 }, { "R2", 2 }, { "R3", 3 },
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

    return OK_VALID;
    return OK_VALID;
}

_16_BIT Assembly::ADD(vector<string> vec) {

    return OK_VALID;
    return OK_VALID;
}

// EOF