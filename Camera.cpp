#include "Camera.h"



Camera::Camera(glm::vec3 cameraPos)
{
	this->cameraPos = cameraPos;
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

Camera::~Camera()
{
}

void Camera::updateMovement()
{
	//This External Global Variable Gets Updated On Key Events
	extern bool keys[1024];
	//Update Vectors With Key Controls
	GLfloat cameraSpeed = 0.01f;
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
