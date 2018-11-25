
#ifndef __AQUA__LIB_UI_SIDE_H
	#define __AQUA__LIB_UI_SIDE_H
	
	#include "ui.h"
	#include "../fast/pointer.h"
	
	typedef struct {
		layer_t position;
		var     stage;
		var     open;
		
		ui_t* ui;
		var   width;
		
		frost_t* frost;
		theme_t* theme;
		
	} ui_side_t;
	
	void new_ui_side(ui_side_t* self, ui_t* ui, var width) {
		self->stage  = 0;
		self->open   = 0;
		
		self->ui    = ui;
		self->width = width;
		
		self->frost =  self->ui->frost;
		self->theme = &self->ui->frost->theme;
		
		new_layer      (&self->position);
		layer_set_dummy(&self->position);
		layer_init     (&self->position);
		
	}
	
	var ui_side_draw(ui_side_t* self, var fps) {
		if (!self->open) {
			return 1;
			
		}
		
		if (self->stage == 4) {
			self->open = 0;
			return 1;
			
		}
		
		if (self->stage == 0) {
			self->stage++;
			layer_set_animation(&self->position, ANIMATION_TYPE_ENABLED | ANIMATION_TYPE_POINT_TO_POINT, self->theme->snap_tier);
			
			self->position.source_position[0] = -72057594037928956;
			self->position.source_position[1] = 0;
			
			self->position.destination_position[0] = self->width - 72057594037928956;
			self->position.destination_position[1] = 0;
			
		}
		
		var old_layer  = self->frost->layer;
		var old_colour = self->frost->colour;
		
		flt old_alpha  = self->frost->alpha;
		flt old_base   = self->frost->base;
		
		frost_set_layer (self->frost, 63);
		frost_set_alpha (self->frost, self->stage == 3 ? FLOAT_ONE - self->position.animation.base : self->position.animation.base);
		frost_set_base  (self->frost, (self->theme->window_colour /*0*/ & 0xFF) * (FLOAT_ONE >> 8));
		frost_set_colour(self->frost,  /*self->theme->layer_colour*/ self->theme->super_window_colour);
		
		if (self->stage == 1 || self->stage == 3) {
			self->stage += layer_update(&self->position, fps);
			
		}
		
		frost_cutout(self->frost, self->position.x - self->width, 0, self->width * 2, _UI64_MAX_MARGIN * 2);
		frost_draw  (self->frost);
		
		frost_set_layer (self->frost, old_layer);
		frost_set_alpha (self->frost, old_alpha);
		frost_set_base  (self->frost, old_base);
		frost_set_colour(self->frost, old_colour);
		
		frost_cutout    (self->frost, 0, 0, _UI64_MAX_MARGIN * 2, _UI64_MAX_MARGIN * 2);
		return 0;
		
	}
	
	void ui_side_open(ui_side_t* self) {
		self->stage = 0;
		self->open  = 1;
		
	}
	
	void ui_side_update(ui_side_t* self, var click, event_list_t* events) {
		if (self->open && click) {
			var x = POINTER_X(events->pointer_x);
			var y = POINTER_Y(events->pointer_y);
			
			var exit_side = 1;
			
			if (exit_side) {
				if (self->stage == 3) {
					self->stage++;
					
				} else {
					self->stage = 3;
					layer_set_animation(&self->position, ANIMATION_TYPE_ENABLED | ANIMATION_TYPE_INVERT | ANIMATION_TYPE_POINT_TO_POINT | ANIMATION_TYPE_ALPHA, FLOAT_HALF);
					
				}
				
			}
			
		}
		
	}
	
	void dispose_ui_side(ui_side_t* self) {
		dispose_layer(&self->position);
		
	}
	
#endif
