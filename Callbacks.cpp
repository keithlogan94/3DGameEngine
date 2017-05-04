#include "Callbacks.h"


//This global variable gets used by the Camera class
bool keys[1024];

//This global variable gets used by the Camera class
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

//These global variables get used by various files
int width = 800, height = 600;


void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (action == GLFW_PRESS)
		keys[key] = true;
	else if (action == GLFW_RELEASE)
		keys[key] = false;
}

void cursor_callback(GLFWwindow* window, double xpos, double ypos)
{
	//These are defined static so they don't need to be global
	static bool firstMouse{ true };
	static GLfloat lastX = 400, lastY = 300;
	static GLfloat pitch = 0, yaw = 0;

	//This is to make sure the camera doesn't jump
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	GLfloat sensitivity = 0.05;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	::cameraFront = glm::normalize(front);
}

void window_resize_callback(GLFWwindow * window, int width, int height)
{
	::width = width;
	::height = height;
}
