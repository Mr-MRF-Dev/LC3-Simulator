#include "simulator.h"

Simulator::Simulator() : msg("OK!") {

    file_path = string(DEFAULT_FILE_NAME) + BIN_FORMAT;
    clear();
    init();
}

Simulator::Simulator(string s) : msg("OK!") {

    file_path = s + BIN_FORMAT;
    clear();
    init();
}

void Simulator::init() {
    PC = 12288;
    REGs = { { "R0", 0 }, { "R1", 0 }, { "R2", 0 }, { "R3", 0 },
             { "R4", 0 }, { "R5", 0 }, { "R6", 0 }, { "R7", 0 } };

    run = false;
    N = false;
    Z = false;
    P = false;
}

void Simulator::setFilePath(string str) { file_path = str + BIN_FORMAT; }

string Simulator::getFilePath() { return file_path; }

string Simulator::getMsg() { return msg; }

/*
clear the basic variables and virtual memory
*/
void Simulator::clear() {
    fill(arr, arr + MEMORY_SIZE, 0);;
}

errorCode Simulator::core() {

    _16_BIT start_line = 0;

    for (auto i : codes) {
        string op_code = i.front();

        // ORG op code
        if (ASB.isORG(op_code)) {
            // convert hex to int for word address
            // start_line = hexToInt(i[1]);
            int new_pc;
            errorCode lab = ASB.convertNumberFormat(&new_pc, i[1]);

            if (lab != OK_VALID) {
                // TODO: fix the err msg
                msg = string("Error in convert hex to int in org in core\n\n") +
                      ASB.getMsg();
                return lab;
            }

            start_line = new_pc;
            continue;
        }

        _16_BIT res = 0;
        // handle the code of line
        errorCode lab = ASB.encode(start_line, &res, i, labels);

        if (lab != OK_VALID) {

            msg = ASB.getMsg();
            return lab;
        }

        arr[start_line] = res;
        start_line++;
    }

    return OK_VALID;
}

/*
open the virtual memory into file
*/
bool Simulator::openFile() {
    try {
        std::ifstream infile(file_path, std::ios::in | std::ios::binary);
        if (infile.is_open()) {
            for (int i = 0; i < MEMORY_SIZE; i++) {
                char *tmp = "12";
                infile.read(reinterpret_cast<char *>(&arr[i]), sizeof(_16_BIT));
            }

            infile.close();
            msg = "Done!";
            run = true;
            return true;
        }

        else {
            msg = "Error: Unable to open the file for reading.\n";
            return false;
        }
    }

    catch (const std::exception &e) {
        msg =
            "Error: Exception occurred during file I/O.\n\n" + string(e.what());
        return false;
    }
}

// EOF