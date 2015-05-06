#include "ShaderManager.h"
#include <gl/glew.h>

ShaderManager::ShaderManager()
{
}


ShaderManager::~ShaderManager()
{
}

char * vertex_shader = "layout(location = 0) int vec4 vPosition; \
					   void main()  \
					   {              \
					   	gl_Position = vPosition;  \
						}								\
						";
char* pixel_shader = "out vec4 fColor;\
void main()\
{\
	fColor = vec4(0.0, 0.0, 1.0, 1.0);\
} ";
void ShaderManager::loadDefaultShader()
{
	GLuint shaderHandle = glCreateShader(GL_VERTEX_SHADER);
	
}

void ShaderManager::LoadVertexShader(const char* filename)
{

}
void ShaderManager::LoadPixelShader(const char* filename)
{

}

void ShaderManager::LoadShader(const char* vs, const char* ps)
{

}