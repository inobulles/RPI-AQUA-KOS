
#ifndef __AQUA__GL_TEXTURE_H
	#define __AQUA__GL_TEXTURE_H
	
	#include "root.h"
	#include "../decoders/bmp.h"

	#define SHARP_TEXTURES 0
	//~ #define TEXTURE_WRAP_TYPE GL_MIRRORED_REPEAT // pushes colour to absolute edge, GL_CLAMP_TO_EDGE to wrap colour around
	
	texture_t texture_create(unsigned long long* _data, unsigned long long bpp, unsigned long long width, unsigned long long height) {
		unsigned char alpha = bpp % 32;
		
		unsigned long long* data = _data;
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		
		if (bpp > 32) { // assuming > 32 BPPs are unsupported by the HW ...
			unsigned long long data_bytes = width * height * (bpp >> 4);
			data = (unsigned long long*) malloc(data_bytes);
			
			unsigned long long i;
			for (i = 0; i < data_bytes; i++) {
				((char*) data)[i] = ((char*) _data)[i << 1];
				
			}
			
		}
		
		GLuint texture_id;
		glGenTextures(1, (GLuint*) &texture_id);
		
		glBindTexture(GL_TEXTURE_2D, (GLuint) texture_id);
		glTexImage2D (GL_TEXTURE_2D, 0, alpha ? GL_RGB : GL_RGBA, (GLuint) width, (GLuint) height, 0, alpha ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, data);
		
		if (bpp > 32) {
			free(data);
			
		}
		
		//~ glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TEXTURE_WRAP_TYPE); // x axis
		//~ glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TEXTURE_WRAP_TYPE); // y axis
		
		if (SHARP_TEXTURES) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			
		} else {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			
		}
		
		return texture_id;
		
	}
	
	void texture_remove(texture_t self) {
		glDeleteTextures(1, (GLuint*) &self);
		
	}
	
#endif

