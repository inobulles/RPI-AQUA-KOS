
#ifndef __AQUA__UTILS_RATIO_H
	#define __AQUA__UTILS_RATIO_H
	
	#include "../gl/root.h"
	
	state_t* state;
	
	float ratio_x(float x) {
		return x / (float) state->screen_width;
		
	}
	
	float ratio_y(float y) {
		return y / (float) state->screen_height;
		
	}
	
#endif
