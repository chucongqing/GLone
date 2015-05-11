#ifndef _common_h_
#define _common_h_


#include <GLTools.h>

#define FREEGLUT_STATIC
#include <gl/glut.h>

#include <gl/glew.h>

#include "LoadShaders.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "loadTexture.h"


#define BUFFER_OFFSET(x) ((void*)x)

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define KEY(x) #@x

static GLuint windowmode = GLUT_RGBA | GLUT_DEPTH;

static int mouse_x;
static int mouse_y;






#endif