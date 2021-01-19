#include "MyScene.h"
#include <GL\glew.h>
#include <iostream>
#include <sstream>
#include "Util.h"

GLint checkShaderCompilation(GLuint shader)
{
	GLint success = 0;
	GLchar infoLog[512];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);
		std::cerr << infoLog << std::endl;
	}

	return success;
}

GLint checkProgramLink(GLuint program)
{
	GLint success = 0;
	GLchar infoLog[512];

	glGetShaderiv(program, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(program, sizeof(infoLog), NULL, infoLog);
		std::cerr << infoLog << std::endl;
	}

	return success;
}

MyScene::MyScene()
{
	std::stringstream vertexSourceStream;
	std::stringstream fragmentSourceStream;

	loadFile("vertex.vs", vertexSourceStream);
	loadFile("fragment.fs", fragmentSourceStream);

	std::string vertexSource = vertexSourceStream.str();
	std::string fragmentSource = fragmentSourceStream.str();

	const char* buff;

	// Criar programa de shader
	m_ShaderProgram = glCreateProgram();

	// Vertex Shader
	buff = vertexSource.c_str();
	m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_VertexShader, 1, &buff, NULL);
	glCompileShader(m_VertexShader);
	checkShaderCompilation(m_VertexShader);
	glAttachShader(m_ShaderProgram, m_VertexShader);
	glDeleteShader(m_VertexShader);

	// Fragment Shader
	buff = fragmentSource.c_str();
	m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_FragmentShader, 1, &buff, NULL);
	glCompileShader(m_FragmentShader);
	checkShaderCompilation(m_FragmentShader);
	glAttachShader(m_ShaderProgram, m_FragmentShader);
	glDeleteShader(m_FragmentShader);

	// Linkando programa de shader
	glLinkProgram(m_ShaderProgram);
	checkProgramLink(m_ShaderProgram);

	glUseProgram(m_ShaderProgram);

	glClearColor(0.5f, 0.5f, 1, 0);
}

MyScene::~MyScene()
{
	glDeleteProgram(m_ShaderProgram);
}

void MyScene::update()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}