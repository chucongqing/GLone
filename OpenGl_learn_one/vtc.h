#ifndef vtc_h_
#define  vtc_h_

#include "common.h"


#include "MyControls.h"


namespace ns_vtc
{
#define KEYBORD_ON
	static GLuint programID;
	static GLuint MatrixID;
	static glm::mat4 MVP;
	static GLuint TextureID;
	static GLuint TextureID2;
	static GLuint Texture;
	static GLuint Texture2;
	static GLuint vertexbuffer;
	static GLuint uvbuffer;
	void init()
	{
		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
		// Enable depth test
		glEnable(GL_DEPTH_TEST);
		// Accept fragment if it closer to the camera than the former one
		glDepthFunc(GL_LESS);
		glEnable(GL_CULL_FACE);

		GLuint VertexArrayID;
		glGenVertexArrays(1, &VertexArrayID);
		glBindVertexArray(VertexArrayID);

		static  ShaderInfo shader_info[] =
		{
			{ GL_VERTEX_SHADER, "./shader/TransformVertexShader.vertexshader" },
			{ GL_FRAGMENT_SHADER, "./shader/TextureFragmentShader.fragmentshader" },
			{ GL_NONE, nullptr }
		};

		 programID = LoadShaders(shader_info);

		// Get a handle for our "MVP" uniform
		 MatrixID = glGetUniformLocation(programID, "MVP");

		glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

		// Camera matrix
		glm::mat4 View = glm::lookAt(
			glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
			glm::vec3(0, 0, 0), // and looks at the origin
			glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
			);

		// Model matrix : an identity matrix (model will be at the origin)
		glm::mat4 Model = glm::mat4(1.0f);
		// Our ModelViewProjection : multiplication of our 3 matrices
		MVP =  Projection* View * Model ; // Remember, matrix multiplication is the other way around
		
		Texture = loadBMP_custom("uvtemplate.bmp");
		Texture2 = loadDDS("uvtemplate.DDS");

		// Get a handle for our "myTextureSampler" uniform
		TextureID = glGetUniformLocation(programID, "myTextureSampler");
		TextureID2 = glGetUniformLocation(programID, "myTextureSampler2");

		// Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
		// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
		static const GLfloat g_vertex_buffer_data[] = {
			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f, 1.0f,
			-1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f, 1.0f, -1.0f,
			1.0f, -1.0f, 1.0f,
			-1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f, 1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f, -1.0f,
			1.0f, -1.0f, 1.0f,
			-1.0f, -1.0f, 1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f, 1.0f, 1.0f,
			-1.0f, -1.0f, 1.0f,
			1.0f, -1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f, 1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, -1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, -1.0f,
			-1.0f, 1.0f, -1.0f,
			1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f, -1.0f,
			-1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f, 1.0f,
			1.0f, -1.0f, 1.0f
		};

		// Two UV coordinatesfor each vertex. They were created withe Blender.
		static const GLfloat g_uv_buffer_data[] = {
			0.000059f, 1.0f - 0.000004f,
			0.000103f, 1.0f - 0.336048f,
			0.335973f, 1.0f - 0.335903f,
			1.000023f, 1.0f - 0.000013f,
			0.667979f, 1.0f - 0.335851f,
			0.999958f, 1.0f - 0.336064f,
			0.667979f, 1.0f - 0.335851f,
			0.336024f, 1.0f - 0.671877f,
			0.667969f, 1.0f - 0.671889f,
			1.000023f, 1.0f - 0.000013f,
			0.668104f, 1.0f - 0.000013f,
			0.667979f, 1.0f - 0.335851f,
			0.000059f, 1.0f - 0.000004f,
			0.335973f, 1.0f - 0.335903f,
			0.336098f, 1.0f - 0.000071f,
			0.667979f, 1.0f - 0.335851f,
			0.335973f, 1.0f - 0.335903f,
			0.336024f, 1.0f - 0.671877f,
			1.000004f, 1.0f - 0.671847f,
			0.999958f, 1.0f - 0.336064f,
			0.667979f, 1.0f - 0.335851f,
			0.668104f, 1.0f - 0.000013f,
			0.335973f, 1.0f - 0.335903f,
			0.667979f, 1.0f - 0.335851f,
			0.335973f, 1.0f - 0.335903f,
			0.668104f, 1.0f - 0.000013f,
			0.336098f, 1.0f - 0.000071f,
			0.000103f, 1.0f - 0.336048f,
			0.000004f, 1.0f - 0.671870f,
			0.336024f, 1.0f - 0.671877f,
			0.000103f, 1.0f - 0.336048f,
			0.336024f, 1.0f - 0.671877f,
			0.335973f, 1.0f - 0.335903f,
			0.667969f, 1.0f - 0.671889f,
			1.000004f, 1.0f - 0.671847f,
			0.667979f, 1.0f - 0.335851f
		};

		//vertexbuffer;
		glGenBuffers(1, &vertexbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	   // uvbuffer;
		glGenBuffers(1, &uvbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);
		
	}

	void display()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	 	MyControls::getInstance()->computeMatricesFromInputs();
		glm::mat4 ProjectionMatrix = MyControls::getInstance()->getProjectionMatrix();
		glm::mat4 ViewMatrix = MyControls::getInstance()->getViewMatrix();
 		glm::mat4 ModelMatrix = glm::mat4(1.0);
 		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;


		// Use our shader
		glUseProgram(programID);
		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		// Set our "myTextureSampler" sampler to user Texture Unit 0
		glUniform1i(TextureID, 0);

		glBindTexture(GL_TEXTURE_2D, 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, Texture2);
		// Set our "myTextureSampler2" sampler to user Texture Unit 1
		glUniform1i(TextureID2, 1);
		
		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
			);

		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			2,                                // size : U+V => 2
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
			);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // 12*3 indices starting at 0 -> 12 triangles

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);


		glutSwapBuffers();
		glutPostRedisplay();
	}

	void keyboard(unsigned char key, int x, int y)
	{
		switch (key) {
		case 033:  // ASCII Escape Key Code
			exit(EXIT_SUCCESS);
			break;
		case KEY(w):{
						printf("key w !");
						MyControls::getInstance()->w = 1;
		}break;
		case KEY(a):{
						MyControls::getInstance()->a = 1;
		}break;
		case KEY(s):{
						MyControls::getInstance()->s = 1;
		}break;
		case KEY(d):{
						MyControls::getInstance()->d = 1;
		}break;

		case KEY(m): {
						 MyControls::getInstance()->w = 0;
						 MyControls::getInstance()->a = 0;
						 MyControls::getInstance()->s = 0;
						 MyControls::getInstance()->d = 0;
		} break;
		default:{
					printf("............");
		}
		}

		glutPostRedisplay();
	}

	void keyboardup(unsigned char key, int x, int y)
	{
		switch (key) {
		case 033:  // ASCII Escape Key Code
			exit(EXIT_SUCCESS);
			break;
		case KEY(w):{
						printf("key w up!");
						MyControls::getInstance()->w = 0;
		}break;
		case KEY(a):{
						MyControls::getInstance()->a = 0;
		}break;
		case KEY(s):{
						MyControls::getInstance()->s = 0;
		}break;
		case KEY(d):{
						MyControls::getInstance()->d = 0;
		}break;

		case KEY(m): {
						 MyControls::getInstance()->w = 0;
						 MyControls::getInstance()->a = 0;
						 MyControls::getInstance()->s = 0;
						 MyControls::getInstance()->d = 0;
		} break;
		default:{
					printf("............");
		}
		}

		glutPostRedisplay();
	}

};
#endif