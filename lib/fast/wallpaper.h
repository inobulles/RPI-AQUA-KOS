
#ifndef __AQUA__LIB_FAST_WALLPAPER_H
	#define __AQUA__LIB_FAST_WALLPAPER_H
	
	#include "../layer.h"
	
	typedef struct {
		var path[128];
		layer_t layer;
		var position;
		
	} wallpaper_t;
	
	void wallpaper_set_layer(wallpaper_t* self, var layer);
	void wallpaper_set_alpha(wallpaper_t* self, uvar alpha);	

	void new_wallpaper_scratch(wallpaper_t* self, layer_t* layer) {
		self->layer = *layer;
		self->position = 0;
		
		wallpaper_set_layer(self, -1);
		//wallpaper_set_alpha(self, _UI64_MAX);
		
	}
	
	 void lib(new_wallpaper)(wallpaper_t* self, const char* path, texture_t texture, bool use_path) {
		new_layer(&self->layer);
		self->layer.fullscreen = true;
		
		if (use_path) {
			if      (path == (const char*) TEXTURE_BACKGROUND)         layer_set_texture(&self->layer, TEXTURE_BACKGROUND);
			else if (path == (const char*) TEXTURE_FROSTED_BACKGROUND) layer_set_texture(&self->layer, TEXTURE_FROSTED_BACKGROUND);
			
			else {
				sprintf((char*) self->path, PATH"%s", path);
				layer_set_bitmap(&self->layer, self->path);
				
			}
			
		} else {
			layer_set_reuse_texture_with_texture(&self->layer, texture);
			
			self->layer.canvas_width  = video_width();
			self->layer.canvas_height = video_height();
			
		}
		
		layer_init(&self->layer);
		new_wallpaper_scratch(self, &self->layer);
		
	}
	
	void new_wallpaper(wallpaper_t* self, const char* path) {
		lib(new_wallpaper)(self, path, 0, true);
		
	}
	
	void new_wallpaper_texture(wallpaper_t* self, texture_t texture) {
		lib(new_wallpaper)(self, nullptr, texture, false);
		
	}
	
	void wallpaper_set_layer(wallpaper_t* self, var layer)  { layer_set_layer(&self->layer, layer); }
	void wallpaper_set_alpha(wallpaper_t* self, uvar alpha) { layer_set_alpha(&self->layer, alpha); }
	
	void wallpaper_draw    (wallpaper_t* self)                                      { layer_draw               (&self->layer); }
	void wallpaper_cutout  (wallpaper_t* self, var x, var y, var width, var height) { layer_cutout_aligned     (&self->layer, x, y, width, height); }
	void wallpaper_set_size(wallpaper_t* self, flt multiplier)                      { layer_set_size_multiplier(&self->layer, multiplier); }
	
	void wallpaper_set_paralax(wallpaper_t* self, var* paralax_x, var* paralax_y) {
		layer_set_paralax(&self->layer, paralax_x, paralax_y);
		
	}
	
	void dispose_wallpaper(wallpaper_t* self) {
		layer_dispose(&self->layer);
		
	}
	
#endif
