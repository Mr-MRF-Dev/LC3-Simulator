#include "assembler.h"

Assembler::Assembler() : msg("OK!") {}

errorCode Assembler::compiler(string in) {

    vector<string> codes = split(in);

    return OK_VALID;
}

void Assembler::saveFile(string file_name) {}

string Assembler::getMsg() { return msg; }

vector<string> Assembler::split(string str) {

    vector<string> final;
    string temp = "";

    for (int i = 0; i < (int)str.size(); i++) {
        if (str[i] != SPLIT_POINT) {
            temp += str[i];
        }

        else {
            // find comments
            auto comm_point = temp.find(COMMENT_CHAR);
            // remove comments
            if (comm_point != string::npos) temp.erase(comm_point);
            if (!temp.empty()) final.push_back(temp);
            temp.clear();
        }
    }
    final.push_back(temp);

    return final;
}