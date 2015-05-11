#pragma once
#include <gl/glew.h>

class Shader
{
public:
	Shader();
	Shader(const char* vShader, const char* fragShader);
	~Shader();
	GLuint loadShader(const char* vShader, const char* fragShader);
	GLuint getProgram() { return m_shaderProgram; }

	void Use();
private:
	GLuint m_shaderProgram;

};

