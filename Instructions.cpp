#include "Instructions.h"
#include <bits/stdc++.h>

using namespace std;

vector<string> Instructions::Get_Instructions() {
    vector<string> content = instruct;
    return content;
}

void Instructions::Read_From_File() {
    string fileName, fileContent, pos = "";
    stringstream content;
    vector<string> instructions;
    cout << "Please enter file name:";
    getline(cin, fileName);                               // get file name and check the validity of format.
    while (fileName.size() < 5 || fileName.substr(fileName.size() - 4, 4) != ".txt") {
        cout << "\nThe file name should be like this ----> (file name).txt\n";
        cout << "Please enter a valid file name :";
        getline(cin, fileName);
    }
    ifstream file(fileName);
    while (fileName.size() < 5 || fileName.substr(fileName.size() - 4, 4) != ".txt" || !file.good()) {
        cout << "\nThe file name should be like this ----> (file name).txt\n";
        cout << "Please enter a valid file name :";
        getline(cin, fileName);
    }
    content << file.rdbuf();
    fileContent = content.str();
    for (int i = 0; i < fileContent.size(); ++i) {
        fileContent.erase(remove(fileContent.begin(), fileContent.end(), '\n'), fileContent.end());
        fileContent.erase(remove(fileContent.begin(), fileContent.end(), ' '), fileContent.end());
    }
    for (int i = 0; i < fileContent.size(); i += 4) {
        instructions.push_back(fileContent.substr(i, 4));
    }
    for (int i = 0; i < instructions.size(); ++i) {
        for (int j = 0; j < 4; ++j) {
            if (instructions[i][j] < 48 || (instructions[i][j] > 57 && instructions[i][j] < 65) ||
                (instructions[i][j] > 70 && instructions[i][j] < 97) || instructions[i][j] > 102) {
                instructions.erase(instructions.begin() + i);
                i --;
                break;
            }
        }
    }
    instruct = instructions;
}

int Instructions::Hexa_To_Decimal(string Hex_Number) {
    // Convert the hexadecimal number to decimal.
    int decimalValue = stoi(Hex_Number, nullptr, 16);
    return decimalValue;
}

string Instructions::Decimal_To_Hexa (int Dec_Number) {
    stringstream hexadecimal;
    // Convert the decimal number to hexadecimal.
    hexadecimal << hex << (static_cast<uint16_t>(Dec_Number) & 0xFF);
    return hexadecimal.str();
}

string Instructions::OneComplement(string binary) {
    while (binary.size() < 16) {binary = '0' + binary;}

    // For ones complement flip every bit in the binary number.
    for (int i = 0; i < binary.size(); ++i) {
        binary[i] = (binary[i] == '0') ? '1' : '0';
    }
    return binary;
}

string Instructions::TwoComplement(string& binary) {
    string onesComplement = OneComplement(binary);

    // For twos complement add 1 to the ones complement.
    int carry = 1;
    for (int i = binary.size() - 1; i >= 0; --i) {
        if (onesComplement[i] == '1' && carry == 1) onesComplement[i] = '0';
        else if (onesComplement[i] == '0' && carry == 1) {
            onesComplement[i] = '1';
            carry = 0;
        }
    }
    return onesComplement;
}

string Instructions::decimalToBinary(int num) {
    string bin = "";
    bool isNegative = false;
    
    // If the number is zero, return 0.
    if (num == 0) {return "0";}
    // If the number is negative, convert it to positive and set the isNegative flag to true.
    else if (num < 0) {
        isNegative = true, num *= -1;
    }
    
    // Convert the decimal number to binary.
    while (num > 0) {
        bin = char('0' + num % 2) + bin;
        num /= 2;
    }
    
    // Make the binary number have 16 bits.
    while (bin.size() < 16) {bin = '0' + bin;}
    return isNegative ? TwoComplement(bin) : bin;
}

string Instructions::AddingBinaryNumbers(string binary1, string binary2) {
    string result;
    int carry = 0;
    binary1 = '0' + binary1, binary2 = '0' + binary2;

    // Make the two binary numbers have the same size.
    while (binary1.size() > binary2.size()) {binary2 = '0' + binary2;}
    while (binary2.size() > binary1.size()) {binary1 = '0' + binary1;}

    // Adding the two binary numbers.
    for (int i = binary1.size() - 1; i >= 0; --i) {
        int sum = (binary1[i] - '0') + (binary2[i] - '0') + carry;
        if (sum == 0) {
            result.push_back('0');
            carry = 0;
        }
        else if (sum == 1) {
            result.push_back('1');
            carry = 0;
        }
        else if (sum == 2) {
            result.push_back('0');
            carry = 1;
        }
        else if (sum == 3) {
            result.push_back('1');
            carry = 1;
        }
    }

    reverse(result.begin(), result.end());
    return result;
}

void Instructions::AddingTwoComplement(string& address1, string& address2, string& address3, Register& reg) {
    int valReg1 = Hexa_To_Decimal(reg.getRegister(address2));
    int valReg2 = Hexa_To_Decimal(reg.getRegister(address3));
    string binary1 = decimalToBinary(valReg1);
    string binary2 = decimalToBinary(valReg2);
    string result = AddingBinaryNumbers(binary1, binary2);
    reg.setRegister(address1, Decimal_To_Hexa(Hexa_To_Decimal(result)));
}

void Instructions::OrBitwiseOperation(string& address1, string& address2, string& address3, Register& reg) {
    int valReg1 = Hexa_To_Decimal(reg.getRegister(address2));
    int valReg2 = Hexa_To_Decimal(reg.getRegister(address3));
    int result = valReg1 | valReg2;
    reg.setRegister(address1, Decimal_To_Hexa(result));
}

void Instructions::AndBitwiseOperation(string& address1, string& address2, string& address3, Register& reg) {
    int valReg1 = Hexa_To_Decimal(reg.getRegister(address2));
    int valReg2 = Hexa_To_Decimal(reg.getRegister(address3));
    int result = valReg1 & valReg2;
    reg.setRegister(address1, Decimal_To_Hexa(result));
}

void Instructions::exclusiveOr(int R, int S, int T) {
    int result = getRegister(S) ^ getRegister(T);
    setRegister(R, result);

    cout << "Performed XOR between registers " << S << " and " << T << ". Result stored in register " << R << ": " << result << endl;
}

void Instructions::rotateRight(int R, int X) {
    int value = getRegister(R);
    int rotatedValue = (value >> X) | (value << (32 - X));
    setRegister(R, rotatedValue);

    cout << "Rotated register " << R << " to the right by " << X << " bits. New value: " << rotatedValue << endl;
}

void Instructions::conditionalJump(int R, int XY) {
    if (getRegister(R) == getRegister(0)) {
        setProgramCounter(XY);
        cout << "Jumping to address " << XY << " because register " << R << " equals register 0" << endl;
    } else {
        cout << "No jump. Register " << R << " does not equal register 0." << endl;
    }
}

void Instructions::halt() {
    halted = true;
    cout << "Execution halted." << endl;
}

void Instructions::conditionalJumpGreater(int R, int XY) {
    int regRValue = getRegister(R);
    int reg0Value = getRegister(0);
    
    if (regRValue > reg0Value) {
        setProgramCounter(XY);
        cout << "Jumping to address " << XY << " because register " << R << " (" << regRValue << ") is greater than register 0 (" << reg0Value << ")" << endl;
    } else {
        cout << "No jump. Register " << R << " (" << regRValue << ") is not greater than register 0 (" << reg0Value << ")" << endl;
    }
}
