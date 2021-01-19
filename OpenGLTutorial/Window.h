#pragma once

#include <GL\glew.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window(int width = 800, int height = 600, const char* title = "");
	void update();
	~Window();

	inline bool shouldClose() const { return m_ShouldClose; }

private:
	GLFWwindow* m_Window;
	bool m_ShouldClose;
	static void errorCallback(int error, const char* description);
};
