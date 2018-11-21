
#ifndef __AQUA__UITILS_RAINBOW_H
	#define __AQUA__UITILS_RAINBOW_H
	
	typedef struct {
		int direction;
		
		float r;
		float g;
		float b;
		
	} rainbow_t;
	
	rainbow_t rainbow(void) {
		rainbow_t this = {
			.direction = 0,
			
			.r = 1.0f,
			.g = 0.0f,
			.b = 0.0f
			
		};
		
		return this;
		
	}
	
	void update_rainbow(rainbow_t* this, float delta) {
		if (this->direction == 0) {
			this->r -= delta;
			this->g += delta;
			
		} else if (this->direction == 1) {
			this->g -= delta;
			this->b += delta;
			
		} else if (this->direction == 2) {
			this->r += delta;
			this->b -= delta;
			
		}
		
		if (this->r < 0) {
			this->direction++;
			this->r = 0;
			
		} else if (this->g < 0) {
			this->direction++;
			this->g = 0;
		
		} else if (this->b < 0) {
			this->r = 1.0f;
			this->g = 0.0f;
			this->b = 0.0f;
			
			this->direction++;
			
		}
		
		if (this->direction > 2) {
			this->direction = 0;
			
		}
		
	}
	
#endif
