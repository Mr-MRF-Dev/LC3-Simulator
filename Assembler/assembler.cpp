#include "assembler.h"

Assembler::Assembler():msg("OK!") {}

errorCode Assembler::compiler(string * in) {
    return OK_VALID;
}

void Assembler::saveFile(string file_name) {}

string Assembler::getMsg() {
    return msg;
}
