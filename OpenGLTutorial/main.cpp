#include <iostream>
#include <memory>
#include "Window.h"
#include "MyScene.h"

int main()
{
    Window w(800, 600, "Introdução OpenGL");

    w.setScene(std::unique_ptr<Scene>(new MyScene()));

    while (!w.shouldClose())
    {
        w.update();
    }

    return 0;
}
