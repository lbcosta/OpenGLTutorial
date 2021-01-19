#include <iostream>
#include "Window.h"

int main()
{
    Window w(800, 600, "Introdução OpenGL");

    while (!w.shouldClose())
    {
        w.update();
    }

    return 0;
}
