#include "Shader.h"

#include "LoadShaders.h"

Shader::Shader()
{
	m_shaderProgram = 0;
}


Shader::~Shader()
{
}
Shader::Shader(const char* vShader, const char* fragShader)
{
	loadShader(vShader, fragShader);
}

void Shader::Use()
{
	glUseProgram(m_shaderProgram);
}
GLuint Shader::loadShader(const char* vShader, const char* fragShader)
{
	ShaderInfo shader_info[] =
	{
		{ GL_VERTEX_SHADER, vShader },
		{ GL_FRAGMENT_SHADER, fragShader },
		{ GL_NONE, nullptr }
	};

	m_shaderProgram = LoadShaders(shader_info);

	return m_shaderProgram;
}