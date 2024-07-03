#include "display.h"
#include <cstring>
#include <iostream>
using namespace std;

int cols = 64;
int rows = 32;
int scale = 10;

// constructor
Display::Display()
{
    // height and width of the display
    int width = cols * scale;
    int height = rows * scale;

    // initializing the glfw library
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    // creating a window and its context
    window = glfwCreateWindow(width, height, "CHIP8 Emulator Display", nullptr, nullptr);

    // if window  creation fails
    if (!window)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // making the openGl context current
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD\n";
        exit(EXIT_FAILURE);
    }

    // initializing the viewport where result will be displayed
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, -1, 1);
}

// free allocated memory in the destructor
Display::~Display()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

bool Display::isOpen()
{
    return !glfwWindowShouldClose(window);
}

bool Display::setPixel(int x, int y)
{
    if (x < 0)
        x += cols;
    if (x >= cols)
        x -= cols;
    if (y < 0)
        y += rows;
    if (y >= rows)
        y -= rows;

    int index = x + y * cols;
    displayArray[index] ^= 1;

    return !displayArray[index];
}

void Display::render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < cols * rows; ++i)
    {
        int x = (i % cols) * scale;
        int y = (i / cols) * scale;

        if (displayArray[i])
        {
            glColor3f(1.0f, 1.0f, 1.0f); // Set pixel color to black
            glBegin(GL_QUADS);
            glVertex2i(x, y);
            glVertex2i(x + scale, y);
            glVertex2i(x + scale, y + scale);
            glVertex2i(x, y + scale);
            glEnd();
        }
    }

    glfwSwapBuffers(window);
}

void Display::clear()
{
    memset(displayArray, 0, cols * rows);
}