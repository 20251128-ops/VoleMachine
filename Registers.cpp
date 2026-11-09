#include "Registers.h"
#include <iostream>

Registers::Registers() {
    regs.resize(16, "00");
}

std::string Registers::getRegister(int index) const {
    if (index >= 0 && index < 16) {
        return regs[index];
    }
    return "00";
}

void Registers::setRegister(int index, const std::string& value) {
    if (index >= 0 && index < 16) {
        regs[index] = value;
    }
}

void Registers::display() const {
    std::cout << "\n--- Registers ---\n";
    for (int i = 0; i < 16; ++i) {
        std::cout << "R" << std::hex << std::uppercase << i << ": " << regs[i] << "  ";
        if ((i + 1) % 4 == 0) std::cout << "\n";
    }
}
