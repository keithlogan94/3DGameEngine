#pragma once
#include <GLFW\glfw3.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

class Projection
{
	glm::mat4 projection;
public:
	Projection();
	~Projection();

	inline  glm::mat4 getProjection() const { return projection; }
};

