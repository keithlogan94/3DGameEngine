//
// Title: 3D Game Engine
// Summary: A 3D Game engine developed to integrate Blender object files, lighting
// and animation.
// Software By Keith Becker Copyright 2017 (c)
//

#include <GL\glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <exception>

#include "Callbacks.h"

int main(int argc, char ** argv) {
	//Initialize GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	//Create Window
	GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if (!window) {
		const char *err = "The Window failed to create.";
		std::cerr << err;
		throw std::exception{ err };
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	
	//Initialize Glew
	if (glewInit() != GLEW_OK) {
		const char *err = "Failed to initialize glew";
		std::cerr << err;
		throw std::exception{ err };
		//delete window...

		glfwTerminate();
		return -1;
	}

	//Set the view port for rendering
	int width = 800, height = 600;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	//Set Callbacks
	glfwSetKeyCallback(window, key_callback);

	//Pre Game Loop Setup
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	//Tmp
	GLfloat	vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.0f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_STATIC_DRAW);


	//Game Loop
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	//Clean Up
	glfwTerminate();
	return 0;
}