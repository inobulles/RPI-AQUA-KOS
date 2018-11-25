
#ifndef __AQUA__LIB_FAST_FLASH_H
	#define __AQUA__LIB_FAST_FLASH_H
	
	#include "../floats.h"
	
	typedef struct {
		var direction;
		flt alpha;
		uvar colour[3];
		
	} flash_t;
	
	void new_flash(flash_t* self) {
		self->direction = 1;
		self->alpha = FLOAT_ONE;
		
	}
	
	void flash_update(flash_t* self, var fps) {
		if (!fps) {
			return;
			
		}
		
		flt delta = FLOAT_ONE / fps / 3;
		
		if      (self->direction == 0) self->alpha -= delta;
		else if (self->direction == 1) self->alpha += delta;
		
		if (self->alpha < FLOAT_HALF) {
			self->direction = 1;
			self->alpha = FLOAT_HALF;
			
		}
		
		if (self->alpha > FLOAT_ONE) {
			self->direction = 0;
			self->alpha = FLOAT_ONE;
			
		}
		
		uvar colour = FLOAT_TO_U64_MAX(self->alpha);
		
		self->colour[0] = colour;
		self->colour[1] = colour;
		self->colour[2] = colour;
		
	}
	
#endif
