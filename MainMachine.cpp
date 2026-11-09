#include "MainMachine.h"
#include <fstream>
#include <iomanip>

MainMachine::MainMachine() {
    memory.resize(256, "00");
    registers.resize(16, "00");
    pc = 0;
    ir = "0000";
}

bool MainMachine::loadProgramFromFile(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open program file!\n";
        return false;
    }


    fill(memory.begin(), memory.end(), "00");
    fill(registers.begin(), registers.end(), "00");
    pc = 0;
    ir = "0000";

    string b1, b2;
    int address = 0;

    while (file >> b1 && address < 256) {
        if (b1[0] == ';') {
            string dummy;
            getline(file, dummy);
            continue;
        }

        memory[address] = b1;
        if (file >> b2) {
            memory[address + 1] = b2;
            address += 2;
        } else {
            address += 1;
            break;
        }
    }

    file.close();
    cout << "Program loaded into memory successfully. Total bytes loaded: " << address << "\n";
    return true;
}

void MainMachine::runContinuous() {
    while (pc < 256) {
        string byte1 = memory[pc];
        string byte2 = memory[pc + 1];

        if (byte1 == "00" && byte2 == "00") break;
        if (byte1 == "C0" && byte2 == "00") {
            ir = byte1 + byte2;
            pc += 2;
            break;
        }

        ir = byte1 + byte2;
        pc += 2;
    }
    cout << "\nProgram execution finished.\n";
}

void MainMachine::runStepByStep() {
    if (pc >= 256) {
        cout << "End of memory reached.\n";
        return;
    }

    string byte1 = memory[pc];
    string byte2 = memory[pc + 1];
    ir = byte1 + byte2;
    pc += 2;

    char opCode = ir[0];
    int regIndex = stoi(string(1, ir[1]), nullptr, 16);
    string operand = ir.substr(2, 2);

    cout << "\n[Executing] Opcode: " << opCode << " | Register: R" << hex << uppercase << regIndex << " | Operand: " << operand << "\n";

    switch (opCode) {
        case '1':
        {
            int address = stoi(operand, nullptr, 16);
            if (address >= 0 && address < 256) {
                registers[regIndex] = memory[address];
                cout << "-> Loaded value " << memory[address] << " from memory [0x" << operand << "] into R" << regIndex << "\n";
            }
            break;
        }
        case '2':
        {
            registers[regIndex] = operand;
            cout << "-> Loaded immediate value " << operand << " into R" << regIndex << "\n";
            break;
        }
        case '3':
        {
            int address = stoi(operand, nullptr, 16);
            if (address >= 0 && address < 256) {
                memory[address] = registers[regIndex];
                cout << "-> Stored value " << registers[regIndex] << " from R" << regIndex << " into memory [0x" << operand << "]\n";
            }
            break;
        }
        case '5':
        {
            int regS = stoi(string(1, operand[0]), nullptr, 16);
            int regT = stoi(string(1, operand[1]), nullptr, 16);

            int valS = stoi(registers[regS], nullptr, 16);
            int valT = stoi(registers[regT], nullptr, 16);
            int sum = valS + valT;

            if (sum > 255) sum %= 256;

            stringstream ss;
            ss << uppercase << hex << setw(2) << setfill('0') << sum;
            registers[regIndex] = ss.str();

            cout << "-> Added R" << regS << " (" << valS << ") + R" << regT << " (" << valT << ") = " << sum << " and stored in R" << regIndex << "\n";
            break;
        }
        case 'B':
        {
            int targetReg = stoi(string(1, ir[1]), nullptr, 16);
            if (registers[targetReg] == registers[0]) {
                pc = stoi(operand, nullptr, 16);
                cout << "-> Jumped to address 0x" << operand << " because R" << targetReg << " equals R0.\n";
            } else {
                cout << "-> Jump condition not met (R" << targetReg << " != R0).\n";
            }
            break;
        }
        case 'C':
        case 'c':
        {
            cout << "-> Program Halted (C000 executed).\n";
            pc = 256;
            break;
        }
        default:
            cout << "-> Opcode '" << opCode << "' executed.\n";
            break;
    }
}
void MainMachine::displayStatus() {
    cout << "\n=========================================\n";
    cout << "            CURRENT MACHINE STATE          \n";
    cout << "=========================================\n";
    cout << "PC (Program Counter): 0x" << hex << uppercase << pc << dec << "\n";
    cout << "IR (Instruction Reg): " << ir << "\n";

    cout << "--- Registers State ---\n";
    for (int i = 0; i < 16; i++) {
        cout << "R" << hex << uppercase << i << ": " << registers[i] << "  ";
        if ((i + 1) % 8 == 0) cout << "\n";
    }

    cout << "\n--- Memory State (First bytes) ---\n";
    for (int i = 0; i < 32; i += 2) {
        cout << "[" << hex << uppercase << i << "]: " << memory[i] << " " << memory[i+1] << "   ";
        if ((i + 2) % 8 == 0) cout << "\n";
    }
    cout << "\n-----------------------------------------\n";
}

