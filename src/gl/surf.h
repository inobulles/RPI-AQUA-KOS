
#ifndef __AQUA__GL_SURF_H
	#define __AQUA__GL_SURF_H

	#include "root.h"
	
	static Vertex3D surface_add(int i, int j) {
		unsigned char add_x;
		unsigned char add_y;
		
		if (i > 2) {
			j = i % 3;

			if (j == 0) {
				j = 3;

			}

		} else {
			j = i;

		}

		if (j == 1) {
			add_x = 0;
			add_y = 1;

		} else if (j == 2) {
			add_x = 1;
			add_y = 0;

		} else if (j == 3) {
			add_x = 1;
			add_y = 1;

		} else {
			add_x = 0;
			add_y = 0;

		}
		
		Vertex3D result = {
			.x = add_x,
			.y = add_y,
			.z = j
			
		};
		
		return result;
		
	}
	
	void surface_update_vertices(surface_t* this) {
		int j;

		unsigned char add_x;
		unsigned char add_y;

		Vertex3D add;

		int i;
		for (i = 0; i < SURFACE_VERTEX_COUNT; i++) {
			add = surface_add(i, j);
			
			add_x = add.x;
			add_y = add.y;
			j = add.z;
			
			this->vertices[i].z = (GLfloat) this->layer;

			this->vertices[i].x = (GLfloat) (this->x + (add_x ? this->width : 0));
			this->vertices[i].y = (GLfloat) (this->y + (add_y ? this->height : 0));
			
			if (!this->scroll_texture) {
				this->tex_coords[i].x = (GLfloat) add_x;
				this->tex_coords[i].y = (GLfloat) add_y;
				
			}

		}

	}
	
	void surface_scroll_texture(surface_t* this, float x, float y, float width, float height) {
		this->scroll_texture = 1;
		
		unsigned char add_x;
		unsigned char add_y;
		
		int j;
		Vertex3D add;
		
		int i;
		for (i = 0; i < SURFACE_VERTEX_COUNT; i++) {
			add = surface_add(i, j);
			j = add.z;
			
			add_x = add.x;
			add_y = add.y;
			
			this->tex_coords[i].x = ((GLfloat) add_x) * width + x;
			this->tex_coords[i].y = ((GLfloat) add_y) * height + y;
			
		}
		
	}

	void surface_update_colours(surface_t* this) {
		int i;
		for (i = 0; i < SURFACE_VERTEX_COUNT; i++) {
			this->colours[i].alpha = this->alpha;

			this->colours[i].red = this->r;
			this->colours[i].green = this->g;
			this->colours[i].blue = this->b;

		}

	}

	void surface_set_alpha(surface_t* this, float alpha) {
		this->alpha = alpha;

		int i;
		for (i = 0; i < SURFACE_VERTEX_COUNT; i++) {
			this->colours[i].alpha = alpha;

		}

	}
	
	void surface_set_colour(surface_t* this, float r, float g, float b, float a) {
		this->alpha = a;
		
		this->r = r;
		this->g = g;
		this->b = b;
		
		surface_update_colours(this);

	}

	inline void surface_update(surface_t* this) {
		surface_update_vertices(this);
		surface_update_colours(this);

	}

	static void surface_faces(surface_t* this) {
		this->faces[0] = 0;
		this->faces[1] = 1;
		this->faces[2] = 2;

		this->faces[3] = 3;
		this->faces[4] = 4;
		this->faces[5] = 5;

	}

	void surface_set_texture(surface_t* this, GLuint texture) {
		this->has_texture = 1;
		this->texture = texture;

	}

	void surface_new(surface_t* this, float x, float y, float width, float height) {
		this->r = 1.0f;
		this->g = 1.0f;
		this->b = 1.0f;
		
		this->x = x;
		this->y = y;

		this->width = width;
		this->height = height;

		this->layer = 0;
		this->alpha = 1.0f;
		
		this->scroll_texture = 0;
		this->has_texture = 0;

		surface_update(this);
		surface_faces(this);

	}

	void surface_draw(surface_t* this) {
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

	}

#endif
