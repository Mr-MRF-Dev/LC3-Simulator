#ifndef SIMULATOR_H
#define SIMULATOR_H

// includes
#include <algorithm>
#include <fstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

// define keywords
#define BIN_FORMAT ".bin"
#define DEFAULT_FILE_NAME "memory"

#define MEMORY_SIZE 65536            // 64 * 1024
#define PROGRAM_BORDER 0xFE00        // start I/O memory
typedef unsigned short int _16_BIT;  // 2 Byte ~ 16 bit

typedef enum simErrCode { OK, CANT_RUN, ERROR } simErrCode;

class Simulator {
    private:
        bool run;
        bool N, Z, P;
        _16_BIT PC;
        _16_BIT IR;
        _16_BIT MDR;
        _16_BIT MAR;
        map<string, _16_BIT> assembly_codes;
        map<string, _16_BIT> REGs;

        int status;

        string msg;
        vector<string> edit;
        string file_path;

        // virtual memory
        _16_BIT arr[MEMORY_SIZE];

        simErrCode core();
        simErrCode decode();
        void setCC(_16_BIT);
        void clear();
        void init();

    public:
        Simulator();
        Simulator(string);

        simErrCode step();

        void setFilePath(string);
        string getFilePath();
        bool openFile();

        string getRegs(_16_BIT, int);
        _16_BIT convertTo16BIT(_16_BIT, int);

        _16_BIT* getMem();
        // return the msg (Errors and status and ...)
        string getMsg();
        vector<string> getEdit();
        _16_BIT getData(string);
};

#endif  // SIMULATOR_H
