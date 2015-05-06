#include <iostream>
#include <tchar.h>
#include <windows.h>


#include <GLTools.h>

#define FREEGLUT_STATIC
#include <gl/glut.h>

#include "ShaderManager.h"
#include "LoadShaders.h"
#include "customshader.h"
#define WINDOW_WIDTH ( 800 ) 
#define WINDOW_HEIGHT ( 600 ) 


#define BUFFER_OFFSET(x) ((void*)x)
enum VAO_IDs { Triangles = 0, NumVAOs =1 };
enum Buffer_IDs { ArrayBuffer = 0, NumBuffers =1 };
enum Attrib_IDs { vPosition = 0 };
GLuint VAOs[1];
GLuint Buffers[1];
const GLuint NumVertices = 6;


// A four vertices
GLuint ebo[1];
GLuint vao[1];
GLuint vbo[1];

void init4()
{
	static const GLfloat vertex_positions[] =
	{
		-1.0f, -1.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 0.0f, 1.0f,
		-1.0f, 1.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 1.0f,
	};

	// Color for each vertex
	static const GLfloat vertex_colors[] =
	{
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f
	};

	// Three indices (we’re going to draw one triangle at a time
	static const GLushort vertex_indices[] =
	{
		0, 1, 2
	};

	// Set up the element array buffer
	glGenBuffers(1, ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		sizeof(vertex_indices), vertex_indices, GL_STATIC_DRAW);

	// Set up the vertex attributes
	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);

	glGenBuffers(1, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(vertex_positions)+sizeof(vertex_colors),
		NULL, GL_STATIC_DRAW);
}


/* Helper function to convert GLSL types to storage sizes */
size_t
TypeSize(GLenum type)
{
	size_t size;
#define CASE(Enum, Count, Type) \
	case Enum: size = Count * sizeof(Type); break


	switch (type) {
		CASE(GL_FLOAT, 1, GLfloat);
		CASE(GL_FLOAT_VEC2, 2, GLfloat);
		CASE(GL_FLOAT_VEC3, 3, GLfloat);
		CASE(GL_FLOAT_VEC4, 4, GLfloat);
		CASE(GL_INT, 1, GLint);
		CASE(GL_INT_VEC2, 2, GLint);
		CASE(GL_INT_VEC3, 3, GLint);
		CASE(GL_INT_VEC4, 4, GLint);
		CASE(GL_UNSIGNED_INT, 1, GLuint);
		CASE(GL_UNSIGNED_INT_VEC2, 2, GLuint);
		CASE(GL_UNSIGNED_INT_VEC3, 3, GLuint);
		CASE(GL_UNSIGNED_INT_VEC4, 4, GLuint);
		CASE(GL_BOOL, 1, GLboolean);
		CASE(GL_BOOL_VEC2, 2, GLboolean);
		CASE(GL_BOOL_VEC3, 3, GLboolean);
		CASE(GL_BOOL_VEC4, 4, GLboolean);
		CASE(GL_FLOAT_MAT2, 4, GLfloat);

		CASE(GL_FLOAT_MAT2x3, 6, GLfloat);
		CASE(GL_FLOAT_MAT2x4, 8, GLfloat);
		CASE(GL_FLOAT_MAT3, 9, GLfloat);
		CASE(GL_FLOAT_MAT3x2, 6, GLfloat);
		CASE(GL_FLOAT_MAT3x4, 12, GLfloat);
		CASE(GL_FLOAT_MAT4, 16, GLfloat);
		CASE(GL_FLOAT_MAT4x2, 8, GLfloat);
		CASE(GL_FLOAT_MAT4x3, 12, GLfloat);
#undef CASE
	default:
		fprintf(stderr, "Unknown type: 0x%x\n", type);
		exit(EXIT_FAILURE);
		break;
	}
	return size;
}


