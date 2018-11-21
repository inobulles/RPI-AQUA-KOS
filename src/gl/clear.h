
#ifndef __AQUA__GL_CLEAR_H
	#define __AQUA__GL_CLEAR_H
	
	#include "root.h"
	
	void clear(colour_t colour) {
		glClearColor(colour.r, colour.g, colour.b, colour.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
	}
	
	void clear_alpha(unsigned char alpha_mask) {
		glColorMask(1, 1, 1, alpha_mask);
		
	}
	
#endif
