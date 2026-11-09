#ifndef REGISTERS_H
#define REGISTERS_H

#include <string>
#include <vector>

class Registers {
private:
    std::vector<std::string> regs;
public:
    Registers();
    std::string getRegister(int index) const;
    void setRegister(int index, const std::string& value);
    void display() const;
};

#endif
