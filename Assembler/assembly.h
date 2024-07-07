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
#define PROGRAM_BORDER 0xFE00        // start I/O memory
typedef unsigned short int _16_BIT;  // 2 Byte ~ 16 bit

// type of Errors
typedef enum errorCode {
    OK_VALID,            /* No Error */
    UNDEFINED_LABEL,     /* LABEL used without definition */
    INVALID_LABEL,       /* Duplicate label used or label not found */
    INVALID_OPCODE,      /* OPCODE doesn't exist in ISA */
    INVALID_CONSTANT,    /* Illegal use of CONSTANT operand */
    INVALID_NUMBER,      /* invalid number format */
    NUMBER_OUT_OF_RANGE, /* when number out of range */
    INVALID_ORG,         /* when the org number is invalid */
    INVALID_REG,         /* invalid register used */
    INVALID_NZP,         /* invalid n z p flags */
    OTHER_ERROR          /* All other errors */

} errorCode;

// includes
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

class Assembly {
    private:
        string msg;

        vector<string> assembly_labels;
        map<string, _16_BIT> assembly_codes;
        map<string, _16_BIT> REGs;

        errorCode ADD(_16_BIT *, vector<string>);
        errorCode AND(_16_BIT *, vector<string>);
        errorCode NOT(_16_BIT *, vector<string>);
        errorCode LD(_16_BIT, _16_BIT *, vector<string>,
                     map<string, _16_BIT> &);
        errorCode LDI(_16_BIT, _16_BIT *, vector<string>,
                      map<string, _16_BIT> &);
        errorCode LDR(_16_BIT *, vector<string>);
        errorCode LEA(_16_BIT, _16_BIT *, vector<string>,
                      map<string, _16_BIT> &);
        errorCode ST(_16_BIT, _16_BIT *, vector<string>,
                     map<string, _16_BIT> &);
        errorCode STI(_16_BIT, _16_BIT *, vector<string>,
                      map<string, _16_BIT> &);
        errorCode STR(_16_BIT *, vector<string>);
        errorCode BR(_16_BIT, _16_BIT *, vector<string>,
                     map<string, _16_BIT> &);
        errorCode JMP(_16_BIT *, vector<string>);
        errorCode RET(_16_BIT *, vector<string>);
        errorCode JSR(_16_BIT *, vector<string>, map<string, _16_BIT> &);
        errorCode JSRR(_16_BIT *, vector<string>);
        errorCode Variable(_16_BIT *, vector<string>);

        void shiftCopy(_16_BIT *, int, int);

    public:
        Assembly();
        bool isOpcode(string);
        bool isORG(string);

        errorCode imm5Range(int);
        errorCode orgRange(int);
        errorCode PCoffest9Range(int);
        errorCode offest6Range(int);
        errorCode convertNumberFormat(int *, string);
        errorCode convertNumberFormat(_16_BIT *, string);

        errorCode encode(_16_BIT, _16_BIT *, vector<string>,
                         map<string, _16_BIT> &);
        string getMsg();
};

#endif  // ASSEMBLY_H
