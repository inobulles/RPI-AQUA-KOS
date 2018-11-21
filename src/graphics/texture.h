
#ifndef __AQUA__GRAPHICS_TEXTURE_H
	#define __AQUA__GRAPHICS_TEXTURE_H
	
	#include "../gl/root.h"
	
	/// THIS IS IN #include "colour.h"
	
	#ifndef __AQUA__GRAPHICS_COLOUR_H
		#define __AQUA__GRAPHICS_COLOUR_H
		
		typedef struct {
			float r;
			float g;
			float b;
			
			float a;
			
		} colour_t;
		
		colour_t new_colour(float r, float g, float b, float a) {
			colour_t colour = {
				.r = r,
				.g = g,
				.b = b,
				
				.a = a
				
			};
			
			return colour;
			
		}
		
	#endif
	
	unsigned char* solid_texture(unsigned int width, unsigned int height, unsigned int bpp, colour_t colour) {
		unsigned int size = width * height * (bpp == 32 ? 4 : 3);
		unsigned char* data = (unsigned char*) malloc(size);
		
		int i;
		for (i = 0; i < size; i += bpp == 32 ? 4 : 3) {
			data[i] = colour.r * 255.0f;
			data[i + 1] = colour.g * 255.0f;
			data[i + 2] = colour.b * 255.0f;
			
			if (bpp == 32) {
				data[i + 3] = colour.a * 255.0f;
				
			}
			
		}
		
		return data;
		
	}
	
	unsigned char* npot_to_pot(unsigned char* data, unsigned int width, unsigned int height) {
		return data; /// TODO
		
	}
	
	unsigned char* get_accelerated_image(const char* path) {
		printf("%s\n", path);
		return load_bmp(path).data;
		
	}
	
#endif
