
#ifndef __AQUA__GL_EXIT_H
	#define __AQUA__GL_EXIT_H

	#include "root.h"

	static void opengl_exit(state_t* state) {
		glClear(GL_COLOR_BUFFER_BIT);
		eglSwapBuffers(state->display, state->surface);

		eglMakeCurrent(state->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
		eglDestroySurface(state->display, state->surface);
		eglDestroyContext(state->display, state->context);
		eglTerminate(state->display);

	}

#endif
