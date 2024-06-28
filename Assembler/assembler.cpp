#include "assembler.h"

Assembler::Assembler() : msg("OK!") {

    file_name = string("memory") + BIN_FORMAT;
    fill(arr, arr + MEMORY_SIZE, 0);  // clear the memory
}

Assembler::Assembler(string s) : msg("OK!") {

    file_name = s + BIN_FORMAT;
    fill(arr, arr + MEMORY_SIZE, 0);  // clear the memory
}

void Assembler::setFileName(string str) { file_name = str; }

string Assembler::getFileName() { return file_name; }

string Assembler::getMsg() { return msg; }

errorCode Assembler::compiler(string str) {

    // clear the basic variables and virtual memory
    fill(arr, arr + MEMORY_SIZE, 0);
    codes.clear();

    tokenize(str);

    return OK_VALID;
}

/*
save the virtual memory into file
*/
bool Assembler::saveFile() {
    try {
        std::ofstream outfile(file_name, std::ios::binary);
        if (outfile.is_open()) {
            outfile.write(reinterpret_cast<char *>(arr),
                          MEMORY_SIZE * sizeof(_16_BIT));
            outfile.close();
            msg = "Done!";
            return true;
        }

        else {
            // Set the error message
            msg = "Error: Unable to open the file for writing.";
            return false;
        }
    }

    catch (const std::exception &e) {
        msg =
            "Error: Exception occurred during file I/O.\n\n" + string(e.what());
        return false;
    }
}

/*
Splits this source by line, removes comments,
pads commas, and then splits by whitespace.
*/
void Assembler::tokenize(string str) {

    codes.clear();
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
            if (!vec.empty()) codes.push_back(vec);
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
    if (!vec.empty()) codes.push_back(vec);
}

// map<string, int> Assembler::getLabelAddr() {}
