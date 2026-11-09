#include "ALU.h"
#include <sstream>
#include <iomanip>
#include <algorithm>

int ALU::hexCharToInt(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return 0;
}

char ALU::intToHexChar(int val) {
    if (val >= 0 && val <= 9) return '0' + val;
    if (val >= 10 && val <= 15) return 'A' + (val - 10);
    return '0';
}

int ALU::hexToDecimal(const std::string& hex) {
    int val;
    std::stringstream ss;
    ss << std::hex << hex;
    ss >> val;
    return val;
}

std::string ALU::decimalToHex(int dec) {
    std::stringstream ss;
    ss << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << (dec & 0xFF);
    return ss.str();
}

std::string ALU::addHex(const std::string& hex1, const std::string& hex2) {
    int val1 = hexToDecimal(hex1);
    int val2 = hexToDecimal(hex2);
    int sum = val1 + val2;
    return decimalToHex(sum);
}
