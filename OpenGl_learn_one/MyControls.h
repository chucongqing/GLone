#pragma once

#include "common.h"

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;



class MyControls
{
public:
	
	~MyControls();

	static MyControls* getInstance();
	void computeMatricesFromInputs();

	static  void keyboard(unsigned char key, int x, int y);
	static void keyboardup(unsigned char key, int x, int y);
	static void mouse_routine(int x, int y);

	glm::mat4 getViewMatrix(){
		return ViewMatrix;
	}
	glm::mat4 getProjectionMatrix(){
		return ProjectionMatrix;
	}

	int screen_width;
	int screen_height;

	glm::vec3 getPosition(){
	return position;
	}
	glm::vec3 getFront(){
		return m_direction;
	}

	short w;
	short s;
	short a;
	short d;
private:
	MyControls();
	static MyControls* m_pInstance;
	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;

	// Initial position : on +Z
	glm::vec3 position ;
	glm::vec3 m_direction;
	// Initial horizontal angle : toward -Z
	float horizontalAngle ;
	// Initial vertical angle : none
	float verticalAngle ;
	// Initial Field of View
	float initialFoV;

	float speed; // 3 units / second
	float mouseSpeed ;

	int pos_x;
	int pos_y;

	float deltax;
	float deltay;

};

