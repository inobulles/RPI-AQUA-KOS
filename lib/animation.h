
#ifndef __AQUA__UTILS_ANIMATION_H
	#define __AQUA__UTILS_ANIMATION_H
	
	#include "../root.h"
	#include "floats.h"
	
	#define ANIMATION_TYPE_ENABLED        0b1
	#define ANIMATION_TYPE_ALPHA          0b10
	#define ANIMATION_TYPE_COLOUR         0b100
	#define ANIMATION_TYPE_POINT_TO_POINT 0b1000
	#define ANIMATION_TYPE_SCALE          0b10000
	#define ANIMATION_TYPE_INVERT         0b100000
	#define ANIMATION_TYPE_BACKWARDS      0b1000000
	
	typedef struct {
		flt original_time;
		flt time; // in seconds
		
		flt elapsed;
		
		flt original_base;
		flt base;
		
		var backwards;
		flt offset;
		
	} animation_t;
	
	void new_animation(animation_t* self, flt base, flt time) {
		self->backwards = 0;
		self->elapsed   = 0;
		self->offset    = 0;
		
		self->original_time = time;
		self->time          = time;
		
		self->original_base = base;
		self->base          = base;
		
	}
	
	void reset_animation(animation_t* self) {
		self->backwards = 0;
		self->elapsed   = 0;
		
		self->time = self->original_time;
		self->base = self->original_base;
		
	}
	
	var reverse_animation(animation_t* self) {
		reset_animation(self);
		
	}
	
	var animate(animation_t* self, var fps) {
		if (!(self->time / ROOT_PRECISION)) {
			print("WARNING Animation time property does not seem to be a float. Maybe you passed an integer in its place? Multipling self->time by FLOAT_ONE for now ... If you see \"Floating point exception\" (x86), then self work-around has probably not worked, so FIX YOUR CODE\n");
			self->time *= FLOAT_ONE;
			
		}
		
		if (fps == 0) {
			return self->base;
			
		}
		
		if (self->backwards) self->elapsed -= FLOAT_ONE / fps;
		else                 self->elapsed += FLOAT_ONE / fps;
		
		#define ELAPSED (self->elapsed + self->offset)
		
		if (ELAPSED > 0) {
			var radius = self->time / ROOT_PRECISION;
			var x      = ELAPSED    / ROOT_PRECISION;
			
			var a =      radius  *      radius;
			var b = (x - radius) * (x - radius);
			
			self->base = SQRT_FLOAT(a - b) * ROOT_PRECISION / (self->time / ROOT_PRECISION);
			
			if (x > radius) {
				//~ self->base = 0;
				
			}
			
		} else {
			self->base = 0;
			return 0;
			
		}
		
		if (self->backwards) return FLOAT_ONE - self->base;
		else                 return             self->base;
		
	}
	
#endif
