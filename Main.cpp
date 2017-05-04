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
#include "Shaders.h"

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

	//Encapsulate Buffer Object Data In Vertex Array Object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//Define How To Handle Buffer Data To Shader
	glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);


	//Unbind Vertex Array Object
	glBindVertexArray(0);
	
	//Create Shader Program
	GLuint simpleShader = createShaderProgram(
		compileShader(e_shader_type::VERTEX_SHADER, &glsl::vs::simple),/* vertex shader source in Shaders.h */
		compileShader(e_shader_type::FRAGMENT_SHADER, &glsl::fs::simple)/* fragment shader source in Shader.h */
	);




	//Game Loop
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();


		//Use Shader
		glUseProgram(simpleShader);

		//Bind VAO Object & Draw
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	//Clean Up
	glfwTerminate();
	return 0;
}