
#ifndef __AQUA__LIB_UI_KBRD_H
	#define __AQUA__LIB_UI_KBRD_H
	
	#include "ui.h"
	#include "../animation.h"
	
	#define KBRD_STAGE_CLOSED 0b00 // LSB defines if the stage is and animation or a static state
	#define KBRD_STAGE_OPENING 0b01
	#define KBRD_STAGE_OPEN 0b10
	#define KBRD_STAGE_CLOSING 0b11
	
	#define KBRD_HEIGHT(x) (map(x, FLOAT_ONE + FLOAT_HALF))
	
	#ifndef KBRD_LAYER
		#define KBRD_LAYER 100
	#endif
	
	#define KBRD_ROW_COUNT 4
	
	typedef struct {
		var stage;
		animation_t animation;
		
		ui_t* ui;
		flt temp;
	
		layer_t rows[KBRD_ROW_COUNT];
		
	} kbrd_t;
	
	void new_kbrd(kbrd_t* self, ui_t* ui) {
		self->stage = KBRD_STAGE_CLOSED;
		self->ui = ui;
		new_animation(&self->animation, 0, FLOAT_THIRD);
		self->temp = FLOAT_HALF;
		
		#define S "    "
		
		const char* row_text[KBRD_ROW_COUNT] = {
			"Q"S"W"S"E"S"R"S"T"S"Y"S"U"S"I"S"O"S"P",
			"A"S"S"S"D"S"F"S"G"S"H"S"J"S"K"S"L",
			"Caps"S"Z"S"X"S"C"S"V"S"B"S"N"S"M"S"Back",
			"?123"S","S"Space"S"."S"Enter",
		};
		
		var i;
		for (i = 0; i < KBRD_ROW_COUNT; i++) {
			new_layer(&self->rows[i]);
			layer_set_text(&self->rows[i], ui->main_font, 	row_text[i]);
			layer_init(&self->rows[i]);
			
		}
		
	}

	void dispose_kbrd(kbrd_t* self) {
		var i;
		for (i = 0; i < KBRD_ROW_COUNT; i++) {
			layer_dispose(&self->rows[i]);
			
		}
		
	}
	
	var kbrd_is_animation(kbrd_t* self) {
		return self->stage & 0b01;
		
	}
	
	var kbrd_is_direction_open(kbrd_t* self) {
		return self->stage & 0b10;
		
	}
	
	void kbrd_open(kbrd_t* self) {
		if (self->stage != KBRD_STAGE_OPEN && self->stage != KBRD_STAGE_OPENING) {
			self->stage = KBRD_STAGE_OPENING;
			reset_animation(&self->animation);
			
		}
		
	}
	
	void kbrd_close(kbrd_t* self) {
		if (self->stage != KBRD_STAGE_CLOSED && self->stage != KBRD_STAGE_CLOSING) {
			self->stage = KBRD_STAGE_CLOSING;
			reset_animation(&self->animation);
			
		}
		
	}
	
	void kbrd_switch(kbrd_t* self) {
		if (kbrd_is_direction_open(self)) kbrd_close(self);
		else kbrd_open(self);
		
	}
	
	var kbrd_draw(kbrd_t* self, var fps, event_list_t* events) { // returns the pressed key
		if (self->stage != KBRD_STAGE_CLOSED) {
			flt y = 0;
			
			if (kbrd_is_animation(self)) {
				if (animate(&self->animation, fps) >= FLOAT_ONE) {
					if (self->stage == KBRD_STAGE_OPENING) {
						self->stage = KBRD_STAGE_OPEN;
						y = FLOAT_ONE;
						
					} else {
						self->stage = KBRD_STAGE_CLOSED;
						
					}

				} else {
					y = self->stage == KBRD_STAGE_OPENING ? self->animation.base : FLOAT_ONE - self->animation.base;
					
				}
				
			} else {
				y = FLOAT_ONE;
				
			}
			
			var draw_y = KBRD_HEIGHT(y);

			ui_panel_alpha(self->ui, y);
			ui_draw_panel_full(self->ui, self->ui->theme.window_colour, KBRD_LAYER, 0, -_UI64_MAX_MARGIN + (draw_y / 2), _UI64_MAX_MARGIN * 2, draw_y);
			
			layer_set_xa(&self->rows[0], 0);
			layer_set_ya(&self->rows[0], 0);
			
			layer_draw(&self->rows[0]);
			
		}
		
		return '\0';
		
	}
	
#endif
