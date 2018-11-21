
#ifndef __AQUA__GL_CLEAR_H
	#define __AQUA__GL_CLEAR_H
	
	#include "root.h"
	
	void clear(...) {
		
	}
	
	void clear_alpha(unsigned char alpha_mask) {
		glColorMask(1, 1, 1, alpha_mask);
		
	}
	
#endif
