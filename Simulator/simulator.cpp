#include "simulator.h"

Simulator::Simulator() : msg("OK!") {

    file_path = string(DEFAULT_FILE_NAME) + BIN_FORMAT;
    clear();
    init();
}

Simulator::Simulator(string s) : msg("OK!") {

    file_path = s + BIN_FORMAT;
    clear();
    init();
}

void Simulator::init() {

    PC = 12288;  // x3000
    status = 0;

    REGs = { { "R0", 0 }, { "R1", 0 }, { "R2", 0 }, { "R3", 0 },
             { "R4", 0 }, { "R5", 0 }, { "R6", 0 }, { "R7", 0 } };

    assembly_codes = { { "ADD", 0x1000 }, { "AND", 0x5000 }, { "BR", 0x0000 },
                       { "JMP", 0xc000 }, { "JSR", 0x4000 }, { "JSRR", 0x4000 },
                       { "LD", 0x2000 },  { "LDI", 0xa000 }, { "LDR", 0x6000 },
                       { "LEA", 0xe000 }, { "NOT", 0x9000 }, { "RET", 0xc000 },
                       { "RTI", 0x8000 }, { "ST", 0x3000 },  { "STR", 0x7000 },
                       { "TRAP", 0xf000 } };

    run = false;
    N = false;
    Z = false;
    P = false;
}

void Simulator::setFilePath(string str) { file_path = str + BIN_FORMAT; }

string Simulator::getFilePath() { return file_path; }

string Simulator::getMsg() { return msg; }

vector<string> Simulator::getEdit() { return edit; }

_16_BIT *Simulator::getMem() { return arr; }

_16_BIT Simulator::getData(string str) {

    if (str == "PC")
        return PC;
    else if (str == "IR")
        return IR;
    else if (str == "MDR")
        return MDR;
    else if (str == "MAR")
        return MAR;
    else if (str[0] == 'R')
        return REGs[str];
    else if (str == "N")
        return N;
    else if (str == "P")
        return P;
    else if (str == "Z")
        return Z;
    else if (str == "ARR")
        return arr[MAR];
    else
        return 0;
}

