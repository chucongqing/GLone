#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "Base.h"
#include "common.h"
#include "Shader.h"



class LearnLight : public Base
{
public:
	LearnLight();
	~LearnLight();

	virtual void init();
	virtual void selfDisplay();

protected:
	Shader  m_lightShader;
	Shader m_lampShader;
	glm::vec3 lightPos;
	
	
	GLuint VBO, containerVAO;
	GLuint lightVAO;
	DWORD deltatime;
};
#endif