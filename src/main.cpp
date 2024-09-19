#include "display.h"
#include "CPU.h"

int main()
{
    // Making a new display
    Display display;
    CPU cpu;

    display.setPixel(0, 0);
    cpu.loadSpritesIntoMemory();
    
    while (display.isOpen())
    {

        display.render();
    }

    return 0;
}
