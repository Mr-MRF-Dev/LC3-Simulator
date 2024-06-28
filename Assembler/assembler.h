#ifndef ASSEMBLER_H
#define ASSEMBLER_H

// define keywords
#define SPLIT_POINT '\n'
#define COMMENT_CHAR ';'

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

    public:
        Assembler();

        // compiler kernel & functions
        errorCode compiler(string);
        vector<string> split(string);

        // create bin file
        void saveFile(string);

        // return the error msg (if ok the msg is ok)
        string getMsg();
};

#endif  // ASSEMBLER_H
