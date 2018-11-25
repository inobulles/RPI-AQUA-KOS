
#ifndef __AQUA__LIB_FAST_RAINBOW_H
	#define __AQUA__LIB_FAST_RAINBOW_H
	
	#include "../floats.h"
	
	typedef struct {
		var direction;
		flt colour[3];
		
	} rainbow_t;
	
	void new_rainbow(rainbow_t* self) {
		self->direction = 0;
		
		self->colour[0] = FLOAT_ONE;
		self->colour[1] = 0;
		self->colour[2] = 0;
		
	}
	
	static void rainbow_colour(rainbow_t* self, flt delta) {
		if (self->direction == 0) {
			self->colour[0] -= delta;
			self->colour[1] += delta;
			
		} else if (self->direction == 1) {
			self->colour[1] -= delta;
			self->colour[2] += delta;
			
		} else if (self->direction == 2) {
			self->colour[2] -= delta;
			self->colour[0] += delta;
			
		}
		
	}
	
	void rainbow_update(rainbow_t* self, var fps) {
		if (!fps) {
			return;
			
		}
		
		flt delta = FLOAT_ONE / fps;
		rainbow_colour(self, delta);
		
		if (self->colour[0] < 0) {
			self->direction++;
			self->colour[0] = 0;
			
		} else if (self->colour[1] < 0) {
			self->direction++;
			self->colour[1] = 0;
			
		} else if (self->colour[2] < 0) {
			self->direction++;
			
			self->colour[0] = FLOAT_ONE;
			self->colour[1] = 0;
			self->colour[2] = 0;
			
		}
		
		if (self->colour[0] > FLOAT_ONE) self->colour[0] = FLOAT_ONE;
		if (self->colour[1] > FLOAT_ONE) self->colour[1] = FLOAT_ONE;
		if (self->colour[2] > FLOAT_ONE) self->colour[2] = FLOAT_ONE;
		
		self->direction %= 3;
		
	}
	
#endif
