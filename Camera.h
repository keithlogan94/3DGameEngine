#pragma once
#include <GLFW\glfw3.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

#include <iostream>
#include <exception>
#include <stdexcept>

class Camera
{
	//View Matrix Used In Shaders
	glm::mat4 view;

	//Vectors Used to Construct View Matrix
	glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraFront;
	glm::vec3 cameraPos;
public:
	Camera(glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f));
	~Camera();

	inline glm::mat4 getView() const { return view; }
	inline glm::vec3 getPos() const { return cameraPos; }
	void updateMovement();
};

