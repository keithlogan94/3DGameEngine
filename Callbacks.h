#pragma once
#include <GLFW\glfw3.h>
#include <glm.hpp>


void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
void cursor_callback(GLFWwindow* window, double xpos, double ypos);