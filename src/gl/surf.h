
#ifndef __AQUA__GL_SURF_H
	#define __AQUA__GL_SURF_H

	#include "root.h"

	static const float vertex_matrix[] = {
		0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
	};
	
	static const float texture_coords[] = {
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
	};

	static inline void surface_update_vertices(surface_t* self) {
		float width  = (float) self->width  / _UI64_MAX_MARGIN;
		float height = (float) self->height / _UI64_MAX_MARGIN;
		
		float x      = (float) self->x      / _UI64_MAX_MARGIN;
		float y      = (float) self->y      / _UI64_MAX_MARGIN;
		
		int i;
		for (i = 0; i < 4; i++) {
			self->vertices[i].z =           (GLfloat) self->layer / 256.0f;
			
			self->vertices[i].x =           (GLfloat) (width  * vertex_matrix[i * 3]     + x);
			self->vertices[i].y =           (GLfloat) (height * vertex_matrix[i * 3 + 1] + y);
			
			if (!self->scroll_texture) {
				self->texture_coords[i].x = (GLfloat) texture_coords[i * 2];
				self->texture_coords[i].y = (GLfloat) texture_coords[i * 2 + 1];
				
			}
			
		}
		
	}
	
	void surface_scroll(surface_t* self, signed long long _x, signed long long _y, unsigned long long _width, unsigned long long _height) {
		self->scroll_texture = 1;
		
		float x      = ((float) _x      / _SI64_MAX_MARGIN / 4) + 0.5f;
		float y      = ((float) _y      / _SI64_MAX_MARGIN / 4) + 0.5f;
		
		float width  =  (float) _width  / _UI64_MAX_MARGIN / 2;
		float height =  (float) _height / _UI64_MAX_MARGIN / 2;
		
		y = -y - height - 1.0f;
		
		int i;
		for (i = 0; i < 4; i++) {
			self->texture_coords[i].x = (GLfloat) (texture_coords[i * 2]     * width  + x);
			self->texture_coords[i].y = (GLfloat) (texture_coords[i * 2 + 1] * height + y);
			
		}
		
	}
	
	static void surface_update_colours(surface_t* self) {
		float red   = (float) self->red   / _UI64_MAX;
		float green = (float) self->green / _UI64_MAX;
		float blue  = (float) self->blue  / _UI64_MAX;
		float alpha = (float) self->alpha / _UI64_MAX;
		
		int i;
		for (i = 0; i < SURFACE_VERTEX_COUNT; i++) {
			self->colours[i].alpha = alpha;
			
			self->colours[i].red   = red;
			self->colours[i].green = green;
			self->colours[i].blue  = blue;
			
		}
		
	}

	static void surface_update(surface_t* self) {
		surface_update_vertices(self);
		surface_update_colours( self);
		
	}

	static void surface_faces(surface_t* self) {
		self->faces[0] = 0;
		self->faces[1] = 1;
		self->faces[2] = 2;
		
		self->faces[3] = 0; // 3;
		self->faces[4] = 2; // 4;
		self->faces[5] = 3; // 5;
		
	}

	void surface_new(surface_t* self, signed long long x, signed long long y, unsigned long long width, unsigned long long height) {
		self->red    = _UI64_MAX;
		self->green  = _UI64_MAX;
		self->blue   = _UI64_MAX;
		
		self->x      = x;
		self->y      = y;
		
		self->width  = width;
		self->height = height;
		
		self->layer  = 0;
		self->alpha  = _UI64_MAX;
		
		self->scroll_texture = 0;
		self->has_texture    = 0;
		
		surface_update(self);
		surface_faces( self);
		
	}
	
	void surface_free(surface_t* self) {
		//~ printf("FREED SURFACE %p\n", self);
		
	}
	
	void surface_set_texture(surface_t* self, texture_t texture) {
		self->has_texture = 1;
		self->texture = texture;
		
	}
	
	void surface_set_alpha(surface_t* self, unsigned long long alpha) {
		self->alpha         = alpha;
		GLfloat float_alpha = (GLfloat) self->alpha / _UI64_MAX;
		
		int i;
		for (i = 0; i < SURFACE_VERTEX_COUNT; i++) {
			self->colours[i].alpha = float_alpha;
			
		}
		
	}
	
	void surface_set_colour(surface_t* self, unsigned long long red, unsigned long long green, unsigned long long blue) {
		self->red   = red;
		self->green = green;
		self->blue  = blue;
		
		surface_update_colours(self);
		
	}
	
	void surface_set_x(surface_t* self, signed long long x) {
		self->x = x;
		surface_update_vertices(self);
		
	}
	
	void surface_set_y(surface_t* self, signed long long y) {
		self->y = y;
		surface_update_vertices(self);
		
	}
	
	void surface_set_width(surface_t* self, unsigned long long width) {
		self->width = width;
		surface_update_vertices(self);
		
	}
	
	void surface_set_height(surface_t* self, unsigned long long height) {
		self->height = height;
		surface_update_vertices(self);
		
	}
	
	void surface_set_layer(surface_t* self, signed long long layer) {
		self->layer = layer;
		surface_update_vertices(self);
		
	}
	
	// gradient functions
	
	#define KOS_SURF_FULL_COLOUR_FUNCTION_PARAMS unsigned long long __self, unsigned long long red, unsigned long long green, unsigned long long blue, unsigned long long alpha
	#define SURFACE_GRADIENT_FUNCTIONS 1
	
	#define KOS_SURF_SET_COLOUR_FOR_VERTEX(index) { \
		self->colours[index].red   = (float) red   / _UI64_MAX; \
		self->colours[index].green = (float) green / _UI64_MAX; \
		self->colours[index].blue  = (float) blue  / _UI64_MAX; \
		self->colours[index].alpha = (float) alpha / _UI64_MAX; \
	}
	
	void surface_gradient_left(KOS_SURF_FULL_COLOUR_FUNCTION_PARAMS) {
		surface_t* self = (surface_t*) __self;
		
		KOS_SURF_SET_COLOUR_FOR_VERTEX(0)
		KOS_SURF_SET_COLOUR_FOR_VERTEX(1)
		
	}
	
	void surface_gradient_right(KOS_SURF_FULL_COLOUR_FUNCTION_PARAMS) {
		surface_t* self = (surface_t*) __self;
		
		KOS_SURF_SET_COLOUR_FOR_VERTEX(3)
		KOS_SURF_SET_COLOUR_FOR_VERTEX(2)
		
	}
	
	void surface_gradient_top(KOS_SURF_FULL_COLOUR_FUNCTION_PARAMS) {
		surface_t* self = (surface_t*) __self;
		
		KOS_SURF_SET_COLOUR_FOR_VERTEX(0)
		KOS_SURF_SET_COLOUR_FOR_VERTEX(3)
		
	}
	
	void surface_gradient_bottom(KOS_SURF_FULL_COLOUR_FUNCTION_PARAMS) {
		surface_t* self = (surface_t*) __self;
		
		KOS_SURF_SET_COLOUR_FOR_VERTEX(1)
		KOS_SURF_SET_COLOUR_FOR_VERTEX(2)
		
	}

	int surface_draw(surface_t* self) {
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		
		if (self->has_texture) {
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			
		}

		glVertexPointer(3, GL_FLOAT, 0, self->vertices);
		glColorPointer(4, GL_FLOAT, 0, self->colours);
		
		if (self->has_texture) {
			glTexCoordPointer(2, GL_FLOAT, 0, self->texture_coords);
			
		}

		glBindTexture(GL_TEXTURE_2D, self->texture);
		glDrawElements(GL_TRIANGLES, SURFACE_VERTEX_COUNT, GL_UNSIGNED_BYTE, self->faces);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		
		if (self->has_texture) {
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			
		}
		
		return 0;

	}

#endif
