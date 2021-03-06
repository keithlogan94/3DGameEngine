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
	//Create Shader Program
	GLuint shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

#ifdef _DEBUG
	//Check Link Status
	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		const char *err { "error linking shader program " };
		std::cerr << err << infoLog << std::endl;
		throw std::exception{ err };
	}
	else {
		std::cout << "shader program created successfully" << std::endl;
	}
#endif //_DEBUG
	
	//Clean Up Individual Shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

//Uniform variables must be named 'model' 'view' 'projection'
void sendModelViewProjToShader(GLuint shaderProgram, glm::mat4 & model, glm::mat4 & view, glm::mat4 & proj)
{
	GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
	GLuint viewLoc = glGetUniformLocation(shaderProgram, "view");
	GLuint projectionLoc = glGetUniformLocation(shaderProgram, "projection");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &proj[0][0]);
}
