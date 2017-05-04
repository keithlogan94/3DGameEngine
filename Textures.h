#pragma once
#include <GL\glew.h>

enum class e_image_format { RGB, RGBA };

GLuint raw_texture_load(const char *filename, int width, int height, e_image_format format);