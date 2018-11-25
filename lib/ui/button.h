
#ifndef __AQUA__LIB_UI_BUTTON_H
	#define __AQUA__LIB_UI_BUTTON_H
	
	#include "ui.h"
	#include "../graphics/text.h"
	
	typedef struct {
		var     state;
		layer_t position;
		text_t  text;
		var     layer;
		
		frost_t* frost;
		theme_t* theme;
		
		bool wallpaper;
		
	} ui_button_t;
	
	#define __lib_function_UI_BUTTON_STAGE_IDLE      0
	#define __lib_function_UI_BUTTON_STAGE_ANIMATION 1
	
	void ui_button_set_wallpaper(ui_button_t self[notnull], bool wallpaper) {
		self->wallpaper = wallpaper;
		
	}
	
	void new_ui_button(ui_button_t self[notnull], font_t font, final char text[notnull], frost_t frost[notnull], var layer) {
		self->state = lib(UI_BUTTON_STAGE_IDLE);
		
		self->frost = frost;
		self->layer = layer;
		
		self->theme = &frost->theme;
		new_text(&self->text, font, text, *self->theme, layer + 2);
		
		ui_button_set_wallpaper(self, false);
		
	}
	
	void ui_button_point_to_point(ui_button_t self[notnull], flt time, var src_x, var src_y, var dest_x, var dest_y) {
		self->state = lib(UI_BUTTON_STAGE_ANIMATION);
		layer_set_animation(&self->position, ANIMATION_TYPE_ENABLED | ANIMATION_TYPE_POINT_TO_POINT, time);
		
		self->position.source_position[0] = src_x;
		self->position.source_position[1] = src_y;
		
		self->position.destination_position[0] = dest_x;
		self->position.destination_position[1] = dest_y;
		
	}
	
	void ui_button_draw(ui_button_t self[notnull], var fps) {
		var old_layer  = self->frost->layer;
		var old_colour = self->frost->colour;
		
		flt old_alpha  = self->frost->alpha;
		flt old_base   = self->frost->base;
		
		frost_set_layer (self->frost, self->layer);
		frost_set_alpha (self->frost, self->position.animation.base);
		
		if (self->wallpaper) {
			frost_set_base  (self->frost, 0);
			frost_set_colour(self->frost, self->theme->layer_colour);
			
		} else {
			frost_set_base  (self->frost, (self->theme->window_colour & 0xFF) * (FLOAT_ONE >> 8));
			frost_set_colour(self->frost,  self->theme->super_window_colour);
			
		}
		
		if (self->state == lib(UI_BUTTON_STAGE_ANIMATION)) {
			self->state -= layer_update(&self->position, fps);
			
		}
		
		frost_cutout(self->frost, self->position.x, self->position.y, self->text.width + self->theme->general_margin * 2, self->text.height + self->theme->general_margin * 2);
		frost_draw  (self->frost);
		
		frost_set_layer (self->frost, old_layer);
		frost_set_alpha (self->frost, old_alpha);
		frost_set_base  (self->frost, old_base);
		frost_set_colour(self->frost, old_colour);
		
		frost_cutout(self->frost, 0, 0, _UI64_MAX_MARGIN * 2, _UI64_MAX_MARGIN * 2);
		
		text_set_alpha   (&self->text, FLOAT_TO_U64_MAX(self->position.animation.base));
		text_set_position(&self->text, self->position.x, self->position.y);
		text_draw        (&self->text, fps);
		
	}
	
	var ui_button_click(ui_button_t self[notnull], var x, var y) {
		return text_click(&self->text, x, y);
		
	}
	
	void dispose_ui_button(ui_button_t self[notnull]) {
		dispose_text(&self->text);
		
	}
	
#endif
