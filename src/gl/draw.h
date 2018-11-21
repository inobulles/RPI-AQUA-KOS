
#ifndef __AQUA__GL_DRAW_H
	#define __AQUA__GL_DRAW_H

	#include "root.h"
	
	void flip(state_t* state) {
		eglSwapBuffers(state->display, state->surface);

	}

#endif
