#include <iostream>
#include "Memory.h"
#include "Registers.h"
#include "ALU.h"

int main() {
    Memory memory;
    Registers registers;
    ALU alu;

    std::cout << "Vole Machine Initialized Successfully!\n";
    memory.display();
    registers.display();

    return 0;
}
