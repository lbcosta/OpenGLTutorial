#version 330

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vColor;

out vec4 vertexColor;

void main()
{
	gl_Position = vPosition;
	vertexColor = vColor;
}