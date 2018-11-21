
#ifndef __AQUA__GL_TEXTURE_H
	#define __AQUA__GL_TEXTURE_H
	
	#include "root.h"
	#include "../decoders/bmp.h"

	GLuint create_texture(unsigned int width, unsigned int height, unsigned char* data, unsigned char bpp) {
		if ((((width & ~(width - 1)) == width) ? 0 : 1) || (((height & ~(height - 1)) == height) ? 0 : 1)) {
			printf("WARNING The width (%d) and height (%d) you have provided are not powers of 2\n", width, height);
			
		}
		
		GLuint texture_id;
		glGenTextures(1, &texture_id);

		glBindTexture(GL_TEXTURE_2D, texture_id);
		glTexImage2D(GL_TEXTURE_2D, 0, bpp == 24 ? GL_RGB : GL_RGBA, width, height, 0, bpp == 24 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		return texture_id;

	}
	
	GLuint create_texture_from_bmp(bitmap_image_t image) {
		return create_texture(image.width, image.height, image.data, 24);
		
	}
	
#endif

