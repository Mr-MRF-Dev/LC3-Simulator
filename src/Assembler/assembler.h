#ifndef ASSEMBLER_H
#define ASSEMBLER_H

// includes
#include <algorithm>
#include <fstream>
#include <map>
#include <string>
#include <vector>

#include "assembly.h"
using namespace std;

class Assembler {
    private:
        Assembly ASB;

        string msg;
        string file_name;

        // lines of codes
        vector<vector<string>> codes;
        map<string, _16_BIT> labels;
        // virtual memory
        _16_BIT arr[MEMORY_SIZE];

        errorCode core();
        errorCode createLabels();
        void tokenize(string);

        void clear();

    public:
        Assembler();
        Assembler(string);

        void setFileName(string);
        string getFileName();

        // compiler kernel & functions
        errorCode compiler(string);

        bool saveFile();

        // return the msg (Errors and status and ...)
        string getMsg();
};

#endif  // ASSEMBLER_H
