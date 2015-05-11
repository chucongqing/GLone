#include "LightMap.h"
#include "SOIL.h"

LightMap::LightMap()
{
	lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
}


LightMap::~LightMap()
{
}


glm::vec3 cubePositions[] = {
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3(2.0f, 5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f, 3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f, 2.0f, -2.5f),
	glm::vec3(1.5f, 0.2f, -1.5f),
	glm::vec3(-1.3f, 1.0f, -1.5f)
};

void LightMap::init()
{

	// Set up vertex data (and buffer(s)) and attribute pointers
	// Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat vertices[] = {
		// Positions          // Normals           // Texture Coords
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
	};

	// Positions all containers

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	//glDepthFunc(GL_LESS);
	//glEnable(GL_CULL_FACE);


	m_lightShader.loadShader("./shader/lightmap.vs", "./shader/lightmap.frag");
	m_lampShader.loadShader("./shader/lamp.vs", "./shader/lamp.frag");


	// First, set the container's VAO (and VBO)
	//GLuint VBO, containerVAO;
	glGenVertexArrays(1, &containerVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(containerVAO);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);



	// Then, we set the light's VAO (VBO stays the same. After all, the vertices are the same for the light object (also a 3D cube))
	//GLuint lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	// We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Set the vertex attributes (only position data for the lamp))
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);



	// Load textures
	
	glGenTextures(1, &diffuseMap);
	int width, height;
	unsigned char* image;
	// Diffuse map
	image = SOIL_load_image(".\\res\\textures\\container2.png", &width, &height, 0, SOIL_LOAD_RGB);
	glBindTexture(GL_TEXTURE_2D, diffuseMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);



	glGenTextures(1, &specularMap);
	// Diffuse map
	image = SOIL_load_image(".\\res\\textures\\container2_specular.png", &width, &height, 0, SOIL_LOAD_RGB);
	glBindTexture(GL_TEXTURE_2D, specularMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);


	// Set texture units
	m_lightShader.Use();
	glUniform1i(glGetUniformLocation(m_lightShader.getProgram(), "material.diffuse"), 0);
	glUniform1i(glGetUniformLocation(m_lightShader.getProgram(), "material.specular"), 1);
}

void LightMap::selfDisplay()
{
	// Calculate deltatime of current frame

// 	static DWORD lasttime = GetTickCount();
// 	deltatime += GetTickCount() - lasttime;
// 	lasttime = GetTickCount();
// 	static float ppp = 0;
// 	if (deltatime > 100)
// 	{
// 		deltatime -= 100;
// 		ppp = ppp + 0.03f;
// 	}


	MyControls::getInstance()->computeMatricesFromInputs();
	glm::mat4 ProjectionMatrix = MyControls::getInstance()->getProjectionMatrix();
	glm::mat4 ViewMatrix = MyControls::getInstance()->getViewMatrix();
	//glm::mat4 ModelMatrix = glm::mat4(1.0);
	//glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

	MyControls* mc = MyControls::getInstance();
	// Clear the colorbuffer
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	m_lightShader.Use();

	GLint lightDirPos = glGetUniformLocation(m_lightShader.getProgram(), "light.direction");
	glUniform3f(lightDirPos, mc->getFront().x, mc->getFront().y, mc->getFront().z);
	GLint lightPosLoc = glGetUniformLocation(m_lightShader.getProgram(), "light.position");
	glUniform3f(lightPosLoc, mc->getPosition().x, mc->getPosition().y, mc->getPosition().z);


	glUniform1f(glGetUniformLocation(m_lightShader.getProgram(), "light.cutOff"), glm::cos(glm::radians(12.5f)));
	glUniform1f(glGetUniformLocation(m_lightShader.getProgram(), "light.outerCutOff"), glm::cos(glm::radians(17.5f)));
	glUniform3f(glGetUniformLocation(m_lightShader.getProgram(), "light.ambient"), 0.2, 0.2, 0.2);
	glUniform3f(glGetUniformLocation(m_lightShader.getProgram(), "light.diffuse"), 0.5f, 0.5f, 0.5f);
	glUniform3f(glGetUniformLocation(m_lightShader.getProgram(), "light.specular"), 1.0f, 1.0f, 1.0f);

	glUniform1f(glGetUniformLocation(m_lightShader.getProgram(), "light.constant"), 1.0f);
	glUniform1f(glGetUniformLocation(m_lightShader.getProgram(), "light.linear"), 0.09);
	glUniform1f(glGetUniformLocation(m_lightShader.getProgram(), "light.quadratic"), 0.032);

	// Set material properties
	glUniform3f(glGetUniformLocation(m_lightShader.getProgram(), "material.specular"), 0.5f, 0.5f, 0.5f); // Specular doesn't have full effect on this object's material
	glUniform1f(glGetUniformLocation(m_lightShader.getProgram(), "material.shininess"), 64.0f);

	GLint viewPosLoc = glGetUniformLocation(m_lightShader.getProgram(), "viewPos");
	glUniform3f(viewPosLoc, mc->getPosition().x, mc->getPosition().y, mc->getPosition().z);

	// Create camera transformations

	// Get the uniform locations
	GLint modelLoc = glGetUniformLocation(m_lightShader.getProgram(), "model");
	GLint viewLoc = glGetUniformLocation(m_lightShader.getProgram(), "view");
	GLint projLoc = glGetUniformLocation(m_lightShader.getProgram(), "projection");
	// Pass the matrices to the shader
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(ViewMatrix));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));


	// Bind diffuse map
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseMap);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, specularMap);


	glBindVertexArray(containerVAO);
	glm::mat4 model;
	for (GLuint i = 0; i < 10; i++)
	{
		model = glm::mat4();
		model = glm::translate(model, cubePositions[i]);
		GLfloat angle = 20.0f * i;
		model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	glBindVertexArray(0);


	// Also draw the lamp object, again binding the appropriate shader
	m_lampShader.Use();
	// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
	modelLoc = glGetUniformLocation(m_lampShader.getProgram(), "model");
	viewLoc = glGetUniformLocation(m_lampShader.getProgram(), "view");
	projLoc = glGetUniformLocation(m_lampShader.getProgram(), "projection");
	// Set matrices
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(ViewMatrix));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));
	model = glm::mat4();
	model = glm::translate(model, lightPos);
	model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	// Draw the light object (using light's vertex attributes)
	glBindVertexArray(lightVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	glutSwapBuffers();
	glutPostRedisplay();
}