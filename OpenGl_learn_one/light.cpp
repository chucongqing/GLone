#include "light.h"
#include "customshader.h"
#include "Camera.h"

LearnLight::LearnLight()
{
	lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
	deltatime = 0;
}

LearnLight::~LearnLight()
{

}

void LearnLight::init()
{
	
	// Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat vertices[] = {
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,

		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,

		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,

		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f
	};


	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	//glDepthFunc(GL_LESS);
	//glEnable(GL_CULL_FACE);

	
	m_lightShader.loadShader("./shader/colors.vs", "./shader/colors.frag");
	m_lampShader.loadShader("./shader/lamp.vs", "./shader/lamp.frag");
	

	// First, set the container's VAO (and VBO)
	//GLuint VBO, containerVAO;
	glGenVertexArrays(1, &containerVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(containerVAO);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);


	glBindVertexArray(0);



	// Then, we set the light's VAO (VBO stays the same. After all, the vertices are the same for the light object (also a 3D cube))
	//GLuint lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	// We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Set the vertex attributes (only position data for the lamp))
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);



}

void LearnLight::selfDisplay()
{
	// Calculate deltatime of current frame
	
	static DWORD lasttime =  GetTickCount();
	deltatime += GetTickCount() - lasttime;
	lasttime = GetTickCount();
	static float ppp = 0;
	if (deltatime > 100)
	{
		deltatime -= 100;
		ppp = ppp + 0.03f;
	}


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
	
	GLint lightPosLoc = glGetUniformLocation(m_lightShader.getProgram(), "light.position");
	glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);

	GLint viewPosLoc = glGetUniformLocation(m_lightShader.getProgram(), "viewPos");
	glUniform3f(viewPosLoc, mc->getPosition().x, mc->getPosition().y, mc->getPosition().z);

	glm::vec3 lightColor;
	lightColor.x = sin(ppp  * 2.0f);
	lightColor.y = sin(ppp  * 0.7f);
	lightColor.z = sin(ppp  * 1.3f);

	glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f); // Decrease the influence
	glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // Low influence

	glUniform3f(glGetUniformLocation(m_lightShader.getProgram(), "light.ambient"), ambientColor.x, ambientColor.y, ambientColor.z);
	glUniform3f(glGetUniformLocation(m_lightShader.getProgram(), "light.diffuse"), diffuseColor.x, diffuseColor.y, diffuseColor.z);
	glUniform3f(glGetUniformLocation(m_lightShader.getProgram(), "light.specular"), 1.0f, 1.0f, 1.0f);
	// Set material properties
	glUniform3f(glGetUniformLocation(m_lightShader.getProgram(), "material.ambient"), 1.0f, 0.5f, 0.31f);
	glUniform3f(glGetUniformLocation(m_lightShader.getProgram(), "material.diffuse"), 1.0f, 0.5f, 0.31f);
	glUniform3f(glGetUniformLocation(m_lightShader.getProgram(), "material.specular"), 0.5f, 0.5f, 0.5f); // Specular doesn't have full effect on this object's material
	glUniform1f(glGetUniformLocation(m_lightShader.getProgram(), "material.shininess"), 32.0f);

	// Create camera transformations

	// Get the uniform locations
	GLint modelLoc = glGetUniformLocation(m_lightShader.getProgram(), "model");
	GLint viewLoc = glGetUniformLocation(m_lightShader.getProgram(), "view");
	GLint projLoc = glGetUniformLocation(m_lightShader.getProgram(), "projection");
	// Pass the matrices to the shader
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(ViewMatrix));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));


	// Draw the container (using container's vertex attributes)
	glBindVertexArray(containerVAO);
	glm::mat4 model;
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);


	// Also draw the lamp object, again binding the appropriate shader
	m_lampShader.Use();
// 	objectColorLoc = glGetUniformLocation(m_lampShader.getProgram(), "objectColor");
 //	lightColorLoc = glGetUniformLocation(m_lampShader.getProgram(), "lightColor");
// 	glUniform3f(objectColorLoc, 1.0f, 1.0f, 1.0f);
 //	glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);

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