
#ifndef __AQUA__GL_DRAW_H
	#define __AQUA__GL_DRAW_H

	#include "root.h"

	void draw(state_t* state) {
		glClearColor(0.7, 0.7, 0.7, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	}

	void flip(state_t* state) {
		eglSwapBuffers(state->display, state->surface);

	}

#endif
