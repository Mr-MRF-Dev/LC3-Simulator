#ifndef ASSEMBLER_H
#define ASSEMBLER_H

// define keywords
#define SPLIT_SYMBOL '\n'
#define COMMENT_SYMBOL ';'
#define SPACE_SYMBOL ' '
#define COMMA_SYMBOL ','
#define BIN_FORMAT ".bin"

#define MEMORY_SIZE 65536  // 64 * 1024
typedef unsigned short int _16_BIT;

#include <fstream>
#include <string>
#include <vector>
using namespace std;

typedef enum errorCode {
    OK_VALID,         /* No Error */
    UNDEFINED_LABEL,  /* LABEL used without definition */
    INVALID_OPCODE,   /* OPCODE doesn't exist in ISA */
    INVALID_CONSTANT, /* Illegal use of CONSTANT operand */
    OTHER_ERROR       /* All other errors */

} errorCode;

class Assembler {
    private:
        string msg;
        string file_name;

        // lines of codes
        vector<vector<string>> codes;
        // virtual memory
        _16_BIT arr[MEMORY_SIZE];

        void tokenize(string);

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
