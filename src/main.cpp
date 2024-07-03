#include "display.h"

int main()
{

    // making a new display
    Display display;
    display.setPixel(0, 0);
    while (display.isOpen())
    {

        display.render();
    }

    return 0;
}
