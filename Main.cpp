//
// Title: 3D Game Engine
// Summary: A 3D Game engine developed to integrate Blender object files, lighting
// and animation.
// Software By Keith Becker Copyright 2017 (c)
//

#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif //!_DEBUG

#include <GL\glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <exception>

#include "Callbacks.h"
#include "Shaders.h"
#include "Textures.h"

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
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};
	GLfloat elementVertices[] = {
		 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // Top Right
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Bottom Right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // Bottom Left
		-0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f  // Top Left 
	};
	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 3,   // First Triangle
		1, 2, 3    // Second Triangle
	};
	GLfloat texCoords[] = {
		0.0f, 0.0f,  // Lower-left corner  
		1.0f, 0.0f,  // Lower-right corner
		0.5f, 1.0f   // Top-center corner
	};

	//Encapsulate Buffer Object Data In Vertex Array Object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//Generate & Store Indices In Element Buffer Object
	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof indices, indices, GL_STATIC_DRAW);

	//Generate & Store Vertices in Vertex Buffer Object
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof elementVertices, elementVertices, GL_STATIC_DRAW);

	//Enable Shader Communication Of Data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof GLfloat));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof GLfloat));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);


	//Unbind Vertex Array Object
	glBindVertexArray(0);
	
	//Create Shader Program
	GLuint simpleShader = createShaderProgram(
		compileShader(e_shader_type::VERTEX_SHADER, &glsl::vs::texture),/* vertex shader source in Shaders.h */
		compileShader(e_shader_type::FRAGMENT_SHADER, &glsl::fs::texture)/* fragment shader source in Shader.h */
	);

	GLuint texture = raw_texture_load("wooden-container.data", 512, 512);
	
	//Game Loop
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();

		//Use Shader
		glUseProgram(simpleShader);

		//Bind VAO Object & Draw
		glBindVertexArray(vao);
		glBindTexture(GL_TEXTURE_2D, texture);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	//Clean Up
	glfwTerminate();
	return 0;
}