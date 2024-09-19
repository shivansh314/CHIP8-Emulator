#ifndef CPU_H
#define CPU_H

#include <iostream>
#include<vector>
#include <array>

using namespace std;

#include "display.h"

class CPU
{
public:
    // Constructor and Destructor
    CPU();

    //function
    void loadSpritesIntoMemory();
  

private:
    // memory
    array<uint8_t, 4096> memory;
    // 16 8-bit register
    std::array<uint8_t, 16> v;
    // Stores memory addresses. Set this to 0 since we aren't storing anything at initialization.
    uint16_t i;
    // program counter
    uint16_t pc;
    // delay timer
    uint8_t delayTimer;
    // sound timer
    uint8_t soundTimer;
    // stack pointer
    std::vector<uint16_t> stack;

    // Some instructions require pausing, such as Fx0A.
    bool paused;
    int speed;
};

#endif
