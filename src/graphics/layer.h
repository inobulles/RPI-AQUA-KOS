
#ifndef __AQUA__GRAPHICS_LAYER_H
	#define __AQUA__GRAPHICS_LAYER_H
	
	#include "../gl/texture.h"
	#include "../gl/surf.h"
	
	typedef struct {
		unsigned char used;
		unsigned int id;
		
		surface_t surface;
		unsigned char* data;
		
		unsigned int width;
		unsigned int height;
		
		unsigned char bpp;
		
	} layer_t;
	
	#define MAX_LAYER_COUNT 64
	
	static layer_t internal_layers[MAX_LAYER_COUNT];
	
	layer_t* new_layer(unsigned char* data, float x, float y, int depth, float width, float height, unsigned int resolution_x, unsigned int resolution_y, unsigned char bpp) {
		layer_t layer = {
			.used = 1,
			
			.data = data,
			.bpp = bpp,
			
			.width = resolution_x,
			.height = resolution_y
			
		};
		
		surface_new(&layer.surface, x, y, width, height);
		
		GLuint texture = create_texture(layer.width, layer.height, layer.data, layer.bpp);
		surface_set_texture(&layer.surface, texture);
		
		int i;
		for (i = 0; i < MAX_LAYER_COUNT; i++) {
			if (!internal_layers[i].used) {
				layer.id = i;
				internal_layers[i] = layer;
				
				break;
				
			}
			
		}
		
		return &internal_layers[layer.id];
		
	}
	
	void layer_set_position(layer_t* this, float x, float y) {
		(&this->surface)->x = x;
		(&this->surface)->y = y;
		
	}
	
	void layer_set_outlook(layer_t* this, float x, float y, float width, float height) {
		surface_scroll_texture(&this->surface, x, y, width, height);
		
	}
	
	void layer_set_alpha(layer_t* this, float alpha) {
		surface_set_alpha(&this->surface, alpha);
		
	}
	
	void layer_set_colour(layer_t* this, colour_t colour) {
		surface_set_colour(&this->surface, colour.r, colour.g, colour.b, colour.a);
		
	}
	
	void layer_draw(layer_t* this) {
		surface_draw(&this->surface);
		
	}
	
	void layer_dispose(layer_t* this) {
		internal_layers[this->id].used = 0;
		free(this->data);
		
	}
	
#endif