simErrCode Simulator::decode() {

    _16_BIT op_code = IR & 0xf000;

    if (op_code == assembly_codes["ADD"]) {
        _16_BIT tmp;
        string sr1 = getRegs(IR, 6);
        string dr = getRegs(IR, 9);

        edit.push_back(dr);

        if (IR & 0x0020 == 0x0020) {
            // imm5
            tmp = convertTo16BIT(IR, 5);
            msg = "DR <- SR1 + imm5\nsetCC()\n";
        }

        else {
            string sr2 = getRegs(IR, 0);
            tmp = REGs[sr2];
            msg = "DR <- SR1 + SR2\nsetCC()\n";
        }

        tmp = tmp + REGs[sr1];
        setCC(tmp);
        REGs[dr] = tmp;
        status = 0;
    }

    else if (op_code == assembly_codes["AND"]) {
        _16_BIT tmp;
        string sr1 = getRegs(IR, 6);
        string dr = getRegs(IR, 9);

        edit.push_back(dr);

        if (IR & 0x0020 == 0x0020) {
            // imm5
            tmp = convertTo16BIT(IR, 5);
            msg = "DR <- SR1 & imm5\nsetCC()\n";
        }

        else {
            string sr2 = getRegs(IR, 0);
            tmp = REGs[sr2];
            msg = "DR <- SR1 & SR2\nsetCC()\n";
        }

        tmp = tmp & REGs[sr1];
        setCC(tmp);
        REGs[dr] = tmp;
        status = 0;
    }

    else if (op_code == assembly_codes["NOT"]) {
        string sr1 = getRegs(IR, 6);
        string dr = getRegs(IR, 9);

        edit.push_back(dr);

        msg = "DR <- !(SR)\nsetCC()\n";

        _16_BIT tmp = REGs[sr1];
        tmp = tmp ^ 0xffff;
        setCC(tmp);
        REGs[dr] = tmp;
        status = 0;
    }

    else if (op_code == assembly_codes["LD"]) {

        if (status == 3) {
            _16_BIT tmp = convertTo16BIT(IR, 9);
            MAR = PC + tmp;
            msg = "MAR <- PC + off9\n";
            edit.push_back("MAR");
            status++;
        }

        else if (status == 4) {
            MDR = arr[MAR];
            msg = "MDR <- M[MAR]\n";
            edit.push_back("MDR");
            status++;
        }

        else {
            string dr = getRegs(IR, 9);
            REGs[dr] = MDR;
            setCC(MDR);
            msg = "DR <- MDR\nsetCC()\n";
            edit.push_back(dr);
            status = 0;
        }
    }

    else if (op_code == assembly_codes["LDI"]) {
        if (status == 3) {
            _16_BIT tmp = convertTo16BIT(IR, 9);
            MAR = PC + tmp;
            msg = "MAR <- PC + off9\n";
            edit.push_back("MAR");
            status++;
        }

        else if (status == 4) {
            MDR = arr[MAR];
            msg = "MDR <- M[MAR]\n";
            edit.push_back("MDR");
            status++;
        }

        else if (status == 5) {
            MAR = MDR;
            msg = "MAR <- MDR\n";
            edit.push_back("MAR");
            status++;

        }

        else if (status == 6) {
            MDR = arr[MAR];
            msg = "MDR <- M[MAR]\n";
            edit.push_back("MDR");
            status++;
        }

        else {
            string dr = getRegs(IR, 9);
            REGs[dr] = MDR;
            setCC(MDR);
            msg = "DR <- MDR\nsetCC()\n";
            edit.push_back(dr);
            status = 0;
        }
    }

    else if (op_code == assembly_codes["LDR"]) {
        if (status == 3) {
            _16_BIT tmp = convertTo16BIT(IR, 6);
            string baseR = getRegs(IR, 6);
            MAR = REGs[baseR] + tmp;
            msg = "MAR <- baseR + off6\n";
            edit.push_back("MAR");
            status++;
        }

        else if (status == 4) {
            MDR = arr[MAR];
            msg = "MDR <- M[MAR]\n";
            edit.push_back("MDR");
            status++;
        }

        else {
            string dr = getRegs(IR, 9);
            REGs[dr] = MDR;
            setCC(MDR);
            msg = "DR <- MDR\nsetCC()\n";
            edit.push_back(dr);
            status = 0;
        }
    }

    else if (op_code == assembly_codes["LEA"]) {

        _16_BIT tmp = convertTo16BIT(IR, 9);
        string DR = getRegs(IR, 9);
        REGs[DR] = PC + tmp;
        msg = "DR <- PC + off9\nsetCC()\n";
        setCC(REGs[DR]);
        edit.push_back(DR);
        status = 0;

    }

    else if (op_code == assembly_codes["ST"]) {

        if (status == 3) {
            _16_BIT tmp = convertTo16BIT(IR, 9);
            MAR = PC + tmp;
            msg = "MAR <- PC + off9\n";
            edit.push_back("MAR");
            status++;
        }

        else if (status == 4) {
            string sr = getRegs(IR, 9);
            MDR = REGs[sr];
            msg = "MDR <- SR\n";
            edit.push_back("MDR");
            status++;
        }

        else {
            arr[MAR] = MDR;
            msg = "M[MAR] <- MDR\n";
            edit.push_back("ARR");
            status = 0;
        }
    }

    else if (op_code == assembly_codes["STI"]) {
        if (status == 3) {
            _16_BIT tmp = convertTo16BIT(IR, 9);
            MAR = PC + tmp;
            msg = "MAR <- PC + off9\n";
            edit.push_back("MAR");
            status++;
        }

        else if (status == 4) {
            MDR = arr[MAR];
            msg = "MDR <- M[MAR]\n";
            edit.push_back("MDR");
            status++;
        }

        else if (status == 5) {
            MAR = MDR;
            msg = "MAR <- MDR\n";
            edit.push_back("MAR");
            status++;

        }

        else if (status == 6) {
            string sr = getRegs(IR, 9);
            MDR = REGs[sr];
            msg = "MDR <- SR\n";
            edit.push_back("MDR");
            status++;
        }

        else {
            arr[MAR] = MDR;
            msg = "M[MAR] <- MDR\n";
            edit.push_back("ARR");
            status = 0;
        }
    }

    else if (op_code == assembly_codes["STR"]) {
        if (status == 3) {
            _16_BIT tmp = convertTo16BIT(IR, 6);
            string baseR = getRegs(IR, 6);
            MAR = REGs[baseR] + tmp;
            msg = "MAR <- baseR + off6\n";
            edit.push_back("MAR");
            status++;
        }

        else if (status == 4) {
            string sr = getRegs(IR, 9);
            MDR = REGs[sr];
            msg = "MDR <- SR\n";
            edit.push_back("MDR");
            status++;
        }

        else {
            arr[MAR] = MDR;
            msg = "M[MAR] <- MDR\n";
            edit.push_back("ARR");
            status = 0;
        }
    }

    else if (op_code == assembly_codes["BR"]) {

        if ((N && (IR & 0x0800)) || (Z && (IR & 0x0400)) ||
            (P && (IR & 0x0200))) {
            _16_BIT tmp = convertTo16BIT(IR, 9);
            PC = PC + tmp;
            msg = "PC <- PC + off9\n";
            edit.push_back("PC");
        }
        status = 0;
    }

    else if (op_code == assembly_codes["JMP"] /* or RET */) {

        string sr = getRegs(IR, 6);
        PC = REGs[sr];
        msg = "PC <- baseR\n";
        edit.push_back("PC");
        status = 0;

    }

    // else if (op_code == assembly_codes["RET"]) {
    //     return RET(src, code);
    // }

    else if (op_code == assembly_codes["JSR"] /* or JSRR */) {

        _16_BIT tmpp = PC;
        msg = "tmpp <- PC\n";
        status++;

        if (IR & 0x0800 != 0) {
            _16_BIT tmp = convertTo16BIT(IR, 11);
            PC = PC + tmp;
            msg += "PC <- PC + off11\n";
            edit.push_back("PC");
        }

        else {
            string baseR = getRegs(IR, 6);
            PC = REGs[baseR];
            msg += "PC <- baseR\n";
            edit.push_back("PC");
        }
        REGs["R7"] = tmpp;
        edit.push_back("R7");
        msg += "R7 <- tmpp\n";
        status = 0;
    }

    // else if (op_code == assembly_codes["JSRR"]) {
    //     return JSRR(src, code);
    // }

    else {
        status = 0;
        return OTHER_ERROR;
    }

    return OK;
}

