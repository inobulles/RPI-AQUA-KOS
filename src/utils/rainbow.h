
#ifndef __AQUA__UITILS_RAINBOW_H
	#define __AQUA__UITILS_RAINBOW_H
	
	typedef struct {
		int direction;
		
		float r;
		float g;
		float b;
		
	} rainbow_t;
	
	rainbow_t rainbow(void) {
		rainbow_t self = {
			.direction = 0,
			
			.r = 1.0f,
			.g = 0.0f,
			.b = 0.0f
			
		};
		
		return self;
		
	}
	
	void update_rainbow(rainbow_t* self, float delta) {
		if (self->direction == 0) {
			self->r -= delta;
			self->g += delta;
			
		} else if (self->direction == 1) {
			self->g -= delta;
			self->b += delta;
			
		} else if (self->direction == 2) {
			self->r += delta;
			self->b -= delta;
			
		}
		
		if (self->r < 0) {
			self->direction++;
			self->r = 0;
			
		} else if (self->g < 0) {
			self->direction++;
			self->g = 0;
		
		} else if (self->b < 0) {
			self->r = 1.0f;
			self->g = 0.0f;
			self->b = 0.0f;
			
			self->direction++;
			
		}
		
		if (self->direction > 2) {
			self->direction = 0;
			
		}
		
	}
	
#endif
