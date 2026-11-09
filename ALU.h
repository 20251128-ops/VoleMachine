#ifndef ALU_H
#define ALU_H

#include <string>

class ALU {
public:
    int hexCharToInt(char c);
    char intToHexChar(int val);
    std::string addHex(const std::string& hex1, const std::string& hex2);
    int hexToDecimal(const std::string& hex);
    std::string decimalToHex(int dec);
};

#endif
