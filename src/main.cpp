#include "display.h"

int main()
{

    // making a new display
    Display display;

    while (display.isOpen())
    {
        display.setPixel(0, 0);
        display.render();
    }

    return 0;
}
