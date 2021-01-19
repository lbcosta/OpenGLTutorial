#include "Window.h"
#include <iostream>

Window::Window(int width, int height, const char* title)
{

	m_ShouldClose = true;

	// Inicializar a biblioteca GLFW
	if (!glfwInit())
	{
		std::cerr << "Erro ao inicializar o GLFW" << std::endl;
		return;
	}

	// Definir atributos do contexto OpenGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GL_FALSE);

	glfwSetErrorCallback(Window::errorCallback);

	// Criar a janela
	m_Window = glfwCreateWindow(width, height, title, NULL, NULL);

	if (!m_Window)
	{
		std::cerr << "Erro ao criar a janela" << std::endl;
		return;
	}

	// Tornar o contexto da janela o contexto atual
	glfwMakeContextCurrent(m_Window);

	// Inicializar o GLEW
	GLenum glewInitErr = glewInit();

	if (glewInitErr != GLEW_OK)
	{
		std::cerr << "Erro ao inicializar o GLEW" << glewGetErrorString(glewInitErr) << std::endl;
	}

	// Mostrar dados de ambiente
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);


	std::cout << "Renderizador: " << renderer << std::endl;
	std::cout << "Versao do OpenGL suportada: " << version << std::endl;

	glClearColor(0.5f, 0.5f, 1, 0);

	m_ShouldClose = false;

}

void Window::update()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glfwPollEvents();
	glfwSwapBuffers(m_Window);

	if (!m_ShouldClose)
		m_ShouldClose = glfwWindowShouldClose(m_Window);
}

Window::~Window()
{
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

void Window::errorCallback(int error, const char* description)
{
	std::cerr << "Erro" << error << ": " << description << std::endl;
}