
#ifndef __AQUA__SCREENS_DESKTOP_H
	#define __AQUA__SCREENS_DESKTOP_H
	
	#include "../wrapper.h"
	#include "../common/error.h"
	#include "../utils/wallpaper.h"
	
	#define DESKTOP_LAYER_COUNT 2
	
	#define DESKTOP_LAYER_WALLPAPER 0
	#define DESKTOP_LAYER_TEXT 1
	
	unsigned int screen_width;
	unsigned int screen_height;
	
	typedef struct {
		unsigned char valid;
		
		float x;
		float y;
		
		float width;
		float height;
		
		int layer;
		
		layer_t* layers[DESKTOP_LAYER_COUNT];
		
	} desktop_t;
	
	void layer_set_outlook(layer_t* this, float x, float y, float width, float height);
	
	void new_desktop(desktop_t* this) {
		this->valid = 1;
		
		this->x = -1.0f;
		this->y = -1.0f;
		
		this->width = 2.0f;
		this->height = 2.0f;
		
		this->layer = 0;
		
		// set this->layers
		
		this->layers[DESKTOP_LAYER_WALLPAPER] = new_layer(get_wallpaper(WALLPAPER_WALLPAPER), this->x, this->y, this->layer, this->width, this->height, 2048, 2048, 24);
		layer_set_outlook(this->layers[DESKTOP_LAYER_WALLPAPER], 0.0f, 0.0f, 1.0f, 1.0f);
		this->layers[DESKTOP_LAYER_TEXT] = new_layer(get_wallpaper(WALLPAPER_FROST), this->x / 2, this->y / 2, this->layer + 1, this->width / 2, this->height / 2, 2048, 2048, 24);
		//this->layers[DESKTOP_LAYER_TEXT] = new_layer(solid_texture(screen_width, screen_height, 32, new_colour(0.0f, 0.0f, 0.0f, 0.5f)), this->x / 4, this->y / 4, this->layer, this->width / 4, this->height / 4, screen_width, screen_height, 32);
		
		layer_set_alpha(this->layers[DESKTOP_LAYER_TEXT], 0.5f);
		
	}
	
	static int desktop_test(desktop_t* this) {
		if (!this->valid) {
			printf("WARNING Desktop object @ %p is not valid\n", this);
			return ERROR_ERROR;
			
		} else {
			return ERROR_SUCCESS;
			
		}
		
	}
	
	void desktop_set_dimensions(desktop_t* this, float x, float y, int layer, float width, float height) {
		desktop_test(this);
		
		this->x = x;
		this->y = y;
		
		this->width = width;
		this->height = height;
		
		this->layer = layer;
		
		int i;
		for (i = 0; i < DESKTOP_LAYER_COUNT; i++) {
			(&this->layers[i]->surface)->width = width;
			(&this->layers[i]->surface)->height = height;
			
			(&this->layers[i]->surface)->layer = layer;
			layer_set_position(this->layers[i], x, y);
			
		}
		
	}
	
	/// TODO desktop set alpha
	
	void desktop_draw(desktop_t* this) {
		desktop_test(this);
		clear_alpha(0);
		
		int i;
		for (i = 0; i < DESKTOP_LAYER_COUNT; i++) {
			layer_draw(this->layers[i]);
			
		}
		
	}
	
	void desktop_dispose(desktop_t* this) {
		desktop_test(this);
		this->valid = 0;
		
		int i;
		for (i = 0; i < DESKTOP_LAYER_COUNT; i++) {
			layer_dispose(this->layers[i]);
			
		}
		
	}
	
#endif
