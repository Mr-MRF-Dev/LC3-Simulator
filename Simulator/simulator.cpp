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

    PC = 12288;  // x3000
    status = 0;

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

_16_BIT *Simulator::getMem() { return arr; }

simErrCode Simulator::decode() { return OK; }

simErrCode Simulator::core() {

    switch (status) {
        // fetch
        case 0:
            msg = "MAR <- PC\nPC <- PC + 1\n";
            MAR = PC;
            PC++;

            edit = { "MAR", "PC" };
            break;

        case 1:
            msg = "MDR <- M[MAR]\n";
            MDR = arr[MAR];

            edit = { "MDR" };
            break;

        case 2:
            msg = "IR <- MDR\n";
            IR = MDR;

            edit = { "IR" };
            break;

        // decode
        default:
            decode();
            break;
    }

    status++;
}

simErrCode Simulator::step() {
    edit.clear();

    if (!run) {
        msg = "cant run codes\n";
        return CANT_RUN;
    }

    return core();
}

/*
clear the basic variables and virtual memory
*/
void Simulator::clear() { fill(arr, arr + MEMORY_SIZE, 0); }

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