simErrCode Simulator::core() {

    switch (status) {
        // fetch
        case 0:
            msg = "MAR <- PC\nPC <- PC + 1\n";
            MAR = PC;
            PC++;

            edit = { "MAR", "PC" };
            break;

        case 1:
            msg = "MDR <- M[MAR]\n";
            MDR = arr[MAR];

            edit = { "MDR" };
            break;

        case 2:
            msg = "IR <- MDR\n";
            IR = MDR;

            edit = { "IR" };
            break;

        // decode
        default:
            decode();
            break;
    }
}

simErrCode Simulator::step() {

    edit.clear();

    if (!run) {
        msg = "cant run codes\n";
        return CANT_RUN;
    }

    return core();
}

/*
clear the basic variables and virtual memory
*/
void Simulator::clear() { fill(arr, arr + MEMORY_SIZE, 0); }

/*
open the virtual memory into file
*/
bool Simulator::openFile() {
    try {
        std::ifstream infile(file_path, std::ios::in | std::ios::binary);
        if (infile.is_open()) {
            for (int i = 0; i < MEMORY_SIZE; i++) {
                char *tmp = "12";
                infile.read(reinterpret_cast<char *>(&arr[i]), sizeof(_16_BIT));
            }

            infile.close();
            msg = "Done!";
            run = true;
            return true;
        }

        else {
            msg = "Error: Unable to open the file for reading.\n";
            return false;
        }
    }

    catch (const std::exception &e) {
        msg =
            "Error: Exception occurred during file I/O.\n\n" + string(e.what());
        return false;
    }
}

string Simulator::getRegs(_16_BIT num, int count) {

    _16_BIT tmp = 7;  // 0000 0000 0000 0111
    if (count != 0) num >>= count;

    tmp = tmp & num;
    if (tmp == 0) return "R0";
    if (tmp == 1) return "R1";
    if (tmp == 2) return "R2";
    if (tmp == 3) return "R3";
    if (tmp == 4) return "R4";
    if (tmp == 5) return "R5";
    if (tmp == 6) return "R6";
    if (tmp == 7) return "R7";

    return "R0";
}

_16_BIT Simulator::convertTo16BIT(_16_BIT num, int count) {

    _16_BIT f = 0;

    for (int i = 0; i < count - 1; i++, num >>= 1) {

        if (num % 2 != 0) {
            _16_BIT tmp = 1;
            tmp <<= i;
            f += tmp;
        }
    }

    if (num % 2 != 0) {
        for (int i = 0; i < 16 - count + 1; i++) {
            _16_BIT tmp = 1;
            tmp <<= i;
            f += tmp;
        }
    }
}

void Simulator::setCC(_16_BIT num) {
    Z = 0;
    P = 0;
    N = 0;

    if (num == 0) Z = 1;
    if (num >> 15 == 1)
        N = 1;
    else
        P = 1;
}

// EOF