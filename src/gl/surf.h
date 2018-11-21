
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

	static inline void surface_update_vertices(surface_t* this) {
		float width  = (float) this->width  / _UI64_MAX_MARGIN;
		float height = (float) this->height / _UI64_MAX_MARGIN;
		
		float x      = (float) this->x      / _UI64_MAX_MARGIN;
		float y      = (float) this->y      / _UI64_MAX_MARGIN;
		
		int i;
		for (i = 0; i < 4; i++) {
			this->vertices[i].z =           (GLfloat) this->layer / 256.0f;
			
			this->vertices[i].x =           (GLfloat) (width  * vertex_matrix[i * 3]     + x);
			this->vertices[i].y =           (GLfloat) (height * vertex_matrix[i * 3 + 1] + y);
			
			if (!this->scroll_texture) {
				this->texture_coords[i].x = (GLfloat) texture_coords[i * 2];
				this->texture_coords[i].y = (GLfloat) texture_coords[i * 2 + 1];
				
			}
			
		}
		
	}
	
	void surface_scroll(surface_t* this, signed long long _x, signed long long _y, unsigned long long _width, unsigned long long _height) {
		this->scroll_texture = 1;
		
		float x      = ((float) _x      / _SI64_MAX_MARGIN / 4) + 0.5f;
		float y      = ((float) _y      / _SI64_MAX_MARGIN / 4) + 0.5f;
		
		float width  =  (float) _width  / _UI64_MAX_MARGIN / 2;
		float height =  (float) _height / _UI64_MAX_MARGIN / 2;
		
		y = -y - height - 1.0f;
		
		int i;
		for (i = 0; i < 4; i++) {
			this->texture_coords[i].x = (GLfloat) (texture_coords[i * 2]     * width  + x);
			this->texture_coords[i].y = (GLfloat) (texture_coords[i * 2 + 1] * height + y);
			
		}
		
	}
	
	static void surface_update_colours(surface_t* this) {
		float red   = (float) this->red   / _UI64_MAX;
		float green = (float) this->green / _UI64_MAX;
		float blue  = (float) this->blue  / _UI64_MAX;
		float alpha = (float) this->alpha / _UI64_MAX;
		
		int i;
		for (i = 0; i < SURFACE_VERTEX_COUNT; i++) {
			this->colours[i].alpha = alpha;
			
			this->colours[i].red   = red;
			this->colours[i].green = green;
			this->colours[i].blue  = blue;
			
		}
		
	}

	static void surface_update(surface_t* this) {
		surface_update_vertices(this);
		surface_update_colours( this);
		
	}

	static void surface_faces(surface_t* this) {
		this->faces[0] = 0;
		this->faces[1] = 1;
		this->faces[2] = 2;
		
		this->faces[3] = 0; // 3;
		this->faces[4] = 2; // 4;
		this->faces[5] = 3; // 5;
		
	}

	void surface_new(surface_t* this, signed long long x, signed long long y, unsigned long long width, unsigned long long height) {
		this->red    = _UI64_MAX;
		this->green  = _UI64_MAX;
		this->blue   = _UI64_MAX;
		
		this->x      = x;
		this->y      = y;
		
		this->width  = width;
		this->height = height;
		
		this->layer  = 0;
		this->alpha  = _UI64_MAX;
		
		this->scroll_texture = 0;
		this->has_texture    = 0;
		
		surface_update(this);
		surface_faces( this);
		
	}
	
	void surface_free(surface_t* this) {
		//~ printf("FREED SURFACE %p\n", this);
		
	}
	
	void surface_set_texture(surface_t* this, texture_t texture) {
		this->has_texture = 1;
		this->texture = texture;
		
	}
	
	void surface_set_alpha(surface_t* this, unsigned long long alpha) {
		this->alpha         = alpha;
		GLfloat float_alpha = (GLfloat) this->alpha / _UI64_MAX;
		
		int i;
		for (i = 0; i < SURFACE_VERTEX_COUNT; i++) {
			this->colours[i].alpha = float_alpha;
			
		}
		
	}
	
	void surface_set_colour(surface_t* this, unsigned long long red, unsigned long long green, unsigned long long blue) {
		this->red   = red;
		this->green = green;
		this->blue  = blue;
		
		surface_update_colours(this);
		
	}
	
	void surface_set_x(surface_t* this, signed long long x) {
		this->x = x;
		surface_update_vertices(this);
		
	}
	
	void surface_set_y(surface_t* this, signed long long y) {
		this->y = y;
		surface_update_vertices(this);
		
	}
	
	void surface_set_width(surface_t* this, unsigned long long width) {
		this->width = width;
		surface_update_vertices(this);
		
	}
	
	void surface_set_height(surface_t* this, unsigned long long height) {
		this->height = height;
		surface_update_vertices(this);
		
	}
	
	void surface_set_layer(surface_t* this, signed long long layer) {
		this->layer = layer;
		surface_update_vertices(this);
		
	}
	
	// gradient functions
	
	#define KOS_SURF_FULL_COLOUR_FUNCTION_PARAMS unsigned long long __this, unsigned long long red, unsigned long long green, unsigned long long blue, unsigned long long alpha
	#define SURFACE_GRADIENT_FUNCTIONS 1
	
	#define KOS_SURF_SET_COLOUR_FOR_VERTEX(index) { \
		this->colours[index].red   = (float) red   / _UI64_MAX; \
		this->colours[index].green = (float) green / _UI64_MAX; \
		this->colours[index].blue  = (float) blue  / _UI64_MAX; \
		this->colours[index].alpha = (float) alpha / _UI64_MAX; \
	}
	
	void surface_gradient_left(KOS_SURF_FULL_COLOUR_FUNCTION_PARAMS) {
		surface_t* this = (surface_t*) __this;
		
		KOS_SURF_SET_COLOUR_FOR_VERTEX(0)
		KOS_SURF_SET_COLOUR_FOR_VERTEX(1)
		
	}
	
	void surface_gradient_right(KOS_SURF_FULL_COLOUR_FUNCTION_PARAMS) {
		surface_t* this = (surface_t*) __this;
		
		KOS_SURF_SET_COLOUR_FOR_VERTEX(3)
		KOS_SURF_SET_COLOUR_FOR_VERTEX(2)
		
	}
	
	void surface_gradient_top(KOS_SURF_FULL_COLOUR_FUNCTION_PARAMS) {
		surface_t* this = (surface_t*) __this;
		
		KOS_SURF_SET_COLOUR_FOR_VERTEX(0)
		KOS_SURF_SET_COLOUR_FOR_VERTEX(3)
		
	}
	
	void surface_gradient_bottom(KOS_SURF_FULL_COLOUR_FUNCTION_PARAMS) {
		surface_t* this = (surface_t*) __this;
		
		KOS_SURF_SET_COLOUR_FOR_VERTEX(1)
		KOS_SURF_SET_COLOUR_FOR_VERTEX(2)
		
	}

	int surface_draw(surface_t* this) {
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		
		if (this->has_texture) {
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			
		}

		glVertexPointer(3, GL_FLOAT, 0, this->vertices);
		glColorPointer(4, GL_FLOAT, 0, this->colours);
		
		if (this->has_texture) {
			glTexCoordPointer(2, GL_FLOAT, 0, this->tex_coords);
			
		}

		glBindTexture(GL_TEXTURE_2D, this->texture);
		glDrawElements(GL_TRIANGLES, SURFACE_VERTEX_COUNT, GL_UNSIGNED_BYTE, this->faces);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		
		if (this->has_texture) {
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			
		}
		
		return 0;

	}

#endif
