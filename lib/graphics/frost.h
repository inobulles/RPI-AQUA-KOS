
#ifndef __AQUA__LIB_GRAPHICS_FROST_H
	#define __AQUA__LIB_GRAPHICS_FROST_H
	
	#include "../fast/wallpaper.h"
	#include "../theme/theme.h"
	#include "blur.h"
	
	#define TINT_PATH  PATH"tint/noise.bmp"
	#define FROST_PATH PATH"wallpaper/frost.bmp"
	
	typedef struct {
		wallpaper_t wallpaper;
		layer_t tint;
		layer_t noise;
		theme_t theme;
		
		var layer;
		var colour;
		
		// internal

		flt alpha;
		flt base;
		
		bool has_blur_texture;
		var      blur_texture;
		
	} frost_t;
	
	void frost_set_layer (frost_t* self, var layer);
	void frost_set_colour(frost_t* self, var colour);
	void frost_set_alpha (frost_t* self, flt alpha);
	
	void new_frost_scratch(frost_t* self, wallpaper_t* wallpaper, layer_t* tint, layer_t* noise) {
		self->layer = 1;
		self->colour = self->theme.layer_colour;
		
		self->wallpaper = *wallpaper;
		self->tint      = *tint;
		self->noise     = *noise;
		
		self->base = 0;
		frost_set_layer(self, self->layer);
		
		frost_set_alpha(self, FLOAT_ONE);
		frost_set_colour(self, self->colour);
		
	}
	
	void lib(new_frost)(frost_t* self, const char* path, texture_t texture, bool use_path) {
		self->has_blur_texture = false;
		self->theme = theme_default();
		
		if (use_path) new_wallpaper        (&self->wallpaper, path);
		else          new_wallpaper_texture(&self->wallpaper, texture);
		
		new_layer(&self->tint);
		new_layer(&self->noise);
		
		self->tint. fullscreen = true;
		self->noise.fullscreen = true;
		
		layer_set_canvas(&self->tint, 2, 2);
		layer_set_bitmap(&self->noise, (var*) TINT_PATH);
		
		layer_init(&self->tint);
		layer_init(&self->noise);
		
		layer_canvas_wash(&self->tint, 0xFFFFFFFFFFFFFFFF);
		layer_canvas_flip(&self->tint);
		
		new_frost_scratch(self, &self->wallpaper, &self->tint, &self->noise);
		
	}
	
	void new_frost_blur(frost_t* self, theme_t* theme, layer_t* layer) {
		self->blur_texture = blur(layer, theme, 0, 0, video_width(), video_height(), 128);
		lib(new_frost)(self, nullptr, self->blur_texture, false);
		self->has_blur_texture = true;
		
	}
	
	void new_frost(frost_t* self, const char* path) {
		lib(new_frost)(self, path, 0, true);
		
	}
	
	void frost_set_colour(frost_t* self, var colour) {
		self->colour = colour;
		
		if (self->base) {
			wallpaper_set_alpha(&self->wallpaper, _UI64_MAX);
			
		}
		
		var red   = get_red  (colour);
		var green = get_green(colour);
		var blue  = get_blue (colour);
		
		var alpha = FLOAT_TO_U64_MAX(self->base + (self->alpha >> 8) * ((colour & 0xFF) - (self->base << 8) / FLOAT_ONE));
		
		layer_set_alpha (&self->tint,  alpha);
		//~ layer_set_alpha (&self->noise, alpha / FLOAT_ONE * self->theme.noise);
		
		layer_set_colour(&self->tint,  red, green, blue);
		layer_set_colour(&self->noise, red, green, blue);
		
	}

	void frost_set_base(frost_t* self, flt base) {
		self->base = base;
		
	}
	
	void frost_set_alpha(frost_t* self, flt alpha) {
		self->alpha = alpha;
		alpha = FLOAT_TO_U64_MAX(alpha);

		wallpaper_set_alpha(&self->wallpaper, alpha);
		layer_set_alpha    (&self->tint,      alpha);
		layer_set_alpha    (&self->noise,     alpha / FLOAT_ONE * self->theme.noise);

	}
	
	void frost_set_layer(frost_t* self, var layer) {
		self->layer = layer;
		
		wallpaper_set_layer (&self->wallpaper, layer);
		layer_set_layer     (&self->tint,      layer + 1);
		layer_set_layer_fine(&self->noise,     layer + 1, 1);
		
	}
	
	void frost_draw(frost_t* self) {
		wallpaper_draw(&self->wallpaper);
		layer_draw    (&self->tint);
		
		if (self->theme.noise) {
			layer_draw(&self->noise);
			
		}
		
	}
	
	void frost_cutout(frost_t* self, var x, var y, var width, var height) {
		wallpaper_cutout(&self->wallpaper, x, y, width, height);
		
		layer_set_size  (&self->tint,            width, height);
		layer_set_size  (&self->noise,           width, height);
		
		layer_set_xa    (&self->tint,  x);
		layer_set_xa    (&self->noise, x);
		
		layer_set_ya    (&self->tint,  y);
		layer_set_ya    (&self->noise, y);
		
	}
	
	void frost_draw_window(frost_t* self) {
		frost_set_colour(self, self->theme.window_colour);
		frost_cutout    (self, 0, 0, _UI64_MAX_MARGIN * 2, _UI64_MAX_MARGIN * 2);
		frost_draw      (self);
		
	}
	
	void dispose_frost(frost_t* self) {
		if (self->has_blur_texture) {
			texture_remove(self->blur_texture);
			
		}
		
		dispose_wallpaper(&self->wallpaper);
		
		layer_dispose    (&self->tint);
		layer_dispose    (&self->noise);
		
	}
	
#endif
