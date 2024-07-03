#ifndef DISPLAY_H
#define DISPLAY_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Display
{
public:
    int displayArray[64 * 32] = {0};

    Display();
    ~Display();

    bool isOpen();
    bool setPixel(int x, int y);
    void render();
    void clear();

private:
    GLFWwindow *window;
};

#endif // DISPLAY_H
