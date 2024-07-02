#ifndef ASSEMBLY_H
#define ASSEMBLY_H

// define keywords
#define SPLIT_SYMBOL '\n'
#define COMMENT_SYMBOL ';'
#define SPACE_SYMBOL ' '
#define COMMA_SYMBOL ','
#define BIN_FORMAT ".bin"
#define DEFAULT_FILE_NAME "memory"

#define MEMORY_SIZE 65536            // 64 * 1024
typedef unsigned short int _16_BIT;  // 2 Byte ~ 16 bit

// type of Errors
typedef enum errorCode {
    OK_VALID,            /* No Error */
    UNDEFINED_LABEL,     /* LABEL used without definition */
    INVALID_LABEL,       /* Duplicate label used */
    INVALID_OPCODE,      /* OPCODE doesn't exist in ISA */
    INVALID_CONSTANT,    /* Illegal use of CONSTANT operand */
    NUMBER_OUT_OF_RANGE, /* when number out of range */
    INVALID_ORG,         /* when the org number is invalid */
    INVALID_REG,         /* invalid register used */
    OTHER_ERROR          /* All other errors */

} errorCode;

// includes
#include <algorithm>
#include <map>
#include <string>
#include <vector>
using namespace std;

class Assembly {
    private:
        string msg;

        vector<string> assembly_label;
        map<string, _16_BIT> assembly_codes;
        map<string, _16_BIT> REGs;

        errorCode convertNumberFormmat(_16_BIT *, string);

        errorCode ADD(_16_BIT *, vector<string>);

    public:
        Assembly();
        bool isOpcode(string);
        bool isORG(string);

        errorCode encode(_16_BIT *, vector<string>, map<string, _16_BIT> &);
        string getMsg();
};

#endif  // ASSEMBLY_H
