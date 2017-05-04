#include "Shaders.h"

GLuint compileShader(e_shader_type shaderType, const GLchar* const *shaderSource) {
 //Create Shader Storage
 GLuint shader;
 if (shaderType == e_shader_type::VERTEX_SHADER)
	 shader = glCreateShader(GL_VERTEX_SHADER);
 else
	 shader = glCreateShader(GL_FRAGMENT_SHADER);

 //Attach Shader Source Code
 glShaderSource(shader, 1, shaderSource, 0);
 glCompileShader(shader);

 #ifdef _DEBUG
 //Check Compile Status
 GLint success;
 GLchar infoLog[512];
 glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
 if (!success) {
	 glGetShaderInfoLog(shader, 512, NULL, infoLog);
	 char *err = "";
	 if (shaderType == e_shader_type::VERTEX_SHADER)
		 err = { "error on compiling vertex shader " };
	 else
		 err = { "error on compiling fragment shader " };
	 std::cerr << err << infoLog << std::endl;
	 throw std::exception{ err };
 }
 else {
	 if (shaderType == e_shader_type::VERTEX_SHADER)
		 std::cout << "vertex shader compiled successfully" << std::endl;
	 else
		 std::cout << "fragment shader compiled successfully" << std::endl;
 }
 #endif //_DEBUG

 return shader;
}

GLuint createShaderProgram(GLuint vertexShader, GLuint fragmentShader)
{
	GLuint shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

#ifdef _DEBUG
	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(shaderprogram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderprogram, 512, NULL, infoLog);
		const char *err { "error linking shader program " };
		std::cerr << err << infoLog << std::endl;
		throw std::exception{ err };
	}
	else {
		std::cout << "shader program created successfully" << std::endl;
	}
#endif //_DEBUG

	return shaderProgram;
}
