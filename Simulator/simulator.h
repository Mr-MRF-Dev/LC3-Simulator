#ifndef ASSEMBLER_H
#define ASSEMBLER_H

// includes
#include <algorithm>
#include <fstream>
#include <map>
#include <string>
#include <vector>

#include "assembly_decode.h"
using namespace std;

class Simulator {
    private:
        AssemblyDecode ASB;

        bool run;
        bool N, Z, P;
        _16_BIT PC;
        _16_BIT IR;
        _16_BIT MDR;
        _16_BIT MAR;
        map<string, _16_BIT> REGs;

        string msg;
        string file_path;

        // virtual memory
        _16_BIT arr[MEMORY_SIZE];

        errorCode core();
        void clear();
        void init();

    public:
        Simulator();
        Simulator(string);

        void setFilePath(string);
        string getFilePath();
        bool openFile();

        // return the msg (Errors and status and ...)
        string getMsg();
};

#endif  // ASSEMBLER_H
