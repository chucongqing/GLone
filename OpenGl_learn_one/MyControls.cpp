#include "MyControls.h"


MyControls* MyControls::m_pInstance = nullptr;

MyControls::MyControls()
{
	screen_height = 768;
	screen_width = 1024;
	w = 0;
	s = 0;
	a = 0;
	d = 0;
	pos_x = 0;
	pos_y = 0;

	 position = glm::vec3(0, 0, 5);
	// Initial horizontal angle : toward -Z
	 horizontalAngle = 3.14f;
	// Initial vertical angle : none
	 verticalAngle = 0.0f;
	// Initial Field of View
	 initialFoV = 45.0f;
	 deltax = 0;
	 deltay = 0;

	 speed = 0.003f; // 3 units / second
	 mouseSpeed = 0.005f;

}


MyControls::~MyControls()
{
}

MyControls* MyControls::getInstance()
{
	if (!m_pInstance)
	{
		m_pInstance = new MyControls();
	}
	return m_pInstance;
}

void MyControls::mouse_routine(int x, int y)
{
	MyControls* mc = MyControls::getInstance();
	
	
	mc->deltax =  mc->pos_x;
	mc->deltay =  mc->pos_y;
	if (abs(x -mc->pos_x) > 10 || abs(y - mc->pos_y)> 10){
		mc->deltax = x;
		mc->deltay = y;
	}

	mc->pos_x = x;
	mc->pos_y = y;

	//printf("delta x = %f \n", mc->deltax);
	
	 
}
void MyControls::computeMatricesFromInputs(){

	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = GetCurrentTime();

	// Compute time difference between current and last frame
	double currentTime = GetTickCount();
	float deltaTime = float(currentTime - lastTime);
	//printf("deleatime = %f \n", deltaTime);

	// Get mouse position
	//double xpos, ypos;
	
	//glutWarpPointer(screen_width / 2, screen_height / 2);
		// Reset mouse position for next frame
	//glfwSetCursorPos(window, 1024 / 2, 768 / 2);
	MyControls* mc = MyControls::getInstance();
	

	// Compute new orientation
	horizontalAngle += mouseSpeed *float(deltax  - pos_x);
	verticalAngle += mouseSpeed *  float(deltay  - pos_y);
	//printf("horizon  angle = %f\n", horizontalAngle);
	deltax = pos_x;
	deltay = pos_y;

	// Direction : Spherical coordinates to Cartesian coordinates conversion
 	glm::vec3 direction(
 		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
 		cos(verticalAngle) * cos(horizontalAngle)
 		);  // got it!
	this->m_direction = direction;
// 	glm::vec3 direction(
// 		sin(verticalAngle) * cos(horizontalAngle),
// 		cos(verticalAngle),
// 		sin(verticalAngle) * sin(horizontalAngle)
// 		);



	// Right vector
 	glm::vec3 right = glm::vec3(
 		sin(horizontalAngle - 3.14f / 2.0f),
 		0,
		cos(horizontalAngle - 3.14f / 2.0f)
 		);

//	glm::vec3 up1 = glm::vec3(0.0f, 1.0f, 0.0f);
//	glm::vec3 right = glm::normalize(glm::cross(up1, direction));

	// Up vector
	glm::vec3 up = glm::cross(right, direction);

	// Move forward
	if (w){
		position += direction * deltaTime * speed;
	}
	// Move backward
	if (s){
		position -= direction * deltaTime * speed;
	}
	// Strafe right
	if (d){
		position += right * deltaTime * speed;
	}
	// Strafe left
	if (a){
		position -= right * deltaTime * speed;
	}

	float FoV = initialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

	// Projection matrix : 45?Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	ViewMatrix = glm::lookAt(
		position,           // Camera is here
		position + direction, // and looks here : at the same position, plus "direction"
		up                  // Head is up (set to 0,-1,0 to look upside-down)
		);

	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;
}


void MyControls::keyboard(unsigned char key, int x, int y)
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


void MyControls::keyboardup(unsigned char key, int x, int y)
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