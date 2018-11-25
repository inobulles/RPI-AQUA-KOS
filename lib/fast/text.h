

#ifndef __AQUA__LIB_FAST_TEXT_H
	#define __AQUA__LIB_FAST_TEXT_H
	
	#include "../layer.h"
	#include "../theme/theme.h"
	
	#define POSITION_CENTER 0, 0
	
	#define POSITION_BOTTOM 0, (-_UI64_MAX_MARGIN)
	#define POSITION_TOP    0, ( _UI64_MAX_MARGIN)
	
	#define POSITION_TWO_THIRDS 0, ( _UI64_MAX_MARGIN - (_UI64_MAX_MARGIN / 3))
	#define POSITION_ONE_THIRD  0, (-_UI64_MAX_MARGIN + (_UI64_MAX_MARGIN / 3))
	
	typedef struct {
		char* text;
		font_t font;
		layer_t layer;
		theme_t theme;
		
		var xa;
		var ya;
		
		var width;
		var height;
		
		bool grey;
		
	} text_t;
	
	void text_set_grey(text_t* self, bool grey) {
		self->grey = grey;
		
		if (grey) {
			layer_set_colour(&self->layer, get_red  (self->theme.grey_colour), get_green(self->theme.grey_colour), get_blue(self->theme.grey_colour));
			layer_set_alpha (&self->layer, get_alpha(self->theme.grey_colour));
			
		} else {
			layer_set_colour(&self->layer, get_red  (self->theme.text_colour), get_green(self->theme.text_colour), get_blue(self->theme.text_colour));
			layer_set_alpha (&self->layer, get_alpha(self->theme.text_colour));
			
		}
		
	}
	
	void new_text(text_t* self, font_t font, final char* text, theme_t theme, var layer) {
		self->text = (char*) text;
		self->font = font;
		self->theme = theme;
		
		new_layer     (&self->layer);
		layer_set_text(&self->layer, font, text);
		layer_init    (&self->layer);
		
		layer_set_layer(&self->layer, layer);
		text_set_grey(self, false);
		
		self->xa = 1;
		self->ya = 1;
		
		self->width  = self->layer.width;
		self->height = self->layer.height;
		
	}
	
	void text_rainbow(text_t* self) { layer_set_rainbow(&self->layer); }
	void text_flash  (text_t* self) { layer_set_flash  (&self->layer); }
	
	void text_animation(text_t* self, var animation_type, flt time) { layer_set_animation(&self->layer, animation_type, time); } // layer wrappers
	void text_reverse_animation(text_t* self)                       { layer_reverse(      &self->layer); }
	void text_align(text_t* self, var x, var y)                     { layer_align(        &self->layer, x, y); }
	
	void text_point_to_point(text_t* self, flt time, var src_x, var src_y, var dest_x, var dest_y) {
		text_animation(self, ANIMATION_TYPE_ENABLED | ANIMATION_TYPE_POINT_TO_POINT | ANIMATION_TYPE_ALPHA, time);
		
		self->layer.source_position[0] = src_x;
		self->layer.source_position[1] = src_y;
		
		self->layer.destination_position[0] = dest_x;
		self->layer.destination_position[1] = dest_y;
		
	}
	
	void text_set_position(text_t self[notnull], var x, var y) {
		layer_set_xaa(&self->layer, x);
		layer_set_yaa(&self->layer, y);
		
	}
	
	void text_set_text(text_t self[notnull], final char* text) {
		self->text = (char*) text;
		
		var x = self->layer.x + self->layer.width  / 2;
		var y = self->layer.y + self->layer.height / 2;
		
		layer_set_text  (&self->layer, self->font, text);
		layer_reset_size(&self->layer);
		
		text_set_position(self, x, y);
		
	}
	
	void text_fade_out(text_t* self, flt time) {
		text_animation(self, ANIMATION_TYPE_ENABLED | ANIMATION_TYPE_INVERT | ANIMATION_TYPE_ALPHA, time);
		
	}
	
	void text_set_alpha (text_t self[notnull], uvar alpha)                      {        layer_set_alpha (&self->layer, alpha);            }
	void text_set_colour(text_t self[notnull], uvar red, uvar green, uvar blue) {        layer_set_colour(&self->layer, red, green, blue); }
	var  text_click     (text_t self[notnull], var x, var y)                    { return layer_click(&self->layer, x, y);                  }
	
	var text_draw(text_t* self, var fps) {
		var stopped = 0;
		
		if (self->layer.animation_type) {
			stopped += layer_update(&self->layer, fps);
			
		}
		
		layer_draw(&self->layer);
		return stopped;
		
	}
	
	void dispose_text(text_t* self) {
		dispose_layer(&self->layer);
		
	}
	
#endif
