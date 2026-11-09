#ifndef MAINMACHINE_H
#define MAINMACHINE_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class MainMachine {
private:
    vector<string> memory;
    vector<string> registers;
    int pc;
    string ir;

public:
    MainMachine();
    bool loadProgramFromFile(string filename);
    void runContinuous();
    void runStepByStep();
    void displayStatus();
};

#endif

