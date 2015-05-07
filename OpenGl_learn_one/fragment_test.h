#ifndef _fragment_test_h_
#define _fragment_test_h_



#include "common.h"


namespace fragtest{

	enum VAO_IDs { Triangles, NumVAOs };
	enum Buffer_IDs { ArrayBuffer, NumBuffers };
	enum Attrib_IDs { vPosition = 0, vColor = 1 };
	GLuint VAOs[NumVAOs];
	GLuint Buffers[NumBuffers];
	const GLuint NumVertices = 6;

	GLuint windowmode = GLUT_STENCIL | GLUT_RGBA | GLUT_DEPTH;
	void reshape(int x, int y)
	{
		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		// create a diamond shaped stencil area
		glClear(GL_STENCIL_BUFFER_BIT);
		glStencilFunc(GL_ALWAYS, 0x1, 0x1);
		glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
		
	}
	void
		init(void)
	{
			glGenVertexArrays(NumVAOs, VAOs);
			glBindVertexArray(VAOs[Triangles]);
			struct VertexData {
				GLubyte color[4];
				GLfloat position[4];
			};
			VertexData vertices[NumVertices] = {
				{ { 255, 0, 0, 255 }, { -0.90, -0.90 } }, // Triangle 1
				{ { 0, 255, 0, 255 }, { 0.85, -0.90 } },
				{ { 0, 0, 255, 255 }, { -0.90, 0.85 } },
				{ { 10, 10, 10, 255 }, { 0.90, -0.85 } }, // Triangle 2
				{ { 100, 100, 100, 255 }, { 0.90, 0.90 } },
				{ { 255, 255, 255, 255 }, { -0.85, 0.90 } }
			};

			glGenBuffers(NumBuffers, Buffers);
			glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
				vertices, GL_STATIC_DRAW);
			ShaderInfo shaders[] = {
				{ GL_VERTEX_SHADER, ".\\shader\\gouraud.vert" },
				{ GL_FRAGMENT_SHADER, ".\\shader\\gouraud.frag" },
				{ GL_NONE, NULL }
			};
			GLuint program = LoadShaders(shaders);
			glUseProgram(program);
			glVertexAttribPointer(vColor, 4, GL_UNSIGNED_BYTE,
				GL_TRUE, sizeof(VertexData),//stride
				BUFFER_OFFSET(0));
			glVertexAttribPointer(vPosition, 2, GL_FLOAT,
				GL_FALSE, sizeof(VertexData),
				BUFFER_OFFSET(sizeof(vertices[0].color)));
			glEnableVertexAttribArray(vColor);
			glEnableVertexAttribArray(vPosition);

			glClearStencil(0x0);
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_STENCIL_TEST);
		}

	void display(void)
	{
			
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glBindVertexArray(VAOs[Triangles]);
			glDrawArrays(GL_TRIANGLES, 0, NumVertices);

			glFlush();
	}

	void keyboard(unsigned char key, int x, int y)
	{
			switch (key) {
			case 033:  // ASCII Escape Key Code
				exit(EXIT_SUCCESS);
				break;

			case 'm': {
						  static GLenum  mode = GL_FILL;

						  mode = (mode == GL_FILL ? GL_LINE : GL_FILL);
						  glPolygonMode(GL_FRONT_AND_BACK, mode);
			} break;
			}

			glutPostRedisplay();
	}

};
#endif