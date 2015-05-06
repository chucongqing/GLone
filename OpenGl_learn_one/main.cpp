#include <iostream>
#include <tchar.h>
#include <windows.h>


#include <GLTools.h>

#define FREEGLUT_STATIC
#include <gl/glut.h>

#include "ShaderManager.h"
#include "LoadShaders.h"
#include "customshader.h"
#include "vmath.h"
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
GLuint render_prog;

GLint render_model_matrix_loc;
GLint render_projection_matrix_loc;
float aspect;
void init4()
{

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	aspect = float(WINDOW_HEIGHT) / float(WINDOW_WIDTH);


	static  ShaderInfo shader_info[] =
	{
		{ GL_VERTEX_SHADER, "./shader/primitive_restart.vs.glsl" },
		{ GL_FRAGMENT_SHADER, "./shader/primitive_restart.fs.glsl" },
		{ GL_NONE, NULL }
	};

	render_prog = LoadShaders(shader_info);

	glUseProgram(render_prog);

	// "model_matrix" is actually an array of 4 matrices
	render_model_matrix_loc = glGetUniformLocation(render_prog, "model_matrix");
	render_projection_matrix_loc = glGetUniformLocation(render_prog, "projection_matrix");

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

	glBufferSubData(GL_ARRAY_BUFFER, 0,
		sizeof(vertex_positions), vertex_positions);
	glBufferSubData(GL_ARRAY_BUFFER,
		sizeof(vertex_positions), sizeof(vertex_colors),
		vertex_colors);


	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0); // layout == 0
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid *)sizeof(vertex_positions));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void display4()
{
	float t = float(GetTickCount() & 0x1FFF) / float(0x1FFF);
	static float q = 0.0f;
	static const vmath::vec3 X(1.0f, 0.0f, 0.0f);
	static const vmath::vec3 Y(0.0f, 1.0f, 0.0f);
	static const vmath::vec3 Z(0.0f, 0.0f, 1.0f);
	
	vmath::mat4 model_matrix;

	// Setup
	//glEnable(GL_CULL_FACE);
	//glDisable(GL_DEPTH_TEST);

	glClear(GL_COLOR_BUFFER_BIT );

	// Activate simple shading program
	glUseProgram(render_prog);

	// Set up the model and projection matrix
	vmath::mat4 projection_matrix(vmath::frustum(-1.0f, 1.0f, -aspect, aspect, 1.0f, 500.0f));
	glUniformMatrix4fv(render_projection_matrix_loc, 1, GL_FALSE, projection_matrix);

	// Set up for a glDrawElements call
	glBindVertexArray(vao[0]);  //激活
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]); //激活


	// Draw Arrays...
	model_matrix = vmath::translate(-3.0f, 0.0f, -5.0f);
	glUniformMatrix4fv(render_model_matrix_loc, 4, GL_FALSE, model_matrix);
	glDrawArrays(GL_TRIANGLES, 0, 3); //绘制一系列的集合图元，采用数组元素，第二个参数为开始绘制的顶点，第三个为
	//绘制顶点的数量


	// DrawElements
	model_matrix = vmath::translate(-1.0f, 0.0f, -5.0f);
	glUniformMatrix4fv(render_model_matrix_loc, 4, GL_FALSE, model_matrix);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);
	//用第二个参数的数量的元素,来绘制一系列的几何图元  最后一个参数为offset以字节来度量



	// DrawElementsBaseVertex
	model_matrix = vmath::translate(1.0f, 0.0f, -5.0f);
	glUniformMatrix4fv(render_model_matrix_loc, 4, GL_FALSE, model_matrix);
	glDrawElementsBaseVertex(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, NULL, 1); //最后一个参数为基地址

	// DrawArraysInstanced
	model_matrix = vmath::translate(3.0f, 0.0f, -5.0f);
	glUniformMatrix4fv(render_model_matrix_loc, 4, GL_FALSE, model_matrix);
	glDrawArraysInstanced(GL_TRIANGLES, 0, 3, 1);

	
	glutSwapBuffers();
	glutPostRedisplay();
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
	

	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	glutInitDisplayMode(  GLUT_RGBA  );

	glutCreateWindow("3D Effects Demo");



	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		printf("Error: %s\n", glewGetErrorString(err));
		return 1;
	}

	
	init4();
	glutDisplayFunc(display4);
	

	glutMainLoop();


	glUseProgram(0);
	glDeleteProgram(render_prog);
	glDeleteVertexArrays(1, vao);
	glDeleteBuffers(1, vbo);
	return 0;
}