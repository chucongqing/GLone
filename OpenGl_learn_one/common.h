#ifndef _common_h_
#define _common_h_


#include <GLTools.h>

#define FREEGLUT_STATIC
#include <gl/glut.h>

#include <gl/glew.h>

#include "LoadShaders.h"
#include "vmath.h"
#include "loadTexture.h"


#define BUFFER_OFFSET(x) ((void*)x)

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

static GLuint windowmode = GLUT_RGBA | GLUT_DEPTH;

static int mouse_x;
static int mouse_y;






#endif