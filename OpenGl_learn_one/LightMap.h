#pragma once
#include "Base.h"
#include "common.h"
#include "Shader.h"


class LightMap : public Base
{
public:
	LightMap();
	~LightMap();


	virtual void init();
	virtual void selfDisplay();

protected:
	Shader  m_lightShader;
	Shader m_lampShader;
	glm::vec3 lightPos;


	GLuint VBO, containerVAO;
	GLuint lightVAO;
	DWORD deltatime;
	GLuint diffuseMap;
	GLuint specularMap;

};

