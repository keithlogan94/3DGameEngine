#include "Textures.h"
#include <stdlib.h>
#include <stdio.h>


//Supports only raw image data in RGB format
//Must provide the exact width and height of the image in pixesl
GLuint raw_texture_load(const char *filename, int width, int height)
{
	unsigned char *data;
	FILE *file;

	//Open Texture Data
	file = fopen(filename, "rb");
	if (file == NULL) return 0;

	//Allocate Buffer
	data = (unsigned char*)malloc(width * height * 3);

	//Read Texture Data
	fread(data, width * height * 3, 1, file);
	fclose(file);

	//Create Texture
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	//Store Texture Data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	//Clean Up
	free(data);
	return texture;
}
