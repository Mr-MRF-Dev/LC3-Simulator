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

typedef enum simErrCode { OK, CANT_RUN, OTHER_ERROR } simErrCode;

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

        int status;

        string msg;
        vector<string> edit;
        string file_path;

        // virtual memory
        _16_BIT arr[MEMORY_SIZE];

        simErrCode core();
        simErrCode decode();
        void clear();
        void init();

    public:
        Simulator();
        Simulator(string);

        simErrCode step();

        void setFilePath(string);
        string getFilePath();
        bool openFile();

        _16_BIT* getMem();
        // return the msg (Errors and status and ...)
        string getMsg();
};

#endif  // ASSEMBLER_H
