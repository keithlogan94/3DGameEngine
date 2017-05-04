#pragma once
#include <GL\glew.h>
#include <iostream>
#include <exception>
#include <stdexcept>

#define glsl(version, glsl) "#version " #version "\n" #glsl

namespace glsl {  namespace vs {


		//VERTEX SHADERS
		//=========================
		// simple VS
		//=========================
		constexpr GLchar * const simple = glsl(330 core,
			layout(location = 0) in vec3 position;

		void main() {
			gl_Position = vec4(position, 1.0f);
		}
		);


	} namespace fs {


		//FRAGMENT SHADERS
		//=========================
		// simple FS
		//=========================
		constexpr GLchar * const simple = glsl(330 core,
			out vec4 color;

		void main() {
			color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
		}
		);


	} }

enum class e_shader_type { VERTEX_SHADER, FRAGMENT_SHADER };

GLuint compileShader(e_shader_type shaderType, const GLchar* const *shaderSource);
GLuint createShaderProgram(GLuint vertexShader, GLuint fragmentShader);



