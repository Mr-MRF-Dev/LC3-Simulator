# LC3 Simulator

An Assembler and Hardware simulator for the LC3 Architecture.

## get started

- install qt6.7
- open CMake file

## Assembler

execute assembly code and make labels and handle all error (like bad labels, dup labels, and etc)

```cpp
// Error Codes
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
```

### Assembly.cpp

execute one line of assembly code.

```cpp
// the encode function
errorCode Assembly::encode(_16_BIT pc, _16_BIT* src, vector<string> code,
                           map<string, _16_BIT>& labels) {}
```

## Simulator

simulate the lc3 pc and run it step by step in `step()`

```cpp
    simErrCode step(); // run step
    _16_BIT* getMem(); // get all memmory data
    string getMsg(); // get step detail
    vector<string> getEdit(); // get name of changend variable or reg or memmory
    _16_BIT getData(string); // get data of variable or reg or ... by call name
```
