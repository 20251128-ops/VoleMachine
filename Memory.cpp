#include "Memory.h"
#include <iostream>
#include <iomanip>

Memory::Memory() {
    cells.resize(256, "00");
}

std::string Memory::getCell(int address) const {
    if (address >= 0 && address < 256) {
        return cells[address];
    }
    return "00";
}

void Memory::setCell(int address, const std::string& value) {
    if (address >= 0 && address < 256) {
        cells[address] = value;
    }
}

void Memory::display() const {
    std::cout << "\n--- Current Memory State ---\n     ";
    for (int i = 0; i < 16; ++i) std::cout << std::hex << std::uppercase << i << " ";
    std::cout << "\n------------------------------------\n";
    for (int i = 0; i < 256; i += 16) {
        std::cout << std::setw(2) << std::setfill('0') << std::hex << i << " | ";
        for (int j = 0; j < 16; ++j) {
            std::cout << cells[i + j] << " ";
        }
        std::cout << "\n";
    }
}
