#ifndef ASSEMBLY_DECODE_H
#define ASSEMBLY_DECODE_H

// includes
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

class AssemblyDecode {
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
        errorCode JSR(_16_BIT, _16_BIT *, vector<string>,
                      map<string, _16_BIT> &);
        errorCode JSRR(_16_BIT *, vector<string>);
        errorCode Variable(_16_BIT *, vector<string>);

        void shiftCopy(_16_BIT *, int, int);

    public:
        AssemblyDecode();

        errorCode imm5Range(int);
        errorCode orgRange(int);
        errorCode PCoffestRange(int);
        errorCode offest6Range(int);
        errorCode convertNumberFormat(int *, string);
        errorCode convertNumberFormat(_16_BIT *, string);

        errorCode encode(_16_BIT, _16_BIT *, vector<string>,
                         map<string, _16_BIT> &);
        string getMsg();
};

// TODOS:
// 1 : fix pcoffset border
// 2 : error handler

#endif  // ASSEMBLY_DECODE_H
