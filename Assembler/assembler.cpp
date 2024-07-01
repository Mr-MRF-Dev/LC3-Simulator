#include "assembler.h"

Assembler::Assembler() : msg("OK!") {

    file_name = string(DEFAULT_FILE_NAME) + BIN_FORMAT;
    clear();
}

Assembler::Assembler(string s) : msg("OK!") {

    file_name = s + BIN_FORMAT;
    clear();
}

void Assembler::setFileName(string str) { file_name = str; }

string Assembler::getFileName() { return file_name; }

string Assembler::getMsg() { return msg; }

/*
clear the basic variables and virtual memory
*/
void Assembler::clear() {

    fill(arr, arr + MEMORY_SIZE, 0);
    codes.clear();
    labels.clear();
}

errorCode Assembler::compiler(string str) {

    clear();
    tokenize(str);
    errorCode lab = createLabels();
    if (lab == OK_VALID)
        return core();

    else
        return lab;
}

errorCode Assembler::core() {

    int start_line = 0;

    for (auto i : codes) {
        string op_code = i.front();

        // ORG op code
        if (ASB.isORG(op_code)) {
            // convert hex to int for word address
            start_line = hexToInt(i[1]);
            continue;
        }

        if (ASB.isOpcode(op_code)) {

            _16_BIT res = 0;
            // handle the code of line
            errorCode lab = ASB.encode(&res, i, labels);

            if (lab != OK_VALID) {

                msg = ASB.getMsg();
                return lab;
            }

            arr[start_line] = res;

        }

        else {
            // invalid opcode
            // TODO: fix the err msg
            msg = "Error in codes: invalid opcode\n";
            return INVALID_OPCODE;
        }

        start_line++;
    }

    return OK_VALID;
}

_16_BIT Assembler::hexToInt(string str) {

    // xa => int = 10
    str.erase(str.begin());  // remove x
    return stoi(str, 0, 16);
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
            msg = "Error: Unable to open the file for writing.\n";
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

/*
remove the labels from codes and save it in map
*/
errorCode Assembler::createLabels() {

    int start_line = 0;

    for (auto &i : codes) {
        string first = i.front();

        if (ASB.isORG(first)) {
            try {
                // convert hex to int for word address
                start_line = hexToInt(i[1]);

                if (start_line < 0 or start_line >= MEMORY_SIZE) {

                    // TODO: fix the err msg
                    msg = "Error in number if org, out of range\n";
                    return INVALID_ORG;
                }

            }

            catch (const std::exception &e) {
                // TODO: fix the err msg
                msg =
                    string("Error in convert hex to int in org\n\n") + e.what();
                return INVALID_ORG;
            }

            continue;
        }

        if (!ASB.isOpcode(first)) {

            if (labels.find(first) != labels.end()) {
                // TODO: fix the err msg
                msg = "Error in labels: Duplicate label used\n";
                return INVALID_LABEL;
            }

            labels.insert({ first, start_line });
            i.erase(i.begin());
        }

        start_line++;
    }

    return OK_VALID;
}

// EOF