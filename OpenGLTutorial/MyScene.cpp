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

	m_Vertices = new GLfloat[18]{
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
	};

	// Armazenar os vertices no Vertex Buffer
	glGenBuffers(1, &m_VBO);

	// Criar um ID na GPU para um array de Buffers
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	// Vertices e atributos de vertices: GL_ARRAY_BUFFER
	glBufferData(GL_ARRAY_BUFFER,
		18 * sizeof(GL_FLOAT),
		m_Vertices,
		GL_STATIC_DRAW);

	// Informar a API como interpretar os dados do m_Vertices
	// Especificando vertices
	glVertexAttribPointer(0,
		3,
		GL_FLOAT,
		GL_FALSE,
		6 * sizeof(GLfloat),
		(GLvoid*)0);

	// Especificando cores
	glVertexAttribPointer(1,
		3,
		GL_FLOAT,
		GL_FALSE,
		6 * sizeof(GLfloat),
		(GLvoid*)(3 * sizeof(GLfloat)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

}

MyScene::~MyScene()
{
	glDeleteProgram(m_ShaderProgram);
}

void MyScene::update()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Instala o programa como parte do pipeline de renderizacao
	glUseProgram(m_ShaderProgram);
	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}