//---------------------------------------------------------------------
//
// init
//
typedef void GLvoid;
void
init2()
{
	GLuint program;
	glClearColor(1, 0, 0, 1);
	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, vShader },
		{ GL_FRAGMENT_SHADER, fShader },
		{ GL_NONE, NULL }
	};
	program = LoadShaders(shaders);
	glUseProgram(program);
	/* Initialize uniform values in uniform block "Uniforms" */
	GLuint uboIndex;
	GLint uboSize;
	GLuint ubo;
	unsigned char *buffer;
	/* Find the uniform buffer index for "Uniforms", and
	** determine the block’s sizes */
	uboIndex = glGetUniformBlockIndex(program, "Uniforms");
	glGetActiveUniformBlockiv(program, uboIndex,
		GL_UNIFORM_BLOCK_DATA_SIZE, &uboSize);

	buffer = (unsigned char*)malloc(uboSize);

	if (buffer == NULL) {
		fprintf(stderr, "Unable to allocate buffer\n");
		exit(EXIT_FAILURE);
	}
	else {
		enum { Translation, Scale, Rotation, Enabled, NumUniforms };
		/* Values to be stored in the buffer object */
		GLfloat scale = 0.5;
		GLfloat translation[] = { 0.1, 0.1, 0.0 };
		GLfloat rotation[] = { 90, 0.0, 0.0, 1.0 };
		GLboolean enabled = GL_TRUE;
		/* Since we know the names of the uniforms
		** in our block, make an array of those values */
		const char* names[NumUniforms] = {
			"translation",
			"scale",
			"rotation",
			"enabled"
		};
		/* Query the necessary attributes to determine
		** where in the buffer we should write
		** the values */
		GLuint indices[NumUniforms];
		GLint size[NumUniforms];
		GLint offset[NumUniforms];
		GLint type[NumUniforms];
		glGetUniformIndices(program, NumUniforms, names, indices);
		glGetActiveUniformsiv(program, NumUniforms, indices,
			GL_UNIFORM_OFFSET, offset);
		glGetActiveUniformsiv(program, NumUniforms, indices,
			GL_UNIFORM_SIZE, size);
		glGetActiveUniformsiv(program, NumUniforms, indices,
			GL_UNIFORM_TYPE, type);
		/* Copy the uniform values into the buffer */
		memcpy(buffer + offset[Scale], &scale,
			size[Scale] * TypeSize(type[Scale]));
		memcpy(buffer + offset[Translation], &translation,
			size[Translation] * TypeSize(type[Translation]));
		memcpy(buffer + offset[Rotation], &rotation,
			size[Rotation] * TypeSize(type[Rotation]));
		memcpy(buffer + offset[Enabled], &enabled,
			size[Enabled] * TypeSize(type[Enabled]));
		/* Create the uniform buffer object, initialize
		** its storage, and associated it with the shader
		** program */
		glGenBuffers(1, &ubo);
		glBindBuffer(GL_UNIFORM_BUFFER, ubo);
		glBufferData(GL_UNIFORM_BUFFER, uboSize,
			buffer, GL_STATIC_DRAW);
		glBindBufferBase(GL_UNIFORM_BUFFER, uboIndex, ubo);
	}
	
}

GLfloat vertices[NumVertices][2] = { //6个顶点每个顶点2个数据
	{ -0.90, -0.90 }, // Triangle 1
	{ 0.85, -0.90 },
	{ -0.90, 0.85 },
	{ 0.90, -0.85 }, // Triangle 2
	{ 0.90, 0.90 },
	{ -0.85, 0.90 }
};


void
init(void)
{
	
	glGenVertexArrays(1, VAOs); //NumVAOs == 1 
	glBindVertexArray(VAOs[0]);  //Triangles == 0
	GLfloat vertices[NumVertices][3] = { //6个顶点每个顶点2个数据
		{ -0.90, -0.90, 0 }, // Triangle 1
		{ 0.85, -0.90 ,0.5},
		{ -0.90, 0.85 ,0.3},
	
	};
	glGenBuffers(1, Buffers); //NumBuffers == 1
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]); //ArrayBuffer == 0
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
		vertices, GL_STATIC_DRAW);
	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "vertex_shader.vs" },
		{ GL_FRAGMENT_SHADER, "pixel_shader.ps" },
		{ GL_NONE, NULL }
	};
	GLuint program = LoadShaders(shaders);
	glUseProgram(program);
	glVertexAttribPointer(vPosition, 3, GL_FLOAT,  //for shader  2代表一个顶点有几个数组成 1，2，3，4或者 GL_RGB
		GL_FALSE,  0, BUFFER_OFFSET(0));  //BUFFER_OFFSET(0) 是在buffer shader中的偏移
	glEnableVertexAttribArray(vPosition);
	
	
}



static const GLushort vertex_indices[] =
{
	0, 1
};
GLuint vertexArrayObject;
void init3()
{

	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);


	glGenBuffers(1, Buffers);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices,GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "vertex_shader.vs" },
		{ GL_FRAGMENT_SHADER, "pixel_shader.ps" },
		{ GL_NONE, NULL }
	};
	GLuint program = LoadShaders(shaders);
	glUseProgram(program);

}


//---------------------------------------------------------------------
//
// display
//
void
display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(VAOs[Triangles]);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glFlush();
}



void test(VOID)
{
	printf( "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	if (GLEW_ARB_vertex_program)
	{
		/* It is safe to use the ARB_vertex_program extension here. */
		printf("It is safe to use the ARB_vertex_program extension here");
	}

	if (GLEW_VERSION_1_3)
	{
		/* Yay! OpenGL 1.3 is supported! */
		printf("open gl 1.3 supproted!");

	}

	if (glewIsSupported("GL_VERSION_1_4  GL_ARB_point_sprite"))
	{
		/* Great, we have OpenGL 1.4 + point sprites. */
		printf("Great, we have OpenGL 1.4 + point sprites.");
	}

	if (glewGetExtension("GL_ARB_fragment_program"))
	{
		/* Looks like ARB_fragment_program is supported. */
		printf(" Looks like ARB_fragment_program is supported.");
	}
}


int _tmain(int argc, TCHAR* argv[])
{
	
	
	glutInit(&argc, argv);
	

	glutInitWindowSize(640, 480);

	glutInitDisplayMode(  GLUT_RGBA  );

	glutCreateWindow("3D Effects Demo");



	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		printf("Error: %s\n", glewGetErrorString(err));
		return 1;
	}

	
	init();
	glutDisplayFunc(display);
	

	glutMainLoop();
	return 0;
}