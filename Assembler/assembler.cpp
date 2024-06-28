#include "assembler.h"

Assembler::Assembler() : msg("OK!") {}

errorCode Assembler::compiler(string in) {

    vector<vector<string>> codes = tokenize(in);

    return OK_VALID;
}

void Assembler::saveFile(string file_name) {}

string Assembler::getMsg() { return msg; }

/*
Splits this source by line, removes comments,
pads commas, and then splits by whitespace.
*/
vector<vector<string>> Assembler::tokenize(string str) {

    vector<vector<string>> final;
    vector<string> vec;
    string temp = "";
    int count = 0;
    bool is_comment = false;

    for (int i = 0; i < (int)str.size(); i++) {

        if (str[i] != SPLIT_SYMBOL) {

            // ignore comments
            if (is_comment) continue;

            if (str[i] == COMMENT_SYMBOL) {
                is_comment = true;
                continue;
            }

            // remove comma char
            if (str[i] == COMMA_SYMBOL) continue;

            // remove extra spcae
            if (str[i] == SPACE_SYMBOL) {
                if (count == 0)
                    continue;
                else {
                    vec.push_back(temp);
                    temp.clear();
                    count = 0;
                    continue;
                }
            }

            temp += str[i];
            count++;
        }

        else {
            is_comment = false;

            if (!temp.empty()) {
                vec.push_back(temp);
                temp.clear();
                count = 0;
            }

            // remove the empty lines
            if (!vec.empty()) final.push_back(vec);
            vec.clear();
        }
    }

    // check for last code
    if (!temp.empty()) {
        vec.push_back(temp);
        temp.clear();
        count = 0;
    }

    // remove the empty lines
    if (!vec.empty()) final.push_back(vec);

    return final;
}
