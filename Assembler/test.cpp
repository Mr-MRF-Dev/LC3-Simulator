
#include <fstream>
#include <iostream>
#include <map>
#include <string>
using namespace std;

#include "assembler.h"

// int hexToInt(string str) {

//     // x1234 => int
//     str.erase(str.begin());  // remove x
//     return stoi(str, 0, 16);
// }

int main() {

    Assembly a;
    cout << a.isORG("ORG") << endl;

    vector<string> m = { "ADD", "R2", "R1", "x-f" };
    map<string, _16_BIT> s;
    _16_BIT f = 0;
    cout << a.encode(&f, m, s);

    cout << endl << endl << endl << f << endl << endl;

    // map<int, int> aa = { { 1, 2 } };

    // cout << aa[1] << endl;
    // cout << aa[5] << endl;
    // cout << aa[67] << endl;

    int vvv = stoi("-1010", 0, 2);

    if (vvv > 16 || vvv <= -16) {
        cout << vvv << endl;
    } else {
        cout << vvv << endl;
        cout << vvv << endl;
        cout << vvv << endl;
    }

    // cout << stoi("sd w", 0, 10);

    // _16_BIT final = 0x1000, dr = 3, sr1 = 6, sr2 = 2;

    // final += sr2;
    // sr1 <<= 6;
    // cout << endl << endl << sr1 << endl;

    // final += sr1;
    // dr <<= 9;
    // final += dr;

    // cout << endl << endl << final << endl;

    // cout << hexToInt("xffff");

    //  std::vector<unsigned short> arr = {0xFFFF, 2, 3, 4, 5};  // Your array

    // // Open a binary file for writing
    // std::ofstream outfile("array.bin", std::ios::binary);

    // if (outfile.is_open()) {
    //     // Write the array data to the file
    //     outfile.write(reinterpret_cast<char*>(arr.data()), arr.size() *
    //     sizeof(unsigned short)); outfile.close(); std::cout << "Array saved
    //     to array.bin" << std::endl;
    // } else {
    //     std::cerr << "Error opening file!" << std::endl;
    // }

    // typedef unsigned short int MMD;
    // MMD arr[] = {0xffff, 0xff00, 3, 4, 5};  // Your array
    // size_t arrSize = sizeof(arr) / sizeof(arr[0]);

    // std::ofstream outfile("array.bin", std::ios::binary);
    // if (outfile.is_open()) {
    //     outfile.write(reinterpret_cast<char*>(arr), arrSize * sizeof(MMD));
    //     outfile.close();
    //     std::cout << "Array saved to array.bin" << std::endl;
    // } else {
    //     std::cerr << "Error opening file!" << std::endl;
    // }

    Assembler mmd("mmd");

    cout << endl
         << endl
         << "compile:" << mmd.compiler("ADD R2, R1, #456678 ; the add two reg")
         << endl;
    cout << mmd.getMsg() << endl;
    mmd.saveFile();

    // a.saveFile();
    // auto db = a.tokenize(
    //     "asssss ,,             \naas;d,, ,, ,, dddd\n   m m     d ,  "
    //     "asasas,  , asas\nasagdf sdfk sdfsdkfj gdn\n\\sdf "
    //     "sdkfj hsadfkadsjf   ");

    // for (auto i :db) {
    //     for (auto j : i) {
    //         cout << "'" << j << "'";
    //     }
    //     cout << endl;
    // }

    // string aa = "mmdd;sssas";

    // int c = aa.find(";");
    // aa.erase(c);
    // cout << aa;

    // if (aa.empty()) {
    //     cout << "mmmaddd";
    // } else {
    //     cout << "fffff";
    // }

    return 0;
}
