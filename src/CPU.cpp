#include "CPU.h"
#include <iostream>
#include <cstdlib>
#include <array>
#include <ctime>

using namespace std;

// Constructor
CPU::CPU()
{
    cout<<"this is a cpu";
    memory.fill(0);
    v.fill(0);
    i = 0;
    delayTimer = 0;
    soundTimer = 0;
    pc = 0x200; // Program counter starts at 0x200
    paused = false;
    speed = 10;

    // Initialize the stack
    stack.clear();

    // Seed random number generator for instructions needing random numbers
    srand(std::time(nullptr));
}

void CPU::loadSpritesIntoMemory()
{
    // Array of hex values for each sprite. Each sprite is 5 bytes.
    // The technical reference provides us with each one of these values.
    const std::array<uint8_t, 80> sprites = {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };

    // Load sprites into memory starting at 0x000 (interpreter section)
    for (size_t i = 0; i < sprites.size(); ++i)
    {
        memory[i] = sprites[i];
    }
}

void CPU::loadProgramIntoMemory(const std::vector<uint8_t> &program)
{
    // Ensure that program can fit into memory starting at 0x200
    if (program.size() > (4096 - 0x200))
    {
        std::cerr << "Error: Program size exceeds available memory space.\n";
        return;
    }

    // Copy program data into memory starting at address 0x200
    for (size_t loc = 0; loc < program.size(); ++loc)
    {
        memory[0x200 + loc] = program[loc];
    }
}