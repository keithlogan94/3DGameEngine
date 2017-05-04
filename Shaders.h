#pragma once
#include <GL\glew.h>

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
			color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
		}
		);


	} }