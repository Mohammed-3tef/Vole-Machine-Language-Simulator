#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <bits/stdc++.h>
#include "Register.h"
#include "Memory.h"
using namespace std;

class Instructions {
private:
    vector<string> instruct;
    Register& reg; 
    bool halted = false;
    int programCounter = 0;
    void setProgramCounter(int address) { programCounter = address; }
public:
    Instructions(Register& reg) : reg(reg) {}
    void Read_From_File();
    vector<string> Get_Instructions();
    void Move(string address1, string address2, Register &reg);
    void Load_To_Register(string address1, string value, Register &reg);
    void Load_From_Memory_To_Register(string address4, string address1, Register &reg, Memory &mem);
    void Store(string address1, string address2, Register & reg, Memory & mem);
    int Hexa_To_Decimal(string Hex_Number);
    string Decimal_To_Hexa (int Dec_Number);
    string OneComplement(string binary);
    string TwoComplement(string& binary);
    string decimalToBinary(int num);
    int binaryToDecimal(string binNumber);
    string AddingBinaryNumbers(string binary1, string binary2);
    void AddingTwoComplement(string& address1, string& address2, string& address3, Register& reg);
    void OrBitwiseOperation(string& address1, string& address2, string& address3, Register& reg);
    void AndBitwiseOperation(string& address1, string& address2, string& address3, Register& reg);
    void halt();
    void rotateRight(const string& R, int X);
    void conditionalJump(const string& R, int XY);
    void exclusiveOr(int R, int S, int T);
    void conditionalJumpGreater(const string& R, int XY);
};

#endif //INSTRUCTIONS_H
