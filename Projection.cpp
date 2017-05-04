#include "Projection.h"



Projection::Projection()
{
	projection = glm::perspective(45.0f, (GLfloat)800 / (GLfloat)600, 0.1f, 100.0f);
}


Projection::~Projection()
{
}
