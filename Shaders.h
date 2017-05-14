#pragma once
#include <GL\glew.h>
#include <glm.hpp>

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

		//==========================
		// changeing color VS
		//==========================
		constexpr GLchar * const changeColors = glsl(330 core,
			layout(location = 0) in vec3 position;
			out vec4 vertexColor;

			uniform vec4 ourColor;
		void main() {
			gl_Position = vec4(position, 1.0f);
			vertexColor = ourColor;
			}
			);

		//==========================
		// multiple attib pointer
		//==========================
		constexpr GLchar * const multipleAttribPointer = glsl(330 core,
			layout(location = 0) in vec3 position;
			layout(location = 1) in vec3 posColor;
			out vec4 outColor;

			void main() {
				gl_Position = vec4(position, 1.0f);
				outColor = vec4(posColor, 1.0f);
			}
			);

		//==========================
		// Texture
		//==========================
		constexpr GLchar * const texture = glsl(330 core,
			layout(location = 0) in vec3 position;
			layout(location = 1) in vec2 texCoord;

			out vec3 ourColor;
			out vec2 outTexCoord;

			uniform mat4 model;
			uniform mat4 view;
			uniform mat4 projection;

			void main() {
				gl_Position = projection * view * model * vec4(position, 1.0f);
				outTexCoord = vec2(texCoord.x, 1.0f - texCoord.y);
			}
			);

		//==========================
		// Simple Object
		//==========================
		constexpr GLchar * const simpleObject = glsl(330 core,
			layout(location = 0) in vec3 position;
			layout(location = 1) in vec3 normal;

			uniform mat4 model;
			uniform mat4 view;
			uniform mat4 projection;

			out vec3 Normal;
			out vec3 FragPos;

			void main() {
				gl_Position = projection * view * model * vec4(position, 1.0f);
				Normal = normal;
				FragPos = vec3(model * vec4(position, 1.0f));
			}
			);

		//==========================
		// Simple Light
		//==========================
		constexpr GLchar * const simpleLight = glsl(330 core,
			layout(location = 0) in vec3 position;
			
			uniform mat4 model;
			uniform mat4 view;
			uniform mat4 projection;

			void main() {
				gl_Position = projection * view * model * vec4(position, 1.0f);
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

		//==========================
		// changeing color FS
		//==========================
		constexpr GLchar * const changeColors = glsl(330 core,
				in vec4 vertexColor;
				out vec4 color;

				void main() {
					color = vertexColor;
				}
			);

		//==========================
		// multiple attib pointer
		//==========================
		constexpr GLchar * const multipleAttribPointer = glsl(330 core,
				in vec4 outColor;
				out vec4 color;

				void main() {
					color = outColor;
				}
			);

		//==========================
		// Texture FS
		//==========================
		constexpr GLchar * const texture = glsl(330 core,
			in vec2 outTexCoord;

			out vec4 color;

			uniform sampler2D ourTexture1;
			uniform sampler2D ourTexture2;

			void main() {
				color = mix(texture(ourTexture1, outTexCoord), texture(ourTexture2, outTexCoord), 0.5f);
			}
			);

		//==========================
		// simple Object FS
		//==========================
		constexpr GLchar * const simpleObject = glsl(330 core,
			out vec4 color;
	
			uniform vec3 objectColor;
			uniform vec3 lightColor;
			uniform vec3 lightPos;
			uniform vec3 viewPos;

			in vec3 Normal;
			in vec3 FragPos;

			void main() {
				vec3 norm = normalize(Normal);
				//diffuse lighting calculations
				vec3 lightDir = normalize(lightPos - FragPos);
				float diff = max(dot(norm, lightDir), 0.0f);
				vec3 diffuse = diff * lightColor;
				//ambient lighting calculations
				float ambientStrength = 0.1f;
				vec3 ambient = ambientStrength * lightColor;
				//specular lighting calculations
				float specularStrength = 1.0f;
				vec3 viewDir = normalize(viewPos - FragPos);
				vec3 reflectDir = reflect(-lightDir, norm);
				float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
				vec3 specular = specularStrength * spec * lightColor;
				//calculate distance from light
				float r = 0.5f;
				vec3 L = lightPos - FragPos;
				float distance = length(L);
				float d = max(distance - r, 0);
				L /= distance;
				// calculate basic attenuation
				float denom = d / r + 1;
				float attenuation = 1 / (denom*denom);
				// scale and bias attenuation such that:
				//   attenuation == 0 at extent of max influence
				//   attenuation == 1 when d == 0
				attenuation = (attenuation - 0.005f/*cutoff*/) / (1 - 0.005f/*cutoff*/);
				attenuation = max(attenuation, 0);
				//calculate result
				vec3 result = (ambient + diffuse + specular) * objectColor * attenuation;
				color = vec4(result, 1.0f);
			}
			);

		//==========================
		// simple light FS
		//==========================
		constexpr GLchar * const simpleLight = glsl(330 core,
			out vec4 color;

			void main() {
				color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
			}
			);

	} }

enum class e_shader_type { VERTEX_SHADER, FRAGMENT_SHADER };

GLuint compileShader(e_shader_type shaderType, const GLchar* const *shaderSource);
GLuint createShaderProgram(GLuint vertexShader, GLuint fragmentShader);
void sendModelViewProjToShader(GLuint shaderProgram, glm::mat4 &model, glm::mat4 &view, glm::mat4 &proj);


