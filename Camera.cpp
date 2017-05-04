#include "Camera.h"



Camera::Camera(glm::vec3 cameraPos)
{
	//This external variable get updated on mouse movements
	extern glm::vec3 cameraFront;
	this->cameraFront = cameraFront;
	this->cameraPos = cameraPos;
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

Camera::~Camera()
{
}

void Camera::updateMovement()
{
	//This external global variable gets updated on key events
	extern bool keys[1024];

	//This external global variable gets updated each frame
	//in the game loop
	extern GLfloat deltaTime;

	//This external variable get updated on mouse movements
	extern glm::vec3 cameraFront;

	//Update Camera Front
	this->cameraFront = cameraFront;

	//Update Vectors With Key Controls
	GLfloat cameraSpeed = 1.0f * deltaTime;
	if (keys[GLFW_KEY_LEFT_SHIFT] || keys[GLFW_KEY_RIGHT_SHIFT])
		cameraSpeed *= 2;
	if (keys[GLFW_KEY_W])
		cameraPos += cameraSpeed * cameraFront;
	if (keys[GLFW_KEY_S])
		cameraPos -= cameraSpeed * cameraFront;
	if (keys[GLFW_KEY_A])
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (keys[GLFW_KEY_D])
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	//Use Updated Vectors To Create A New Vew Matrix
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}
